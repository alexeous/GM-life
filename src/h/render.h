#ifndef RENDER_H
#define RENDER_H

#include "struct.h"

void outPeriod(const gameSettings settings);
int calculateCellColor(const gameSettings settings, const gameField field,
                       const int h, const int w);
void renderField(const gameSettings settings, const gameField field);
void renderStatusBar(const gameSettings settings, bool firstDraw = false);    // firstDraw - принудительно отрисовать

#endif // RENDER_H
