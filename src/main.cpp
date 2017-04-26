#include "conio.h"
#include "graphics.h"

#include "struct.h"
#include "settings.h"
#include "menu.h"
#include "logic.h"
#include "render.h"

using namespace std;

int main() {
	const char settingsFilename[] = "settings";		// дефолтное имя файла настроек
	gameSettings settings;			// настройки игры
	if(!loadSettings(settingsFilename, settings)) {
		return 1;					// на этом моменте можно попробовать создать новый файл с настройками
	}
	while(menu(settings)) {		// menu возвратит false, если игрок решил выйти, либо true, если решил начать игру
		gameField field;		// поле игры
		startGame(settings, field); 	// открываем игровое окно, инициализируем поле
		do {
			logic(settings, field);		// обрабатываем логику игры
			render(settings, field);	// рисуем на экране
		} while (!kbhit() && getch() != 27);	// пока не нажали Escape
		endGame();			// закрываем игровое окно, освобождаем поле
	}
	return 0;
}