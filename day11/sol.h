#ifndef SOL_H
#define SOL_H

#include <stdbool.h>
#include <stdint.h>

#define NOITEMS 256

typedef enum operation {
    OP_ADD = 0,
    OP_MUL,
} OPERATION;

struct monkey {
    uint64_t items[NOITEMS];
    int iStart, iEnd;
    OPERATION operation;
    bool isCustomOperand;
    int customOperand;
    int div;
    int trueMonkey, falseMonkey;
};

int compareLevel(const void *a, const void *b);
void execute_round(struct monkey *ms, uint64_t *inspectedItems, 
                   int mCount, bool worryMore);

#endif  // !SOL_H
