#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <stdio.h>
#include "graphics.h"

#include "settings.h"
#include "event.h"

bool init(gameSettings &settings, const char *settingsFilename);

#endif // INIT_H