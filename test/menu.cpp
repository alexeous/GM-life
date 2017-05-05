#define CTEST_COLOR_OK

#include "ctest.h"
#include "menu.h"

CTEST(menu_suite, applying_changes) {
    const char filename[] = "settings";
    gameSettings settings {
	    defaultSettings.fieldW, defaultSettings.fieldH,
        defaultSettings.windowW, defaultSettings.windowH,
        defaultSettings.period, defaultSettings.population
    };
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
}
