#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

#define SHAPE_COUNT 3

#define OPPONENT_ROCK 'A'
#define PLAYER_ROCK   'X';

typedef enum {
    SCORE_LOSS = 0,
    SCORE_DRAW,
    SCORE_WIN,
    SCORE_COUNT
} ScoreType;

static int g_shapeScore[] = {1, 2, 3};
static int g_outcomeScore[] = {0, 3, 6};

char g_assertMsg[1024];
int g_testsRun = 0;

static void calculateScore(FILE *stream, int *score, int *guideScore);

static char *testCalculateScoreCase1(void);
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

    int score, guideScore;
    calculateScore(stdin, &score, &guideScore);
    printf("Score: %d\n", score);
    printf("Guide Score: %d\n", guideScore);

    return 0;
}

static void calculateScore(FILE *stream, int *score, int *guideScore) {
    char opponentChar, playerChar;
    *score = 0;
    *guideScore = 0;

    while (fscanf(stream, "%c %c\n", &opponentChar, &playerChar) != EOF) {
        int opponent = opponentChar - OPPONENT_ROCK;

        int player = playerChar - PLAYER_ROCK;
        int outcome = g_outcomeScore[SCORE_LOSS];
        outcome =
            player == opponent ? g_outcomeScore[SCORE_DRAW] : outcome;  // check draw
        outcome = player == (opponent + 1) % SHAPE_COUNT ? g_outcomeScore[SCORE_WIN]
                                                         : outcome;
        *score += g_shapeScore[player] + outcome;

        // guided
        int guideOutcome = playerChar - PLAYER_ROCK;
        int guidePlayer = opponent + guideOutcome - 1;
        guidePlayer = guidePlayer < 0 ? SHAPE_COUNT - 1 : guidePlayer;
        guidePlayer = guidePlayer == SHAPE_COUNT ? 0 : guidePlayer;
        *guideScore += g_outcomeScore[guideOutcome] + g_shapeScore[guidePlayer];
    }
}

static char *testCalculateScoreCase1(void) {
    FILE *tempFile;
    char *testInput = "A Y\nB X\nC Z\n";

    tempFile = muTempFile("/tmp/day1_test.in", testInput);

    int score, guideScore;
    calculateScore(tempFile, &score, &guideScore);
    MU_ASSERT_FMT(15 == score, "Expect score (%d) but got (%d)", 15, score);
    MU_ASSERT_FMT(12 == guideScore, "Expect guided score (%d) but got (%d)", 12,
                  guideScore);

    fclose(tempFile);
    MU_PASS;
}

static char *testCalculateScoreCase2(void) {
    FILE *tempFile;
    char *testInput = "C Z\nB Z\nC X\nB Z\nB Z\nA X\nC Z\nB X\nA Y\nC Y\n";

    tempFile = muTempFile("/tmp/day2_test.in", testInput);

    int score, guideScore;
    calculateScore(tempFile, &score, &guideScore);
    MU_ASSERT_FMT(61 == score, "Expect score (%d) but got (%d)", 61, score);
    MU_ASSERT_FMT(57 == guideScore, "Expect guided score (%d) but got (%d)", 57,
                  guideScore);

    fclose(tempFile);
    MU_PASS;
}

static char *allTests(void) {
    MU_TEST(testCalculateScoreCase1);
    MU_TEST(testCalculateScoreCase2);
    MU_PASS;
}
