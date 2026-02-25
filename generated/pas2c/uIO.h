#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uTypes.h"
void uio_initModule();
void uio_freeModule();
void uio_InitIPC();
void uio_SendIPC(string255 s);
void uio_SendIPCXY(char cmd,LongInt X,LongInt Y);
void uio_SendIPCRaw(pointer p,LongWord len);
void uio_SendIPCAndWaitReply(string255 s);
void uio_FlushMessages(LongWord Lag);
void uio_LoadRecordFromFile(string255 fileName);
void uio_SendStat(TStatInfoType sit,string255 s);
void uio_IPCWaitPongEvent();
void uio_IPCCheckSock();
void uio_NetGetNextCmd();
void uio_doPut(LongInt putX,LongInt putY,boolean fromAI);

