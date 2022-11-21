#include <stdio.h>

#include "value.h"
#include "memory.h"

void initValueArray(ValueArray *array)
{
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

void writeValueArray(ValueArray *array, Value value)
{
    if (array->capacity < array->count + 1)
    {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray *array)
{
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void printValue(Value value)
{
    printf("%g", value);
}

uint_least24_t unpack_24(uint24_t n)
{
    return n.d[2] << 16 | n.d[1] << 8 | n.d[0];
}

uint24_t pack_24(uint_least24_t n)
{
    uint24_t i;
    i.d[0] = n;
    i.d[1] = n >> 8 & 0xff;
    i.d[2] = n >> 16 & 0xff;
    return i;
}
