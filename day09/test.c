#include <stdio.h>
#include "sol.h"
#include "../common/minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

char input[] = "R 4\nU 4\nL 3\nD 1\nR 4\nD 1\nL 5\nR 2";

static char *allTests(void);

int main(int argc, char *argv[]) {
    char *testsResults = allTests();
    printf("Test count: %d\n", g_testsRun);

    if (testsResults != 0) {
        printf("Test failed\n");
        printf("%s\n", testsResults);
        return 1;
    }

    printf("All tests passed.\n");
    return 0;
}

static char *testCountRepoUniquePositions(void) {
    int positions = countRopeUniquePositions(input);
    MU_ASSERT_FMT(13 == positions, "Expect (%d) but got (%d)", 13, positions);
    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testCountRepoUniquePositions);
    MU_PASS;
}
