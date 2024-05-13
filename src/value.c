#include <stdio.h>

#include "memory.h"
#include "value.h"

void initValueArray(ValueArray *array)
{
    array->capacity = 0;
    array->count = 0;
    array->value = NULL;
}
void writeValueArray(ValueArray *array, Value value)
{
    if (array->capacity < array->count + 1)
    {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);                                 // 3
        array->value = GROW_ARRAY(Value, array->value, oldCapacity, array->capacity); // 1, 2, 4, 5
    }

    array->value[array->count] = value; // 6
    array->count++;                     // 7
}
void freeValueArray(ValueArray *array)
{
    FREE_ARRAY(Value, array->value, array->capacity);
    initValueArray(array);
}

void printValue(Value value)
{
    printf("%g", value);
}