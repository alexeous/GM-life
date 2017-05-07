#include "ctest.h"
#include "logic.h"

CTEST(logic_suite, field_filling) {
    gameField field;
    gameSettings settings = defaultSettings;
    bool flag;

    settings.population = 0;
    startGame(settings, field);
    flag = false;
    for(int i = 0; i < settings.fieldH + 2; i++)    // Всё поле, включая краевые клетки,
        for(int j = 0; j < settings.fieldW + 2; j++)    // должно быть false при population = 0
            flag |= field[i][j].isAlive;
    ASSERT_FALSE(flag);

    settings.population = 100;
    startGame(settings, field);

    flag = false;
    for(int i = 0; i < settings.fieldH + 2; i++) {
        flag |= field[i][0].isAlive;    // Проверяем левые и
        flag |= field[i][settings.fieldW + 1].isAlive;  // правые краевые клетки
    }
    ASSERT_FALSE(flag);

    for(int j = 0; j < settings.fieldW + 2; j++) {
        flag |= field[0][j].isAlive;    // Проверяем верхние и
        flag |= field[settings.fieldH + 1][j].isAlive;  // нижние краевые клетки
    }
    ASSERT_FALSE(flag);

    flag = true;
    for(int i = 1; i <= settings.fieldH; i++)   // При population = 100 все некраевые
        for(int j = 1; j <= settings.fieldW; j++)   // клетки должны быть true
            flag &= field[i][j].isAlive;
    ASSERT_TRUE(flag);
}

CTEST(logic_suite, field_copying) {
    gameField fieldSrc, fieldDest;
    gameSettings settings = defaultSettings;
    startGame(settings, fieldSrc);
    copyField(settings, fieldDest, fieldSrc);
    bool flag = true;
    for(int i = 0; i < settings.fieldH + 2; i++) 
        for(int j = 0; j < settings.fieldW + 2; j++)
            flag &= (fieldSrc[i][j].isAlive == fieldDest[i][j].isAlive);
    ASSERT_TRUE(flag);
}

CTEST(logic_suite, neighbors_counting) {
    gameField field;
    gameSettings settings = defaultSettings;
    int neighbors;

    settings.population = 0;
    startGame(settings, field);
    neighbors = 0;
    for(int i = 1; i <= settings.fieldH; i++)
        for(int j = 1; j <= settings.fieldW; j++)
            neighbors += neighborsAlive(field, i, j);
    ASSERT_EQUAL(0, neighbors);

    settings.fieldW = settings.fieldH = 3;
    settings.population = 0;
    startGame(settings, field);
    field[2][2].isAlive = true; // Живая клетка в центре поля
    ASSERT_EQUAL(1, neighborsAlive(field, 1, 1));
    ASSERT_EQUAL(1, neighborsAlive(field, 1, 2));
    ASSERT_EQUAL(1, neighborsAlive(field, 1, 3));

    ASSERT_EQUAL(1, neighborsAlive(field, 2, 1));
    ASSERT_EQUAL(0, neighborsAlive(field, 2, 2)); // У самой клетки живый соседей нет
    ASSERT_EQUAL(1, neighborsAlive(field, 2, 3));

    ASSERT_EQUAL(1, neighborsAlive(field, 3, 1));
    ASSERT_EQUAL(1, neighborsAlive(field, 3, 2));
    ASSERT_EQUAL(1, neighborsAlive(field, 3, 3));
}