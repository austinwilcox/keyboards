#pragma once

// Unique per-keyboard Vial id ("VOID40RP" in ascii).
#define VIAL_KEYBOARD_UID {0x56, 0x4F, 0x49, 0x44, 0x34, 0x30, 0x52, 0x50}

// Unlock combo: hold Q + the top-right key together. (The knob push on GP28
// is injected, not scanned, so Vial's matrix_is_on() check can't see it.)
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {1, 11}

#define DYNAMIC_KEYMAP_LAYER_COUNT 4
