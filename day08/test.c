#include <stdio.h>
#include "sol.h"
#include "../common/minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

const int input[] = {3, 0, 3, 7, 3, 2, 5, 5, 1, 2, 6, 5, 3,
                     3, 2, 3, 3, 5, 4, 9, 3, 5, 3, 9, 0};

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

static char *testCountVisibleTrees(void) {
    int visibleTrees = countVisibleTrees(input, 5, 5);
    MU_ASSERT_FMT(21 == visibleTrees, "Expect (%d) but got (%d)", 21, visibleTrees);
    MU_PASS;
}

static char *testGetHeightScenicScore(void) {
    int visibleTrees = GetHeighestScenicScore(input, 5, 5);
    MU_ASSERT_FMT(8 == visibleTrees, "Expect (%d) but got (%d)", 8, visibleTrees);
    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testCountVisibleTrees);
    MU_TEST(testGetHeightScenicScore);
    MU_PASS;
}
