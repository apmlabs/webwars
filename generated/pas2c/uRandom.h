#pragma once

#include "pas2c.h"

#include "uFloat.h"
void urandom_SetRandomSeed(string255 Seed,boolean dropAdditionalPart);
hwFloat urandom_GetRandomf();
LongWord urandom_GetRandom(LongWord m);
void urandom_AddRandomness(LongWord r);
hwFloat urandom_rndSign(hwFloat num);

