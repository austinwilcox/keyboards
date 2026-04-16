// Copyright 2023 Joe Scotto (@joe-scotto)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x5_5(
               KC_Q, KC_W, KC_E,  KC_R, KC_T,
               KC_A, KC_S, KC_D,  KC_F, KC_G,
               KC_Z, KC_X, KC_C,  KC_V, KC_B,
        KC_NO, KC_NO,      KC_NO,       KC_LCTL, KC_SPC
    )
};
