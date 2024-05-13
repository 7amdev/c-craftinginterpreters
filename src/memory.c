#include <stdlib.h>

#include "memory.h"

// https://stackoverflow.com/questions/12134315/realloc-on-null-valued-or-undefined-pointer
void *reallocate(void *pointer, size_t oldSize, size_t newSize)
{
    if (newSize == 0)
    {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, newSize);
    if (result == NULL)
    {
        exit(1);
    }

    return result;
}