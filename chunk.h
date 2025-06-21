#ifndef CHUNK_H
#define CHUNK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "value.h"

typedef enum {
    OP_RETURN,                              /* return from current function */
    OP_CONSTANT                             /* produce constant */
} OpCode;

/* make array for op codes */
typedef struct {
    unsigned int            count;
    unsigned int            cap;            /* if cap is done we will make realloc */
    uint8_t                 *code;          /* pointer on array of opcodes */
    ValueArray              constants;      /* constants of type 'Value' */
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t op_code);
void freeChunk(Chunk *chunk);
unsigned int add_constant(Chunk *chunk, Value value);


#ifdef __cplusplus
}
#endif                                      /* __cplusplus */

#endif                                      /* CHUNK_H */
