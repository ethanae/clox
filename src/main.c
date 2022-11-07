#include "common.h"
#include "chunk.h"
#include "debug.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
    Chunk chunk;
    initChunk(&chunk);

    int index = addConstant(&chunk, 1.234567891234567);

    writeChunk(&chunk, OP_CONSTANT, 1);

    writeChunk(&chunk, index, 1);

    writeChunk(&chunk, OP_RETURN, 1);

    for (int i = 2; i < 21; i++)
    {
        writeChunk(&chunk, OP_RETURN, i);
    }
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}
