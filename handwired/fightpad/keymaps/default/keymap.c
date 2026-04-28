#include QMK_KEYBOARD_H
#include "joystick.h"

/*
 * Dual output: each key emits both a keyboard keycode AND a joystick button,
 * so the stick works as a gamepad on hosts that accept HID gamepads (Linux,
 * Steam Deck via sdl2) and as a keyboard on hosts that don't (iOS).
 *
 * Keyboard side (iOS RetroArch, etc): W A S D  U I O P  H J K L
 * Joystick side (Deck RetroArch via sdl2):
 *   W = btn 0 (up)    S = btn 1 (down)   A = btn 2 (left)   D = btn 3 (right)
 *   U/I/O/P = btn 4..7  (top face row)
 *   H/J/K/L = btn 8..11 (bottom face row)
 */

static int8_t keycode_to_js(uint16_t kc) {
    switch (kc) {
        case KC_W: return 0;
        case KC_S: return 1;
        case KC_A: return 2;
        case KC_D: return 3;
        case KC_U: return 4;
        case KC_I: return 5;
        case KC_O: return 6;
        case KC_P: return 7;
        case KC_H: return 8;
        case KC_J: return 9;
        case KC_K: return 10;
        case KC_L: return 11;
    }
    return -1;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int8_t js = keycode_to_js(keycode);
    if (js >= 0) {
        if (record->event.pressed) {
            register_joystick_button(js);
        } else {
            unregister_joystick_button(js);
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 KC_W,                    KC_U, KC_I, KC_O, KC_P,
        KC_A,    KC_S,    KC_D,           KC_H, KC_J, KC_K, KC_L
    ),
};
