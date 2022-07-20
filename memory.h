#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : capacity * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * oldCount, sizeof(type) * newCount)

void* reallocate(void* pointer, size_t oldCount, size_t newCount);

#define FREE_ARRAY(type, ptr, capacity) \
    reallocate(ptr, sizeof(type) * capacity, 0)

#endif
