#ifndef MINUNIT_H
#define MINUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MU_PASS     return NULL
#define MU_MSG_FMT  "%s | %s::%d -> "
#define MU_MSG_ARGS __FILE__, __FUNCTION__, __LINE__

#define MU_ASSERT(test, message)                                   \
    do {                                                           \
        if (!(test)) {                                             \
            sprintf(g_assertMsg, MU_MSG_FMT message, MU_MSG_ARGS); \
            return g_assertMsg;                                    \
        }                                                          \
    } while (0)

#define MU_ASSERT_FMT(test, msg_format, ...)                                         \
    do {                                                                             \
        if (!(test)) {                                                               \
            sprintf(g_assertMsg, MU_MSG_FMT msg_format, MU_MSG_ARGS, ##__VA_ARGS__); \
            return g_assertMsg;                                                      \
        }                                                                            \
    } while (0)

#define MU_TEST(test)                \
    do {                             \
        char *message = test();      \
        g_testsRun++;                \
        if (message) return message; \
    } while (0)

extern char g_assertMsg[1024];
extern int g_testsRun;

static inline FILE *muTempFile(const char *filepath, char *content) {
    FILE *tempFile;

    tempFile = fopen(filepath, "w+");
    if (tempFile == NULL) {
        fprintf(stderr, "Failed to create temp file\n");
        exit(1);
    }

    fwrite(content, sizeof(char), strlen(content), tempFile);
    rewind(tempFile);

    return tempFile;
}

#endif  // MINUNIT_H
