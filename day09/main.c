#include <stdio.h>
#include <stdlib.h>

#include "sol.h"

int main(int argc, char *argv[]) {
    char *input = malloc(1000000);
    fread(input, 1, 1000000, stdin);

    int positions = countRopeUniquePositions(input);
    printf("Positions: %d\n", positions);

    free(input);
    return 0;
}
