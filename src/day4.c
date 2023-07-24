#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

static int assignmentPairContains(int x1, int x2, int y1, int y2);
static int countAssignmentPairContained(void);

static char *testAssignmentPairContains(void);
static char *allTests(void);

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "--test") || strcmp(argv[1], "-t"))) {
        // run tests and exit
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

    int count = countAssignmentPairContained();
    printf("Count: %d\n", count);

    return 0;
}

static int assignmentPairContains(int x1, int x2, int y1, int y2) {
    return (x1 <= y1 && x2 >= y2) || (y1 <= x1 && y2 >= x2);
}

static int countAssignmentPairContained(void) {
    int x1, x2, y1, y2;
    int count = 0;

    while (scanf("%d-%d,%d-%d", &x1, &x2, &y1, &y2) != EOF) {
        int result = assignmentPairContains(x1, x2, y1, y2);
        count += result;
    }

    return count;
}

static char *testAssignmentPairContains(void) {
    int input[] = {
        2, 4, 6, 8,  // One entry per line
        2, 3, 4, 5,  //
        5, 7, 7, 9,  //
        2, 8, 3, 7,  //
        6, 6, 4, 6,  //
        2, 6, 4, 8,
    };
    int expected[] = {0, 0, 0, 1, 1, 0};
    int index = 0;

    for (int i = 0; i < sizeof(expected)/sizeof(expected[0]); ++i) {
        int result = assignmentPairContains(input[index], input[index + 1], input[index + 2], input[index + 3]);
        index += 4;
        MU_ASSERT_FMT(expected[i] == result, "Expect (%d) but got (%d)", expected[i], result);
    }

    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testAssignmentPairContains);
    MU_PASS;
}
