// SPDX-License-Identifier: 0BSD
#include "cecd.h"
#include <3ds/ipc.h>
#include <3ds/result.h>
#include <3ds/srv.h>
#include <3ds/svc.h>
#include <3ds/synchronization.h>
#include <3ds/types.h>

#define RUNCOMMAND_MAGIC 0x000B

static Handle cecdHandle;
static int cecdRefCount;

Result cecdInit(void) {
	Result ret;

	if (AtomicPostIncrement(&cecdRefCount)) {
		return 0;
	}

	ret = srvGetServiceHandle(&cecdHandle, "cecd:u");

	if (R_FAILED(ret)) {
		AtomicDecrement(&cecdRefCount);
	}

	return ret;
}

void cecdExit(void) {
	if (AtomicDecrement(&cecdRefCount)) {
		return;
	}

	svcCloseHandle(cecdHandle);
}

Handle cecdGetSessionHandle(void) {
	return cecdHandle;
}

Result CECD_Start(CEC_Command command) {
	Result ret = 0;
	u32* ipcbuf = getThreadCommandBuffer();

	ipcbuf[0] = IPC_MakeHeader(RUNCOMMAND_MAGIC, 1, 0); // 0x000B0040
	ipcbuf[1] = command;

	ret = svcSendSyncRequest(cecdHandle);

	if (R_FAILED(ret)) {
		return ret;
	}

	return (Result)ipcbuf[1];
}
