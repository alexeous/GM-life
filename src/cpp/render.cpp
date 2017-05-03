#include "const.h"
#include "event.h"
#include "graphics.h"
#include "render.h"
#include <iostream>

void outPeriod(const gameSettings settings) {
    settextstyle(COMPLEX_FONT, 0, 1);
    setcolor(DARKGRAY);
    char buffer[20];
    sprintf(buffer, "%2.1f sec", settings.period / 1000.0f);
    outtextxy(settings.windowW - 40, settings.windowH - 5, buffer);
}

void renderField(const gameSettings settings, const gameField field) {
    for(int i = 1; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW; j++) {
            setfillstyle(SOLID_FILL, (field[i][j].isAlive) ? GREEN : COLOR(230, 230, 230));
            int left = (CELL_SIZE_PX) * (j - 1) + GRID_THICKNESS_PX * j;
            int top = (CELL_SIZE_PX) * (i - 1) + GRID_THICKNESS_PX * i;
            bar(left, top, left + CELL_SIZE_PX - 1, top + CELL_SIZE_PX - 1);
        }
    }
}

void renderStatusBar(const gameSettings settings) {
    setfillstyle(SOLID_FILL, WHITE);
    bar(0, settings.windowH - STATUS_BAR_HEIGHT, settings.windowW, settings.windowH);   // очистка статусбара
    outPeriod(settings);
}