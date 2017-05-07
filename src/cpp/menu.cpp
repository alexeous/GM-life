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
    const int firstPos = centerH - 30,   // Позиция первого пункта меню
              slipL = 150, slipR = 100,   // Смещение влево и вправо относительно центра
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

// Устанавливает цвет зелёным, если текущий пункт равен аргументу
#define HIGHLIGHT_IF_CHOSEN(number) setcolor((number) == menuPoint ? GREEN : BLACK)
// Сокращённый в одну строку sprintf
#define FORMAT(format, ...) (sprintf(buffer, (format), ##__VA_ARGS__), buffer)

void menuGene(const char *filename, gameSettings &settings) {
    int menuPoint = 1;
    char key;

    while(true) {
        setbkcolor(WHITE);
        cleardevice();

        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 3); setcolor(BLACK);
        centralString(settings, -100, "GENE SETTINGS");

        settextjustify(LEFT_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 2);

        HIGHLIGHT_IF_CHOSEN(1);
        settingMenuString (settings, 1, "SOCIALITY GENE", "OFF");
        HIGHLIGHT_IF_CHOSEN(2);
        settingMenuString (settings, 2, "SURVIVAL GENE", "OFF");
        HIGHLIGHT_IF_CHOSEN(3);
        settingMenuString (settings, 3, "LAZINESS GENE", "OFF");

        settextjustify(CENTER_TEXT, CENTER_TEXT);

        HIGHLIGHT_IF_CHOSEN(4);
        centralString(settings, 85, "APPLY");
        HIGHLIGHT_IF_CHOSEN(5);
        centralString(settings, 115, "BACK");

        key = getch();
        switch(key) {
            case KEY_DOWN:  if (++menuPoint > GENE_MENU_POINTS) menuPoint = 1; break;
            case KEY_UP:    if (--menuPoint < 1) menuPoint = GENE_MENU_POINTS; break;
            case VK_RETURN:
                if(menuPoint == 5) return;  // Нажатие на "BACK"
                break;
            case VK_ESCAPE: return;    // Выход в предыдущее меню по нажатию Escape
        }
    }
}

void menuSettings(const char *filename, gameSettings &settings) {
    int fieldW = settings.fieldW,
        fieldH = settings.fieldH,
        population = settings.population,
        menuPoint = 1;
    char key = 0, buffer[5];

    while (true) {
        setbkcolor(WHITE);
        cleardevice();

        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 3); setcolor(BLACK);
        centralString(settings, -100, "SETTINGS");

        settextjustify(LEFT_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 2);

        HIGHLIGHT_IF_CHOSEN(1);
        settingMenuString (settings, 1, "FIELD WIDTH", FORMAT("% 3d", fieldW));
        HIGHLIGHT_IF_CHOSEN(2);
        settingMenuString (settings, 2, "FIELD HEIGHT", FORMAT("% 3d", fieldH));
        HIGHLIGHT_IF_CHOSEN(3);
        settingMenuString (settings, 3, "POPULATION", FORMAT("% 3d%%", population));

        settextjustify(CENTER_TEXT, CENTER_TEXT);

        HIGHLIGHT_IF_CHOSEN(4);
        centralString(settings, 75, "GENE SETTINGS");
        HIGHLIGHT_IF_CHOSEN(5);
        centralString(settings, 120, "APPLY");
        HIGHLIGHT_IF_CHOSEN(6);
        centralString(settings, 150, "MAIN MENU");

        key = getch();
        switch(key) {
            case KEY_DOWN:  if (++menuPoint > SETT_MENU_POINTS) menuPoint = 1; break;
            case KEY_UP:    if (--menuPoint < 1) menuPoint = SETT_MENU_POINTS; break;
            case KEY_LEFT:
                if ((menuPoint == 1) && (fieldW > MIN_FIELD_W)) fieldW--;
                if ((menuPoint == 2) && (fieldH > MIN_FIELD_H)) fieldH--;
                if ((menuPoint == 3) && (population > MIN_POPULATION)) population -= 10;
                break;
            case KEY_RIGHT:
                if ((menuPoint == 1) && (fieldW < MAX_FIELD_W)) fieldW++;
                if ((menuPoint == 2) && (fieldH < MAX_FIELD_H)) fieldH++;
                if ((menuPoint == 3) && (population < MAX_POPULATION)) population += 10;
                break;
            case VK_RETURN:
                switch(menuPoint) {
                    case 4: menuGene(filename, settings); break;    // Нажатие на "GENE SETTINGS"
                    case 5: applyChanges(fieldW, fieldH, population, filename, settings); break; // "APPLY"
                    case 6: return; // "MAIN MENU"
                }
                break;
            case VK_ESCAPE: return ;    // Выход в главное меню по нажатию Escape
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

        HIGHLIGHT_IF_CHOSEN(1);
        centralString(settings, 0, "START GAME");
        HIGHLIGHT_IF_CHOSEN(2);
        centralString(settings, 50, "SETTINGS");
        HIGHLIGHT_IF_CHOSEN(3);
        centralString(settings, 100, "EXIT");

        key = getch();
        switch(key) {
            case KEY_DOWN:  if(++menuPoint > MAIN_MENU_POINTS) menuPoint = 1; break;
            case KEY_UP:    if(--menuPoint < 1) menuPoint = MAIN_MENU_POINTS; break;
            case VK_RETURN:
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
