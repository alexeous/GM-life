#include "const.h"
#include "event.h"
#include "graphics.h"
#include "render.h"

void outPeriod(const gameSettings settings) {
    static int oldPeriod = settings.period;
    static long drawStartTime = getTime();
    static bool started = true;         
    
    if(settings.period != oldPeriod) {   // если игрок поменял период,
        oldPeriod = settings.period;     // то его надо вывести на экран
        drawStartTime = getTime();
        started = true;
    }
    if(getTime() - drawStartTime < PERIOD_SHOW_DURATION) {
        setfillstyle(SOLID_FILL, WHITE);
        bar(settings.windowW - 80, settings.windowH - 24, 
            settings.windowW, settings.windowH - 8);
        settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
        settextstyle(COMPLEX_FONT, 0, 1);
        setcolor(BLACK);
        char buffer[10];
        sprintf(buffer, "%2.1f sec", settings.period / 1000.0f);
        outtextxy(settings.windowW - 5, settings.windowH - 5, buffer);
    }
    else if(started) {      // рисуем белый прямоугольник в последний раз, чтобы стереть текст, иначе 
        setfillstyle(SOLID_FILL, WHITE);    // между клетками будут виднеться черные остатки текста
        bar(settings.windowW - 80, settings.windowH - 24, 
            settings.windowW, settings.windowH - 8);
        started = false;
    }
}

void render(const gameSettings settings, const gameField field, bool drawField) {
    if(drawField) {
        for(int i = 1; i <= settings.fieldH; i++) {
            for(int j = 1; j <= settings.fieldW ; j++) {
                if (field[i][j].isAlive) setfillstyle(SOLID_FILL, GREEN);    // клетка живая - зеленый
                else setfillstyle(SOLID_FILL, COLOR(230, 230, 230));         // мертвая - серый
                int left = (CELL_SIZE_PX) * (j - 1) + GRID_THICKNESS_PX * j;
                int top = (CELL_SIZE_PX) * (i - 1) + GRID_THICKNESS_PX * i;
                bar(left, top, left + CELL_SIZE_PX - 1, top + CELL_SIZE_PX - 1);
            }
        }
    }
    outPeriod(settings);
}
