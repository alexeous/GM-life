#include "const.h"
#include "logic.h"
#include "graphics.h"

void startGame(const gameSettings &settings, gameField &field) {
	int w = settings.fieldW;
	int h = settings.fieldH;
	for(int i = 0; i < h+2; i++) {
		field[i][0].isAlive = field[i][w+1].isAlive = false;	// заполняем клетки по бокам поля
		for(int j = 1; j <= w; j++)
			field[i][j].isAlive = (rand() % 10 >= 8);	// рандомное начальное заполнение ~20% клеток
	}
	for(int j = 0; j < h+2; j++) {
		field[0][j].isAlive = field[h+1][j].isAlive = false;	// заполняем клетки сверху и снизу поля
	}
	cleardevice();
}

void logic(gameSettings &settings, gameField &field) {	// TODO

}
