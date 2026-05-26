#!/usr/bin/env bash
# Symlink each board in handwired/ into every known QMK tree:
#   - submodules under this repo (vial-qmk, qmk_firmware)
#   - the QMK_HOME path from ~/.config/qmk/qmk.ini, if set
#   - sibling /home/austin/Software/{vial-qmk,qmk_firmware} clones, if present
# Idempotent: removes existing entries (file, dir, or symlink) then re-links.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOURCE_DIR="$REPO_ROOT/handwired"

TARGETS=(
  "$REPO_ROOT/qmk_firmware/keyboards/handwired"
  "$REPO_ROOT/vial-qmk/keyboards/handwired"
)

# Pick up qmk CLI's configured qmk_home so boards land where the CLI actually looks.
QMK_INI="$HOME/.config/qmk/qmk.ini"
if [[ -f "$QMK_INI" ]]; then
  qmk_home="$(awk -F'=' '/^[[:space:]]*qmk_home[[:space:]]*=/{gsub(/[[:space:]]/,"",$2); print $2; exit}' "$QMK_INI")"
  if [[ -n "${qmk_home:-}" ]]; then
    TARGETS+=("$qmk_home/keyboards/handwired")
  fi
fi

# Common sibling clones outside the repo.
for sibling in /home/austin/Software/vial-qmk /home/austin/Software/qmk_firmware; do
  TARGETS+=("$sibling/keyboards/handwired")
done

# Dedupe.
mapfile -t TARGETS < <(printf '%s\n' "${TARGETS[@]}" | awk '!seen[$0]++')

for target in "${TARGETS[@]}"; do
  if [[ ! -d "$target" ]]; then
    echo "skip: $target does not exist"
    continue
  fi
  for board_path in "$SOURCE_DIR"/*/; do
    board="$(basename "$board_path")"
    link="$target/$board"
    if [[ -e "$link" || -L "$link" ]]; then
      rm -rf "$link"
    fi
    ln -s "$board_path" "$link"
    echo "linked: $link -> $board_path"
  done
done
