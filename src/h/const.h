#ifndef CONST_H
#define CONST_H

#define MAX_FIELD_W 110
#define MAX_FIELD_H 55
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

#define MAX_AGE 10
#define MAX_HEALTH 5

#include "struct.h"

// Массив отступов для доступа к каждому соседу
struct {
    int h, w;
} const neighborsOffsets[8] = { {-1, -1}, {-1, 0}, {-1, 1},
                                {0,  -1},          {0,  1},
                                {1,  -1}, {1,  0}, {1,  1} };

inline int calcWindowW(int fieldW) {
    return fieldW * CELL_SIZE_PX + (fieldW + 1) * GRID_THICKNESS_PX;
}
inline int calcWindowH(int fieldH) {
    return fieldH * CELL_SIZE_PX + (fieldH + 1) * GRID_THICKNESS_PX + STATUS_BAR_HEIGHT;
}

// Палитра цветов клеток (для гена социальности)
const int socialRed[9]   = { 250, 250, 125,   0,   0,   0, 125, 250, 250 };
const int socialGreen[9] = {   0, 190, 250, 250, 250,  60,   0,   0,   0 };
const int socialBlue[9]  = {   0,   0,   0,  60, 250, 250, 250, 190,   0 };

const gameSettings defaultSettings = {
    MIN_FIELD_W, MIN_FIELD_H,  // fieldW, fieldH
    calcWindowW(MIN_FIELD_W),  //screenW
    calcWindowH(MIN_FIELD_H),  //screenH
    1000,     // period
    false,    // pause
    20,       // population
    false,    // socialGene
	false,    // survivalGene
	false,    // lazyGene
	false     // aging
};

#endif // CONST_H
