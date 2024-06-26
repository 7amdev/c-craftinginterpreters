#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "table.h"
#include "value.h"

#define STACK_MAX 256

typedef struct
{
    Chunk *chunk; // bytecode instructions
    uint8_t *ip;  // (i)nstruction (p)ointer
    Value stack[STACK_MAX];
    Value *stackTop;
    Table globals;
    Table strings;
    Obj *objects; // A pointer to the head of the object linked-list
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
    INTERPRET_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();

#endif