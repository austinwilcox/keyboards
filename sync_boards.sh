#!/usr/bin/env bash
# Symlink each board in handwired/ into both submodules' keyboards/handwired/.
# Idempotent: removes existing entries (file, dir, or symlink) then re-links.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOURCE_DIR="$REPO_ROOT/handwired"

TARGETS=(
  "$REPO_ROOT/qmk_firmware/keyboards/handwired"
  "$REPO_ROOT/vial-qmk/keyboards/handwired"
)

for target in "${TARGETS[@]}"; do
  if [[ ! -d "$target" ]]; then
    echo "skip: $target does not exist (submodule not initialized?)"
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
