#ifdef _WIN32
#define __USE_MINGW_ANSI_STDIO 0	// для устранения проблемы с компиляцией с ключом -std=c++14
#endif

#define CTEST_MAIN
#define CTEST_COLOR_OK

#include "ctest.h"

int main(int argc, const char** argv) {
    return ctest_main(argc, argv);
}