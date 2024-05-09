@echo off

rmdir /S /Q build
mkdir build
pushd build
cl /Zi ../src/main.cpp
popd