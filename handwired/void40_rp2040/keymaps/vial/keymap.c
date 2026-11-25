// Copyright 2022 Victor Lucachi (@victorlucachi)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Ported from the void40 `colemak_dh_grid` keymap onto the RP2040 MIT layout
// (47 keys: the bottom-row center is a single 2u spacebar at matrix [3,5];
// matrix cell [3,6] has no switch). The original col-6 key on each layer is
// therefore dropped — on the base layer that was Enter, which Vial can rebind.
//
// Tap dance: in a Vial build tap dances are DYNAMIC (vial-qmk owns the
// tap_dance_actions[] array, so a static one can't be defined here). The
// slash/backslash key is wired to TD(0); configure dynamic tap-dance #0 in the
// Vial app (tap = /, the original behaviour was double-tap = \).
//
// Encoder: rotary signal pins on GP26/GP27 (see keyboard.json). The encoder
// PUSH is wired directly from GP28 to GND (not in the matrix). It is polled
// below and injected as a press of the unused matrix cell [3,6] (the slot
// beside the 2u space, which has no physical switch), so the push keycode is
// the last entry of each layer and is remappable in Vial. The knob sits where
// the top-left switch would be, so matrix cell [0,0] has no switch and is not
// in the layout. To enter the bootloader without opening the case, hold Esc
// (matrix [1,0], set via bootmagic in keyboard.json) while plugging in.
// Rotation maps
// per-layer via encoder_map below and is remappable in Vial
// (ENCODER_MAP_ENABLE).

#include QMK_KEYBOARD_H

enum layer_names {
  _COLEMAK,
  _RAISE,
  _LOWER,
  _ADJUST,
  _L4,
  _L5,
  _L6,
  _L7
};

// Vial custom keycodes start at QK_KB_0 (listed under "User" in the Vial app,
// names come from customKeycodes in vial.json).
enum custom_keycodes {
  MEDIA_TAP = QK_KB_0 // 1 tap: play/pause, 2 taps: next, 3 taps: previous
};

// Defaults mirror void40Layout.vil (Vial export) so a fresh flash comes up with
// the current layout. Tap dance #0 (/ , double-tap \) is dynamic and must be
// restored by loading the .vil in Vial.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak-DH, home row mods */
[_COLEMAK] = LAYOUT_ortho_4x12_mit(
             KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,    KC_J,    KC_L,         KC_U,         KC_Y,         KC_SCLN,      KC_MINS,
    KC_ESC,  LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,    KC_M,    RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O), KC_EQL,
    KC_LSFT, KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,    KC_K,    KC_H,         KC_COMM,      KC_DOT,       TD(0),        KC_QUOT,
    QK_BOOT, KC_NO,        KC_LBRC,      KC_RBRC,      KC_TAB,       KC_SPC,           LT(2, KC_ENT), LT(1, KC_BSPC), LT(1, KC_TAB), KC_NO,   TO(_ADJUST),
    MEDIA_TAP
),

/* Layer 1: symbols / arrows / mouse */
[_RAISE] = LAYOUT_ortho_4x12_mit(
             KC_GRV,  S(KC_7), S(KC_8), S(KC_9), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_ESC,  KC_NO,   S(KC_4), S(KC_5), S(KC_6), KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
    KC_LSFT, KC_NO,   S(KC_1), S(KC_2), S(KC_3), KC_NO,   KC_NO,   MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_NO,
    KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_NO,   S(KC_0),          MS_BTN1, MS_BTN2, KC_NO,   KC_NO,   KC_NO,
    KC_NO
),

/* Layer 2: numpad */
[_LOWER] = LAYOUT_ortho_4x12_mit(
             KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_ESC,  KC_NO,   KC_4,    KC_5,    KC_6,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_LSFT, KC_NO,   KC_1,    KC_2,    KC_3,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_DOT,  TD(0),   KC_NO,
    KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_NO,   KC_0,             KC_ENT,  KC_BSPC, KC_NO,   KC_NO,   KC_NO,
    KC_MUTE
),

/* Layer 3: QWERTY (TO(3) on base to enter, TO(0) to leave; or hold LT1 + LT2) */
[_ADJUST] = LAYOUT_ortho_4x12_mit(
             KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_NO,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_NO,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SPC,           KC_ENT,  KC_BSPC, KC_NO,   KC_NO,   TO(_COLEMAK),
    KC_TAB
),

/* Layers 4-7: empty (transparent), assign in Vial */
[_L4] = LAYOUT_ortho_4x12_mit(
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______
),
[_L5] = LAYOUT_ortho_4x12_mit(
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______
),
[_L6] = LAYOUT_ortho_4x12_mit(
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______
),
[_L7] = LAYOUT_ortho_4x12_mit(
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_COLEMAK] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_RAISE]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LOWER]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_ADJUST]  = { ENCODER_CCW_CW(_______, _______) },
    [_L4]      = { ENCODER_CCW_CW(_______, _______) },
    [_L5]      = { ENCODER_CCW_CW(_______, _______) },
    [_L6]      = { ENCODER_CCW_CW(_______, _______) },
    [_L7]      = { ENCODER_CCW_CW(_______, _______) },
};
#endif

// Multi-tap media key. Static tap dances can't be used here (vial-qmk owns
// tap_dance_actions[]), so taps are counted by hand: each press restarts the
// window, and the action fires once MEDIA_TAP_TERM passes with no new press
// (or immediately on the third tap).
#define MEDIA_TAP_TERM 500

static uint8_t  media_taps  = 0;
static uint16_t media_timer = 0;

static void media_tap_fire(void) {
    switch (media_taps) {
        case 1:  tap_code(KC_MPLY); break;
        case 2:  tap_code(KC_MNXT); break;
        default: tap_code(KC_MPRV); break;
    }
    media_taps = 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == MEDIA_TAP) {
        if (record->event.pressed) {
            media_timer = timer_read();
            if (++media_taps >= 3) {
                media_tap_fire();
            }
        }
        return false;
    }
    return true;
}

// Tri-layer: holding Raise + Lower turns on Adjust. Unlike
// update_tri_layer_state(), only switch Adjust back off if the tri-layer
// turned it on, so MO/TO/TG(_ADJUST) keys still work on their own.
static bool tri_adjust = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    const layer_state_t adjust = (layer_state_t)1 << _ADJUST;
    if (layer_state_cmp(state, _LOWER) && layer_state_cmp(state, _RAISE)) {
        if (!(state & adjust)) {
            state |= adjust;
            tri_adjust = true;
        }
    } else if (tri_adjust) {
        state &= ~adjust;
        tri_adjust = false;
    }
    return state;
}

// Direct-wired encoder push switch (GP28 -> GND, internal pull-up).
#define ENCODER_SW_PIN GP28
#define ENCODER_SW_ROW 3
#define ENCODER_SW_COL 6
#define ENCODER_SW_DEBOUNCE_MS 5

void keyboard_post_init_user(void) {
    gpio_set_pin_input_high(ENCODER_SW_PIN);
}

void housekeeping_task_user(void) {
    if (media_taps && timer_elapsed(media_timer) >= MEDIA_TAP_TERM) {
        media_tap_fire();
    }

    static bool     pressed    = false;
    static bool     last_raw   = false;
    static uint16_t changed_at = 0;

    bool raw = !gpio_read_pin(ENCODER_SW_PIN);
    if (raw != last_raw) {
        last_raw   = raw;
        changed_at = timer_read();
    } else if (raw != pressed && timer_elapsed(changed_at) >= ENCODER_SW_DEBOUNCE_MS) {
        pressed = raw;
        action_exec(MAKE_KEYEVENT(ENCODER_SW_ROW, ENCODER_SW_COL, pressed));
    }
}
