#include "ctest.h"
#include "logic.h"
#include "graphics.h"
#include "render.h"

CTEST(render_suite, calculating_cell_color) {
    gameField field;
    gameSettings settings = defaultSettings;
    settings.population = 0;
    startGame(settings, field);

    int expected = 0, real = 0;
    int h = 1, w = 1;

    field[h][w].health = field[h][w].maxHealth = 1;

    // Мертвая клетка
    settings.socialGene = false;
    field[h][w].isAlive = false;
    expected = COLOR(230, 230, 230);
    real = calculateCellColor(settings, field[h][w]);
    ASSERT_EQUAL(expected, real);

    // Живая клетка
    settings.socialGene = false;
    field[h][w].isAlive = true;
    expected = COLOR(71, 181, 16);
    real = calculateCellColor(settings, field[h][w]);
    ASSERT_EQUAL(expected, real);

    // Включен ген социальности
    settings.socialGene = true;
    field[h][w].isAlive = true;
    for (int i = 0; i < 9; i++) {
        field[h][w].socialGene = i;
        expected = COLOR(socialRed[i], socialGreen[i], socialBlue[i]);
        real = calculateCellColor(settings, field[h][w]);
        ASSERT_EQUAL(expected, real);
    }
}
