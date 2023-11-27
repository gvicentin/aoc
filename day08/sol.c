#include "sol.h"

int countVisibleTrees(const int *map, int rows, int columns) {
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

int GetHeighestScenicScore(const int *map, int rows, int columns) {
    int heighestScenicScore = 0;

    for (int y = 1; y < rows - 1; ++y) {
        for (int x = 1; x < columns - 1; ++x) {
            int curHeight = map[y * columns + x];
            int right = 0, down = 0, left = 0, up = 0;
            int dx, dy;
            
            dx = x + 1;
            while (dx < columns - 1 && curHeight > map[y * columns + dx]) ++dx;
            right = dx - x;

            dy = y + 1;
            while (dy < rows - 1 && curHeight > map[dy * columns + x]) ++dy;
            down = dy - y;

            dx = x - 1;
            while (dx > 0 && curHeight > map[y * columns + dx]) --dx;
            left = x - dx;

            dy = y - 1;
            while (dy > 0 && curHeight > map[dy * columns + x]) --dy;
            up = y - dy;

            int score = right * down * left * up;
            if (score > heighestScenicScore) {
                heighestScenicScore = score;
            }
        }
    }

    return heighestScenicScore;
}
