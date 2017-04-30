#include "const.h"
#include "graphics.h"
#include "render.h"

void render(const gameSettings settings, const gameField field) {
	cleardevice();
    setfillstyle(SOLID_FILL, WHITE);
    for(int i = 0; i < settings.fieldW - 1; i++) {
        int xstart = CELL_SIZE_PX * (i+1) + GRID_THICKNESS_PX * i;
        int xend = xstart + GRID_THICKNESS_PX - 1;
        bar(xstart, 0, xend, settings.windowH);
    }
    for(int i = 0; i < settings.fieldH - 1; i++) {
        int ystart = CELL_SIZE_PX * (i+1) + GRID_THICKNESS_PX * i;
        int yend = ystart + GRID_THICKNESS_PX - 1;
        bar(0, ystart, settings.windowW, yend);
    }
}
