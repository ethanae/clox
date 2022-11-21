#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

typedef struct
{
    uint8_t d[3];
} uint24_t;

typedef uint32_t uint_least24_t;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);
uint_least24_t unpack_24(uint24_t n);
uint24_t pack_24(uint_least24_t n);

#endif