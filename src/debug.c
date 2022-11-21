#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk *chunk, const char *name)
{
    printf("== %s ==\n", name);
    for (int offset = 0; offset < chunk->count;)
    {
        offset = disassembleInstr(chunk, offset);
    }
}

static int simpleInstr(const char *name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

/**
 * @brief prints a four-byte instruction - the opcode and its three-byte operand
 * 
 * @param name instruction name
 * @param chunk code chunk
 * @param offset code offset
 * @return int offset of next instruction
 */
static int constantLongInstr(const char *name, Chunk *chunk, int offset)
{
    uint24_t c;
    c.d[0] = chunk->code[offset + 1];
    c.d[1] = chunk->code[offset + 2];
    c.d[2] = chunk->code[offset + 3];
    uint_least24_t i = unpack_24(c);
    printf("%-16s %4d '", name, offset + 1);
    printValue(chunk->constants.values[i]);
    printf("'\n");
    return offset + 4;
}

/**
 * @brief prints a two-byte instruction - the opcode and its operand
 * 
 * @param name instruction name
 * @param chunk code chunk
 * @param offset code offset
 * @return int offset of next instruction
 */
static int constantInstr(const char *name, Chunk *chunk, int offset)
{
    uint8_t constIdx = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constIdx);
    printValue(chunk->constants.values[constIdx]);
    printf("'\n");
    return offset + 2;
}

static int getLine(Chunk *chunk, int offset)
{
    for (int i = 0; i < chunk->line_c; i++)
    {
        if (offset <= chunk->lines[i])
        {
            return i + 1;
        }
    }
    return -1;
}

int disassembleInstr(Chunk *chunk, int offset)
{
    printf("%04d ", offset);
    printf("%4d ", getLine(chunk, offset));
    uint8_t instr = chunk->code[offset];
    switch (instr)
    {
    case OP_RETURN:
        return simpleInstr("OP_RETURN", offset);
    case OP_CONSTANT:
        return constantInstr("OP_CONSTANT", chunk, offset);
    case OP_CONSTANT_LONG:
        return constantLongInstr("OP_CONSTANT_LONG", chunk, offset);
    default:
        printf("Unknown opcode %d", instr);
        return offset + 1;
    }
}
