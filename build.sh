#!/bin/bash

echo "==== Running on Windows ===="
flags="//Zi //TC"
libs=""
includes=""
outputFile="clox.exe"

rm -rf build
mkdir -p build
cd build
cl $flags //Fe:$outputFile  ../src/*.c 
cd - # back to project root directory
