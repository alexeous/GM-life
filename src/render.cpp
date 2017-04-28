#include "const.h"
#include "graphics.h"
#include "render.h"

void render(const gameSettings settings, const gameField field) {	// TODO
	cleardevice();
    setcolor(LIGHTGRAY);
    for(int i = 0; i < settings.fieldW - 1; i++) {
        int y = CELL_SIZE_PX * (i+1) + i;
        line(y, 0, y, settings.windowH);
    }
    for(int i = 0; i < settings.fieldH - 1; i++) {
        int x = CELL_SIZE_PX * (i+1) + 1;
        line(0, x, settings.windowW, x);
    }
    delay(1000);
}