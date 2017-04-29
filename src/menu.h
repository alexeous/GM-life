#ifndef MENU_H
#define MENU_H

#include "struct.h"

bool menu(const char *filename, gameSettings &settings);	// false - выход, true - запуск игры
void menuSettings(const char *filename, gameSettings &settings);

#endif // MENU_H
