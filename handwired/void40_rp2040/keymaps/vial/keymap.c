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
// in the layout (Tab is unbound by default -- set it in Vial). QK_BOOT lives
// on the knob push in the Adjust layer. Rotation maps
// per-layer via encoder_map below and is remappable in Vial
// (ENCODER_MAP_ENABLE).

#include QMK_KEYBOARD_H

enum layer_names {
  _COLEMAK,
  _RAISE,
  _LOWER,
  _ADJUST
};

// Vial custom keycodes start at QK_KB_0 (listed under "User" in the Vial app,
// names come from customKeycodes in vial.json).
enum custom_keycodes {
  MEDIA_TAP = QK_KB_0 // 1 tap: play/pause, 2 taps: next, 3 taps: previous
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak */
[_COLEMAK] = LAYOUT_ortho_4x12_mit(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_MINS,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_EQL,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  TD(0),   KC_QUOT,
    KC_LCTL, TO(_LOWER), KC_LGUI, KC_LBRC, KC_RBRC,    KC_SPC,    KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    MEDIA_TAP
),

/* Lower */
[_LOWER] = LAYOUT_ortho_4x12_mit(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_ASTR,
    KC_LSFT, KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_COMM, KC_DOT,  TD(0),   KC_QUOT,
    KC_TRNS, TO(_COLEMAK), KC_LGUI, KC_LBRC, KC_RBRC, KC_SPC, KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,
    KC_MUTE
),

/* Raise */
[_RAISE] = LAYOUT_ortho_4x12_mit(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, KC_ENT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
    KC_MUTE
),

/* Adjust */
[_ADJUST] = LAYOUT_ortho_4x12_mit(
    KC_NO,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_NO,   KC_DEL,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    EE_CLR,  KC_NO,   KC_NO,   KC_NO,   KC_TRNS,    KC_NO,    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,
    QK_BOOT
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_COLEMAK] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_RAISE]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LOWER]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_ADJUST]  = { ENCODER_CCW_CW(_______, _______) },
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

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
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
