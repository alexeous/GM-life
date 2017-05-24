#ifndef LOGIC_H
#define LOGIC_H

#include <stdlib.h>
#include <string.h>
#include "struct.h"

void firstBorn(const gameSettings settings, cell &newcell);
void bornCell(const gameField oldField, gameField &newField, const int h, const int w);
void harmCell(cell &c);
void cellAging(const gameSettings settings, cell &c);

bool wouldMigrateTo(const gameSettings settings, gameField field, int h, int w, int toH, int toW);
void migrateCell(const gameSettings settings, gameField &field, const int h, const int w);

void startGame(const gameSettings settings, gameField &field);
void logic(const gameSettings settings, gameField &oldField);
// Количество живых соседей клетки. Если neighbors_out не NULL, запсывает по этому адресу массив живых соседей
int neighborsAlive(const gameField field, const int h, const int w, cell *neighbors_out = NULL); 
void copyField(const gameSettings settings, gameField &dest, const gameField src);  // копирует поле из src в dest

#endif // LOGIC_H
