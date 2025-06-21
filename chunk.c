#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk *chunk)
{
    /* we have to have pointer contract above */
    chunk->count         = 0;
    chunk->cap           = 0;
    chunk->code          = NULL;
    
    /* init ValueArray */
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t op_code)
{
    if (chunk->cap < chunk->count + 1)
    {
        unsigned int old_cap = chunk->cap;
        chunk->cap = GROW_CAPACITY(old_cap);
        chunk->code = GROW_UINT8_T_ARRAY(chunk->code,
                                    old_cap, chunk->cap);
    }

    chunk->code[chunk->count] = op_code;
    chunk->count++;
}

void freeChunk(Chunk *chunk)
{
    FREE_UINT8_T_ARRAY(chunk->code, chunk->cap);

    /* set valid empty state for chunk
     * avoid access to uninitialized memory */
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

unsigned int add_constant(Chunk *chunk, Value value)
{
    writeValueArray(&chunk->constants, value);

    /* return current index (len(x) - 1) */
    return chunk->constants.count - 1;
}
