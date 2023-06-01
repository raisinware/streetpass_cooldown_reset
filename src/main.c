// SPDX-License-Identifier: 0BSD
#include "cecd.h"
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>

/// deinit everything
static inline void prog_deinit(void) {
	gfxExit();
	cecdExit();
	srvExit();
}

/// Flush and swap framebuffers
static inline void prog_flush_buffers(void) {
	gfxFlushBuffers();
	gfxSwapBuffers();
}

/// loop for when program fails
static void prog_fail_loop(Result fcode) {
	// Scan all the inputs. This should be done once for each frame
	hidScanInput();

	// hidKeysDown returns information about which buttons have been just
	// pressed (and they weren't in the previous frame)
	u32 kDown = hidKeysDown();

	if (kDown & KEY_START) {
		prog_deinit();
		exit(fcode);
	}

	prog_flush_buffers();

	// Wait for VBlank
	gspWaitForVBlank();
}

int main(void) {
	Result res;

	// init services and framebuffers
	srvInit();
	cecdInit();
	gfxInitDefault();

	// init default PrintConsole
	consoleInit(GFX_BOTTOM, NULL);

	puts("Streetpass Cooldown Reset ver. 1.0.0");
	puts("By raisinware\n");
	prog_flush_buffers();

	puts("Telling CECD to clear MacFilter__...");
	prog_flush_buffers();

	res = CECD_Start(CEC_COMMAND_RESET_FILTER);

	if (R_SUCCEEDED(res)) {
		puts("Success! ^w^\n");
		prog_flush_buffers();
	} else {
		printf("\nAn Error has occured.\n");
		printf("Error Code: %d\n\n", res);
		printf("Press HOME/Start to exit\n");
		prog_flush_buffers();

		// fail loop
		while (aptMainLoop()) {
			prog_fail_loop(res);
		}
	}

	puts("Exiting :3");
	prog_flush_buffers();

	// sleeping because the program finishes too quickly to see any of the
	// output. wasn't even trying and my app is already faster then the
	// devkit apps
	svcSleepThread(1500000000); // NOLINT: 1.5 seconds in nanoseconds

	prog_deinit();
	return 0;
}
