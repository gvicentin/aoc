#ifndef PUZZLE_H
#define PUZZLE_H

#include <stdbool.h>

#define NOROWS   32
#define NOCOLS   32
#define NOVERTEX (NOROWS * NOCOLS)

struct map {
    int heightmap[NOVERTEX];
    bool adj[NOVERTEX][NOVERTEX];
    int width, height;
    int startx, starty;
    int destx, desty;
};

int init_map(struct map *m, const char *state);
int get_height(struct map *m, int col, int row);
bool get_edge(struct map *m, int src, int dest);

#endif  // !PUZZLE_H
