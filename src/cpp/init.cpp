#include "init.h"

using namespace std;

bool init(gameSettings &settings, const char *settingsFilename) {
    switch(initSettings(settingsFilename, settings)) {
	case 1:
		cout << "Не удалось ни загрузить старый файл настроек, ни создать новый.\n";
		return false;
	case 2:
		cout << "Был создан новый файл настроек, так как старый не удалось загрузить.\n";
		fflush(stdout);
	}
	initTime();
	initwindow(settings.windowW, settings.windowH, "GM-life");
    return true;
}
