#ifndef MENU_H
#define MENU_H

#define MAIN_MENU_POINTS 3
#define SETT_MENU_POINTS 8

#include "struct.h"

bool menu(const char *filename, gameSettings &settings);	// false - выход, true - запуск игры
void menuSettings(const char *filename, gameSettings &settings);
bool applyChanges(const char *filename, gameSettings &dest, gameSettings src);
void centralString(const gameSettings settings, const int height, const char *text);
void settingMenuString(const gameSettings settings, const int number,
                       const char *textLeft, const char *textRight);

#endif // MENU_H
