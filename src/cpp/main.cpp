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
		gameField oldField;    // Два поля: для сохранения текущего состояния
		gameField newField;    // и для просчета нового хода
		startGame(settings, oldField);    // Инициализируем поля
		startGame(settings, newField);
		render(settings, oldField, true);	// Первая отрисовка перед первым просчётом поля
		bool run = true;
		long prevFrameTime = getTime();
		do {
			event(settings, run);			// обрабатываем события (клавиатура)
			if(run && (getTime() - prevFrameTime > settings.period)) { // логика и рендер только раз в период
				prevFrameTime = getTime();	// обновляем время начала текущего кадра,
				logic(settings, oldField, newField);		// обрабатываем логику игры
				render(settings, oldField, true);	// и рисуем поле на экране.
			}
			else render(settings, oldField, false);	// render без перерисовки поля
			delay(20);	// задержка, чтоб не грузить процессор
		} while (run);
		saveSettingsFile(settingsFilename, settings);
	}
	closegraph();
	return 0;
}
