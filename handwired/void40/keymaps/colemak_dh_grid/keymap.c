// Copyright 2022 Victor Lucachi (@victorlucachi)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _COLEMAK,
  _RAISE,
  _LOWER,
  _ADJUST
};

enum {
  TD_SLSH_BSLS,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap Once for slash, tap and hold for back slash
  [TD_SLSH_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak
 * qwfpbjluy;
 * arstgmneio
 * zxcdvkh,./
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   f  |   p  |   b  |   j  |   l  |   u  |   y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   r  |   s  |   t  |   g  |   m  |   n  |   e  |   i  |   o  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   d  |   v  |   k  |   h  |   ,  |   .  |   /  |RShift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LCtrl|LOWER | LGUI | {    | }    | Space| Enter| Left | Down |  Up  |Right | 9 (  |
 * `-----------------------------------------------------------------------------------,
 */
[_COLEMAK] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,       KC_B,     KC_J,     KC_L,       KC_U,    KC_Y,    KC_SCLN,    KC_MINS,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,       KC_G,     KC_M,     KC_N,       KC_E,    KC_I,    KC_O, KC_EQL,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,       KC_V,     KC_K,     KC_H,       KC_COMM, KC_DOT,  TD(TD_SLSH_BSLS), KC_QUOT,
    KC_LCTL, TO(_LOWER),   KC_LGUI, KC_LBRC, KC_RBRC, KC_SPC,   KC_ENT, KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),
   

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | esc  |  1   |  2   |  3   |  4   |  5   |  6   |   7  |   8  |   9  |   0  |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Alt   |COLE  |      |      |      | Play | Play |      | Prev | Vol- | Vol+ | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_TRNS,
    KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9, KC_0, KC_ASTR,
    KC_LSFT, KC_F10,   KC_F11,   KC_F12,   KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_COMM, KC_DOT, TD(TD_SLSH_BSLS),  KC_QUOT,
    KC_TRNS, TO(_COLEMAK), KC_LGUI, KC_LBRC, KC_RBRC, KC_SPC, KC_ENT, KC_BSPC,    KC_LEFT,    KC_DOWN, KC_UP, KC_RGHT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Play | Play |      | Prev | Vol- | Vol+ | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, KC_ENT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MPLY, KC_TRNS, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),

/* Adjust
* ,-----------------------------------------------------------------------------------.
 * |RESET |      |RGBTOG|RGBMOD| HUE+ | HUE- | SAT+ | SAT- | BRI+ | BRI- |      | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |EEPROM|      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
    RESET,    KC_NO,    RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  KC_NO, KC_DEL,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, KC_NO,
    EEP_RST,  KC_NO,    KC_NO,    KC_NO,    KC_TRNS,  KC_NO,    KC_NO,    KC_TRNS,  KC_NO,    KC_NO,    KC_NO, KC_NO
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

/* Rotary Encoder Settings */
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_MNXT);
    } else {
        tap_code(KC_MPRV);
    }
    return false;
}
