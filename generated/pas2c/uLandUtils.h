#pragma once

#include "pas2c.h"

#include "SDLh.h"
void ulandutils_GenerateOutlineTemplatedLand(LongWord featureSize,string255 seed,string255 templateType,astring dataPath);
void ulandutils_GenerateWfcTemplatedLand(LongWord featureSize,string255 seed,string255 templateType,astring dataPath);
void ulandutils_GenerateMazeLand(LongWord featureSize,string255 seed,string255 templateType,astring dataPath);
void ulandutils_ResizeLand(LongWord width,LongWord height);
void ulandutils_DisposeLand();
void ulandutils_InitWorldEdges();
Word ulandutils_LandGet(LongInt y,LongInt x);
void ulandutils_LandSet(LongInt y,LongInt x,Word value);
PWordArray ulandutils_LandRow(LongInt row);
void ulandutils_FillLand(LongInt x,LongInt y,Word border,Word value);
LongWord ulandutils_LandPixelGet(LongInt y,LongInt x);
void ulandutils_LandPixelSet(LongInt y,LongInt x,LongWord value);
PLongWordArray ulandutils_LandPixelRow(LongInt row);
extern pointer gameField;

