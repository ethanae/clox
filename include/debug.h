#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);
int getLine(Chunk *chunk, int offset);
void printArray(int arr[], size_t s);

#endif