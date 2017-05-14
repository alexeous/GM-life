#include "const.h"
#include "event.h"
#include "graphics.h"
#include "render.h"
#include "struct.h"
#include <iostream>

void outPeriod(const gameSettings settings) {
    int wndW = settings.windowW, wndH = settings.windowH;
    setfillstyle(SOLID_FILL, WHITE);
    bar(wndW - 105, wndH - STATUS_BAR_HEIGHT, wndW - 45, wndH);   // очистка старой надписи
    settextstyle(COMPLEX_FONT, 0, 1);
    settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
    setcolor(DARKGRAY);
    char buffer[20];
    sprintf(buffer, "%2.1f s + - ", settings.period / 1000.0f);
    bar3d(wndW - 22, wndH - 17, wndW - 8, wndH - 3, 2, true);
    bar3d(wndW - 42, wndH - 17, wndW - 28, wndH - 3, 2, true);
    outtextxy(wndW, wndH, buffer);
}

int changeCellColor(const gameField field, const int i, const int j){
    int x, y;
    if(!field[i][j].isAlive) return COLOR(230, 230, 230);
    else {
        x = (127 * field[i][j].health) / field[i][j].maxHealth;
        y = 127 - x;
        return COLOR(y, x, 0);
    }
}

void renderField(const gameSettings settings, const gameField field){
    for(int i = 1; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW; j++) {
            setfillstyle(SOLID_FILL, (field[i][j].isAlive) ? changeCellColor(field, i, j): changeCellColor(field, i, j));
            int left = (CELL_SIZE_PX) * (j - 1) + GRID_THICKNESS_PX * j;
            int top = (CELL_SIZE_PX) * (i - 1) + GRID_THICKNESS_PX * i;
            bar(left, top, left + CELL_SIZE_PX - 1, top + CELL_SIZE_PX - 1);
        }
    }
}

void renderStatusBar(const gameSettings settings, bool firstDraw) {
    static int oldPeriod = -1;
    if(firstDraw || oldPeriod != settings.period) {
        oldPeriod = settings.period;
        outPeriod(settings);
    }
    if(firstDraw) {
        settextstyle(COMPLEX_FONT, 0, 1);
        settextjustify(LEFT_TEXT, BOTTOM_TEXT);
        setcolor(DARKGRAY);
        bar3d(1, settings.windowH - 19, 36, settings.windowH - 2, 2, true);
        outtextxy(4, settings.windowH, "Esc menu");
    }
}
