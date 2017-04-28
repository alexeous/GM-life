#ifndef LOGIC_H
#define LOGIC_H

#include "struct.h"

void startGame(gameSettings &settings, gameField &field);
void logic(gameSettings &settings, gameField &field);
void endGame(const gameSettings settings, gameField &field);

#endif // LOGIC_H