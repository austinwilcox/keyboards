# Custom keyboard configurations

Most of the handwired boards in this repo now support [Vial](https://get.vial.today/) in addition to QMK. Each board has a `keymaps/vial/` directory with the matching `vial.json` so layouts can be edited live without reflashing.

## ZSA Moonlander
My latest ZSA keyboard configuration is using my variation of the [Miryoku](https://github.com/manna-harbour/miryoku) keyboard layout. The only significant change I have made so far is to change ' with ; on the base layout. Because I write enough code and need to use semi colon all the time, it made sense to keep it on the base layer.
[Oryx Configuration](https://configure.zsa.io/moonlander/layouts/BqXMv/latest/0)

## Void 40
Void 40 was the first handwired keyboard that I built, and it was more of an experiment than anything else. I recently busted the micro controller on this one while trying to fix some sotter joints on the switches, so this one is out of commission and I might not end up fixing this one.

I built this with a 3d printed case, and Glorious Panda switches, with a QMK configuration. Vial support has since been added under `handwired/void40/keymaps/vial/`.

## Void 9
A 9-key macro pad built on the same handwired approach as the Void 40. Lives at `handwired/void9/` with both default QMK and Vial keymaps.

## Dactyl Manuform 5x6
My second hand wired keyboard, and it's a split 5x6 Dactyl Manuform. This keyboard has been my daily driver for over a year now, and I find the comfort to be top notch and the concavity allows my fingers to travel less than on the Moonlander.

I built this with a 3d printed case, and Akko Lavender Switches (My current favorite switches to use), with a QMK configuration. The board now also has Vial support and uses the [Easy EAKL hand-swap (EE_HANDS)](https://docs.qmk.fm/features/split_keyboard#handedness-by-eeprom) split handedness so the same firmware works on either half.

## Skeletyl
A smaller split board added to the collection. Located at `handwired/skeletyl/`. Like the Dactyl, it uses `EE_HANDS` for split handedness and has Vial support alongside the default keymap.

## Scotto Ergo
```shell
❯ source ~/py_envs/bin/activate
❯ qmk compile --keyboard handwired/scottokeebs/scottoergo --keymap austinwilcox
❯ qmk flash .build/handwired_scottokeebs_scottoergo_austinwilcox.hex
```
To flash the software onto the keyboard, hold the number layer, and then press `;`.

The Scotto Ergo also has a Vial keymap (`handwired/scottoergo/keymaps/vial/`) for live layout editing. A reference Miryoku-style tap-dance JSON for the Vial GUI is checked in at `qmk_configurator/scottoergo_miryoku_tapdance.json`.

## Scotto Frog
A newer Scotto-family handwired board sitting at `handwired/scottofrog/`. Ships with both default QMK and Vial keymaps.

## Fightpad
A handwired arcade-style fightpad used with RetroArch on the Steam Deck. Lives at `handwired/fightpad/`. The keymap was consolidated so the Vial-only variant was dropped in favor of a single mirrored default layout in `keymaps/default/keymap.c`.
