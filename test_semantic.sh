#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo "Testing Semantic Analyzer"
echo "------------------------"

# Compile the compiler if needed
echo "Compiling the compiler..."
make clean
make

if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed${NC}"
    exit 1
fi

# Test semantic analysis
echo -e "\nRunning semantic analysis on test file..."
./nova_compiler test_semantic.nova

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Semantic analysis completed successfully${NC}"
else
    echo -e "${RED}Semantic analysis failed${NC}"
    exit 1
fi

# Test invalid cases
echo -e "\nTesting invalid cases..."

# Test 1: Undefined variable
echo "Test 1: Using undefined variable"
cat > test_invalid1.nova << EOF
main() {
    ra9m x = y;  // y is undefined
    rje3 0;
}
EOF

./nova_compiler test_invalid1.nova
if [ $? -eq 0 ]; then
    echo -e "${RED}Test 1 failed: Should detect undefined variable${NC}"
else
    echo -e "${GREEN}Test 1 passed: Correctly detected undefined variable${NC}"
fi

# Test 2: Type mismatch
echo -e "\nTest 2: Type mismatch in assignment"
cat > test_invalid2.nova << EOF
main() {
    ra9m x = "string";  // Type mismatch
    rje3 0;
}
EOF

./nova_compiler test_invalid2.nova
if [ $? -eq 0 ]; then
    echo -e "${RED}Test 2 failed: Should detect type mismatch${NC}"
else
    echo -e "${GREEN}Test 2 passed: Correctly detected type mismatch${NC}"
fi

# Test 3: Function call with wrong number of arguments
echo -e "\nTest 3: Function call with wrong number of arguments"
cat > test_invalid3.nova << EOF
ra9m add(ra9m a, ra9m b) {
    rje3 a + b;
}

main() {
    ra9m x = add(1);  // Missing argument
    rje3 0;
}
EOF

./nova_compiler test_invalid3.nova
if [ $? -eq 0 ]; then
    echo -e "${RED}Test 3 failed: Should detect wrong number of arguments${NC}"
else
    echo -e "${GREEN}Test 3 passed: Correctly detected wrong number of arguments${NC}"
fi

# Clean up
rm -f test_invalid*.nova

echo -e "\nAll tests completed!" 