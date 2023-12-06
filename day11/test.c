#include <stdint.h>
#include <stdio.h>

#include "../common/minunit.h"
#include "sol.h"

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

static char *testLevelOfMonkeyBusiness(void) {
    struct monkey ms[] = {{{79, 98}, 0, 2, OP_MUL, true, 19, 23, 2, 3},
                          {{54, 65, 75, 74}, 0, 4, OP_ADD, true, 6, 19, 2, 0},
                          {{79, 60, 97}, 0, 3, OP_MUL, false, 0, 13, 1, 3},
                          {{74}, 0, 1, OP_ADD, true, 3, 17, 0, 1}};

    uint64_t inspectedItems[4] = {0};
    uint64_t expected[4] = {101, 95, 7, 105};

    int i = 20;
    do {
        execute_round(ms, inspectedItems, 4, true);
    } while (--i > 0);

    for (int i = 0; i < 4; ++i) {
        MU_ASSERT_FMT(expected[i] == inspectedItems[i],
                      "[Monkey %d] Expect (%lu) but got (%lu)", i, expected[i],
                      inspectedItems[i]);
    }

    qsort(inspectedItems, 4, sizeof(inspectedItems[0]), compareLevel);
    uint64_t result = inspectedItems[0] * inspectedItems[1];
    MU_ASSERT_FMT(10605L == result, "Expect result (%lu) but got (%lu)", 10605L,
                  result);
    MU_PASS;
}

static char *testLevelOfMonkeyBusiness2(void) {
    struct monkey ms[] = {{{79, 98}, 0, 2, OP_MUL, true, 19, 23, 2, 3},
                          {{54, 65, 75, 74}, 0, 4, OP_ADD, true, 6, 19, 2, 0},
                          {{79, 60, 97}, 0, 3, OP_MUL, false, 0, 13, 1, 3},
                          {{74}, 0, 1, OP_ADD, true, 3, 17, 0, 1}};
    uint64_t inspectedItems[4] = {0};
    uint64_t expected[4] = {52166, 47830, 1938, 52013};

    int i = 10000;
    do {
        execute_round(ms, inspectedItems, 4, false);
    } while (--i > 0);

    for (int i = 0; i < 4; ++i) {
        MU_ASSERT_FMT(expected[i] == inspectedItems[i],
                      "[Monkey %d] Expect (%lu) but got (%lu)", i, expected[i],
                      inspectedItems[i]);
    }

    qsort(inspectedItems, 4, sizeof(inspectedItems[0]), compareLevel);
    uint64_t result = inspectedItems[0] * inspectedItems[1];
    MU_ASSERT_FMT(2713310158L == result, "Expect result (%lu) but got (%lu)",
                  2713310158L, result);
    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testLevelOfMonkeyBusiness);
    MU_TEST(testLevelOfMonkeyBusiness2);
    MU_PASS;
}
