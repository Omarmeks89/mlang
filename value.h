#ifndef VALUE_H
#define VALUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#define ALIGNED_BY_16BITS                   16

typedef double Value;

typedef struct __attribute__((aligned(ALIGNED_BY_16BITS))) {
    unsigned int                            cap;
    unsigned int                            count;
    Value                                   *values;
} ValueArray;

void initValueArray(ValueArray *va);
void writeValueArray(ValueArray *va, Value value);
void freeValueArray(ValueArray *va);
void print_value(Value value);

#ifdef __cplusplus
}
#endif                                      /* __cplusplus */

#endif                                      /* VALUE_H */
