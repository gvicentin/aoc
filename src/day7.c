#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"

#define MAX_FILENAME       64
#define MAX_FILENAME_FMT  "63"
#define MAX_CHILDREN_FILES 32
#define MAX_CHILDREN_DIRS  32

#define MAX_CALC_SIZE 100000

typedef struct File {
    char name[MAX_FILENAME];
    int size;
} File;

typedef struct Dir {
    struct Dir *parent;
    char name[MAX_FILENAME];
    int size, totalSize;
    // Ideally children directories and files should be a map
    // so we can retrieve them by name with O(1).
    // Also we could expand it to not wast so much memory.
    struct Dir *children[MAX_CHILDREN_DIRS];
    struct File files[MAX_CHILDREN_FILES];
    int childrenCount;
    int filesCount;
} Dir;

char g_assertMsg[1024];
int g_testsRun = 0;

static Dir *CreateFileSystem(const char *input);
static int CalculateTotalDirSize(Dir *dir);
static void AccumulateSizes(Dir *dir, int *accum);

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

    // read stdin in a big buffer
    char *input = malloc(1000000);
    int inputSize = fread(input, 1, 1000000, stdin);

    Dir *root = CreateFileSystem(input);
    int totalSize = 0;

    CalculateTotalDirSize(root);
    AccumulateSizes(root, &totalSize);
    printf("Total size: %d\n", totalSize);

    return 0;
}

static void InitDir(Dir *dir, const char *dirname, Dir *parent) {
    strncpy(dir->name, dirname, MAX_FILENAME);
    dir->parent = parent;
    dir->size = 0;
    dir->totalSize = 0;
    dir->filesCount = 0;
    dir->childrenCount = 0;
}

static int DirCreateFile(Dir *dir, const char *filename, int size) {
    int currentFilesCount = dir->filesCount;
    assert(currentFilesCount < MAX_CHILDREN_FILES);
    if (currentFilesCount >= MAX_CHILDREN_FILES) {
        fprintf(stderr, "Exceeded file count for dir (%s)\n", dir->name);
        return 1;
    }

    strncpy(dir->files[currentFilesCount].name, filename, MAX_FILENAME);
    dir->files[currentFilesCount].size = size;
    dir->size += size;
    ++dir->filesCount;
    return 0;
}

static int DirAddSubdir(Dir *dir, Dir *subdir) {
    int childrenCount = dir->childrenCount;
    assert(childrenCount < MAX_CHILDREN_DIRS);
    if (childrenCount >= MAX_CHILDREN_DIRS) {
        fprintf(stderr, "Exceeded children count for dir (%s)\n", dir->name);
        return 1;
    }

    dir->children[childrenCount] = subdir;
    ++dir->childrenCount;
    return 0;
}

static int CalculateTotalDirSize(Dir *dir) {
    int childrenSize = 0;
    for (int i = 0; i < dir->childrenCount; ++i) {
        childrenSize += CalculateTotalDirSize(dir->children[i]);
    }

    dir->totalSize = childrenSize + dir->size;
    return dir->totalSize;
}

static void AccumulateSizes(Dir *dir, int *accum) {
    for (int i = 0; i < dir->childrenCount; ++i) {
        AccumulateSizes(dir->children[i], accum);
    }

    if (dir->totalSize < MAX_CALC_SIZE) {
        *accum += dir->totalSize;
    }
}

static Dir *CreateFileSystem(const char *input) {
    Dir *root = NULL;

    // initialize root
    root = malloc(sizeof(Dir));
    InitDir(root, "/", NULL);

    char *inputCopy = strdup(input);
    char *lineSavePtr, *tokenSavePtr;
    Dir *currentDir = root;

    for (char *line = strtok_r(inputCopy, "\n", &lineSavePtr); line != NULL;
         line = strtok_r(NULL, "\n", &lineSavePtr)) {
        char *token = strtok_r(line, " ", &tokenSavePtr);
        if (strcmp(token, "$") == 0) {
            // command
            token = strtok_r(NULL, " ", &tokenSavePtr);
            if (strcmp(token, "cd") == 0) {
                // change directory
                token = strtok_r(NULL, " ", &tokenSavePtr);
                printf("Changing directory to %s\n", token);
                if (strcmp(token, "/") == 0) {
                    printf("Changing directory to root\n");
                    currentDir = root;
                } else if (strcmp(token, "..") == 0) {
                    printf("Returning one directory\n");
                    currentDir = currentDir->parent;
                } else {
                    // find directory to change
                    Dir *aux = NULL;
                    for (int i = 0; i < currentDir->childrenCount; ++i) {
                        if (strcmp(token, currentDir->children[i]->name) == 0) {
                            aux = currentDir->children[i];
                        }
                    }
                    if (aux != NULL) {
                        printf("Found subdir %s, entering it...\n", token);
                        currentDir = aux;
                    }
                }
            } else if (strcmp(token, "ls") == 0) {
                // listing directory
                printf("Listing current directory\n");
            } else {
                printf("Invalid command %s\n", token);
            }
        } else if (strcmp(token, "dir") == 0) {
            // print directory name
            token = strtok_r(NULL, " ", &tokenSavePtr);
            printf("Found dir with name %s\n", token);
            Dir *newDir = malloc(sizeof(Dir));
            InitDir(newDir, token, currentDir);
            DirAddSubdir(currentDir, newDir);
        } else {
            // print filesize and filename
            int filesize = atoi(token);
            char *filename = strtok_r(NULL, " ", &tokenSavePtr);
            printf("Found file with name %s and size %d\n", filename, filesize);
            DirCreateFile(currentDir, filename, filesize);
        }
    }

    // deinitialization
    free(inputCopy);
    return root;
}

static char *allTests(void) {
    const char *input =
        "$ cd /\n"
        "$ ls\n"
        "dir a\n"
        "14848514 b.txt\n"
        "8504156 c.dat\n"
        "dir d\n"
        "$ cd a\n"
        "$ ls\n"
        "dir e\n"
        "29116 f\n"
        "2557 g\n"
        "62596 h.lst\n"
        "$ cd e\n"
        "$ ls\n"
        "584 i\n"
        "$ cd ..\n"
        "$ cd ..\n"
        "$ cd d\n"
        "$ ls\n"
        "4060174 j\n"
        "8033020 d.log\n"
        "5626152 d.ext\n"
        "7214296 k";

    MU_PASS;
}
