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
    const int firstPos = centerH - 90,   // Позиция первого пункта меню
              slipL = 150, slipR = 100,   // Смещение влево и вправо относительно центра
              strHeight = 30;
    outtextxy(centerW - slipL, firstPos + strHeight * (number - 1), (char*)textLeft);
    outtextxy(centerW + slipR, firstPos + strHeight * (number - 1), (char*)textRight);
}

bool applyChanges(const char *filename, gameSettings &dest, gameSettings src) {
    if (validateSettings(src)) {
        src.windowW = calcWindowW(src.fieldW);
        src.windowH = calcWindowH(src.fieldH);
        if ((src.fieldW != dest.fieldW) ||
            (src.fieldH != dest.fieldH)) {
                closegraph();
                initwindow(src.windowW, src.windowH, "GM-life");
        }
        dest = src;
        saveSettingsFile(filename, dest);
        return true;
    } else return false;    // Если настройки приняли недопустимые значения
}

// Устанавливает цвет зелёным, если текущий пункт равен аргументу
#define HIGHLIGHT_IF_CHOSEN(number) setcolor((number) == menuPoint ? GREEN : BLACK)
// Сокращённый в одну строку sprintf
#define FORMAT(format, ...) (sprintf(buffer, (format), ##__VA_ARGS__), buffer)

void menuSettings(const char *filename, gameSettings &settings) {
    int menuPoint = 1;
    gameSettings tempSet = settings;
    char key, buffer[10];

    while (true) {
        setbkcolor(WHITE);
        cleardevice();

        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 3); setcolor(BLACK);
        centralString(settings, -150, "SETTINGS");

        settextjustify(LEFT_TEXT, CENTER_TEXT);
        settextstyle(COMPLEX_FONT, 0, 2);

        HIGHLIGHT_IF_CHOSEN(1);
        settingMenuString (tempSet, 1, "FIELD WIDTH", FORMAT("% 3d", tempSet.fieldW));
        HIGHLIGHT_IF_CHOSEN(2);
        settingMenuString (tempSet, 2, "FIELD HEIGHT", FORMAT("% 3d", tempSet.fieldH));
        HIGHLIGHT_IF_CHOSEN(3);
        settingMenuString (tempSet, 3, "POPULATION", FORMAT("% 3d%%", tempSet.population));
        HIGHLIGHT_IF_CHOSEN(4);
        settingMenuString (tempSet, 4, "SOCIALITY GENE", tempSet.socialGene ? " ON" : " OFF");
        HIGHLIGHT_IF_CHOSEN(5);
        settingMenuString (tempSet, 5, "SURVIVAL GENE", tempSet.survivalGene ? " ON" : " OFF");
        HIGHLIGHT_IF_CHOSEN(6);
        settingMenuString (tempSet, 6, "LAZINESS GENE", tempSet.lazyGene ? " ON" : " OFF");
        HIGHLIGHT_IF_CHOSEN(7);
        settingMenuString (tempSet, 7, "AGING", tempSet.aging ? " ON" : " OFF");

        settextjustify(CENTER_TEXT, CENTER_TEXT);

        HIGHLIGHT_IF_CHOSEN(8);
        centralString(tempSet, 120, "APPLY");
        HIGHLIGHT_IF_CHOSEN(9);
        centralString(tempSet, 150, "CANCEL");

        key = getch();
        switch(key) {
        case KEY_DOWN:  if (++menuPoint > SETT_MENU_POINTS) menuPoint = 1; break;
        case KEY_UP:    if (--menuPoint < 1) menuPoint = SETT_MENU_POINTS; break;
        case KEY_LEFT:
            switch(menuPoint) {
                case 1:     if(tempSet.fieldW > MIN_FIELD_W) tempSet.fieldW--;  break;
                case 2:     if(tempSet.fieldH > MIN_FIELD_H) tempSet.fieldH--;  break;
                case 3:     if(tempSet.population > MIN_POPULATION) tempSet.population -= 10; break;
                case 4:     tempSet.socialGene = !tempSet.socialGene;
                            if(tempSet.lazyGene) tempSet.lazyGene = false; break;
                case 5:     tempSet.survivalGene = !tempSet.survivalGene; break;
                case 6:     tempSet.lazyGene = !tempSet.lazyGene;
                            if(!tempSet.socialGene) tempSet.socialGene = true; break;
                case 7:     tempSet.aging = !tempSet.aging; break;
            }
            break;
        case KEY_RIGHT:
            switch(menuPoint) {
                case 1:     if(tempSet.fieldW < MAX_FIELD_W) tempSet.fieldW++;  break;
                case 2:     if(tempSet.fieldH < MAX_FIELD_H) tempSet.fieldH++;  break;
                case 3:     if(tempSet.population < MAX_POPULATION) tempSet.population += 10; break;
                case 4:     tempSet.socialGene = !tempSet.socialGene;
                            if(tempSet.lazyGene) tempSet.lazyGene = false; break;
                case 5:     tempSet.survivalGene = !tempSet.survivalGene; break;
                case 6:     tempSet.lazyGene = !tempSet.lazyGene;
                            if(!tempSet.socialGene) tempSet.socialGene = true; break;
                case 7:     tempSet.aging = !tempSet.aging; break;
            }
            break;
        case VK_RETURN:
            switch(menuPoint) {
                case 8: applyChanges(filename, settings, tempSet); // "APPLY"
                        return;
                case 9: return; // "CANCEL"
            }
            break;
        case VK_ESCAPE: return;    // Выход в главное меню по нажатию Escape
        }
    }
}

bool menu(const char *filename, gameSettings &settings) {
    int menuPoint = 1;
    char key;

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
