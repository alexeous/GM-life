#ifndef LOGIC_H
#define LOGIC_H

#include "struct.h"

void startGame(const gameSettings settings, gameField &field);
void logic(gameSettings &settings, gameField &field);
void endGame();

#endif // LOGIC_H