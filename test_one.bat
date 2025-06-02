@echo off
echo Compiling and running %1...
.\nova_compiler.exe %1
gcc output.c -o output.exe
echo.
echo Output:
.\output.exe
echo. 