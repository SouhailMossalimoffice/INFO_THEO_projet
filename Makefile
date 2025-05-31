CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -ll

# Source files
LEXER_SRC = LazyUi_Analex.l
PARSER_SRC = LazyUi_Parser.y
AST_SRC = ast.c
TEST_SRC = test_ast.c

# Generated files
LEXER_GEN = lex.yy.c
PARSER_GEN = LazyUi_Parser.tab.c LazyUi_Parser.tab.h
AST_OBJ = ast.o
TEST_OBJ = test_ast.o

# Executables
COMPILER = nova_compiler
TEST_EXE = test_ast

# Default target
all: $(COMPILER)

# Generate lexer
$(LEXER_GEN): $(LEXER_SRC)
	flex $(LEXER_SRC)

# Generate parser
$(PARSER_GEN): $(PARSER_SRC)
	bison -d $(PARSER_SRC)

# Compile AST
$(AST_OBJ): ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

# Compile test
$(TEST_OBJ): test_ast.c ast.h
	$(CC) $(CFLAGS) -c test_ast.c

# Build compiler
$(COMPILER): $(LEXER_GEN) $(PARSER_GEN) $(AST_OBJ) codegen.c
	$(CC) $(CFLAGS) -o $@ $(LEXER_GEN) LazyUi_Parser.tab.c $(AST_OBJ) codegen.c $(LDFLAGS)

# Build test executable
$(TEST_EXE): $(TEST_OBJ) $(AST_OBJ)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ) $(AST_OBJ)

# Run tests
test: $(TEST_EXE)
	./test_semantic.sh

# Clean generated files
clean:
	rm -f $(LEXER_GEN) $(PARSER_GEN) $(AST_OBJ) $(TEST_OBJ) $(COMPILER) $(TEST_EXE)
	rm -f *.o *.tab.c *.tab.h lex.yy.c

# Run compiler on a specific file
run: $(COMPILER)
	@if [ -z "$(file)" ]; then \
		echo "Usage: make run file=<nova_file>"; \
		exit 1; \
	fi
	./$(COMPILER) $(file)

.PHONY: all clean test run 