#include <stdio.h>

#include "value.h"
#include "memory.h"

void initValueArray(ValueArray *va)
{
    va->cap                 = 0;
    va->count               = 0;
    va->values              = NULL;
}

void writeValueArray(ValueArray *va, Value value)
{
    if (va->cap < va->count + 1)
    {
        unsigned int old_cap = va->cap;
        va->cap = GROW_CAPACITY(old_cap);
        va->values = GROW_VALUE_ARRAY(va->values, old_cap, va->cap);
    }

    va->values[va->count] = value;
    va->count++;
}

void freeValueArray(ValueArray *va)
{
    FREE_VALUE_ARRAY(va->values, va->cap);
    initValueArray(va);
}

void print_value(Value value)
{
    printf("%g", value);
}
