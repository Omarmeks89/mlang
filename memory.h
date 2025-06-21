#ifndef MEMORY_H
#define MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#define GROW_CAPACITY(c) ((c) < 8 ? (unsigned int) 8 : (unsigned int) (c * 2))

#define GROW_UINT8_T_ARRAY(code_ptr, old_cap, actual_cap) \
    (uint8_t *) reallocate(code_ptr, sizeof(uint8_t) * (old_cap), \
            sizeof(uint8_t) * (actual_cap))

#define FREE_UINT8_T_ARRAY(ptr, old_count) \
    reallocate(ptr, sizeof(uint8_t) * (old_count), 0)

/* macro for ValueArray */
#define GROW_VALUE_ARRAY(ptr, old_cap, new_cap) \
    (Value *) reallocate(ptr, sizeof(Value) * (old_cap), \
            sizeof(Value) * (new_cap))

#define FREE_VALUE_ARRAY(ptr, old_count) \
    reallocate(ptr, sizeof(Value) * (old_count), 0)

void *
reallocate(void *ptr, size_t old_size, size_t new_size);

#ifdef __cplusplus
}
#endif

#endif
