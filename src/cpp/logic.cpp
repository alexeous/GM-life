#include "const.h"
#include "logic.h"
#include "graphics.h"

void startGame(const gameSettings settings, gameField &field) {
	int w = settings.fieldW;
	int h = settings.fieldH;
	for(int i = 0; i < h+2; i++) {
		field[i][0].isAlive = field[i][w+1].isAlive = false;	// заполняем клетки по бокам поля
		for(int j = 1; j <= w; j++)
			field[i][j].isAlive = (rand() % 10 >= 8);	// рандомное начальное заполнение ~20% клеток
	}
	for(int j = 0; j < h+2; j++)
		field[0][j].isAlive = field[h+1][j].isAlive = false;	// заполняем клетки сверху и снизу поля

	cleardevice();
}

int neighborsAlive(const gameField field, const int h, const int w) {    // Считает живых соседей
    int neighbors = 0;
    if (field[h - 1][w - 1].isAlive) neighbors++;    //
    if (field[h - 1][  w  ].isAlive) neighbors++;    //
    if (field[h - 1][w + 1].isAlive) neighbors++;    //
    if (field[  h  ][w - 1].isAlive) neighbors++;    // Проверяем все
    if (field[  h  ][w + 1].isAlive) neighbors++;    // соседние клетки
    if (field[h + 1][w - 1].isAlive) neighbors++;    //
    if (field[h + 1][  w  ].isAlive) neighbors++;    //
    if (field[h + 1][w + 1].isAlive) neighbors++;    //
    return neighbors;
}

void copyField(const gameSettings settings,                      // Копирует значения из
               gameField &oldField, const gameField &newField) { // newField в oldField
    for(int i = 1; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW; j++) {
            oldField[i][j].isAlive = newField[i][j].isAlive;
        }
    }
}

void logic(const gameSettings settings, gameField &oldField, gameField &newField) {
    for(int i = 0; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW; j++) {
            if ((oldField[i][j].isAlive == false)
                    && (neighborsAlive(oldField, i, j) == 3))
                newField[i][j].isAlive = true;    // Клетка оживает, если рядом 3 живых соседа
        }

	}
	copyField(settings, oldField, newField);
}
