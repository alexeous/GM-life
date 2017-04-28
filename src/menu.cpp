#include "menu.h"
#include "const.h"
#include "graphics.h"
#include "conio.h"
#include <stdio.h>

void menuSettings(gameSettings &settings) {
    int fieldW = settings.fieldW,
        fieldH = settings.fieldH,
        menuPoint = 1;
    char key = 0, strFieldW[4], strFieldH[4];

    while (true) {
        setbkcolor(WHITE);
        cleardevice();

        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 4); setcolor(BLACK);
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2,
                  (settings.fieldH * CELL_SIZE_PX) / 2 - 100, (char*)"SETTINGS");

        settextjustify(LEFT_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 3);

        if (menuPoint == 1) setcolor(GREEN);
        else setcolor(BLACK);
        sprintf(strFieldW, "% 3d", fieldW);
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2 - 130,
                  (settings.fieldH * CELL_SIZE_PX) / 2, (char*)"FIELD WIDTH");
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2 + 80,
                  (settings.fieldH * CELL_SIZE_PX) / 2, strFieldW);

        if (menuPoint == 2) setcolor(GREEN);
        else setcolor(BLACK);
        sprintf(strFieldH, "% 3d", fieldH);
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2 - 130,
                  (settings.fieldH * CELL_SIZE_PX) / 2 + 30, (char*)"FIELD HEIGHT");
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2 + 80,
                  (settings.fieldH * CELL_SIZE_PX) / 2 + 30, strFieldH);

        settextjustify(CENTER_TEXT, CENTER_TEXT);

        if (menuPoint == 3) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2,
                  (settings.fieldH * CELL_SIZE_PX) / 2 + 90, (char*)"APPLY");

        if (menuPoint == 4) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2,
                  (settings.fieldH * CELL_SIZE_PX) / 2 + 120, (char*)"MAIN MENU");

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
            if (menuPoint == 3) {
                settings.fieldW = fieldW;
                settings.fieldH = fieldH;
                closegraph();
                initwindow(settings.fieldW * CELL_SIZE_PX,
                           settings.fieldH * CELL_SIZE_PX);
            }
            if (menuPoint == 4) {
                return ;
            }
        }
    }
}

bool menu(gameSettings &settings) {
    int menuPoint = 1;
    char key = 0;

    initwindow(settings.fieldW * CELL_SIZE_PX, settings.fieldH * CELL_SIZE_PX);
    while (true) {
        setbkcolor(WHITE);
        cleardevice();
        settextjustify(CENTER_TEXT, CENTER_TEXT);

        settextstyle(COMPLEX_FONT, 0, 5); setcolor(BLACK);
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2,
                  (settings.fieldH * CELL_SIZE_PX) / 2 - 100, (char*)"GM-life");

        settextstyle(COMPLEX_FONT, 0, 4);
        if (menuPoint == 1) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2,
                  (settings.fieldH * CELL_SIZE_PX) / 2, (char*)"START GAME");

        if (menuPoint == 2) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2,
                  (settings.fieldH * CELL_SIZE_PX) / 2 + 50, (char*)"SETTINGS");

        if (menuPoint == 3) setcolor(GREEN);
        else setcolor(BLACK);
        outtextxy((settings.fieldW * CELL_SIZE_PX) / 2,
                  (settings.fieldH * CELL_SIZE_PX) / 2 + 100, (char*)"EXIT");

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
                closegraph(); return true;
            case 2:    // Нажатие на "SETTINGS"
                menuSettings(settings); break;
            case 3:    // Нажатие на "EXIT"
                closegraph(); return false;
            }
        }
    }
}
