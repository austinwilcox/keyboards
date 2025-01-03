#include QMK_KEYBOARD_H

// Define layer names
enum layer_names {
    _BASE,
    _EDIT,
    _MOUSE,
    _MEDIA,
    _NUM,
    _SYM,
    _FUNC
};
// Tap Dance declarations
enum {
    TD_SLASH_BACKSLASH = 0,
};

// Tap Dance functions
void dance_slash_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Single tap: output /
        register_code(KC_SLSH);
    } else if (state->count == 2) {
        if (get_mods() & MOD_MASK_SHIFT) {
            // Double-tap with Shift: output |
            unregister_code(KC_LSFT);
            tap_code16(KC_PIPE);
            register_code(KC_LSFT);
        } else {
            // Double-tap: output \
            tap_code16(KC_BSLS);
        }
    }
}

void dance_slash_reset(qk_tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_SLSH);
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SLASH_BACKSLASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_slash_finished, dance_slash_reset),
};

// Define the keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G, KC_M, RSFT_T(KC_N), RCTL(KC_E), RALT_T(KC_I), RGUI_T(KC_O),
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  TD(TD_SLASH_BACKSLASH),
        LT(1, KC_TAB), LT(2, KC_ESC), LT(3, KC_LGUI), LT(4, KC_ENT), LT(5, KC_BSPC), LT(6, KC_DEL)
    ),
    [_EDIT] = LAYOUT_split_3x5_3(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
        KC_NO,   KC_NO,   KC_NO,   KC_ENT,  KC_BSPC, KC_NO
    ),
    [_MOUSE] = LAYOUT_split_3x5_3(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,   KC_NO,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
        KC_NO,   KC_NO,   KC_NO,   KC_BTN1, KC_BTN2, KC_BTN3
    ),
    [_MEDIA] = LAYOUT_split_3x5_3(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,   KC_NO,   KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_MPLY, KC_MSTP, KC_MUTE
    ),
    [_NUM] = LAYOUT_split_3x5_3(
        KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_QUOT, KC_4,    KC_5,    KC_6,    KC_EQL,  KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LPRN, KC_RPRN, KC_MINS, KC_0,    KC_NO,   KC_NO
    ),
    [_SYM] = LAYOUT_split_3x5_3(
        KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_DQUO, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS, KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_MINS, KC_NO,   KC_NO,   KC_NO
    ),
    [_FUNC] = LAYOUT_split_3x5_3(
        KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL, KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_TAB,  KC_SPC,  KC_NO,   KC_NO,   KC_NO
    )
};
