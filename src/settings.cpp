#include <stdio.h>
#include "const.h"
#include "settings.h"

bool validateSettings(const gameSettings settings) {
	return (settings.fieldW >= MIN_FIELD_W && settings.fieldW <= MAX_FIELD_W) &&
		   (settings.fieldH >= MIN_FIELD_H && settings.fieldH <= MAX_FIELD_H);
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

bool saveSettingsFile(const char *filename, const gameSettings settings) {
	FILE *settingsFile = fopen(filename, "w");
	if(!settingsFile)
		return false;	// не удалось создать
	if(!fwrite(&settings, sizeof(gameSettings), 1, settingsFile)) {
		fclose(settingsFile);
		return false;	// не удалось записать
	}
	fclose(settingsFile);
	return true;
}

int initSettings(const char *filename, gameSettings &settings) {
	if(!loadSettingsFile(filename, settings)) {
		settings = defaultSettings;
		bool recreateSucceed = saveSettingsFile(filename, defaultSettings); 		// defaultSettings - в struct.h
		return  recreateSucceed ? 2 : 1; 	// 2 - успешно создан новый, 1 - не удалось создать новый
	}
	else return 0;		// загрузка успешна
}
