#ifndef MENU_H
#define MENU_H

#include "struct.h"

bool menu(const char *filename, gameSettings &settings);	// false - выход, true - запуск игры
void menuSettings(const char *filename, gameSettings &settings);
bool applyChanges(const int fieldW, const int fieldH, const int population,
                  const char *filename, gameSettings &settings);
void centralString(const gameSettings settings, const int height, const char *text);
void settingMenuString(const gameSettings settings, const int number,
                       const char *textLeft, const char *textRight)

#endif // MENU_H
