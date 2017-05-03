#include <iostream>
#include "graphics.h"

#include "init.h"
#include "menu.h"
#include "logic.h"
#include "render.h"

using namespace std;

int main() {
	setlocale(0, "RUS");
	const char settingsFilename[] = "settings";		// дефолтное имя файла настроек

	gameSettings settings;
	if(!init(settings, settingsFilename))
		return 1;
	
	while(menu(settingsFilename, settings)) {	// menu возвратит false, если игрок решил выйти, либо true, если решил начать игру
		gameField field;
		startGame(settings, field);
		renderField(settings, field);	// Первая отрисовка перед первым просчётом поля
		bool run = true;
		long prevFrameTime = getTime();
		do {
			event(settings, run);			// обрабатываем события (клавиатура)
			if(run && (getTime() - prevFrameTime > settings.period)) { // логика и рендер только раз в период
				prevFrameTime = getTime();	// обновляем время начала текущего кадра,
				logic(settings, field);		// обрабатываем логику игры
				renderField(settings, field);	// и рисуем поле на экране.
			}
			renderStatusBar(settings);
			delay(80);	// задержка, чтоб не грузить процессор
		} while (run);
		saveSettingsFile(settingsFilename, settings);
	}
	closegraph();
	return 0;
}
