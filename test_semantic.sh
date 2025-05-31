#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Build the compiler
echo "Building NOVA compiler..."
make clean
make

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed${NC}"
    exit 1
fi

# Function to run a test
run_test() {
    local test_file=$1
    local expected_status=$2
    local test_name=$(basename $test_file)
    
    echo -n "Testing $test_name... "
    
    ./nova_compiler $test_file > /dev/null 2>&1
    local status=$?
    
    if [ $status -eq $expected_status ]; then
        echo -e "${GREEN}PASSED${NC}"
    else
        echo -e "${RED}FAILED${NC}"
        echo "Expected status: $expected_status, got: $status"
        exit 1
    fi
}

# Run valid test
run_test "tests/test_semantic_valid.nova" 0

# Run error test
run_test "tests/test_semantic_errors.nova" 1

echo -e "\n${GREEN}All tests passed!${NC}" 