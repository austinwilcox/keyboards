#include QMK_KEYBOARD_H
#include "joystick.h"

/*
 * Vial keymap. Dual output, same idea as the default keymap: every press emits
 * a keyboard keycode AND a joystick button, so the stick works as a gamepad on
 * hosts that accept HID gamepads (Linux, Steam Deck via sdl2) and as a keyboard
 * on hosts that don't (iOS).
 *
 * Difference from the default keymap: the joystick button is chosen by matrix
 * position instead of by keycode. Vial rewrites the keycodes in EEPROM, so a
 * keycode lookup would silently drop the gamepad output as soon as a key is
 * remapped. Keyed off the matrix, the gamepad button stays welded to the
 * physical button and existing RetroArch bindings survive any remap.
 *
 *   up = btn 0   down = btn 1   left = btn 2   right = btn 3
 *   top face row    = btn 4..7
 *   bottom face row = btn 8..11
 */

static const int8_t js_map[MATRIX_ROWS][MATRIX_COLS] = {
    // col: 0   1   2   3   4   5   6
    /* row 0 */ { -1,  0, -1,  4,  5,  6,  7 },
    /* row 1 */ {  2,  1,  3,  8,  9, 10, 11 },
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Combos and other virtual events report out-of-range positions.
    if (record->event.key.row < MATRIX_ROWS && record->event.key.col < MATRIX_COLS) {
        int8_t js = js_map[record->event.key.row][record->event.key.col];
        if (js >= 0) {
            if (record->event.pressed) {
                register_joystick_button(js);
            } else {
                unregister_joystick_button(js);
            }
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 KC_W,                    KC_U, KC_I, KC_O, KC_P,
        KC_A,    KC_S,    KC_D,           KC_H, KC_J, KC_K, KC_L
    ),
    // Spare layers, transparent until a layer key is assigned in Vial.
    [1] = LAYOUT(
                 _______,                 _______, _______, _______, _______,
        _______, _______, _______,        _______, _______, _______, _______
    ),
    [2] = LAYOUT(
                 _______,                 _______, _______, _______, _______,
        _______, _______, _______,        _______, _______, _______, _______
    ),
    [3] = LAYOUT(
                 _______,                 _______, _______, _______, _______,
        _______, _______, _______,        _______, _______, _______, _______
    ),
};
