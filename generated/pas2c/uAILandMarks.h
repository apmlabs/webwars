#pragma once

#include "pas2c.h"

enum{markWalkedHere = 0x01};
enum{markHJumped = 0x02};
enum{markLJumped = 0x04};
void uailandmarks_addMark(LongInt X,LongInt Y,Byte mark);
boolean uailandmarks_checkMark(LongInt X,LongInt Y,Byte mark);
void uailandmarks_clearAllMarks();
void uailandmarks_clearMarks(Byte mark);
void uailandmarks_setAILandMarks();
void uailandmarks_initModule();
void uailandmarks_freeModule();

