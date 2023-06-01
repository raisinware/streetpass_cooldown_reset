#!/bin/sh
# SPDX-License-Identifier: 0BSD
set -e

TITLE="Streetpass Cooldown Reset"
#DESCRIPTION="Resets the 8 hour Streetpass cooldown"
AUTHOR="raisinware"
ICON="./icon.png"

./bannertool makebanner -i ./banner.png -a ./auddio.wav -o ./banner.bnr
./bannertool makesmdh -s "$TITLE" -l "$TITLE" -p "$AUTHOR" -i "$ICON" -o ./icon.icn
