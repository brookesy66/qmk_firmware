#include QMK_KEYBOARD_H

// layers
#define _BL 0 // base layer (default)
#define _ML 1 // modify/movement layer
#define _UL 2 // utility layer (fn keys & RGB)
#define _GL 3 // gaming layer (act like a pleb keeb)
#define _PL 4 // mouse (pointer) layer
#define SPC_ML LT(_ML, KC_SPC) // tap for space, hold for modify/movement layer

// Tap Dance declarations
enum {
    TD_G,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for RGUI key, tap twice for toggling game mode
    [TD_G] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_RGUI, _GL),
};

// layer change code
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _GL:
            // lights off for gaming layer
            rgblight_disable();
            break;
        default:
            // on for all others
            rgblight_enable();
            break;
    }
    return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Template
//          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
//          _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
//          _______,          _______, _______,                            _______,                            _______, _______, _______,

    [_BL] = LAYOUT_60_ansi(
        QK_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
        CAPSWRD,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSPO,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSPC,
        KC_LCTL,        KC_LGUI, KC_LALT,                            SPC_ML,                             KC_RALT, TD(TD_G), MO(_UL), KC_RCTL
    ),
    [_ML] = LAYOUT_60_ansi(
        KC_GRV,         KC_MUTE, KC_VOLD, KC_VOLU, KC_END,  KC_F5,   _______, _______, _______, _______, KC_HOME, _______,  _______, KC_DEL,
        _______,        _______, _______, _______, _______, _______, _______, KC_PGUP, KC_INS,  _______, _______, _______,  _______, _______,
        _______,        _______, _______, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,           _______,
        MO(_PL),                 KC_Z,    KC_DEL,  KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           _______,
        KC_LCTL,        _______, _______,                            _______,                            _______, _______,  _______, _______
    ),
    [_UL] = LAYOUT_60_ansi(
        KC_GRV,         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  _______,
        _______,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______,  _______, _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______,
        _______,                 _______, _______, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, _______, _______, _______, _______,           _______,
        _______,        _______, _______,                            _______,                            _______, _______,  _______, _______
    ),
    [_GL] = LAYOUT_60_ansi(
        QK_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
        KC_CAPS,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSPO,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSPC,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, TD(TD_G), MO(_UL), KC_RCTL
    ),
    [_PL] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,          _______,
        _______,          KC_BTN1, KC_BTN2, KC_BTN3, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______,                            _______,                            _______, _______, _______,
    ),
};
