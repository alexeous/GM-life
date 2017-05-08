#ifndef STRUCT_H
#define STRUCT_H

struct gameSettings {
	int fieldW, fieldH;
	int windowW, windowH;
	int period;		// Интервал между ходами (в миллисекундах)
	int population;    // Численность популяции (в процентах)
	bool socialGene;
	bool survivalGene;
	bool lazyGene;
};

typedef signed char sbyte;

struct cell {
	bool isAlive;
	sbyte health;
};

#include "const.h"

typedef cell gameField[MAX_FIELD_H+2][MAX_FIELD_W+2];	// +2 строки и столбца вокруг поля

#endif // STRUCT_H
