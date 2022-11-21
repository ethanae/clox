#include <stdlib.h>
#include <stdio.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk *chunk)
{
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    chunk->line_c = 0;
    initValueArray(&chunk->constants);
}

static void mapLineNumber(Chunk *chunk, int line)
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

static void checkCapacity(Chunk *chunk, int upperBound)
{
    if (chunk->capacity < chunk->count + upperBound)
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
}

const UINT24_MAX = 16777215;
void writeConstant(Chunk *chunk, Value value, int line)
{
    if (*(&chunk->constants.count) + 1 > UINT24_MAX) 
    {
        printf("Found too many constants. Max allowed constants: %d", UINT24_MAX);
    } 
    else 
    {
        uint24_t i = pack_24(chunk->constants.count);
        writeValueArray(&chunk->constants, value);
        writeChunk(chunk, i.d[0], line);
        writeChunk(chunk, i.d[1], line);
        writeChunk(chunk, i.d[2], line);
    }
}

void writeChunk(Chunk *chunk, uint8_t byte, int line)
{
    checkCapacity(chunk, 1);

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
