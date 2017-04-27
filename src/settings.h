#ifndef SETTINGS_H
#define SETTINGS_H

#include "struct.h"

bool validateSettings(const gameSettings settings);
bool loadSettingsFile(const char *filename, gameSettings &settings);	// только пытается загрузить файл
int initSettings(const char *filename, gameSettings &settings);			// в случае неудачи загрузки файла пытается создать новый

#endif // SETTINGS_H