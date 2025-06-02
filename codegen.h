#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

// Initialize code generation
void init_codegen(const char *output_filename);

// Close code generation
void close_codegen();

// Generate code from AST
void generate_code(ASTNode *node);

// Generate program code
void generate_program(ASTNode *node);

// Generate function declaration code
void generate_function_declaration(ASTNode *node);

// Generate return statement code
void generate_return(ASTNode *node);

// Generate variable declaration code
void generate_variable_declaration(ASTNode *node);

// Generate assignment code
void generate_assignment(ASTNode *node);

// Generate binary operation code
void generate_binary_op(ASTNode *node);

// Generate function call code
void generate_function_call(ASTNode *node);

// Generate print statement code
void generate_print(ASTNode *node);

// Generate code entry point
void generate_code_entry(ASTNode* ast_root);

#endif // CODEGEN_H 