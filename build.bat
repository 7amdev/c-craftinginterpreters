@echo off

rmdir /S /Q build
mkdir build
pushd build
cl /Fe:clox.exe /Zi ../src/*.cpp 
popd