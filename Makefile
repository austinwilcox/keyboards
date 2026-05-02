# Build / flash targets for each handwired board.
#
# Usage:
#   make sync               # symlink boards into both submodules
#   make <board>            # compile primary firmware
#   make <board>-flash      # compile and flash (qmk autodetects bootloader)
#
# Boards default to their "daily" keymap. Alternate keymaps are exposed as
# explicit targets (e.g. skeletyl-miryoku, void40-colemak).

REPO_ROOT := $(shell pwd)
QMK       := $(REPO_ROOT)/qmk_firmware
VIAL      := $(REPO_ROOT)/vial-qmk

# Run qmk inside a given fork's tree so QMK_HOME picks it up.
QMK_RUN  = QMK_HOME=$(QMK)  qmk
VIAL_RUN = QMK_HOME=$(VIAL) qmk

.PHONY: sync clean help \
        fightpad fightpad-flash \
        dactyl dactyl-flash dactyl-vial dactyl-vial-flash \
        scottoergo scottoergo-flash \
        scottofrog scottofrog-flash \
        skeletyl skeletyl-flash skeletyl-miryoku skeletyl-miryoku-flash \
        void40 void40-flash void40-colemak void40-colemak-flash \
        void9 void9-flash

help:
	@echo "Targets:"
	@echo "  sync                       symlink boards into both submodules"
	@echo "  fightpad / -flash          (vanilla qmk, default keymap)"
	@echo "  dactyl / -flash            (vial-qmk, austinwilcox keymap)"
	@echo "  dactyl-vial / -flash       (vial-qmk, vial keymap)"
	@echo "  scottoergo / -flash        (vial-qmk, vial keymap)"
	@echo "  scottofrog / -flash        (vial-qmk, vial keymap)"
	@echo "  skeletyl / -flash          (vial-qmk, vial keymap)"
	@echo "  skeletyl-miryoku / -flash  (vanilla qmk, miryoku keymap)"
	@echo "  void40 / -flash            (vial-qmk, vial keymap)"
	@echo "  void40-colemak / -flash    (vanilla qmk, colemak_dh_grid keymap)"
	@echo "  void9 / -flash             (vial-qmk, vial keymap)"
	@echo "  clean                      remove .build/ artifacts in both forks"

sync:
	./sync_boards.sh

clean:
	rm -rf $(QMK)/.build $(VIAL)/.build

# fightpad: vanilla qmk only (no vial keymap)
fightpad:
	$(QMK_RUN) compile -kb handwired/fightpad -km default
fightpad-flash:
	$(QMK_RUN) flash -kb handwired/fightpad -km default

# dactyl manuform 5x6
dactyl:
	$(VIAL_RUN) compile -kb handwired/dactyl_manuformm/5x6 -km austinwilcox
dactyl-flash:
	$(VIAL_RUN) flash -kb handwired/dactyl_manuformm/5x6 -km austinwilcox
dactyl-vial:
	$(VIAL_RUN) compile -kb handwired/dactyl_manuformm/5x6 -km vial
dactyl-vial-flash:
	$(VIAL_RUN) flash -kb handwired/dactyl_manuformm/5x6 -km vial

# scotto ergo
scottoergo:
	$(VIAL_RUN) compile -kb handwired/scottoergo -km vial
scottoergo-flash:
	$(VIAL_RUN) flash -kb handwired/scottoergo -km vial

# scotto frog
scottofrog:
	$(VIAL_RUN) compile -kb handwired/scottofrog -km vial
scottofrog-flash:
	$(VIAL_RUN) flash -kb handwired/scottofrog -km vial

# skeletyl
skeletyl:
	$(VIAL_RUN) compile -kb handwired/skeletyl -km vial
skeletyl-flash:
	$(VIAL_RUN) flash -kb handwired/skeletyl -km vial
skeletyl-miryoku:
	$(QMK_RUN) compile -kb handwired/skeletyl -km miryoku
skeletyl-miryoku-flash:
	$(QMK_RUN) flash -kb handwired/skeletyl -km miryoku

# void40
void40:
	$(VIAL_RUN) compile -kb handwired/void40 -km vial
void40-flash:
	$(VIAL_RUN) flash -kb handwired/void40 -km vial
void40-colemak:
	$(QMK_RUN) compile -kb handwired/void40 -km colemak_dh_grid
void40-colemak-flash:
	$(QMK_RUN) flash -kb handwired/void40 -km colemak_dh_grid

# void9
void9:
	$(VIAL_RUN) compile -kb handwired/void9 -km vial
void9-flash:
	$(VIAL_RUN) flash -kb handwired/void9 -km vial
