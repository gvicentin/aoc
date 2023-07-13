#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

static int calculateTotalPriority(FILE *stream);

static char *testCalculatePriority(void);
static char *allTests(void);

int main(int argc, char *argv[]) {
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

    int priority = calculateTotalPriority(stdin);
    printf("Total priority: %d\n", priority);

    return 0;
}

static int calculateTotalPriority(FILE *stream) {
    char lineBuff[256];
    int items[52];
    int totalPriority = 0;

    while (fscanf(stream, "%255s", lineBuff) != EOF) {
        size_t halfIndex = strlen(lineBuff) / 2;

        memset(items, 0, 52 * sizeof(int));
        for (size_t i = 0; i <= strlen(lineBuff); ++i) {
            int itemIndex =
                isupper(lineBuff[i]) ? lineBuff[i] - 'A' + 26 : lineBuff[i] - 'a';

            if (i < halfIndex) {
                ++items[itemIndex];
            }

            if (items[itemIndex] > 0 && i >= halfIndex) {
                totalPriority += itemIndex + 1;
                break;
            }
        }
    }

    return totalPriority;
}

static char *testCalculatePriority(void) {
    FILE *tempFile;
    char *testInput =
        "vJrwpWtwJgWrhcsFMMfFFhFp\n"
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n"
        "PmmdzqPrVvPwwTWBwg\n"
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n"
        "ttgJtRGJQctTZtZT\n"
        "CrZsJsPPZsGzwwsLwLmpwMDw\n";

    tempFile = muTempFile("/tmp/day2_test.in", testInput);

    int priority = calculateTotalPriority(tempFile), expectedPriority = 157;
    MU_ASSERT_FMT(expectedPriority == priority, "Expect priority (%d) but got (%d)",
                  expectedPriority, priority);

    fclose(tempFile);
    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testCalculatePriority);
    MU_PASS;
}
