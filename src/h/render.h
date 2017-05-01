#ifndef RENDER_H
#define RENDER_H

#include "struct.h"

void outPeriod(const gameSettings settings, const gameField field);
void render(const gameSettings settings, const gameField field, bool drawField);

#endif // RENDER_H