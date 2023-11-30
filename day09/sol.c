#include "sol.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool hasVisitedPosition(const int *trail, int trailSize, int x, int y) {
    for (int i = 0; i < trailSize - 1; i += 2) {
        if (trail[i] == x && trail[i + 1] == y)
            return true;
    }

    return false;
}

int countRopeUniquePositions(const char *movements) {
    int positions = 0;
    int hx = 0, hy = 0, tx = 0, ty = 0;
    int trail[100000];
    int trailSize = 0;

    // TODO: duplicate string
    char *lineToken = strtok((char *)movements, "\n");
    while (lineToken != NULL) {
        char dir;
        int qnt;
        sscanf(lineToken, "%c %d", &dir, &qnt);
        lineToken = strtok(NULL, "\n");

        int dx = 0, dy = 0;
        switch (dir) {
            case 'd':
            case 'D':
                dy = 1;
                break;
            case 'u':
            case 'U':
                dy = -1;
                break;
            case 'r':
            case 'R':
                dx = 1;
                break;
            case 'l':
            case 'L':
                dx = -1;
                break;
        }

        int i = qnt;
        do {
            hx += dx;
            hy += dy;

            if (abs(hx - tx) + abs(hy - ty) > 2) {
                // NOTE(gvicentin): need to move diagonally
                tx += hx > tx ? 1 : -1;
                ty += hy > ty ? 1 : -1;
            } else if (abs(hx - tx) > 1 && abs(hy - ty) == 0) {
                // NOTE(gvicentin): need to move sideways
                tx += hx > tx ? 1 : -1;
            } else if (abs(hy - ty) > 1 && abs(hx - tx) == 0) {
                // NOTE(gvicentin): need to move up/down
                ty += hy > ty ? 1 : -1;
            } 

            assert(trailSize < 100000);
            bool visited = hasVisitedPosition(trail, trailSize, tx, ty);
            if (!visited) {
                ++positions;
                trail[trailSize++] = tx;
                trail[trailSize++] = ty;
            }
        } while (--i > 0);
    }

    return positions;
}
