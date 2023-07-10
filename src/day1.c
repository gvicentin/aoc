#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculateTop3Calories(FILE *stream, unsigned int *top3) {
    char lineBuff[64];
    unsigned int mostCalories = 0, elfCaloriesCount = 0;

    while (fgets(lineBuff, sizeof(lineBuff), stream) != NULL) {
        if (strlen(lineBuff) == 1) {
            // found an empty line
            elfCaloriesCount = 0;
            continue;
        }

        int calories = atoi(lineBuff);
        elfCaloriesCount += calories;

        if (elfCaloriesCount > mostCalories) {
            mostCalories = elfCaloriesCount;
        }
    }

    top3[0] = mostCalories;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int shouldCloseFile = 1;
    unsigned int top3[3];

    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "Failed to open file %s\n", argv[1]);
            return 1;
        }
    } else {
        fp = stdin;
        shouldCloseFile = 0;
    }

    calculateTop3Calories(fp, top3);
    printf("%u\n", top3[0]);

    if (shouldCloseFile) {
        fclose(fp);
    }

    return 0;
}
