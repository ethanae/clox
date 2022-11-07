#include <stdlib.h>
#include <stdio.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"
#include "debug.h"

void initChunk(Chunk *chunk)
{
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    chunk->line_c = 0;
    initValueArray(&chunk->constants);
}

static void mapLineNumber(Chunk* chunk, int line)
{
    if (line == 0)
    {
        chunk->lines[0] = chunk->count;
    }
    else
    {
        // code is on the same line as previous code
        // add the count to the same index
        chunk->lines[line - 1] = chunk->count;
    }
}

void writeConstant(Chunk* chunk, Value value, int line)
{

}

// ensure that subsequent calls to writeChunk do not skip line numbers
// this will bloat the backing store for instruction-line mappings
void writeChunk(Chunk *chunk, uint8_t byte, int line)
{
    // need to re-allocate
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(
            uint8_t,
            chunk->code,
            oldCapacity,
            chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    mapLineNumber(chunk, line);
    chunk->line_c = line;
    chunk->count++;
}

void freeChunk(Chunk *chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}
