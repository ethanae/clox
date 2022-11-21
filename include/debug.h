#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstr(Chunk* chunk, int offset);
void printArray(int arr[], size_t s);

#endif