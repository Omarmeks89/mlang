#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "chunk.h"

void disasm_chunk(Chunk *chunk, const char *name);              /* disasm all inside chunk */
unsigned int disasm_opcode(Chunk *chunk, unsigned int offset);

#ifdef __cplusplus
}
#endif

#endif
