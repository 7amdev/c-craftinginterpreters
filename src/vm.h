#ifndef clox_vm_h
#define clox_vm_h

#include "object.h"
#include "chunk.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct
{
    // ObjFunction *function;
    ObjClosure *closure;
    uint8_t *ip;
    Value *vm_stack_pointer;
} CallFrame;

typedef struct
{
    CallFrame frames[FRAMES_MAX]; // Call Stack
    int frameCount;

    Value stack[STACK_MAX]; // Value Stack
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