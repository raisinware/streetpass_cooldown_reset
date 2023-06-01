=========================
Streetpass Cooldown Reset
=========================
Very simple program to reset the streetpass cooldown on a Nintendo 3DS with
custom firmware.

Installing
==========
Check the releases page for installation instructions.

Building
========
This guide assumes you are running Linux.
You will need to have devkitARM installed.

3DSX:
-----
.. code-block:: sh

    git clone https://github.com/raisinware/streetpass_cooldown_reset.git
    cd streetpass_cooldown_reset

    mkdir build
    cd build
    $DEVKITPRO/portlibs/3ds/bin/arm-none-eabi-cmake .. -GNinja -DCMAKE_BUILD_TYPE=MinSizeRel

    ninja


CIA:
----
Instructions to build in CIA will be added once I write proper cmake scripts to
handle the process (and possibly rewrite bannertool in rust to fix some problems
I have with it.)

Licensing
=========
The code in this repository is licensed under 0BSD.
