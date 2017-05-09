#ifndef LOGIC_H
#define LOGIC_H

#include <stdlib.h>
#include <string.h>
#include "struct.h"

void firstBorn(gameField &field, const int h, const int w);
void bornCell(const gameField oldField, gameField &newField, const int h, const int w);
void harmCell(gameField &field, const int h, const int w);
void moveCell(const gameSettings settings, const gameField oldField,
              gameField &newField, const int h, const int w);
void startGame(const gameSettings settings, gameField &field);
void logic(const gameSettings settings, gameField &oldField);
int neighborsAlive(const gameField field, const int h, const int w); // кол-во живый соседей клетки
void copyField(const gameSettings settings, gameField &dest, const gameField src);  // копирует поле из src в dest

#endif // LOGIC_H
