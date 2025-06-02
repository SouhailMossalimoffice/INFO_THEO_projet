@echo off
echo Running all test files...

echo.
echo Running test_control.nova...
test_one.bat tests\test_control.nova

echo.
echo Running test_arithmetic.nova...
test_one.bat tests\test_arithmetic.nova

echo.
echo Running test_variables.nova...
test_one.bat tests\test_variables.nova

echo.
echo Running test_func.nova...
test_one.bat tests\test_func.nova

echo.
echo Running test_print.nova...
test_one.bat tests\test_print.nova

echo.
echo Running test_errors.nova...
test_one.bat tests\test_errors.nova

echo.
echo Running test_jadwal.nova...
test_one.bat tests\test_jadwal.nova

echo.
echo Running test_lists.nova...
test_one.bat tests\test_lists.nova

echo.
echo Running test_functions.nova...
test_one.bat tests\test_functions.nova

echo.
echo Running test_minimal.nova...
test_one.bat tests\test_minimal.nova

echo.
echo Running test_main_only.nova...
test_one.bat tests\test_main_only.nova

echo.
echo Running test_semantic_errors.nova...
test_one.bat tests\test_semantic_errors.nova

echo.
echo Running test_semantic_valid.nova...
test_one.bat tests\test_semantic_valid.nova

echo.
echo All tests completed! 