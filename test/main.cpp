#define CTEST_MAIN
#define CTEST_COLOR_OK

#include "ctest.h"

int main(int argc, const char** argv) {
    return ctest_main(argc, argv);
}

CTEST(basicSuite, basicTest) {
	ASSERT_EQUAL(25, 10+15);
}