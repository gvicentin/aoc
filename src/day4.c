#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

static int assignmentPairContains(int x1, int x2, int y1, int y2);
static int assignmentPairOverlaps(int x1, int x2, int y1, int y2);
static void countAssignmentPairs(int *contains, int *overlaps);

static char *testAssignmentPair(void);
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

    int countContains, countOverlaps;
    countAssignmentPairs(&countContains, &countOverlaps);
    printf("Count contains: %d\n", countContains);
    printf("Count overlaps: %d\n", countOverlaps);

    return 0;
}

static int assignmentPairContains(int x1, int x2, int y1, int y2) {
    return (x1 <= y1 && x2 >= y2) || (y1 <= x1 && y2 >= x2);
}

static int assignmentPairOverlaps(int x1, int x2, int y1, int y2) {
    return (y1 <= x2 && y1 >= x1) || (x1 <= y2 && x1 >= y1);
}

static void countAssignmentPairs(int *contains, int *overlaps) {
    int x1, x2, y1, y2;
    *contains = 0;
    *overlaps = 0;

    while (scanf("%d-%d,%d-%d", &x1, &x2, &y1, &y2) != EOF) {
        int resultContains = assignmentPairContains(x1, x2, y1, y2);
        int resultOverlaps = assignmentPairOverlaps(x1, x2, y1, y2);
        *contains += resultContains;
        *overlaps += resultOverlaps;
    }
}

static char *testAssignmentPair(void) {
    int input[] = {2, 4, 6, 8,  // One entry per line
                   2, 3, 4, 5,  //
                   5, 7, 7, 9,  //
                   2, 8, 3, 7,  //
                   6, 6, 4, 6,  //
                   2, 6, 4, 8, 82, 93, 4, 81};
    int expectedContains[] = {0, 0, 0, 1, 1, 0, 0};
    int expectedOverlaps[] = {0, 0, 1, 1, 1, 1, 0};
    int index = 0;

    for (int i = 0; i < sizeof(expectedContains) / sizeof(expectedContains[0]); ++i) {
        int resultContains = assignmentPairContains(input[index], input[index + 1],
                                                    input[index + 2], input[index + 3]);
        int resultOverlaps = assignmentPairOverlaps(input[index], input[index + 1],
                                                    input[index + 2], input[index + 3]);
        MU_ASSERT_FMT(expectedContains[i] == resultContains,
                      "[%d-%d,%d-%d] Expect contains (%d) but got (%d)", input[index],
                      input[index + 1], input[index + 2], input[index + 3],
                      expectedContains[i], resultContains);
        MU_ASSERT_FMT(expectedOverlaps[i] == resultOverlaps,
                      "[%d-%d,%d-%d] Expect overlaps (%d) but got (%d)", input[index],
                      input[index + 1], input[index + 2], input[index + 3],
                      expectedOverlaps[i], resultOverlaps);
        index += 4;
    }

    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testAssignmentPair);
    MU_PASS;
}
