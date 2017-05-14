#include "event.h"

void initTime() {
    initialTime = chrono::steady_clock::now();
}

long getTime() {
    auto delta = chrono::steady_clock::now() - initialTime;
    return chrono::duration_cast<chrono::milliseconds>(delta).count();
}

void event(gameSettings &settings, bool &run) {
    while(kbhit())
        switch(getch()) {
            case 27:    run = false;    break;      // 27 - Esc
            case KEY_LEFT:   settings.period = min(settings.period + PERIOD_STEP, MAX_PERIOD); break;
            case KEY_RIGHT:   settings.period = max(settings.period - PERIOD_STEP, MIN_PERIOD); break;
        }
}
