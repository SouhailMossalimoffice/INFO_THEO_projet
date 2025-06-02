#!/bin/bash

echo "=== Compiling NOVA compiler ==="
flex LazyUi_Analex.l && bison -d LazyUi_Parser.y && gcc -o nova_compiler lex.yy.c LazyUi_Parser.tab.c ast.c -ll

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo -e "\n=== Testing valid NOVA code ==="
./nova_compiler test_lexer.nova

echo -e "\n=== Testing invalid NOVA code ==="
./nova_compiler test_parser_invalid.nova

echo -e "\n=== Testing specific features ==="

# Test des expressions arithmétiques
echo -e "\nTesting arithmetic expressions..."
cat > test_arithmetic.nova << EOF
taarif ra9m x = 10 + 5 * 2;
taarif ra9m y = (20 - 8) / 4;
taarif ra9m z = 100 div 3;
EOF
./nova_compiler test_arithmetic.nova

# Test des structures de contrôle
echo -e "\nTesting control structures..."
cat > test_control.nova << EOF
taarif ra9m x = 10;
ila (x > 0) {
    kteb("x est positif");
} ilamakanch {
    kteb("x est négatif");
}

htal (x > 0) {
    kteb(x);
    x = x - 1;
}
EOF
./nova_compiler test_control.nova

# Test des fonctions
echo -e "\nTesting functions..."
cat > test_functions.nova << EOF
taarif ra9m add(ra9m a, ra9m b) {
    rje3 a + b;
}

main {
    taarif ra9m result = add(5, 3);
    kteb(result);
}
EOF
./nova_compiler test_functions.nova

# Test des Jadwal
echo -e "\nTesting Jadwal..."
cat > test_jadwal.nova << EOF
taarif jadwal Person {
    ra9m age;
    ktaba name;
    wa9ila is_active;
}

main {
    taarif Person p1;
    p1.age = 25;
    p1.name = "John";
    p1.is_active = true;
}
EOF
./nova_compiler test_jadwal.nova

echo -e "\n=== All tests completed ===" 