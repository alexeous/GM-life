#include "const.h"
#include "graphics.h"
#include "render.h"

void render(const gameSettings settings, const gameField field) {
    for(int i = 1; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW ; j++) {
            if (field[i][j].isAlive) setfillstyle(SOLID_FILL, GREEN);    // клетка живая - зеленый
            else setfillstyle(SOLID_FILL, COLOR(230, 230, 230));         // мертвая - серый
            int left = (CELL_SIZE_PX) * (j - 1) + GRID_THICKNESS_PX * j;
            int top = (CELL_SIZE_PX) * (i - 1) + GRID_THICKNESS_PX * i;
            bar(left, top, left + CELL_SIZE_PX - 1, top + CELL_SIZE_PX - 1);
        }
    }
}
