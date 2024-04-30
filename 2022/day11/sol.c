#include "sol.h"

int compareLevel(const void *a, const void *b) {
    return *((uint64_t *)b) - *((uint64_t *)a);
}

void execute_round(struct monkey *ms, uint64_t *inspectedItems, int mCount, bool worryMore) {
    int divProduct = 1;
    for (int m = 0; m < mCount; ++m) {
        divProduct *= ms[m].div;
    }

    for (int m = 0; m < mCount; ++m) {
        while (ms[m].iStart != ms[m].iEnd) {
            int item = ms[m].iStart;
            ms[m].iStart = (ms[m].iStart + 1) % NOITEMS;
            ++inspectedItems[m];

            uint64_t worryLevel = ms[m].items[item];
            uint64_t operand = ms[m].isCustomOperand ? (uint64_t) ms[m].customOperand : worryLevel;

            switch (ms[m].operation) {
                case OP_ADD:
                    worryLevel += operand;
                    break;
                case OP_MUL:
                    worryLevel *= operand;
                    break;
            }

            worryLevel %= (uint64_t) divProduct;

            if (worryMore) 
                worryLevel /= 3;

            int tMonkey =
                (worryLevel % ms[m].div == 0) ? ms[m].trueMonkey : ms[m].falseMonkey;
            
            ms[tMonkey].items[ms[tMonkey].iEnd] = worryLevel;
            ms[tMonkey].iEnd = (ms[tMonkey].iEnd + 1) % NOITEMS;
        }
    }
}
