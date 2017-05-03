#ifndef RENDER_H
#define RENDER_H

#include "struct.h"

void outPeriod(const gameSettings settings);
void renderField(const gameSettings settings, const gameField field);
void renderStatusBar(const gameSettings settings, bool firstDraw = false);    // firstDraw - принудительно отрисовать

#endif // RENDER_H