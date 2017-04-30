#include "menu.h"
#include "const.h"
#include "settings.h"
#include "graphics.h"
#include "conio.h"
#include <stdio.h>

void menuSettings (const char *filename, gameSettings &settings) {
    int fieldW = settings.fieldW,
        fieldH = settings.fieldH,
        menuPoint = 1;
    char key = 0, strFieldW[4], strFieldH[4];

    while (true) {
        setbkcolor(WHITE);
        cleardevice();

        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 3); setcolor(BLACK);
        outtextxy((settings.windowW) / 2,
                  (settings.windowH) / 2 - 100, (char*)"SETTINGS");

        settextjustify(LEFT_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 2);

        if (menuPoint == 1) setcolor(GREEN);
        else setcolor(BLACK);
        sprintf(strFieldW, "% 3d", fieldW);
        outtextxy((settings.windowW) / 2 - 130,
                  (settings.windowH) / 2, (char*)"FIELD WIDTH");
        outtextxy((settings.windowW) / 2 + 80,
                  (settings.windowH) / 2, strFieldW);

        if (menuPoint == 2) setcolor(GREEN);
        else setcolor(BLACK);
        sprintf(strFieldH, "% 3d", fieldH);
        outtextxy((settings.windowW) / 2 - 130,
                  (settings.windowH) / 2 + 30, (char*)"FIELD HEIGHT");
        outtextxy((settings.windowW) / 2 + 80,
                  (settings.windowH) / 2 + 30, strFieldH);

        settextjustify(CENTER_TEXT, CENTER_TEXT);

        if (menuPoint == 3) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.windowW) / 2,
                  (settings.windowH) / 2 + 90, (char*)"APPLY");

        if (menuPoint == 4) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.windowW) / 2,
                  (settings.windowH) / 2 + 120, (char*)"MAIN MENU");

        key = getch();
        if (key == KEY_DOWN) {
            if (menuPoint == 4) menuPoint = 1; else menuPoint++;
        }
        if (key == KEY_UP) {
            if (menuPoint == 1) menuPoint = 4; else menuPoint--;
        }
        if (key == KEY_LEFT) {
            if ((menuPoint == 1) && (fieldW > MIN_FIELD_W)) fieldW--;
            if ((menuPoint == 2) && (fieldH > MIN_FIELD_H)) fieldH--;
        }
        if (key == KEY_RIGHT) {
            if ((menuPoint == 1) && (fieldW < MAX_FIELD_W)) fieldW++;
            if ((menuPoint == 2) && (fieldH < MAX_FIELD_H)) fieldH++;
        }

        if (key == VK_RETURN) {
            if (menuPoint == 3) {    // Нажатие на "APPLY"
                settings.fieldW = fieldW;
                settings.fieldH = fieldH;
                settings.windowW = fieldW * CELL_SIZE_PX + (fieldW + 1) * GRID_THICKNESS_PX;    // Включая сетку между
                settings.windowH = fieldH * CELL_SIZE_PX + (fieldH + 1) * GRID_THICKNESS_PX;    // клетками и по краям
                saveSettingsFile(filename, settings);
                closegraph();
                initwindow(settings.windowW, settings.windowH);
            }
            if (menuPoint == 4) return ;    // Нажатие на "MAIN MENU"
        }
    }
}

bool menu(const char *filename, gameSettings &settings) {
    int menuPoint = 1;
    char key = 0;

    while (true) {
        setbkcolor(WHITE);
        cleardevice();
        settextjustify(CENTER_TEXT, CENTER_TEXT);

        settextstyle(COMPLEX_FONT, 0, 4); setcolor(BLACK);
        outtextxy((settings.windowW) / 2,
                  (settings.windowH) / 2 - 100, (char*)"GM-life");

        settextstyle(COMPLEX_FONT, 0, 3);
        if (menuPoint == 1) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.windowW) / 2,
                  (settings.windowH) / 2, (char*)"START GAME");

        if (menuPoint == 2) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.windowW) / 2,
                  (settings.windowH) / 2 + 50, (char*)"SETTINGS");

        if (menuPoint == 3) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.windowW) / 2,
                  (settings.windowH) / 2 + 100, (char*)"EXIT");

        key = getch();
        if (key == KEY_DOWN) {
            if (menuPoint == 3) menuPoint = 1; else menuPoint++;
        }
        if (key == KEY_UP) {
            if (menuPoint == 1) menuPoint = 3; else menuPoint--;
        }

        if (key == VK_RETURN) {
            switch (menuPoint) {
            case 1:    // Нажатие на "START GAME"
                return true;
            case 2:    // Нажатие на "SETTINGS"
                menuSettings(filename, settings); break;
            case 3:    // Нажатие на "EXIT"
                closegraph(); return false;
            }
        }
    }
}
