#ifndef EVENT_H
#define EVENT_H

#include <conio.h>
#include <chrono>
#include <algorithm>
#include "settings.h"
using namespace std;

static chrono::steady_clock::time_point initialTime;

void initTime();
long getTime();     // в миллисекундах
void event(gameSettings &settings, bool &run);

#endif // EVENT_H