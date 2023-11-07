#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"

typedef struct Stack {
    char crates[128];
    int top;
} Stack;

char g_assertMsg[1024];
int g_testsRun = 0;

static void crateMover9000(Stack *stacks, int stackCount, int source, int destination,
                      int quantity);
static void crateMover9001(Stack *stacks, int stackCount, int source, int destination,
                      int quantity);

static char *testCraneMover9000(void);
static char *testCraneMover9000(void);
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

    // [G]                 [D] [R]
    // [W]         [V]     [C] [T] [M]
    // [L]         [P] [Z] [Q] [F] [V]
    // [J]         [S] [D] [J] [M] [T] [V]
    // [B]     [M] [H] [L] [Z] [J] [B] [S]
    // [R] [C] [T] [C] [T] [R] [D] [R] [D]
    // [T] [W] [Z] [T] [P] [B] [B] [H] [P]
    // [D] [S] [R] [D] [G] [F] [S] [L] [Q]
    //  1   2   3   4   5   6   7   8   9
    Stack stacks1[9] = {{"DTRBJLWG", 8}, {"SWC", 3},     {"RZTM", 4},
                       {"DTCHSPV", 7},  {"GPTLDZ", 6},  {"FBRZJQCD", 8},
                       {"SBDJMFTR", 8}, {"LHRBTVM", 7}, {"QPDSV", 5}};
    Stack stacks2[9] = {{"DTRBJLWG", 8}, {"SWC", 3},     {"RZTM", 4},
                       {"DTCHSPV", 7},  {"GPTLDZ", 6},  {"FBRZJQCD", 8},
                       {"SBDJMFTR", 8}, {"LHRBTVM", 7}, {"QPDSV", 5}};

    int quantity, source, destination;
    while (scanf("%d %d %d", &quantity, &source, &destination) != EOF) {
        crateMover9000(stacks1, 9, source - 1, destination - 1, quantity);
        crateMover9001(stacks2, 9, source - 1, destination - 1, quantity);
    }

    char resultCrates1[10] = {0};
    char resultCrates2[10] = {0};
    for (int i = 0; i < 9; ++i) {
        resultCrates1[i] = stacks1[i].crates[stacks1[i].top - 1];
        resultCrates2[i] = stacks2[i].crates[stacks2[i].top - 1];
    }
    printf("CraneMover9000: %s\n", resultCrates1);
    printf("CraneMover9001: %s\n", resultCrates2);

    return 0;
}

static void crateMover9000(Stack *stacks, int stackCount, int source, int destination,
                      int quantity) {
    if (source >= stackCount) {
        fprintf(stderr, "Invalid source: %d\n", source);
    }
    if (destination >= stackCount) {
        fprintf(stderr, "Invalid destination: %d\n", destination);
    }

    for (int i = 0; i < quantity; ++i) {
        if (stacks[source].top > 0) {
            // pop
            char crate = stacks[source].crates[stacks[source].top - 1];
            --stacks[source].top;

            // push
            stacks[destination].crates[stacks[destination].top] = crate;
            ++stacks[destination].top;
        }
    }
}

static void crateMover9001(Stack *stacks, int stackCount, int source, int destination,
                      int quantity) {
    if (source >= stackCount) {
        fprintf(stderr, "Invalid source: %d\n", source);
    }
    if (destination >= stackCount) {
        fprintf(stderr, "Invalid destination: %d\n", destination);
    }

    for (int i = 0; i < quantity; ++i) {
        int index = stacks[source].top - quantity + i;
        int crate = stacks[source].crates[index];

        // push
        stacks[destination].crates[stacks[destination].top] = crate;
        ++stacks[destination].top;
    }

    stacks[source].top -= quantity;
}

static char *testCraneMover9000(void) {
    Stack stacks1[3] = {{"ZN", 2}, {"MCD", 3}, {"P", 1}};

    crateMover9000(stacks1, 3, 1, 0, 1);
    crateMover9000(stacks1, 3, 0, 2, 3);
    crateMover9000(stacks1, 3, 1, 0, 2);
    crateMover9000(stacks1, 3, 0, 1, 1);

    MU_ASSERT(stacks1[0].crates[stacks1[0].top - 1] == 'C',
              "Part One: Stack 1 should have a C on top");
    MU_ASSERT(stacks1[1].crates[stacks1[1].top - 1] == 'M',
              "Part One: Stack 2 should have a M on top");
    MU_ASSERT(stacks1[2].crates[stacks1[2].top - 1] == 'Z',
              "Part One: Stack 1 should have a Z on top");

    MU_PASS;
}

static char *testCraneMover9001(void) {
    Stack stacks2[3] = {{"ZN", 2}, {"MCD", 3}, {"P", 1}};

    crateMover9001(stacks2, 3, 1, 0, 1);
    crateMover9001(stacks2, 3, 0, 2, 3);
    crateMover9001(stacks2, 3, 1, 0, 2);
    crateMover9001(stacks2, 3, 0, 1, 1);

    MU_ASSERT(stacks2[0].crates[stacks2[0].top - 1] == 'M',
              "Part Two: Stack 1 should have a C on top");
    MU_ASSERT(stacks2[1].crates[stacks2[1].top - 1] == 'C',
              "Part Two: Stack 2 should have a M on top");
    MU_ASSERT(stacks2[2].crates[stacks2[2].top - 1] == 'D',
              "Part Two: Stack 1 should have a Z on top");

    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testCraneMover9000);
    MU_TEST(testCraneMover9001);
    MU_PASS;
}
