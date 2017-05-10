#ifndef CONST_H
#define CONST_H

#define MAX_FIELD_W 115
#define MAX_FIELD_H 65
#define MIN_FIELD_W 30
#define MIN_FIELD_H 30

#define CELL_SIZE_PX 10
#define GRID_THICKNESS_PX 2

#define STATUS_BAR_HEIGHT 20

#define MIN_PERIOD 100
#define MAX_PERIOD 5000
#define PERIOD_STEP 100 // шаг, с которым меняется период

#define MIN_POPULATION 10
#define MAX_POPULATION 100

#include "struct.h"

inline int calcWindowW(int fieldW) {
    return fieldW * CELL_SIZE_PX + (fieldW + 1) * GRID_THICKNESS_PX;
}
inline int calcWindowH(int fieldH) {
    return fieldH * CELL_SIZE_PX + (fieldH + 1) * GRID_THICKNESS_PX + STATUS_BAR_HEIGHT;
}

const gameSettings defaultSettings = {
    MIN_FIELD_W, MIN_FIELD_H,       // fieldW, fieldH
    calcWindowW(MIN_FIELD_W),  //screenW
    calcWindowH(MIN_FIELD_H),  //screenH
    1000,        // period
    20,      // population
    false,    // socialGene
	false,    // survivalGene
	false     // lazyGene
};

#endif // CONST_H
