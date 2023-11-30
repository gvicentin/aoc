#include "sol.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool hasVisitedPosition(const int *trail, int trailSize, int x, int y) {
    for (int i = 0; i < trailSize - 1; i += 2) {
        if (trail[i] == x && trail[i + 1] == y) return true;
    }

    return false;
}

int countRopeUniquePositions(const char *movements, int knotsCount) {
    int positions = 0;
    int knotsx[10] = {0};
    int knotsy[10] = {0};
    int trail[15000];
    int trailSize = 0;

    // TODO: duplicate string
    char *dupStr = strdup(movements);
    char *lineToken = strtok(dupStr, "\n");
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
            // move head towards direction
            knotsx[0] += dx;
            knotsy[0] += dy;

            for (int j = 1; j < knotsCount; ++j) {
                if (abs(knotsx[j - 1] - knotsx[j]) + abs(knotsy[j - 1] - knotsy[j]) >
                    2) {
                    // NOTE(gvicentin): need to move diagonally
                    knotsx[j] += knotsx[j - 1] > knotsx[j] ? 1 : -1;
                    knotsy[j] += knotsy[j - 1] > knotsy[j] ? 1 : -1;
                } else if (abs(knotsx[j - 1] - knotsx[j]) > 1 &&
                           abs(knotsy[j - 1] - knotsy[j]) == 0) {
                    // NOTE(gvicentin): need to move sideways
                    knotsx[j] += knotsx[j - 1] > knotsx[j] ? 1 : -1;
                } else if (abs(knotsy[j - 1] - knotsy[j]) > 1 &&
                           abs(knotsx[j - 1] - knotsx[j]) == 0) {
                    // NOTE(gvicentin): need to move up/down
                    knotsy[j] += knotsy[j - 1] > knotsy[j] ? 1 : -1;
                }
            }

            assert(trailSize < 15000);
            bool visited = hasVisitedPosition(trail, trailSize, knotsx[knotsCount - 1],
                                              knotsy[knotsCount - 1]);
            if (!visited) {
                ++positions;
                trail[trailSize++] = knotsx[knotsCount - 1];
                trail[trailSize++] = knotsy[knotsCount - 1];
            }
        } while (--i > 0);
    }

    free(dupStr);
    return positions;
}
