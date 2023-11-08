#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

char g_assertMsg[1024];
int g_testsRun = 0;

static int findStartOfPacket(const char *input);
static int findStartOfMessage(const char *input);
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

    char buff[10000];
    scanf("%9999s", buff);
    int startPackage = findStartOfPacket(buff);
    int startMessage = findStartOfMessage(buff);
    printf("Start of packet: %d\n", startPackage);
    printf("Start of message: %d\n", startMessage);

    return 0;
}

static bool isDistinct(const char *input, int start, int end) {
    int occurences[26] = {0};

    for (int i = start; i < end; ++i) {
        if (++occurences[input[i] - 'a'] > 1 )
            return false;
    }

    return true;
}

static int findStartOfPacket(const char *input) {
    for (int i = 0; i < strlen(input) - 4; ++i) {
        if (isDistinct(input, i, i + 4))
            return i + 4;
    }

    return 0;
};

static int findStartOfMessage(const char *input) {
    for (int i = 0; i < strlen(input) - 14; ++i) {
        if (isDistinct(input, i, i + 14))
            return i + 14;
    }

    return 0;
};

static char *testFindStartOfPacket(void) {
    const char *inputs[] = {
        "mjqjpqmgbljsphdztnvjfqwrcgsmlb",
        "bvwbjplbgvbhsrlpgdmjqwftvncz",
        "nppdvjthqldpwncqszvftbrmjlhg",
        "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
        "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw",
    };
    int expect[] = {7, 5, 6, 10, 11};

    for (int i = 0; i < sizeof(expect) / sizeof(expect[0]); ++i) {
        int got = findStartOfPacket(inputs[i]);
        MU_ASSERT_FMT(expect[i] == got, "For '%s', expect (%d) but got (%d)", inputs[i],
                      expect[i], got);
    }

    MU_PASS;
};

static char *testFindStartOfMessage(void) {
    const char *inputs[] = {
        "mjqjpqmgbljsphdztnvjfqwrcgsmlb",
        "bvwbjplbgvbhsrlpgdmjqwftvncz",
        "nppdvjthqldpwncqszvftbrmjlhg",
        "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
        "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw",
    };
    int expect[] = {19, 23, 23, 29, 26};

    for (int i = 0; i < sizeof(expect) / sizeof(expect[0]); ++i) {
        int got = findStartOfMessage(inputs[i]);
        MU_ASSERT_FMT(expect[i] == got, "For '%s', expect (%d) but got (%d)", inputs[i],
                      expect[i], got);
    }

    MU_PASS;
};

static char *allTests(void) {
    MU_TEST(testFindStartOfPacket);
    MU_TEST(testFindStartOfMessage);
    MU_PASS;
}
