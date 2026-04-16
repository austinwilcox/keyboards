#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_3x3(
        KC_1, KC_2,    MO(_FN1),
        KC_4, KC_5,    KC_6,
        KC_7, KC_8,    KC_9
    ),
    [_FN1] = LAYOUT_ortho_3x3(
        _______, _______, MO(_FN2),
        KC_VOLD, KC_MUTE, KC_VOLU,
        KC_MPRV, KC_MPLY, KC_MNXT
    ),
    [_FN2] = LAYOUT_ortho_3x3(
        _______, _______, MO(_FN3),
        KC_F4,   KC_F5,   KC_F6,
        KC_F1,   KC_F2,   KC_F3
    ),
    [_FN3] = LAYOUT_ortho_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    )
};
