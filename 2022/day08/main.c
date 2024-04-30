#include <stdio.h>
#include "sol.h"

char g_assertMsg[1024];
int g_testsRun = 0;

int main(int argc, char *argv[]) {
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
    int heightesScenicScore = GetHeighestScenicScore(map, rows, cols);
    printf("Visible trees: %d\n", visibleTrees);
    printf("Heighest Scenic Score: %d\n", heightesScenicScore);

    return 0;
}
