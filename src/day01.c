#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

static void updateTopRank(unsigned int *top3, unsigned int caloriesCount);
static void calculateTop3Calories(FILE *stream, unsigned int *top3);

static char *testGetTop3Calories(void);
static char *allTests(void);

int main(int argc, char *argv[]) {
    unsigned int top3Elfs[3] = {0};

    if (argc > 1 && (strcmp(argv[1], "--test") || strcmp(argv[1], "-t"))) {
        // run tests and exit
        char *testsResults = allTests();
        printf("Test count: %d\n", g_testsRun);
        if (testsResults != 0) {
            printf("Test failed\n");
            printf("%s\n", testsResults);
            return 1;
        }
        printf("All tests passed.\n");
        return 0;
    }

    // finding the answer
    calculateTop3Calories(stdin, top3Elfs);
    printf("Total calories (top 1 Elf): %u\n", top3Elfs[0]);
    printf("Total calories (top 3 Elfs): %u\n",
           top3Elfs[0] + top3Elfs[1] + top3Elfs[2]);

    return 0;
}

void updateTopRank(unsigned int *top3, unsigned int caloriesCount) {
    if (caloriesCount > top3[0]) {
        top3[2] = top3[1];
        top3[1] = top3[0];
        top3[0] = caloriesCount;
    } else if (caloriesCount > top3[1]) {
        top3[2] = top3[1];
        top3[1] = caloriesCount;
    } else if (caloriesCount > top3[2]) {
        top3[2] = caloriesCount;
    }
}

void calculateTop3Calories(FILE *stream, unsigned int *top3) {
    char lineBuff[64];
    unsigned int elfCaloriesCount = 0;

    while (fgets(lineBuff, sizeof(lineBuff), stream) != NULL) {
        if (strlen(lineBuff) == 1) {
            // found an empty line
            updateTopRank(top3, elfCaloriesCount);
            elfCaloriesCount = 0;
        }

        int calories = atoi(lineBuff);
        elfCaloriesCount += calories;
    }

    updateTopRank(top3, elfCaloriesCount);
}

static char *testGetTop3Calories(void) {
    FILE *tempFile;
    unsigned int top3[3] = {0};
    char *testInput =
        "1000\n2000\n3000\n\n4000\n\n5000\n"
        "6000\n\n7000\n8000\n9000\n\n10000\n";

    tempFile = muTempFile("/tmp/day1_test.in", testInput);

    calculateTop3Calories(tempFile, top3);
    MU_ASSERT_FMT(24000 == top3[0], "Top 1 calories should be %u, but got %u", 24000,
                  top3[0]);
    MU_ASSERT_FMT(45000 == top3[0] + top3[1] + top3[2],
                  "Top 3 calories total should be %u, but got %u", 45000,
                  top3[0] + top3[1] + top3[2]);

    fclose(tempFile);
    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testGetTop3Calories);
    MU_PASS;
}
