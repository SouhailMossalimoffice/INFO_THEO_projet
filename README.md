# Symbol Table and AST for LazyUi Compiler

This project implements a symbol table and Abstract Syntax Tree (AST) for the LazyUi programming language compiler.

## Features

- Symbol table with support for nested scopes
- Type management (ra9m, ktaba, wa9ila, lista, jadwal)
- AST node creation and management
- Semantic analysis
- Memory management for all allocated structures
- Debug utilities for visualization

## Files

- `ast.h` - Header file with symbol table and AST definitions
- `ast.c` - Implementation of symbol table and AST operations
- `test_ast.c` - Test program for basic symbol table and AST operations
- `test_jadwal.c` - Test program specifically for jadwal (struct) functionality
- `Makefile` - Build configuration

## Building

To build all the test programs:

```
make
```

To build specific test program:

```
make test_ast
```

or

```
make test_jadwal
```

## Running Tests

To run all tests:

```
make run
```

To run a specific test:

```
make run_ast
```

or

```
make run_jadwal
```

## Integrating with Your Parser

To integrate this symbol table and AST implementation with your parser:

1. Include `ast.h` in your parser file (LazyUi_Parser.y)
2. Initialize the symbol table in your main function
3. Build AST nodes during parsing using the node creation functions
4. Perform semantic analysis on the resulting AST
5. Use the AST for code generation or interpretation

Example integration:

```c
#include "ast.h"

// In your main function
SymbolTable *symbol_table = create_symbol_table();
ASTNode *ast_root = NULL;

// After successful parsing
analyze_ast(ast_root, symbol_table);

// When done
free_ast_node(ast_root);
free_symbol_table(symbol_table);
```

## Memory Management

All memory allocated for the symbol table and AST is properly managed with these functions:

- `free_symbol_table(table)` - Frees all memory for a symbol table
- `free_ast_node(node)` - Recursively frees all memory for an AST node and its children
- `free_parameters(param)` - Frees a linked list of parameters
- `free_fields(field)` - Frees a linked list of fields

Make sure to call these functions when your structures are no longer needed to avoid memory leaks.