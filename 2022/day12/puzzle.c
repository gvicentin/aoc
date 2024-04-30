#include "puzzle.h"

#include <assert.h>

static void set_edge(struct map *m, int srcc, int srcr, int destc, int destr) {
    int vsrc = srcr * m->width + srcc;
    int vdest = destr * m->width + destc;
    assert(vsrc >= 0 && vsrc < NOVERTEX && vdest >= 0 && vdest < NOVERTEX);
    m->adj[vsrc][vdest] = true;
}

static void setup_graph(struct map *m) {
    for (int y = 0; y < m->height; ++y) {
        for (int x = 0; x < m->width; ++x) {
            if (x - 1 >= 0 &&
                (get_height(m, x, y) >= get_height(m, x - 1, y) ||
                 get_height(m, x, y) + 1 == get_height(m, x - 1, y)))
                set_edge(m, x, y, x - 1, y);
            if (x + 1 < NOCOLS &&
                (get_height(m, x, y) >= get_height(m, x + 1, y) ||
                 get_height(m, x, y) + 1 == get_height(m, x + 1, y)))
                set_edge(m, x, y, x + 1, y);
            if (y - 1 >= 0 &&
                (get_height(m, x, y) >= get_height(m, x, y - 1) ||
                 get_height(m, x, y) + 1 == get_height(m, x, y - 1)))
                set_edge(m, x, y, x, y - 1);
            if (y + 1 < m->height &&
                (get_height(m, x, y) >= get_height(m, x, y + 1) ||
                 get_height(m, x, y) + 1 == get_height(m, x, y + 1)))
                set_edge(m, x, y, x, y + 1);
        }
    }
}

int init_map(struct map *m, const char *state) {
    char c;
    int i = 0, rows = 0, cols = 0, prevcols = 0;

    while ((c = state[i++]) != 0) {
        if (c == '\n') {
            ++rows;
            prevcols = cols;
            cols = 0;
            continue;
        }

        int height = 0;
        switch (c) {
            case 'S':
                height = 'a' - 'a';
                m->startx = cols;
                m->starty = rows;
                break;
            case 'E':
                height = 'z' - 'a';
                m->destx = cols;
                m->desty = rows;
                break;
            default:
                height = c - 'a';
        }
        m->heightmap[rows * NOCOLS + cols++] = height;
    }

    if (!rows) {
        return 1;
    }

    m->height = rows;
    m->width = prevcols;
    setup_graph(m);

    return 0;
}

int get_height(struct map *m, int col, int row) {
    int id = row * NOCOLS + col;
    assert(id >= 0 && id < NOVERTEX);
    return m->heightmap[id];
}

bool get_edge(struct map *m, int src, int dest) {
    return m->adj[src][dest];
}
