#include <stdlib.h>

#include "chunk.h"
#include "memory.h" // NOTE: verify this include - should it be on the .h file

void initChunk(Chunk *chunk)
{
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    // Order matters
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line)
{
    // 1. Allocate a new array with more capacity.
    // 2. Copy the existing elements from the old array to the new one.
    // 3. Store the new capacity.
    // 4. Delete the old array.
    // 5. Update code to point to the new array.
    // 6. Store the element in the new array now that there is room.
    // 7. Update the count.

    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);                                 // 3
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity); // 1, 2, 4, 5
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);   // 1, 2, 4, 5
    }

    chunk->code[chunk->count] = byte; // 6
    chunk->lines[chunk->count] = line;
    chunk->count++; // 7
}

int addConstant(Chunk *chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}