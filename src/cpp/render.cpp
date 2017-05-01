#include "const.h"
#include "event.h"
#include "graphics.h"
#include "render.h"
#include <iostream>
void outPeriod(const gameSettings settings, const gameField field) {
    static int oldPeriod = settings.period;
    static long drawStartTime = getTime();
    static bool started = true;
    int wndW = settings.windowW;
    int wndH = settings.windowH;
    
    if(settings.period != oldPeriod) {   // если игрок поменял период,
        oldPeriod = settings.period;     // то его надо вывести на экран
        drawStartTime = getTime();
        started = true;
    }
    if(getTime() - drawStartTime < PERIOD_SHOW_DURATION) {
        setfillstyle(SOLID_FILL, WHITE);
        bar(wndW - 80, wndH - 24, wndW, wndH - 8);
        settextstyle(COMPLEX_FONT, 0, 1);
        setcolor(BLACK);
        char buffer[10];
        sprintf(buffer, "%2.1f sec", settings.period / 1000.0f);
        outtextxy(wndW - 42, wndH - 11, buffer);
    }
    else if(started) {      // рисуем часть поля после последнего вывода сообщения, чтобы стереть текст, иначе 
        setfillstyle(SOLID_FILL, WHITE);    // между клетками будут виднеться черные остатки текста
        bar(wndW - 80, wndH - 24, wndW, wndH - 8);
        int i = (wndH - 24 + CELL_SIZE_PX) / (CELL_SIZE_PX + GRID_THICKNESS_PX);
        for(; i <= settings.fieldH; i++) {
            int j = (wndW - 80 + CELL_SIZE_PX) / (CELL_SIZE_PX + GRID_THICKNESS_PX);
            for(; j <= settings.fieldW; j++) {
                setfillstyle(SOLID_FILL, (field[i][j].isAlive) ? GREEN : COLOR(230, 230, 230));
                int left = (CELL_SIZE_PX) * (j - 1) + GRID_THICKNESS_PX * j;
                int top = (CELL_SIZE_PX) * (i - 1) + GRID_THICKNESS_PX * i;
                bar(left, top, left + CELL_SIZE_PX - 1, top + CELL_SIZE_PX - 1);
            }
        }
        started = false;
    }
}

void render(const gameSettings settings, const gameField field, bool drawField) {
    if(drawField) {
        for(int i = 1; i <= settings.fieldH; i++) {
            for(int j = 1; j <= settings.fieldW; j++) {
                setfillstyle(SOLID_FILL, (field[i][j].isAlive) ? GREEN : COLOR(230, 230, 230));
                int left = (CELL_SIZE_PX) * (j - 1) + GRID_THICKNESS_PX * j;
                int top = (CELL_SIZE_PX) * (i - 1) + GRID_THICKNESS_PX * i;
                bar(left, top, left + CELL_SIZE_PX - 1, top + CELL_SIZE_PX - 1);
            }
        }
    }
    outPeriod(settings, field);
}
