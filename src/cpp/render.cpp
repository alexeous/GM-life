#include "const.h"
#include "event.h"
#include "graphics.h"
#include "render.h"
#include "struct.h"
#include <iostream>

int calculateCellColor(const gameSettings settings, const cell c) {
    int red = 71, green = 181, blue = 16;
    if (c.isAlive) {
        if (settings.socialGene) {
            int activeGene = c.socialGene;
            red = socialRed[activeGene];
            green = socialGreen[activeGene];
            blue = socialBlue[activeGene];
        }
        return COLOR(red, green, blue);
    }
    else return COLOR(230, 230, 230);
}

inline int mulColor(const int color, const float factor) {
    byte r = (color & 0xFF) * factor;
    byte g = ((color >> 8) & 0xFF) * factor;
    byte b = ((color >> 16) & 0xFF) * factor;
    return COLOR(r, g, b);
}

void renderField(const gameSettings settings, gameField &field) {
    for(int i = 1; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW; j++) {
            cell &c = field[i][j];
            if (c.needRefresh) {
                int left = calcCellLeft(j), top = calcCellTop(i);
                int off = CELL_SIZE_PX - 1;
                int color = calculateCellColor(settings, c);
                setfillstyle(SOLID_FILL, color);
                bar(left, top, left + off, top + off);

                if (c.isAlive) {
                    if(c.maxHealth > 1) {
                        int rate = c.maxHealth - 1;
                        setfillstyle(SOLID_FILL, mulColor(color, 0.65f));
                        bar(left, top, left + rate, top + off);
                        bar(left + rate, top + off - rate, left + off, top + off);
                    }
                    if(c.isLazy) {
                        int centerW = left + CELL_SIZE_PX / 2;
                        int centerH = top + CELL_SIZE_PX / 2;
                        setcolor(~color & 0xFFFFFF);
                        line(centerW, centerH - 4, centerW + 3, centerH - 1);
                        line(centerW, centerH - 1, centerW + 3, centerH - 4);
                    }
                }
                c.needRefresh = false;
            }
        }
    }
}

void outPeriod(const gameSettings settings) {
    int wndW = settings.windowW, wndH = settings.windowH;
    setfillstyle(SOLID_FILL, WHITE);
    bar(wndW - 105, wndH - STATUS_BAR_HEIGHT, wndW - 48, wndH);   // очистка старой надписи
    settextstyle(COMPLEX_FONT, 0, 1);
    settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
    setcolor(DARKGRAY);
    char buffer[20];
    sprintf(buffer, "%2.1f s     ", settings.period / 1000.0f);
    outtextxy(wndW, wndH, buffer);
}

void outPause(const gameSettings settings) {
    int wndH = settings.windowH;
    settextjustify(LEFT_TEXT, BOTTOM_TEXT);
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(DARKGRAY);
    bar(110, wndH - STATUS_BAR_HEIGHT, 250, wndH);
    bar3d(115, wndH - 19, 170, wndH - 2, 2, true);
    outtextxy(118, wndH, settings.pause ? "Space unpause" : "Space pause");
}

void renderStatusBar(const gameSettings settings, bool firstDraw) {
    static int oldPeriod = -1;
    if(firstDraw || oldPeriod != settings.period) {
        oldPeriod = settings.period;
        outPeriod(settings);
    }
    static bool oldPause = false;
    if(firstDraw || oldPause != settings.pause) {
        oldPause = settings.pause;
        outPause(settings);
    }
    if(firstDraw) {
        int wndW = settings.windowW, wndH = settings.windowH;
        setcolor(DARKGRAY);
        settextstyle(COMPLEX_FONT, 0, 1);
        settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
        bar3d(wndW - 22, wndH - 17, wndW - 8, wndH - 3, 2, true);
        bar3d(wndW - 42, wndH - 17, wndW - 28, wndH - 3, 2, true);

        line(wndW - 11, wndH - 10, wndW - 17, wndH - 10);
        line(wndW - 19, wndH - 10, wndW - 15, wndH - 14);
        line(wndW - 19, wndH - 10, wndW - 15, wndH - 6);
        line(wndW - 40, wndH - 10, wndW - 31, wndH -10);
        line(wndW - 31, wndH -10, wndW - 35, wndH - 14);
        line(wndW - 31, wndH -10, wndW - 35, wndH - 6);

        bar3d(1, wndH - 19, 36, wndH - 2, 2, true);
        settextjustify(LEFT_TEXT, BOTTOM_TEXT);
        outtextxy(4, wndH, "Esc menu");
    }
}
