# Void40 (RP2040 MIT)

Void40 driven by a Waveshare RP2040-Zero, MIT bottom row (2u spacebar), Vial-enabled.

This is a separate board from `handwired/void40` (which stays vanilla QMK on its
original atmega32u4 Pro Micro). Same matrix, different MCU + layout + firmware fork.

## Wiring (matrix → RP2040-Zero GPIO)

- Rows (4): `GP0, GP1, GP2, GP3`
- Cols (12): `GP4` through `GP15`
- Diode direction: `COL2ROW`
- Bootloader: `rp2040` (UF2)
- Encoder (top-left): `pin_a = GP26`, `pin_b = GP27`, middle pin to GND.
- Encoder push-switch: direct-wired `GP28` -> GND (internal pull-up, no diode).
  Firmware polls it and injects it as matrix cell `[3,6]` (the empty slot beside
  the 2u space), so it is remappable in Vial like a normal key.
- The knob sits in the top-left switch position, so matrix `[0,0]` is unused and
  not in the layout. Tab is unbound by default; remap it in Vial.
- Spare: `GP29`. Avoid `GP16` (onboard RGB LED).
- Full wiring guide: `void40-rp2040-zero-wiring.md` at the repo root.

## Layout notes

- `LAYOUT_ortho_4x12_mit` — 46 keys + encoder push (last arg). `QK_BOOT` is the
  knob push on the Adjust layer. The center bottom switch is a 2u space at
  matrix `[3,5]`; cell `[3,6]` has no switch and is used for the encoder push. The original base-layer Enter (col 6)
  is therefore not bound by default — remap any key to Enter in the Vial app.
- Tap dance is dynamic (Vial owns it). The slash key is wired to `TD(0)` — set up
  dynamic tap-dance #0 in the Vial app (tap = `/`, double-tap = `\`). Backslash also
  lives on the Raise layer.
- The top-left encoder rotation is mapped per layer (`encoder_map`) and is
  remappable in Vial; defaults: base = prev/next track, raise/lower = volume.

## Build / flash (vial-qmk)

    make void40-vial            # compile
    make void40-vial-flash      # compile + flash

Flashing: put the RP2040-Zero into UF2 mode (hold BOOT, tap RESET) before running
the flash target, or press the knob on the Adjust layer (`QK_BOOT`) once Vial firmware is on it.

## Vial unlock

Hold Q (`[0,1]`) + top-right (`[0,11]`) to unlock in Vial. The knob push can't
be part of the combo (it's injected in firmware, not scanned in the matrix).
