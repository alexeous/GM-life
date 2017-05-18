#include "ctest.h"
#include "settings.h"

CTEST(settings_suite, validation) {
    gameSettings settings;

    settings = {MIN_FIELD_W, MIN_FIELD_H, 0, 0, MIN_PERIOD, 0, MIN_POPULATION, 0, 0, 0};
    ASSERT_TRUE(validateSettings(settings));

    settings = {MIN_FIELD_W - 1, MIN_FIELD_H, 0, 0, MIN_PERIOD, 0,  MIN_POPULATION, 0, 0, 0};
    ASSERT_FALSE(validateSettings(settings));

    settings = {MIN_FIELD_W, MIN_FIELD_H - 1, 0, 0, MIN_PERIOD, 0,  MIN_POPULATION, 0, 0, 0};
    ASSERT_FALSE(validateSettings(settings));

    settings = {MIN_FIELD_W, MIN_FIELD_H, 0, 0, MIN_PERIOD - 1, 0,  MIN_POPULATION, 0, 0, 0};
    ASSERT_FALSE(validateSettings(settings));

    settings = {MIN_FIELD_W, MIN_FIELD_H, 0, 0, MIN_PERIOD, 0,  MIN_POPULATION - 1, 0, 0, 0};
    ASSERT_FALSE(validateSettings(settings));

    settings = {MAX_FIELD_W, MAX_FIELD_H, 0, 0, MAX_PERIOD, 0,  MAX_POPULATION, 0, 0, 0};
    ASSERT_TRUE(validateSettings(settings));

    settings = {MAX_FIELD_W + 1, MAX_FIELD_H, 0, 0, MAX_PERIOD, 0,  MAX_POPULATION, 0, 0, 0};
    ASSERT_FALSE(validateSettings(settings));

    settings = {MAX_FIELD_W, MAX_FIELD_H + 1, 0, 0, MAX_PERIOD, 0,  MAX_POPULATION, 0, 0, 0};
    ASSERT_FALSE(validateSettings(settings));

    settings = {MAX_FIELD_W, MAX_FIELD_H, 0, 0, MAX_PERIOD + 1, 0,  MAX_POPULATION, 0, 0, 0};
    ASSERT_FALSE(validateSettings(settings));

    settings = {MAX_FIELD_W, MAX_FIELD_H, 0, 0, MAX_PERIOD, 0,  MAX_POPULATION + 1, 0, 0, 0};
    ASSERT_FALSE(validateSettings(settings));
}

CTEST(settings_suite, loading) {
    const char nonexistentFilename[] = "####__NONEXISTENT_SETTINGS__####";
    const char emptyFilename[] = "test/settings_files/empty_settings";
    const char workingFilename[] = "test/settings_files/working_settings";
    gameSettings settings;

    ASSERT_FALSE(loadSettingsFile(nonexistentFilename, settings));
    ASSERT_FALSE(loadSettingsFile(emptyFilename, settings));
    ASSERT_TRUE(loadSettingsFile(workingFilename, settings));
}
