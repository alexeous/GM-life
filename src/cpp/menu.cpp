#include "menu.h"
#include "const.h"
#include "settings.h"
#include "graphics.h"
#include "stdio.h"

void centralString(const gameSettings settings, const int height, const char *text) {
    int centerW = settings.windowW / 2,
        centerH = settings.windowH / 2;
    outtextxy(centerW, centerH + height, (char*)text);
}

// number - номер пункта, textLeft - название параметра, textRight - значение параметра
void settingMenuString(const gameSettings settings, const int number,
                       const char *textLeft, const char *textRight) {
    int centerW = settings.windowW / 2,
        centerH = settings.windowH / 2;
    const int firstPos = centerH,   // Позиция первого пункта меню
              slipL = 130, slipR = 80,   // Смещение влево и вправо относительно центра
              strHeight = 30;
    outtextxy(centerW - slipL, firstPos + strHeight * (number - 1), (char*)textLeft);
    outtextxy(centerW + slipR, firstPos + strHeight * (number - 1), (char*)textRight);
}

bool applyChanges(const int fieldW, const int fieldH, const int population,
                  const char *filename, gameSettings &settings) {
    gameSettings tempSettings = settings;
    tempSettings.fieldW = fieldW;
    tempSettings.fieldH = fieldH;
    tempSettings.windowW = fieldW * CELL_SIZE_PX + (fieldW + 1) * GRID_THICKNESS_PX;
    tempSettings.windowH = fieldH * CELL_SIZE_PX + (fieldH + 1) * GRID_THICKNESS_PX
                                                            + STATUS_BAR_HEIGHT;
    tempSettings.population = population;
    if (validateSettings(tempSettings)) {
        settings = tempSettings;
        saveSettingsFile(filename, settings);
        closegraph();
        initwindow(settings.windowW, settings.windowH, "GM-life");
        return true;
    } else return false;    // Если настройки приняли недопустимые значения
}

void menuSettings(const char *filename, gameSettings &settings) {
    int fieldW = settings.fieldW,
        fieldH = settings.fieldH,
        population = settings.population,
        menuPoint = 1;
    char key = 0, strFieldW[4], strFieldH[4], strPopulation[4];

    while (true) {
        setbkcolor(WHITE);
        cleardevice();

        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 3); setcolor(BLACK);
        centralString(settings, -100, "SETTINGS");

        settextjustify(LEFT_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 2);

        if (menuPoint == 1) setcolor(GREEN);
            else setcolor(BLACK);
        sprintf(strFieldW, "% 3d", fieldW);
        settingMenuString (settings, 1, "FIELD WIDTH", strFieldW);

        if (menuPoint == 2) setcolor(GREEN);
            else setcolor(BLACK);
        sprintf(strFieldH, "% 3d", fieldH);
        settingMenuString (settings, 2, "FIELD HEIGHT", strFieldH);

        if (menuPoint == 3) setcolor(GREEN);
            else setcolor(BLACK);
        sprintf(strPopulation, "% 3d%%", population);
        settingMenuString (settings, 3, "POPULATION", strPopulation);

        settextjustify(CENTER_TEXT, CENTER_TEXT);

        if (menuPoint == 4) setcolor(GREEN);
        else setcolor(BLACK);
        centralString(settings, 120, "APPLY");

        if (menuPoint == 5) setcolor(GREEN);
        else setcolor(BLACK);
        centralString(settings, 150, "MAIN MENU");

        key = getch();
        if (key == KEY_DOWN) {
            if (menuPoint == 5) menuPoint = 1; else menuPoint++;
        }
        if (key == KEY_UP) {
            if (menuPoint == 1) menuPoint = 5; else menuPoint--;
        }
        if (key == KEY_LEFT) {
            if ((menuPoint == 1) && (fieldW > MIN_FIELD_W)) fieldW--;
            if ((menuPoint == 2) && (fieldH > MIN_FIELD_H)) fieldH--;
            if ((menuPoint == 3) && (population > MIN_POPULATION)) population -= 10;
        }
        if (key == KEY_RIGHT) {
            if ((menuPoint == 1) && (fieldW < MAX_FIELD_W)) fieldW++;
            if ((menuPoint == 2) && (fieldH < MAX_FIELD_H)) fieldH++;
            if ((menuPoint == 3) && (population < MAX_POPULATION)) population += 10;
        }

        if (key == VK_RETURN) {
            if (menuPoint == 4) {    // Нажатие на "APPLY"
                applyChanges(fieldW, fieldH, population, filename, settings);
            }
            if (menuPoint == 5) return ;    // Нажатие на "MAIN MENU"
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
        centralString(settings, -100, "GM-life");

        settextstyle(COMPLEX_FONT, 0, 3);
        if (menuPoint == 1) setcolor(GREEN);
        else setcolor(BLACK);
        centralString(settings, 0, "START GAME");

        if (menuPoint == 2) setcolor(GREEN);
        else setcolor(BLACK);
        centralString(settings, 50, "SETTINGS");

        if (menuPoint == 3) setcolor(GREEN);
        else setcolor(BLACK);
        centralString(settings, 100, "EXIT");

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
                cleardevice(); return true;
            case 2:    // Нажатие на "SETTINGS"
                menuSettings(filename, settings); break;
            case 3:    // Нажатие на "EXIT"
                closegraph(); return false;
            }
        }
    }
}
