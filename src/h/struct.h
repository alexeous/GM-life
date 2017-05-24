#ifndef STRUCT_H
#define STRUCT_H

struct gameSettings {
	int fieldW, fieldH;
	int windowW, windowH;
	int period;		// Интервал между ходами (в миллисекундах)
	bool pause;		// Поставлена ли игра на паузу
	int population;    // Численность популяции (в процентах)
	bool socialGene;
	bool survivalGene;
	bool lazyGene;
	bool aging;
};

typedef unsigned char byte;
typedef signed char sbyte;

struct cell {
	bool isAlive;
	bool isLazy;
	sbyte health;
	sbyte socialGene;
	sbyte maxHealth;
	sbyte age;
	bool needRefresh;    // Показывает, нужно ли перерисовывать клетку
};

#include "const.h"

typedef cell gameField[MAX_FIELD_H+2][MAX_FIELD_W+2];	// +2 строки и столбца вокруг поля

#endif // STRUCT_H
