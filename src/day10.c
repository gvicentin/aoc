#include <stdio.h>
#include <string.h>

#define XREG_START   1
#define CYCLE_START 20
#define CYCLE_INC   40
#define CRT_WIDTH   40
#define CRT_HEIGHT   6

int
main(int argc, char *argv[])
{
    int cycles = 1;
    int sum_strength = 0;
    int xreg = XREG_START;
    int signal_cycle = CYCLE_START;
    char crt[CRT_HEIGHT * CRT_WIDTH];

    char token[64];
    while (scanf("%63s", token) != EOF) {
        int op_cycles = 0;
        int param = 0;

        if (strcmp(token, "noop") == 0) {
            // NOTE(gvicentin): No operation
            op_cycles = 1;
        }
        else if (strcmp(token, "addx") == 0) {
            // NOTE(gvicentin): Add operation
            scanf("%d", &param);
            op_cycles = 2;
        }
        else {
            // NOTE(gvicentin): Invalid operation
            fprintf(stderr, "Operation (%s) not supported", token);
        }

        while (op_cycles-- > 0) {
            if (cycles == signal_cycle) {
                // NOTE(gvicentin): Accumulate strength signal
                sum_strength += cycles * xreg;
                signal_cycle += CYCLE_INC;
            }

            int row_cycles = cycles % CRT_WIDTH;
            crt[cycles - 1] = (row_cycles - 2 <= xreg && xreg <= row_cycles) ? '#' : '.';
            ++cycles;
        }

        xreg += param;
    }
    
    printf("Strength sum: %d\n\n", sum_strength);

    printf("--- CRT ---\n");
    for (int y = 0; y < CRT_HEIGHT; ++y) {
        for (int x = 0; x < CRT_WIDTH; ++x) {
            printf("%c", crt[y * CRT_WIDTH + x]);
        }
        printf("\n");
    }

    return 0;
}
