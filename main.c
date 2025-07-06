#include "common.h"
#include "chunk.h"
#include "clox_debug.h"
#include "mem/amalloc.h"
#include "mem/mem_class.h"
#include "mem/ammap/ammap.h"

int main() 
{
    Chunk chunk;
    unsigned int const_idx = 0;
    initChunk(&chunk);

    /* check constants */
    const_idx = add_constant(&chunk, 1.2);

    /* | opcode | value_idx | */
    writeChunk(&chunk, OP_CONSTANT);
    writeChunk(&chunk, const_idx);

    writeChunk(&chunk, OP_RETURN);

    disasm_chunk(&chunk, "test_impl");
    freeChunk(&chunk);
    return 0;
}
