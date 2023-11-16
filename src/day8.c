#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

static int countVisibleTrees(const int *map, int rows, int columns);
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

    int map[10000];
    int mapTail = 0;
    int rows = 0, cols = 0;

    int c = getchar();
    while (c != EOF) {
        if (c == '\n') {
            rows = cols > 1 ? rows + 1 : rows;
            cols = 0;
        }
        else {
            map[mapTail++] = c - '0';
        }
        c = getchar();
        cols++;
    }
    if (cols > 1) ++rows;
    cols = mapTail / rows;

    int visibleTrees = countVisibleTrees(map, rows, cols);
    printf("Visible trees: %d\n", visibleTrees);

    return 0;
}

static int countVisibleTrees(const int *map, int rows, int columns) {
    int insideVisibleTrees = 0;
    int borderTrees = rows * 2 + columns * 2 - 4;

    for (int y = 1; y < rows - 1; ++y) {
        for (int x = 1; x < columns - 1; ++x) {
            int height = map[y * columns + x];
            int dx, dy;

            // up
            dy = y - 1;
            while (dy >= 0 && height > map[dy * columns + x]) --dy;
            if (dy < 0) {
                ++insideVisibleTrees;
                continue;
            }

            // right
            dx = x + 1;
            while (dx < columns && height > map[y * columns + dx]) ++dx;
            if (dx == columns) {
                ++insideVisibleTrees;
                continue;
            }

            // down
            dy = y + 1;
            while (dy < rows && height > map[dy * columns + x]) ++dy;
            if (dy == rows) {
                ++insideVisibleTrees;
                continue;
            }

            // left
            dx = x - 1;
            while (dx >= 0 && height > map[y * columns + dx]) --dx;
            if (dx < 0)
                ++insideVisibleTrees;
        }
    }

    return insideVisibleTrees + borderTrees;
}

static char *testCountVisibleTrees(void) {
    const int input[] = { 3, 0, 3, 7, 3,
                          2, 5, 5, 1, 2,
                          6, 5, 3, 3, 2,
                          3, 3, 5, 4, 9,
                          3, 5, 3, 9, 0 };

    int visibleTrees = countVisibleTrees(input, 5, 5);
    MU_ASSERT_FMT(21 == visibleTrees, "Expect (%d) but got (%d)", 21, visibleTrees);

    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testCountVisibleTrees);
    MU_PASS;
}
