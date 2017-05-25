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
    for(int i = 1; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW; j++) {
            ASSERT_TRUE(fieldSrc[i][j].isAlive == fieldDest[i][j].isAlive);
            ASSERT_TRUE(fieldSrc[i][j].health == fieldDest[i][j].health);
            ASSERT_TRUE(fieldSrc[i][j].socialGene == fieldDest[i][j].socialGene);
            ASSERT_TRUE(fieldSrc[i][j].maxHealth == fieldDest[i][j].maxHealth);
            ASSERT_TRUE(fieldSrc[i][j].age == fieldDest[i][j].age);
        }
    }
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

CTEST(logic_suite, born_cell) {
    gameField oldField;
    gameField newField;
    gameSettings settings = defaultSettings;
    settings.population = 0;
    startGame(settings, oldField);
    startGame(settings, newField);

    int h = 1, w = 1;
    cell &deadCell = oldField[h][w];
    cell &parentCell = oldField[h + 1][w + 1];
    cell &newCell = newField[h][w];

    deadCell.isAlive = false;
    deadCell.health = 0;
    deadCell.socialGene = 0;
    deadCell.maxHealth = 1;

    parentCell.isAlive = true;
    parentCell.health = 1;
    parentCell.socialGene = 5;
    parentCell.maxHealth = 3;

    bornCell(oldField, newField, h, w);

    ASSERT_TRUE(newCell.isAlive);
    ASSERT_TRUE(newCell.health > 0);
    ASSERT_TRUE(newCell.socialGene == parentCell.socialGene);
    ASSERT_TRUE(newCell.maxHealth == parentCell.maxHealth);
}

CTEST(logic_suite, harm_cell) {
    gameField field;
    gameSettings settings = defaultSettings;
    settings.population = 0;
    startGame(settings, field);

    int h = 1, w = 1;

    field[h][w].isAlive = true;
    field[h][w].health = 2;
    harmCell(field[h][w]);
    ASSERT_TRUE(field[h][w].isAlive);
    ASSERT_EQUAL(1, field[h][w].health);

    field[h][w].isAlive = true;
    field[h][w].health = 1;
    harmCell(field[h][w]);
    ASSERT_FALSE(field[h][w].isAlive);
    ASSERT_EQUAL(0, field[h][w].health);

    field[h][w].isAlive = false;
    field[h][w].health = 0;
    harmCell(field[h][w]);
    ASSERT_FALSE(field[h][w].isAlive);
    ASSERT_EQUAL(0, field[h][w].health);
}

CTEST(logic_suite, cell_aging) {
    gameField field;
    gameSettings settings = defaultSettings;
    startGame(settings, field);

    int h = 1, w = 1;
    field[h][w].isAlive = true;
    field[h][w].age = 1;
    cellAging(field[h][w]);
    ASSERT_EQUAL(2, field[h][w].age);

    field[h][w].isAlive = true;
    field[h][w].age = MAX_AGE;
    cellAging(field[h][w]);
    ASSERT_FALSE(field[h][w].isAlive);

    field[h][w].isAlive = false;
    field[h][w].age = 1;
    ASSERT_FALSE(field[h][w].isAlive);
}

CTEST(logic_suite, migrate_cell) {
    gameField field;
    gameSettings settings = defaultSettings;
    settings.population = 0;
    startGame(settings, field);

    int h = 2, w = 2;

    // Единственное подходящее место
    field[h][w].isAlive = true;
    field[h][w].health = 1;
    field[h][w].socialGene = 4;
    field[h][w].maxHealth = 3;
    field[h][w].age = 5;

    field[h - 1][w    ].isAlive = true;
    field[h - 1][w + 1].isAlive = true;
    field[h + 1][w - 1].isAlive = true;
    field[h + 1][w    ].isAlive = true;
    field[h + 1][w + 1].isAlive = true;

    migrateCell(settings, field, h, w);
    ASSERT_FALSE(field[h][w].isAlive);
    ASSERT_TRUE(field[h][w + 1].isAlive);
    ASSERT_TRUE(field[h][w + 1].health == field[h][w].health);
    ASSERT_TRUE(field[h][w + 1].socialGene == field[h][w].socialGene);
    ASSERT_TRUE(field[h][w + 1].maxHealth == field[h][w].maxHealth);
    ASSERT_TRUE(field[h][w + 1].age == field[h][w].age);

    // Два подходящих места
    startGame(settings, field);
    field[h][w].isAlive = true;
    field[h][w].health = 1;
    field[h][w].socialGene = 4;
    field[h][w].maxHealth = 3;
    field[h][w].age = 5;
    field[h][w - 1] = field[h][w + 1] = { 0, 0, 0, 0 };

    field[h - 1][w - 1].isAlive = true;
    field[h - 1][w    ].isAlive = true;
    field[h - 1][w + 1].isAlive = true;
    field[h + 1][w - 1].isAlive = true;
    field[h + 1][w    ].isAlive = true;
    field[h + 1][w + 1].isAlive = true;

    migrateCell(settings, field, h, w);
    ASSERT_FALSE(field[h][w].isAlive);
    ASSERT_TRUE((field[h][w - 1].isAlive) xor (field[h][w + 1].isAlive));
    ASSERT_TRUE((field[h][w - 1].health == field[h][w].health) xor
                (field[h][w + 1].health == field[h][w].health));
    ASSERT_TRUE((field[h][w - 1].socialGene == field[h][w].socialGene) xor
                (field[h][w + 1].socialGene == field[h][w].socialGene));
    ASSERT_TRUE((field[h][w - 1].maxHealth == field[h][w].maxHealth) xor
                (field[h][w + 1].maxHealth == field[h][w].maxHealth));
    ASSERT_TRUE((field[h][w - 1].age == field[h][w].age) xor
                (field[h][w + 1].age == field[h][w].age));

    // Нет подходящих мест
    startGame(settings, field);
    field[h][w].isAlive = true;
    field[h][w].socialGene = 4;

    migrateCell(settings, field, h, w);
    ASSERT_FALSE(neighborsAlive(field, h, w));
    ASSERT_TRUE(field[h][w].isAlive);
}
