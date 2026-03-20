# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

QMK (Quantum Mechanical Keyboard) Firmware is a keyboard firmware framework based on the tmk_keyboard firmware, primarily targeting AVR (LUFA) and ARM (ChibiOS) controllers. The codebase is written in C with some C++ components.

Official documentation: https://docs.qmk.fm

## Building and Compiling

### Prerequisites
- Python 3.9+ with QMK CLI installed (`pip install qmk`)
- Run `qmk setup` to configure the build environment
- Run `qmk doctor` to verify all dependencies are installed

### Basic Build Commands

```bash
# Compile a specific keyboard and keymap
qmk compile -kb <keyboard> -km <keymap>

# Example for DZ60RGB ANSI keyboard with custom keymap
qmk compile -kb dztech/dz60rgb_ansi/v2_1 -km brookesy66

# Flash firmware to keyboard (bootloader must be active)
qmk flash -kb <keyboard> -km <keymap>

# Clean build artifacts
qmk clean

# Clean all generated binaries
make distclean

# Parallel compilation (faster builds)
qmk compile -j 0 -kb <keyboard> -km <keymap>
```

### Alternative Make-based Build

```bash
# Format: make <keyboard>:<keymap>
make planck/rev6:default

# Flash using make
make planck/rev6:default:flash

# Build all keymaps for a keyboard
make planck/rev6:all
```

### Generate Compilation Database

For IDE/LSP support with proper include paths:

```bash
qmk compile --compiledb -kb <keyboard> -km <keymap>
```

## Repository Structure

### Core Directories

- **`keyboards/`**: Keyboard-specific code organized by manufacturer/model
  - Each keyboard has an `info.json` defining matrix, layouts, and hardware config
  - `keymaps/` subdirectories contain user-specific layouts
  - Hardware-specific C files define initialization and custom features

- **`quantum/`**: QMK core framework
  - `keyboard.c`: Main keyboard task loop and matrix scanning coordination
  - `action*.c`: Key action processing and layer management
  - `process_keycode/`: Modular keycode processors (tap dance, combos, auto shift, etc.)
  - Feature modules for RGB, audio, OLED, encoders, etc.

- **`tmk_core/`**: Low-level keyboard matrix and USB protocol handling (inherited from TMK)

- **`platforms/`**: Platform-specific implementations
  - `avr/`: AVR microcontroller support (LUFA USB stack)
  - `chibios/`: ARM microcontroller support (ChibiOS RTOS)
  - `test/`: Platform abstraction for unit testing

- **`drivers/`**: Hardware driver implementations (LEDs, displays, sensors, etc.)

- **`builddefs/`**: Build system makefiles and feature configuration

- **`layouts/`**: Community layouts that work across multiple keyboards with the same physical layout

- **`tests/`**: Unit tests for QMK features
  - Run with: `make test:<test_name>`
  - List tests: `make list-tests`

- **`docs/`**: Comprehensive documentation (markdown, powered by VitePress)

- **`data/`**: JSON schemas and configuration data

### Important Files

- **`Makefile`**: Top-level build orchestrator (parses `keyboard:keymap:target` format)
- **`rules.mk`**: Global build rules and feature defaults
- **`info.json`** (per keyboard): Hardware configuration, matrix definitions, USB IDs
- **`config.h`** (per keyboard/keymap): Compile-time configuration overrides
- **`keymap.c`**: User keymap definitions

## Architecture Overview

### Firmware Boot and Main Loop

1. **Startup** (`quantum/main.c`):
   - `main()` initializes hardware and USB
   - Calls platform-specific `platform_setup()` and `protocol_setup()`
   - Enters infinite main loop

2. **Main Loop** (`quantum/keyboard.c:keyboard_task()`):
   - Matrix scanning runs continuously (10+ times per second)
   - Detects key state changes (press/release)
   - Dispatches to action processing
   - Handles USB communication, LEDs, and peripherals

### Matrix Scanning to Keycode Pipeline

1. **Matrix Scan**: Hardware-specific code reads switch matrix state into 2D array
2. **LAYOUT Macro**: Maps physical switch positions to logical key positions (handles gaps in matrix)
3. **Keymap Array**: Maps logical positions to keycodes (supports layers)
4. **State Change Detection**: Compares current scan to previous to detect press/release events
5. **Action Processing**: `process_record_quantum()` dispatches through feature-specific handlers

### Process Record Chain

When a key state changes, `process_record_quantum()` calls handlers in sequence:
- `pre_process_record_user/kb()`: Early interception point
- Feature processors: combos, tap dance, macros, RGB controls, etc.
- `process_record_user/kb()`: Main custom keycode handler (user overrides here)
- Default action execution if not handled

**Key Extension Points**:
- `process_record_user()`: Handle custom keycodes in keymap
- `process_record_kb()`: Handle keyboard-specific features
- Layer management via `layer_on()`, `layer_off()`, `layer_move()`

## Creating and Modifying Keyboards

### Create New Keymap

```bash
# Using QMK CLI (recommended)
qmk new-keymap -kb <keyboard>

# Manually: copy an existing keymap
cp -r keyboards/<keyboard>/keymaps/default keyboards/<keyboard>/keymaps/<your_name>
```

### Keymap Structure

Keymaps define layers using the `LAYOUT()` macro (generated from `info.json`):

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,   /* ... */
        KC_TAB,  KC_Q,    KC_W,    KC_E,   /* ... */
        /* ... */
    ),
    [1] = LAYOUT(
        /* Layer 1 keys */
    )
};
```

### Common Feature Flags (`rules.mk`)

Enable features by adding to keyboard or keymap `rules.mk`:

```makefile
BOOTMAGIC_ENABLE = yes      # Enable bootmagic lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Media/system control keys
CONSOLE_ENABLE = yes        # Debug console (uses HID)
COMMAND_ENABLE = yes        # Debugging commands
NKRO_ENABLE = yes           # N-key rollover
BACKLIGHT_ENABLE = yes      # Keyboard backlight
RGBLIGHT_ENABLE = yes       # RGB underglow
RGB_MATRIX_ENABLE = yes     # RGB matrix (per-key addressable)
AUDIO_ENABLE = yes          # Audio output
TAP_DANCE_ENABLE = yes      # Tap dance keys
COMBO_ENABLE = yes          # Key combinations
AUTO_SHIFT_ENABLE = yes     # Auto shift (hold for shifted key)
```

## Testing and Debugging

### Enable Debug Output

Add to keymap `rules.mk`:
```makefile
CONSOLE_ENABLE = yes
```

Add to keymap code:
```c
void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
}
```

View debug output:
```bash
qmk console
```

### Useful Debug Patterns

Print matrix events:
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    uprintf("kc: 0x%04X, col: %u, row: %u, pressed: %u\n",
            keycode, record->event.key.col, record->event.key.row,
            record->event.pressed);
    #endif
    return true;
}
```

Measure scan rate:
```c
// In config.h
#define DEBUG_MATRIX_SCAN_RATE
```

### Running Tests

```bash
# Run all tests
make test:all

# Run specific test
make test:<test_name>

# List available tests
make list-tests
```

## Special Notes for This Repository

### Custom KBDfans DZ60RGB Flashing Workaround

The DZ60RGB v2/v2.1 uses a bootloader that requires special handling on Linux:

1. Compile firmware: `qmk compile -kb dztech/dz60rgb_ansi/v2_1 -km brookesy66`
2. Enter bootloader: Hold Escape while plugging in keyboard
3. Flash using dd: `dd if=<firmware>.bin of=/run/media/<user>/KBDFANS/FLASH.BIN bs=512 conv=notrunc oflag=direct,sync`
4. If bricked: Remove keycaps and press reset switch on PCB back while plugging in

### Git Submodules

QMK uses submodules for libraries (ChibiOS, LUFA, pico-sdk, etc.):

```bash
# Initialize/update all submodules
qmk git-submodule

# Or manually
git submodule update --init --recursive
```

## QMK CLI Utility Commands

```bash
# List all keyboards
qmk list-keyboards

# List keymaps for a keyboard
qmk list-keymaps -kb <keyboard>

# Get keyboard info
qmk info -kb <keyboard>

# Format C code
qmk format-c -a

# Lint code
qmk lint -kb <keyboard> -km <keymap>

# Configure defaults (saves typing)
qmk config user.keyboard=<keyboard>
qmk config user.keymap=<keymap>
```

## Development Workflow

1. Create or modify keymap in `keyboards/<keyboard>/keymaps/<name>/`
2. Edit `keymap.c` to define layers and custom keycodes
3. Enable features in `rules.mk` as needed
4. Configure settings in `config.h` if needed
5. Compile to verify: `qmk compile -kb <keyboard> -km <keymap>`
6. Flash to keyboard: `qmk flash -kb <keyboard> -km <keymap>` (put keyboard in bootloader mode first)
7. Test and debug using `qmk console` if issues arise

## Code Conventions

- Follow [QMK C Coding Conventions](https://docs.qmk.fm/coding_conventions_c)
- Use 4 spaces for indentation (configured in `.editorconfig`)
- Format code with `qmk format-c` before committing
- Keyboard names use lowercase with underscores: `my_keyboard`
- Keymap names use lowercase: `default`, `via`, `myusername`
- Macro names use UPPER_CASE: `LAYOUT()`, `KC_A`
- Keep changes focused and test compilation before submitting PRs

## Common Gotchas

- **User keymaps no longer accepted**: QMK no longer accepts PRs for user-specific keymaps to the main repo
- **Submodules**: Always sync submodules after pulling: `qmk git-submodule`
- **Layer count**: Maximum 32 layers (0-31)
- **Matrix gaps**: Use `KC_NO` in LAYOUT macro for non-existent switch positions
- **Bootloader mode**: Different keyboards enter bootloader differently (hold key while plugging in, press reset button, or use `QK_BOOT` keycode)
- **Compile vs Flash**: `compile` only builds firmware; `flash` builds and attempts to program the keyboard
