#include <stdlib.h>                                     /* for malloc */

#include "memory.h"

void *
reallocate(void *ptr, size_t old_size, size_t new_size)
{
    /* old_size = 0, new_size != 0 -> allocate new block
     * old_size != 0, new_size = 0 -> free allocated
     * old_size != 0, new_size < old_size -> shrink pointer
     * old_size != 0, new_size > old_size -> grow pointer */

    void *result = NULL;
    size_t alloc_size = 0;

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    alloc_size = (old_size < new_size) ? new_size : old_size;

    result = realloc(ptr, alloc_size);
    if (result == NULL) exit(1);

    return result;
}
