# LazyUi - A Minimal Functional Programming Language

LazyUi is a minimal functional programming language designed for educational purposes and simple computations. It features a clean syntax inspired by functional programming paradigms while maintaining simplicity and readability.

## Features

- Basic arithmetic operations (addition, subtraction, multiplication, division)
- Function declarations and calls
- Variable declarations and assignments
- Print statements for output
- Type system with number type (ra9m)
- Clean and intuitive syntax

## Language Syntax

### Basic Syntax Elements

```nova
# Variable Declaration
ra9m x = 10;

# Function Declaration
taarif ra9m add(a, b) {
    rje3 a + b;
}

# Function Call
ra9m sum = add(x, y);

# Print Statement
kteb(sum);
```

### Keywords

- `taarif`: Function declaration
- `ra9m`: Number type
- `rje3`: Return statement
- `kteb`: Print statement

## Building and Running

### Prerequisites

- GCC compiler
- Make
- Flex
- Bison

### Building the Compiler

```bash
# Clone the repository
git clone https://github.com/yourusername/lazyui.git
cd lazyui

# Build the compiler
make clean && make
```

### Running Programs

1. Write your program in a `.nova` file
2. Compile and run:
```bash
./nova_compiler your_program.nova
```

The compiler will:
1. Parse your code
2. Generate an AST
3. Perform semantic analysis
4. Generate C code
5. Create an executable

## Example Programs

### Basic Arithmetic

```nova
taarif ra9m add(a, b) {
    rje3 a + b;
}

taarif ra9m subtract(a, b) {
    rje3 a - b;
}

taarif ra9m multiply(a, b) {
    rje3 a * b;
}

taarif ra9m divide(a, b) {
    rje3 a / b;
}

taarif ra9m main() {
    ra9m x = 10;
    ra9m y = 5;
    
    ra9m sum = add(x, y);
    ra9m diff = subtract(x, y);
    ra9m prod = multiply(x, y);
    ra9m quot = divide(x, y);
    
    kteb(sum);
    kteb(diff);
    kteb(prod);
    kteb(quot);
}
```

## Testing

The language comes with a test suite. To run the tests:

```bash
# Run all tests
make test

# Run a specific test
./nova_compiler tests/minimal_func.nova
```

## Project Structure

```
lazyui/
├── LazyUi_Analex.l    # Lexer definition
├── LazyUi_Parser.y    # Parser definition
├── ast.h             # AST definitions
├── ast.c             # AST implementation
├── codegen.h         # Code generation header
├── codegen.c         # Code generation implementation
├── tests/            # Test files
└── Makefile          # Build configuration
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author

[Your Name]

## Acknowledgments

- Thanks to all contributors and users of LazyUi
- Inspired by functional programming languages and compiler design principles