#ifndef VALUE_H
#define VALUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

typedef double Value;

typedef struct {
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
