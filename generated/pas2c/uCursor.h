#pragma once

#include "pas2c.h"

void ucursor_init();
void ucursor_resetPosition();
void ucursor_resetPositionDelta();
void ucursor_updatePositionDelta(LongInt xrel,LongInt yrel);
void ucursor_updatePosition();
void ucursor_handlePositionUpdate(LongInt x,LongInt y);

