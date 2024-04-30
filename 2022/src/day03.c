#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

static int calculatePriority(const char *rucksack);
static int calculatePriorityForGroup(const char *rucksackGroup);
static void calculateTotalPriority(FILE *stream, int *priority, int *priorityGroup);

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

    int priority, priorityGroup;
    calculateTotalPriority(stdin, &priority, &priorityGroup);
    printf("Total priority: %d\n", priority);
    printf("Total priority group: %d\n", priorityGroup);

    return 0;
}

static int calculatePriority(const char *rucksack) {
    static int items[52];

    // zero items
    memset(items, 0, 52 * sizeof(int));

    size_t halfIndex = strlen(rucksack) / 2;
    for (size_t i = 0; i < strlen(rucksack); ++i) {
        int itemIndex =
            isupper(rucksack[i]) ? rucksack[i] - 'A' + 26 : rucksack[i] - 'a';

        if (i < halfIndex) {
            ++items[itemIndex];
        }

        if (items[itemIndex] > 0 && i >= halfIndex) {
            return itemIndex + 1;
        }
    }

    return 0;
}

static int calculatePriorityForGroup(const char *rucksackGroup) {
    static int items[52];
    int groupValues[] = { 0x01, 0x02, 0x04 };
    int currentGroup = 0;

    // zero items
    memset(items, 0, 52 * sizeof(int));

    for (size_t i = 0; i < strlen(rucksackGroup); ++i) {
        int itemIndex =
            isupper(rucksackGroup[i]) ? rucksackGroup[i] - 'A' + 26 : rucksackGroup[i] - 'a';

        if (rucksackGroup[i] == '\n') {
            ++currentGroup;
        } else {
            items[itemIndex] |= groupValues[currentGroup];
        }
    }

    for (int i = 0; i < 52; ++i) {
        if (items[i] == 0x07) {
            return i + 1;
        }
    }

    return 0;
}

static void calculateTotalPriority(FILE *stream, int *priority, int *priorityGroup) {
    char rucksack[64], rucksackGroup[256];
    int totalPriority = 0, totalPriorityGroup = 0;
    int counter = 1;

    while (fscanf(stream, "%63s", rucksack) != EOF) {
        strncat(rucksackGroup, rucksack, 62);
        strncat(rucksackGroup, "\n", 2);

        totalPriority += calculatePriority(rucksack);
        if (counter++ % 3 == 0) {
            totalPriorityGroup += calculatePriorityForGroup(rucksackGroup);
            memset(rucksackGroup, 0, 256);
        }
    }

    *priority = totalPriority;
    *priorityGroup = totalPriorityGroup;
}

static char *testCalculatePriority(void) {
    const char *rucksacks[] = {
        "vJrwpWtwJgWrhcsFMMfFFhFp\n", "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n",
        "PmmdzqPrVvPwwTWBwg\n",       "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n",
        "ttgJtRGJQctTZtZT\n",         "CrZsJsPPZsGzwwsLwLmpwMDw\n"};
    int expectedPriorities[] = {16, 38, 42, 22, 20, 19};
    int count = sizeof(expectedPriorities)/sizeof(expectedPriorities[0]);

    for (int i = 0; i < count; ++i) {
        int priority = calculatePriority(rucksacks[i]);
        MU_ASSERT_FMT(expectedPriorities[i] == priority,
                      "Expect priority (%d), but got (%d)", expectedPriorities[i],
                      priority);
    }

    MU_PASS;
}

static char *testCalculatePriorityForGroup(void) {
    const char *rucksacks[] = {
        "vJrwpWtwJgWrhcsFMMfFFhFp\njqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\nPmmdzqPrVvPwwTWBwg\n",
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\nttgJtRGJQctTZtZT\nCrZsJsPPZsGzwwsLwLmpwMDw\n"};
    int expectedPriorities[] = {18, 52};
    int count = sizeof(expectedPriorities)/sizeof(expectedPriorities[0]);

    for (int i = 0; i < count; ++i) {
        int priority = calculatePriorityForGroup(rucksacks[i]);
        MU_ASSERT_FMT(expectedPriorities[i] == priority,
                      "Expect priority (%d), but got (%d)", expectedPriorities[i],
                      priority);
    }

    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testCalculatePriority);
    MU_TEST(testCalculatePriorityForGroup);
    MU_PASS;
}
