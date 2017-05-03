#include "const.h"
#include "logic.h"
#include "graphics.h"

void startGame(const gameSettings settings, gameField &field) {
	int w = settings.fieldW;
	int h = settings.fieldH;
	for(int i = 0; i < h+2; i++) {
		field[i][0].isAlive = field[i][w+1].isAlive = false;	// заполняем клетки по бокам поля
		for(int j = 1; j <= w; j++)
			field[i][j].isAlive = (rand() % 100 < settings.population);
	}
	for(int j = 0; j < w+2; j++) {
		field[0][j].isAlive = field[h+1][j].isAlive = false;	// заполняем клетки сверху и снизу поля
	}
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

// Копирует поле из src в dest
void copyField(const gameSettings settings, gameField &dest, const gameField src) {
    for(int i = 1; i <= settings.fieldH; i++) {
        size_t size = sizeof(cell) * (settings.fieldW + 2); // вычисляем, сколько байт скопировать
        memcpy(dest[i], src[i], size);  // копируем сразу целую строку
    }
}

void logic(const gameSettings settings, gameField &oldField, gameField &newField) {
    for(int i = 0; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW; j++) {
            if (oldField[i][j].isAlive == false) {
                if(neighborsAlive(oldField, i, j) == 3) {
                    newField[i][j].isAlive = true;    // Клетка рождается, если рядом 3 живых соседа
                }
                else newField[i][j].isAlive = false;
            }
            if (oldField[i][j].isAlive == true) {
                switch (neighborsAlive(oldField, i, j)) {
                case 2: case 3:    // Клетка продолжает жить, если рядом 2 или 3 живых соседа
                    newField[i][j].isAlive = true; break;
                default: newField[i][j].isAlive = false; break; // иначе умирает
                }
            }
        }
	}
	copyField(settings, oldField, newField);
}
