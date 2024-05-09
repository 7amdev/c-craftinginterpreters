@echo off

rmdir /S /Q build
mkdir build
pushd build
cl /TC /Fe:clox.exe /Zi ../src/*.c 
popd