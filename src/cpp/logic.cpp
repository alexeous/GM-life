#include "const.h"
#include "logic.h"
#include "graphics.h"

void startGame(const gameSettings settings, gameField &field) {
	int w = settings.fieldW;
	int h = settings.fieldH;
	for(int i = 0; i < h+2; i++) {
		field[i][0].isAlive = field[i][w+1].isAlive = false;	// заполняем клетки по бокам поля
		for(int j = 1; j <= w; j++)
            if(rand() % 100 < settings.population) 
                bornCell(field, i, j);
            else field[i][j].isAlive = false;
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

void bornCell(gameField &field, const int h, const int w) {
    field[h][w].isAlive = true;
    field[h][w].health = 1;
}

void harmCell(gameField &field, const int h, const int w) {
    if(--field[h][w].health <= 0)
        field[h][w].isAlive = false;
}

void logic(const gameSettings settings, gameField &oldField) {
    gameField newField;
    copyField(settings, newField, oldField);
    for(int i = 1; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW; j++) {
            int neighbors = neighborsAlive(oldField, i, j);
            if (oldField[i][j].isAlive == false) { // Рождается, если 3 живых соседа, иначе остаётся мертвой:
                if(neighbors == 3) bornCell(newField, i, j);
            } else {    // Теряет здоровье, когда меньше 2 или больше 3 соседей:
                if(neighbors < 2 || neighbors > 3) harmCell(newField, i, j);
            }
        }
	}
	copyField(settings, oldField, newField);
}
