#include "../common/minunit.h"
#include "puzzle.h"

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

static char *testMapInit(void) {
    const char input[] =
        "Sab\n"
        "adc\n"
        "cdE\n";
    const int expectedHMap[] = {0, 0, 1, 0, 3, 2, 2, 3, 25};
    const bool expectEdges[] = {
        0, 1, 0, 1, 0, 0, 0, 0, 0, 
        1, 0, 1, 0, 0, 0, 0, 0, 0, 
        0, 1, 0, 0, 0, 1, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 1, 0, 1, 0, 1, 0, 
        0, 0, 1, 0, 1, 0, 0, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0, 1, 0, 0, 
        0, 0, 0, 0, 0, 1, 0, 1, 0};

    struct map m = {};

    init_map(&m, input);
    MU_ASSERT_FMT(m.width == 3 && m.height == 3,
                  "Expect (%d, %d) but got (%d, %d)", 3, 3, m.width, m.height);
    MU_ASSERT_FMT(m.startx == 0 && m.starty == 0,
                  "Expect (%d, %d) but got (%d, %d)", 0, 0, m.startx, m.starty);
    MU_ASSERT_FMT(m.destx == 2 && m.desty == 2,
                  "Expect (%d, %d) but got (%d, %d)", 2, 2, m.destx, m.desty);

    int i = 0;
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            int expect = expectedHMap[i++];
            int got = get_height(&m, x, y);

            MU_ASSERT_FMT(expect == got, "[%d, %d] Expect (%d) but got (%d)", x,
                          y, expect, got);
        }
    }

    for (int src = 0; src < 9; ++src) {
        for (int dest = 0; dest < 9; ++dest) {
            bool expect = expectEdges[src * 9 + dest];
            bool got = get_edge(&m, src, dest);

            MU_ASSERT_FMT(expect == got, "[%d, %d] Expect (%d) but got (%d)",
                          src, dest, expect, got);
        }
    }

    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testMapInit);
    MU_PASS;
}
