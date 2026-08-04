# Keyboards

Personal keyboard configurations and handwired build firmware. Each board lives under `handwired/` and is shared between the [QMK](https://docs.qmk.fm) and [Vial](https://get.vial.today) firmware forks via symlinks. The forks themselves are pulled in as git submodules so the whole toolchain is reproducible from a fresh clone.

## Repo layout

```
keyboards/
├── handwired/           # source of truth for every board
│   ├── dactyl_manuformm/5x6/
│   ├── fightpad/
│   ├── scottoergo/
│   ├── scottofrog/
│   ├── skeletyl/
│   ├── void9/
│   └── void40/
├── qmk_firmware/        # submodule: github.com/qmk/qmk_firmware
├── vial-qmk/            # submodule: github.com/vial-kb/vial-qmk
├── qmk_configurator/    # JSON layouts for the web configurators
├── Makefile             # per-board build / flash targets
├── sync_boards.sh       # symlinks handwired/* into both forks
└── readme.md
```

Each board defaults to one fork (see the table below). Boards I want to retune live live on vial-qmk so the layout is editable in the Vial GUI; the rest stay on vanilla QMK with a fixed keymap I'm happy with.

## Boards at a glance

| Board                   | MCU         | Bootloader  | Default fork | Default keymap     |
| ----------------------- | ----------- | ----------- | ------------ | ------------------ |
| `dactyl_manuformm/5x6`  | atmega32u4  | caterina    | qmk_firmware | `austinwilcox`     |
| `fightpad`              | RP2040      | rp2040      | vial-qmk     | `vial`             |
| `scottoergo`            | atmega32u4  | atmel-dfu   | vial-qmk     | `vial`             |
| `scottofrog`            | RP2040      | rp2040      | vial-qmk     | `vial`             |
| `skeletyl`              | atmega32u4  | caterina    | qmk_firmware | `miryoku`          |
| `void9`                 | RP2040      | rp2040      | vial-qmk     | `vial`             |
| `void40`                | atmega32u4  | caterina    | qmk_firmware | `colemak_dh_grid`  |

## Prerequisites

Tested on Linux. macOS works with the same commands; Windows users should follow the QMK [Windows setup guide](https://docs.qmk.fm/newbs_getting_started).

1. **QMK CLI**, installed in a Python venv to keep system Python clean:
   ```bash
   python3 -m venv ~/py_envs
   source ~/py_envs/bin/activate
   pip install qmk
   ```
   Add `source ~/py_envs/bin/activate` to your shell rc (or alias `qmk` to the venv binary).
2. **Toolchains** for each MCU family. Easiest path is `qmk setup` once after install — it pulls `arm-none-eabi-gcc` (RP2040) and `avr-gcc` (atmega). On Arch Linux the manual route is `pacman -S avr-gcc avr-libc avr-binutils arm-none-eabi-gcc arm-none-eabi-newlib dfu-programmer dfu-util avrdude`.
3. **udev rules** so non-root users can flash. QMK ships them at `qmk_firmware/util/udev/50-qmk.rules`:
   ```bash
   sudo cp qmk_firmware/util/udev/50-qmk.rules /etc/udev/rules.d/
   sudo udevadm control --reload-rules && sudo udevadm trigger
   ```
4. **GNU Make**, `git`, and a USB cable that actually carries data (this catches people more than it should).

## First-time setup

Clone with submodules and wire everything together:

```bash
git clone --recurse-submodules ssh://git@gitea-ssh.theaustinwilcox.com/austinwilcox/keyboards.git
cd keyboards
make sync
```

If you forgot `--recurse-submodules`, fix it after the fact:

```bash
git submodule update --init --recursive
make sync
```

`make sync` runs `sync_boards.sh`, which symlinks every directory in `handwired/` into both `qmk_firmware/keyboards/handwired/` and `vial-qmk/keyboards/handwired/`. The script is idempotent — re-run it any time you add a new board or after a clean checkout.

## Building and flashing

The `Makefile` exposes one target per (board, keymap) pair I actually use. Run `make help` for the full list. The common ones:

```bash
make scottofrog            # compile vial firmware for scottofrog
make scottofrog-flash      # compile + flash (qmk autodetects the bootloader)
make fightpad              # compile vanilla qmk firmware
make sync                  # re-link boards into both forks
make clean                 # wipe both forks' .build/ trees
```

`make <board>-flash` calls `qmk flash`, which polls for the bootloader and pushes the firmware as soon as the board enters it. For boards that aren't in bootloader yet you'll see a `Waiting for drive to deploy...` message — put the board in bootloader (see per-board notes) and the flash completes automatically.

### Manual RP2040 flash (if `qmk flash` misbehaves)

RP2040 boards mount as a USB drive named `RPI-RP2`. If the auto-flow ever fails, build then drag the UF2 manually:

```bash
make scottofrog
# put board in bootloader, then:
udisksctl mount -b /dev/sda1
cp vial-qmk/.build/handwired_scottofrog_vial.uf2 /media/$USER/RPI-RP2/
sync
```

The board reboots into the new firmware as soon as the copy lands.

### Updating the firmware forks

Both forks are pinned commits. To roll forward:

```bash
git -C qmk_firmware fetch && git -C qmk_firmware checkout master && git -C qmk_firmware pull
git -C vial-qmk    fetch && git -C vial-qmk    checkout vial   && git -C vial-qmk    pull
git add qmk_firmware vial-qmk
git commit -m "bump qmk + vial-qmk"
```

After bumping, rebuild any board you flash — upstream changes can shift the keymap API.

## Editing layouts in Vial

For boards with a `vial` keymap, layouts can be edited live in the [Vial GUI](https://get.vial.today/) without reflashing:

1. Flash the vial firmware once (`make <board>-flash`).
2. Open Vial. The board appears automatically.
3. Edit, save, done. Settings live in the keyboard's EEPROM.

Each board's `keymaps/vial/vial.json` is the layout definition Vial uses. Tap-dance / combo / key-override toggles live in `keymaps/vial/rules.mk`.

## Per-board notes

### Scotto Frog (`handwired/scottofrog/`)
- Hand-wired with a custom row pin layout — `rows: GP2, GP4, GP11, GP12` instead of the upstream stock pins. The repo's `keyboard.json` is the source of truth; do not pull row pins from upstream.
- Bootloader entry: hold the top-left key (matrix `[0,1]`) while plugging the cable. Bootmagic is enabled.
- Build: `make scottofrog`. Flash: `make scottofrog-flash`.

### Scotto Ergo (`handwired/scottoergo/`)
- atmega32u4 / atmel-dfu. Bootloader entry: hold the number layer key, then `;` (the existing `RESET` macro on the keymap).
- Build: `make scottoergo`. Flash: `make scottoergo-flash`.
- Reference Miryoku-style tap-dance JSON for the Vial GUI is at `qmk_configurator/scottoergo_miryoku_tapdance.json`.

### Dactyl Manuform 5x6 (`handwired/dactyl_manuformm/5x6/`)
- Split board, atmega32u4 / caterina, daily driver. Vanilla QMK with the `austinwilcox` keymap. Uses [`EE_HANDS`](https://docs.qmk.fm/features/split_keyboard#handedness-by-eeprom) so the same firmware flashes to either half.
- First-time hand setup: flash both halves, then set handedness via QMK's [`SET_HANDEDNESS`](https://docs.qmk.fm/features/split_keyboard#setting-handedness) (e.g. flash one half, plug in alone, hit the eeprom-set keycode), or burn the EEPROM byte with the dedicated handedness firmware target.
- Build: `make dactyl`. Flash: `make dactyl-flash`.
- Switches: Akko Lavender. 3D-printed case.

### Skeletyl (`handwired/skeletyl/`)
- BastardKB Skeletyl, atmega32u4 / caterina, split, also `EE_HANDS`. Vanilla QMK with the `miryoku` keymap.
- Build: `make skeletyl`. Flash: `make skeletyl-flash`.

### Fightpad (`handwired/fightpad/`)
- RP2040 arcade-style fightpad used with RetroArch on the Steam Deck.
- Two keymaps. `default` is vanilla QMK with a fixed layout; `vial` is the same board on vial-qmk with runtime-remappable keys.
- Both emit a keyboard keycode *and* a joystick button per press, so the pad reads as a gamepad on the Deck (sdl2) and as a keyboard elsewhere. In the vial keymap the joystick button is bound to the matrix position rather than the keycode, so remapping in Vial never breaks existing RetroArch button bindings.
- Vial unlock combo: hold **up** + the **far-right bottom** face button.
- Vanilla: build `make fightpad`, flash `make fightpad-flash`.
- Vial: `make fightpad-vial` builds *and* flashes — it parks on `Waiting for drive to deploy...`, so start it first, then double-tap reset the pad. `make fightpad-vial-compile` if you only want the uf2.

### Void 40 (`handwired/void40/`)
- atmega32u4 / caterina. The original handwired board; controller is currently busted, so flashing is mostly an academic exercise until I rebuild it. Vanilla QMK with the `colemak_dh_grid` keymap.
- Build: `make void40`. Flash: `make void40-flash`.
- Switches: Glorious Panda. 3D-printed case.

### Void 9 (`handwired/void9/`)
- RP2040 9-key macro pad. Vial only.
- Build: `make void9`. Flash: `make void9-flash`.

### ZSA Moonlander
- Configured online via [Oryx](https://configure.zsa.io/moonlander/layouts/BqXMv/latest/0). Not built from this repo.
- Layout is a tweaked [Miryoku](https://github.com/manna-harbour/miryoku); base swap is `;` ↔ `'` so the more-frequent semicolon stays on the home row.

## Adding a new board

1. Create `handwired/<board>/` with `keyboard.json`, `rules.mk`, and at least one keymap. Keep the source of truth in this repo, not in the firmware fork.
2. Run `make sync` to link the new board into both forks.
3. Add `make` targets for it (use one of the existing entries in `Makefile` as a template).
4. If the board is meant for Vial, add `keymaps/vial/` with `vial.json`, `keymap.c`, `config.h`, and `rules.mk` (`VIA_ENABLE = yes`, `VIAL_ENABLE = yes`). Generate a unique `VIAL_KEYBOARD_UID` per [the Vial docs](https://get.vial.today/docs/porting-to-via).
5. Update the table at the top of this readme and add a per-board section.

## Troubleshooting

- **`qmk: command not found`** — venv isn't sourced. `source ~/py_envs/bin/activate`.
- **`No such keyboard: handwired/<x>`** — symlinks are missing. Run `make sync`.
- **Build pulls in unexpected pins** — somebody edited the copy inside a fork directly instead of `handwired/<board>/`. The symlink should prevent this; if it doesn't, the fork dir was overwritten with a real directory. Delete it and re-run `make sync`.
- **`make <board>-flash` hangs** — board never entered bootloader. Trigger it (per-board section above) and the flow continues.
- **RP2040 mounts but `cp` says read-only** — the board is in MSC bootloader but already locked. Unplug, replug while holding BOOTSEL, then retry.
- **Vial GUI doesn't see the board** — you flashed the wrong keymap. Re-flash with the `vial` target (or the board's vial-equivalent target).
- **Split halves don't agree** — `EE_HANDS` not set. Use Vial's Hand Setup or burn the EEPROM byte manually.

## License

See `LICENSE`.
