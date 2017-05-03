#ifndef CONST_H
#define CONST_H

#define MAX_FIELD_W 115
#define MAX_FIELD_H 65
#define MIN_FIELD_W 30
#define MIN_FIELD_H 30

#define CELL_SIZE_PX 10
#define GRID_THICKNESS_PX 2

#define MIN_PERIOD 100
#define MAX_PERIOD 5000
#define PERIOD_STEP 100 // шаг, с которым меняется период

#define PERIOD_SHOW_DURATION 1000

#define MIN_POPULATION 10
#define MAX_POPULATION 100

#include "struct.h"

const gameSettings defaultSettings = {
    MIN_FIELD_W, MIN_FIELD_H,       // fieldW, fieldH
    MIN_FIELD_W * CELL_SIZE_PX + (MIN_FIELD_W + 1) * GRID_THICKNESS_PX,  //screenW
    MIN_FIELD_H * CELL_SIZE_PX + (MIN_FIELD_H + 1) * GRID_THICKNESS_PX,  //screenH
    1000,        // period
    20        // population
};

#endif // CONST_H
