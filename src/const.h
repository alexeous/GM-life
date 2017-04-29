#ifndef CONST_H
#define CONST_H

#include "struct.h"

#define MAX_FIELD_W 120
#define MAX_FIELD_H 70
#define MIN_FIELD_W 30
#define MIN_FIELD_H 30
#define CELL_SIZE_PX 10
const gameSettings defaultSettings = { MIN_FIELD_W, MIN_FIELD_H,
                                       MIN_FIELD_W * CELL_SIZE_PX + (MIN_FIELD_W - 1),
                                       MIN_FIELD_H * CELL_SIZE_PX + (MIN_FIELD_H - 1) };

#endif // CONST_H
