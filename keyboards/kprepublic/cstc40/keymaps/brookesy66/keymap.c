/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#define SPC_ML LT(_MOVEMENT, KC_SPC) // tap for space, hold for modify/movement layer


enum planck_layers {
  _BASE,
  _MOVEMENT,
  _POINTER,
  _LOWER,
  _RAISE,
  _ADJUST,
  _RGB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   * ,-----------------------------------------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |SftEnt|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |Adjust| GUI  | Alt  |Lower |   Space/Mv  |Raise | Left | Down | RGB  | RCtl |
   * `-----------------------------------------------------------------------------------'
   */
  [_BASE] = LAYOUT_planck_mit(
    KC_ESC,      KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,    KC_Y,    KC_U,         KC_I,    KC_O,    KC_P,     KC_BSPC,
    KC_TAB,      KC_A,    KC_S,    KC_D,    KC_F,       KC_G,    KC_H,    KC_J,         KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
    KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,    KC_N,    KC_M,         KC_COMM, KC_DOT,  KC_SLSH,  RSFT_T(KC_ENT),
    KC_LCTL, MO(_ADJUST), KC_LGUI, KC_LALT, MO(_LOWER),     SPC_ML,       MO(_RAISE),   KC_LEFT, KC_DOWN, MO(_RGB), KC_RCTL
  ),

  /* Movement (hold Space)
   * ,-----------------------------------------------------------------------------------.
   * | Esc  | Mute | Vol- | Vol+ | End  |  F5  |   Y  | PgUp |   I  |   O  | Home | Del  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   A  |   S  | PgDn |   F  |   G  | Left | Down |  Up  |Right |   ;  |  '   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |  S(  |   Z  | Del  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  S)  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  Ptr |Adjust| GUI  | Alt  |Lower |    Space    |Raise | Left | Prev | Next | Play |
   * `-----------------------------------------------------------------------------------'
   */
  [_MOVEMENT] = LAYOUT_planck_mit(
    _______,      KC_MUTE, KC_VOLD, KC_VOLU, KC_END,   KC_F5,   _______, KC_PGUP, _______, _______,  KC_HOME, KC_DEL,
    _______,      _______, _______, KC_PGDN, _______,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
    SC_LSPO,      _______, KC_DEL,  _______, _______,  _______, _______, _______, _______, _______,  _______, SC_RSPC,
    MO(_POINTER), _______, _______, _______, _______,     _______,       _______, _______, KC_MPRV,  KC_MNXT, KC_MPLY
  ),

  /* Pointer (Movement + Ctrl)
   * ,-----------------------------------------------------------------------------------.
   * | Esc  | Mute | Vol- | Vol+ | End  |  F5  |   Y  | PgUp |   I  |   O  | Home | Del  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   A  |   S  | PgDn |   F  |   G  | Ms L | Ms D | Ms U | Ms R |   ;  |  '   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |  S(  | Btn1 | Btn2 | Btn3 |   V  |   B  |   N  | WhlD | WhlU |   .  |   /  |  S)  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  Ptr |Adjust| GUI  | Alt  |Lower |    Space    |Raise | Left | Prev | Next | Play |
   * `-----------------------------------------------------------------------------------'
   */
  [_POINTER] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______,   _______,   _______, _______, _______, _______,  _______, _______,

    _______, _______, _______, _______, _______,  _______,   MS_LEFT, MS_DOWN, MS_UP,  MS_RGHT, _______, _______,
    _______, MS_BTN1, MS_BTN2, MS_BTN3, _______,  _______,   _______, MS_WHLD, MS_WHLU, _______,  _______, _______,
    _______, _______, _______, _______, _______,       _______,       _______, _______, _______,  _______, _______
  ),

  /* Lower
   * ,-----------------------------------------------------------------------------------.
   * |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|  F7  |  F8  |  F9  | F10  | F11  | F12  |   M  |   ,  |Home  | End  |SftEnt|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |Adjust| GUI  | Alt  |Lower |   Space/Mv  |Raise | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_planck_mit(
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,    _______,    KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______,     _______,      _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
  ),

  /* Raise
   * ,-----------------------------------------------------------------------------------.
   * |   ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|  F7  |  F8  |  F9  | F10  | F11  | F12  |   M  |   ,  |   .  |   /  |SftEnt|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |Adjust| GUI  | Alt  |Lower |   Space/Mv  |Raise | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_planck_mit(
    KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
  ),

  /* Adjust
   * ,-----------------------------------------------------------------------------------.
   * |Debug |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Boot |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |SftEnt|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |Adjust| GUI  | Alt  |Lower |   Space/Mv  |Raise | Left | Down | RGB  | RCtl |
   * `-----------------------------------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT_planck_mit(
    DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
  ),


  /* RGB
   * ,-----------------------------------------------------------------------------------.
   * | Togg | Prev | Next | Hue+ | Sat+ | Val+ | Spd+ |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   A  |   S  | Hue- | Sat- | Val- | Spd- |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |SftEnt|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |Adjust| GUI  | Alt  |Lower |   Space/Mv  |Raise | Left | Down | RGB  | RCtl |
   * `-----------------------------------------------------------------------------------'
   */
  [_RGB] = LAYOUT_planck_mit(
   /* ESC       Q        W        E         R       T        Y */
    RM_TOGG, RM_PREV, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, _______, _______, _______, _______, _______,
    _______, _______, _______, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
  ),

};
