#include <stdio.h>
#include "sol.h"
#include "../common/minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

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
    const char *input[] = {
        "R 4\nU 4\nL 3\nD 1\nR 4\nD 1\nL 5\nR 2",
        "R 5\nU 8\nL 8\nD 3\nR 17\nD 10\nL 25\nU 20"
    };

    // NOTE(gvicentin): test using 1 knot
    int positions = countRopeUniquePositions(input[0], 2);
    MU_ASSERT_FMT(13 == positions, "[1 knot] Expect (%d) but got (%d)", 13, positions);

    // NOTE(gvicentin): test using 10 knot
    positions = countRopeUniquePositions(input[0], 10);
    MU_ASSERT_FMT(1 == positions, "[10 knots] Expect (%d) but got (%d)", 1, positions);
    positions = countRopeUniquePositions(input[1], 10);
    MU_ASSERT_FMT(36 == positions, "[10 knots] Expect (%d) but got (%d)", 36, positions);

    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testCountRepoUniquePositions);
    MU_PASS;
}
