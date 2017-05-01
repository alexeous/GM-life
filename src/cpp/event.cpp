#include "event.h"

void initTime() {
    initialTime = chrono::steady_clock::now();
}

long getTime() {
    auto delta = chrono::steady_clock::now() - initialTime;
    return chrono::duration_cast<chrono::milliseconds>(delta).count();
}

void event(gameSettings &settings, bool &run) {
    if(kbhit())
        switch(getch()) {
            case 27:    run = false;    break;      // 27 - Esc
        }
}