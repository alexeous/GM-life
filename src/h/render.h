#ifndef RENDER_H
#define RENDER_H

#include "struct.h"

void outPeriod(const gameSettings settings);
void outPause(const gameSettings settings);
inline int mulColor(const int color, const float factor);
int calculateCellColor(const gameSettings settings, const cell c);
void renderField(const gameSettings settings, gameField &field);
void renderStatusBar(const gameSettings settings, bool firstDraw = false);    // firstDraw - принудительно отрисовать

#endif // RENDER_H
