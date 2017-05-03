#ifndef LOGIC_H
#define LOGIC_H

#include "struct.h"

void startGame(const gameSettings settings, gameField &field);
void logic(const gameSettings settings, gameField &oldField, gameField &newField);
int neighborsAlive(const gameField field, const int h, const int w); 
void copyField(const gameSettings settings, gameField &dest, const gameField src);  // копирует поле из src в dest

#endif // LOGIC_H
