@echo off
echo Running test_arithmetic.nova...
.\nova_compiler.exe tests\test_arithmetic.nova
gcc output.c -o output.exe
.\output.exe

echo.
echo Running test_control.nova...
.\nova_compiler.exe tests\test_control.nova
gcc output.c -o output.exe
.\output.exe

echo.
echo Running test_functions.nova...
.\nova_compiler.exe tests\test_functions.nova
gcc output.c -o output.exe
.\output.exe

echo.
echo Running test_lists.nova...
.\nova_compiler.exe tests\test_lists.nova
gcc output.c -o output.exe
.\output.exe

echo.
echo Running test_jadwal.nova...
.\nova_compiler.exe tests\test_jadwal.nova
gcc output.c -o output.exe
.\output.exe

echo.
echo Running test_errors.nova...
.\nova_compiler.exe tests\test_errors.nova
gcc output.c -o output.exe
.\output.exe

echo.
echo Running test_minimal.nova...
.\nova_compiler.exe tests\test_minimal.nova
gcc output.c -o output.exe
.\output.exe 