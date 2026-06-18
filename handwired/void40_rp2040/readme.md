# Void40 (RP2040 MIT)

Void40 driven by a Waveshare RP2040-Zero, MIT bottom row (2u spacebar), Vial-enabled.

This is a separate board from `handwired/void40` (which stays vanilla QMK on its
original atmega32u4 Pro Micro). Same matrix, different MCU + layout + firmware fork.

## Wiring (matrix → RP2040-Zero GPIO)

- Rows (4): `GP13, GP12, GP11, GP10`
- Cols (12): `GP29, GP28, GP27, GP26, GP15, GP14, GP8, GP7, GP6, GP5, GP4, GP3`
- Diode direction: `COL2ROW`
- Bootloader: `rp2040` (UF2)
- Encoder (top-left): `pin_a = GP0`, `pin_b = GP1` (only `GP0/GP1/GP2/GP9` are free
  after the matrix; `GP16` drives the onboard RGB). The encoder push-switch is the
  normal matrix key at `[0,0]` (Tab).

## Layout notes

- `LAYOUT_ortho_4x12_mit` — 47 keys. The center bottom switch is a 2u space at
  matrix `[3,5]`; cell `[3,6]` has no switch. The original base-layer Enter (col 6)
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
the flash target, or `QK_BOOT` from the Adjust layer once Vial firmware is on it.

## Vial unlock

Hold the two top corners — Tab (`[0,0]`) + top-right (`[0,11]`) — to unlock in Vial.
