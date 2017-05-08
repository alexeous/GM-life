#include <stdio.h>
#include "ctest.h"
#include "menu.h"

CTEST(menu_suite, applying_changes) {
    const char filename[] = "test/settings_files/test_settings";
    gameSettings settings = defaultSettings;
    int fieldW, fieldH, population;

    fieldW = MIN_FIELD_W, fieldH = MIN_FIELD_H, population = MIN_POPULATION;
    ASSERT_TRUE(applyChanges(fieldW, fieldH, population, filename, settings));

    fieldW = MIN_FIELD_W - 1, fieldH = MIN_FIELD_H, population = MIN_POPULATION;
    ASSERT_FALSE(applyChanges(fieldW, fieldH, population, filename, settings));

    fieldW = MIN_FIELD_W, fieldH = MIN_FIELD_H - 1, population = MIN_POPULATION;
    ASSERT_FALSE(applyChanges(fieldW, fieldH, population, filename, settings));

    fieldW = MIN_FIELD_W, fieldH = MIN_FIELD_H, population = MIN_POPULATION - 1;
    ASSERT_FALSE(applyChanges(fieldW, fieldH, population, filename, settings));

    fieldW = MAX_FIELD_W, fieldH = MAX_FIELD_H, population = MAX_POPULATION;
    ASSERT_TRUE(applyChanges(fieldW, fieldH, population, filename, settings));

    fieldW = MAX_FIELD_W + 1, fieldH = MAX_FIELD_H, population = MAX_POPULATION;
    ASSERT_FALSE(applyChanges(fieldW, fieldH, population, filename, settings));

    fieldW = MAX_FIELD_W, fieldH = MAX_FIELD_H + 1, population = MAX_POPULATION;
    ASSERT_FALSE(applyChanges(fieldW, fieldH, population, filename, settings));

    fieldW = MAX_FIELD_W, fieldH = MAX_FIELD_H, population = MAX_POPULATION + 1;
    ASSERT_FALSE(applyChanges(fieldW, fieldH, population, filename, settings));

    remove(filename);
}
