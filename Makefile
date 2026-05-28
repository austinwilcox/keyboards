# Build / flash targets for each handwired board.
#
# Usage:
#   make sync               # symlink boards into both submodules
#   make <board>            # compile primary firmware
#   make <board>-flash      # compile and flash (qmk autodetects bootloader)

REPO_ROOT := $(shell pwd)
QMK       := $(REPO_ROOT)/qmk_firmware
VIAL      := $(REPO_ROOT)/vial-qmk

# Run qmk inside a given fork's tree so QMK_HOME picks it up.
QMK_RUN  = QMK_HOME=$(QMK)  qmk
VIAL_RUN = QMK_HOME=$(VIAL) qmk

.PHONY: sync clean help \
        fightpad fightpad-flash \
        dactyl dactyl-flash \
        redox redox-flash-left redox-flash-right \
        scottoergo scottoergo-flash \
        scottofrog scottofrog-flash \
        skeletyl skeletyl-flash \
        void40 void40-flash \
        void9 void9-flash

help:
	@echo "Targets:"
	@echo "  sync                       symlink boards into both submodules"
	@echo "  fightpad / -flash          (vanilla qmk, default keymap)"
	@echo "  dactyl / -flash            (vanilla qmk, austinwilcox keymap)"
	@echo "  redox                      compile (vial-qmk, vial keymap, split RP2040)"
	@echo "  redox-flash-left|-right    flash one half (EE_HANDS, run once per side)"
	@echo "  scottoergo / -flash        (vial-qmk, vial keymap)"
	@echo "  scottofrog / -flash        (vial-qmk, vial keymap)"
	@echo "  skeletyl / -flash          (vanilla qmk, miryoku keymap)"
	@echo "  void40 / -flash            (vanilla qmk, colemak_dh_grid keymap)"
	@echo "  void9 / -flash             (vial-qmk, vial keymap)"
	@echo "  clean                      remove .build/ artifacts in both forks"

sync:
	./sync_boards.sh

clean:
	rm -rf $(QMK)/.build $(VIAL)/.build

# fightpad: vanilla qmk, default keymap
fightpad:
	$(QMK_RUN) compile -kb handwired/fightpad -km default
fightpad-flash:
	$(QMK_RUN) flash -kb handwired/fightpad -km default

# dactyl manuform 5x6: vanilla qmk, austinwilcox keymap
dactyl:
	$(QMK_RUN) compile -kb handwired/dactyl_manuformm/5x6 -km austinwilcox
dactyl-flash:
	$(QMK_RUN) flash -kb handwired/dactyl_manuformm/5x6 -km austinwilcox

# redox split (RP2040-Zero): vial-qmk. EE_HANDS — each half needs its own
# flash with handedness baked into EEPROM. Boot each half into UF2 separately.
redox:
	$(VIAL_RUN) compile -kb handwired/redox -km vial
redox-flash-left:
	$(VIAL_RUN) flash -kb handwired/redox -km vial -bl uf2-split-left
redox-flash-right:
	$(VIAL_RUN) flash -kb handwired/redox -km vial -bl uf2-split-right

# scotto ergo: vial-qmk
scottoergo:
	$(VIAL_RUN) compile -kb handwired/scottoergo -km vial
scottoergo-flash:
	$(VIAL_RUN) flash -kb handwired/scottoergo -km vial

# scotto frog: vial-qmk
scottofrog:
	$(VIAL_RUN) compile -kb handwired/scottofrog -km vial
scottofrog-flash:
	$(VIAL_RUN) flash -kb handwired/scottofrog -km vial

# skeletyl: vanilla qmk, miryoku keymap
skeletyl:
	$(QMK_RUN) compile -kb handwired/skeletyl -km miryoku
skeletyl-flash:
	$(QMK_RUN) flash -kb handwired/skeletyl -km miryoku

# void40: vanilla qmk, colemak_dh_grid keymap
void40:
	$(QMK_RUN) compile -kb handwired/void40 -km colemak_dh_grid
void40-flash:
	$(QMK_RUN) flash -kb handwired/void40 -km colemak_dh_grid

# void9: vial-qmk
void9:
	$(VIAL_RUN) compile -kb handwired/void9 -km vial
void9-flash:
	$(VIAL_RUN) flash -kb handwired/void9 -km vial
