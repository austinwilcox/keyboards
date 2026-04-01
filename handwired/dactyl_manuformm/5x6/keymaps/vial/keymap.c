#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_5x6(
        KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                           KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_MINS,
        KC_ESC,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                           KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_EQL,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                           KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
                           KC_LBRC, KC_RBRC,                                                            KC_DOWN, KC_UP,
                                             KC_LGUI, KC_SPC,                         KC_ENT,  KC_ESC,
                                             KC_LALT, KC_LCTL,                        KC_BSPC, KC_DEL,
                                             KC_LEFT, KC_DOWN,                        KC_RIGHT,KC_LEFT
    ),

    [1] = LAYOUT_5x6(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS,                                                             KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS
    ),

};
