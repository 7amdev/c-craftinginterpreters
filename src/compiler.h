#ifndef clox_compile_h
#define clox_compile_h

#include "vm.h"

ObjFunction *compile(const char *source);
void markCompilerRoots();

#endif