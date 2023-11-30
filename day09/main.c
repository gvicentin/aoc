#include <stdio.h>
#include <stdlib.h>

#include "sol.h"

int main(int argc, char *argv[]) {
    char *input = malloc(1000000);
    fread(input, 1, 1000000, stdin);

    int positions = countRopeUniquePositions(input, 2);
    int positions2 = countRopeUniquePositions(input, 10);
    printf("Positions 1 knot: %d\n", positions);
    printf("Positions with 10 knots: %d\n", positions2);

    free(input);
    return 0;
}
