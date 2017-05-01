#ifndef CONST_H
#define CONST_H

#define MAX_FIELD_W 115
#define MAX_FIELD_H 65
#define MIN_FIELD_W 30
#define MIN_FIELD_H 30
#define CELL_SIZE_PX 10
#define GRID_THICKNESS_PX 2

#include "struct.h"

const gameSettings defaultSettings = { 
    MIN_FIELD_W, MIN_FIELD_H,
    MIN_FIELD_W * CELL_SIZE_PX + (MIN_FIELD_W + 1) * GRID_THICKNESS_PX,
    MIN_FIELD_H * CELL_SIZE_PX + (MIN_FIELD_H + 1) * GRID_THICKNESS_PX
};

#endif // CONST_H
