#include <stdio.h>
#include <stdlib.h>

#include "clox_debug.h"
#include "chunk.h"
#include "value.h"

static unsigned int
simple_instruction(const char *name, unsigned int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

static unsigned int
constant_instruction(const char *name, Chunk *chunk, unsigned int offset)
{
    uint8_t opcode = chunk->code[offset + 1];

    /* print 2 immediate bytes: opcode and value by idx */
    printf("%-16s %4d '", name, opcode);
    print_value(chunk->constants.values[opcode]); /* ??? */
    printf("'\n");
    return offset + 2;
}

unsigned int disasm_opcode(Chunk *chunk, unsigned int offset)
{
    printf("%04d ", offset);

    uint8_t opcode = chunk->code[offset];
    switch (opcode)
    {
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", chunk, offset);
        default:
            printf("unknown opcode %d\n", opcode);
            exit(1);
    }
    return (unsigned int) 0;
}

void
disasm_chunk(Chunk *chunk, const char *name)
{
    printf("=== %s ===\n", name);

    unsigned int canary = 0;
    unsigned int i = 0;
    for (i = 0; i < chunk->count;)
    {
        if (canary > i)
        {
            printf("OWF\n");
            exit(1);
        }

        canary = i;
        i = disasm_opcode(chunk, i);

    }
}

