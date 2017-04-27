#include <stdio.h>
#include "settings.h"

bool validateSettings(const gameSettings settings) {
	return (settings.fieldW > 0 && settings.fieldW <= MAX_FIELD_W) &&
		   (settings.fieldH > 0 && settings.fieldH <= MAX_FIELD_H);
}

bool loadSettingsFile(const char *filename, gameSettings &settings) {
	FILE *settingsFile = fopen(filename, "r");
	if(!settingsFile)
		return false;	// не удалось открыть
	if(!fread(&settings, sizeof(gameSettings), 1, settingsFile)) {
		fclose(settingsFile);
		return false;	// не удалось считать
	}
	fclose(settingsFile);
	return validateSettings(settings);
}

int initSettings(const char *filename, gameSettings &settings) {
	if(!loadSettingsFile(filename, settings)) {
		FILE *newSettingsFile = fopen(filename, "w");
		if(!newSettingsFile)
			return 1;	// не удалось создать новый
		if(!fwrite(&defaultSettings, sizeof(gameSettings), 1, newSettingsFile)) {	// defaultSettings - в struct.h
			fclose(newSettingsFile);
			return 1;	// не удалось записать в новый
		}
		fclose(newSettingsFile);
		return 2;		// успешно создан новый
	}
	else return 0;		// загрузка успешна
}