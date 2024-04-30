#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "sol.h"

int main(int argc, char *argv[]) {
    struct monkey ms[] = {
        {{56, 52, 58, 96, 70, 75, 72}, 0, 7, OP_MUL, true, 17, 11, 2, 3},
        {{75, 58, 86, 80, 55, 81}, 0, 6, OP_ADD, true, 7, 3, 6, 5},
        {{73, 68, 73, 90}, 0, 4, OP_MUL, false, 0, 5, 1, 7},
        {{72, 89, 55, 51, 59}, 0, 5, OP_ADD, true, 1, 7, 2, 7},
        {{76, 76, 91}, 0, 3, OP_MUL, true, 3, 19, 0, 3},
        {{88}, 0, 1, OP_ADD, true, 4, 2, 6, 4},
        {{64, 63, 56, 50, 77, 55, 55, 86}, 0, 8, OP_ADD, true, 8, 13, 4, 0},
        {{79, 58}, 0, 2, OP_ADD, true, 6, 17, 1, 5}};
    uint64_t inspectedItems[8] = {0};

    int i = 10000;
    do {
        execute_round(ms, inspectedItems, 8, false);
    } while (--i > 0);

    qsort(inspectedItems, 8, sizeof(inspectedItems[0]), compareLevel);
    int result = inspectedItems[0] * inspectedItems[1];
    printf("Result: %d\n" , result);

    return 0;
}
