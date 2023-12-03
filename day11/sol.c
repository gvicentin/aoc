#include "sol.h"

int compareLevel(const void *a, const void *b) {
    return *((uint64_t *)b) - *((uint64_t *)a);
}

void execute_round(struct monkey *ms, uint64_t *inspectedItems, int mCount, int worryDec) {
    for (int m = 0; m < mCount; ++m) {
        while (ms[m].iStart != ms[m].iEnd) {
            int item = ms[m].iStart;
            ms[m].iStart = (ms[m].iStart + 1) % NOITEMS;
            ++inspectedItems[m];

            int worryLevel = ms[m].items[item];
            int operand = ms[m].isCustomOperand ? ms[m].customOperand : worryLevel;

            switch (ms[m].operation) {
                case OP_ADD:
                    worryLevel += operand;
                    break;
                case OP_MIN:
                    worryLevel -= operand;
                    break;
                case OP_MUL:
                    worryLevel *= operand;
                    break;
                case OP_DIV:
                    worryLevel /= operand;
                    break;
            }

            // get borred
            worryLevel /= worryDec;

            int tMonkey =
                (worryLevel % ms[m].div == 0) ? ms[m].trueMonkey : ms[m].falseMonkey;
            
            ms[tMonkey].items[ms[tMonkey].iEnd] = worryLevel;
            ms[tMonkey].iEnd = (ms[tMonkey].iEnd + 1) % NOITEMS;
        }
    }
}
