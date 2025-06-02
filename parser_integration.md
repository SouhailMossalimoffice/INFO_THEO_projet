# Integrating AST and Symbol Table with LazyUi Parser

This guide explains how to integrate the symbol table and AST implementation with your existing LazyUi parser.

## Step 1: Include AST Header in Parser

At the top of your LazyUi_Parser.y file, include the AST header:

```c
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"  // Add this include

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int yylineno;
void yyerror(const char* s);

// Add global symbol table and AST root
SymbolTable *symbol_table;
ASTNode *ast_root;
%}
```

## Step 2: Define Semantic Types in Union

Add AST nodes to your %union section:

```c
%union {
    double number;
    char* string;
    // Add AST node types
    ASTNode* ast_node;
    Parameter* param_list;
    Field* field_list;
    SymbolType type_value;
}
```

## Step 3: Define Types for Non-Terminals

Update your non-terminals to use AST nodes:

```c
%type <ast_node> programme declarations_variables declaration_variable
%type <ast_node> expression expression_logique expression_comparison expression_arithmetique 
%type <ast_node> terme facteur valeur
%type <ast_node> instructions instruction
%type <field_list> champs_jadwal champ_jadwal
%type <param_list> parametres parametre
%type <type_value> type
```

## Step 4: Update Grammar Rules to Build AST

Update your grammar rules to create AST nodes. Examples:

```c
programme
    : declarations_variables declarations_fonctions programme_principal
      {
          // Create program node with declarations and main
          ASTNode **declarations = (ASTNode**)malloc(sizeof(ASTNode*) * ($1 ? 1 : 0));
          if ($1) declarations[0] = $1;
          ast_root = create_program_node(declarations, ($1 ? 1 : 0), $3, yylineno);
      }
    ;

declaration_variable
    : type TK_IDENTIFIANT TK_SEMICOLON
      {
          // Create variable declaration node
          $$ = create_var_declaration_node($2, $1, NULL, yylineno);
      }
    | type TK_IDENTIFIANT TK_AFFECTATION expression TK_SEMICOLON
      {
          // Create variable declaration node with initializer
          $$ = create_var_declaration_node($2, $1, $4, yylineno);
      }
    ;

type
    : TK_RA9M   { $$ = TYPE_RA9M; }
    | TK_KTABA  { $$ = TYPE_KTABA; }
    | TK_WA9ILA { $$ = TYPE_WA9ILA; }
    ;

expression_arithmetique
    : terme
      { $$ = $1; }
    | expression_arithmetique TK_ADD terme
      { $$ = create_binary_op_node(OP_ADD, $1, $3, yylineno); }
    | expression_arithmetique TK_SUB terme
      { $$ = create_binary_op_node(OP_SUB, $1, $3, yylineno); }
    ;
```

## Step 5: Update Main Function

Update the main function to initialize the symbol table and perform semantic analysis:

```c
int main(int argc, char** argv) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    // Initialize symbol table
    symbol_table = create_symbol_table();
    
    // Parse input
    yyparse();
    
    // Perform semantic analysis
    if (ast_root) {
        analyze_ast(ast_root, symbol_table);
        
        // Print AST for debugging (optional)
        printf("AST Structure:\n");
        print_ast(ast_root, 0);
        
        // Print symbol table for debugging (optional)
        printf("Symbol Table:\n");
        print_symbol_table(symbol_table);
        
        // Free AST nodes when done
        free_ast_node(ast_root);
    }
    
    // Free symbol table
    free_symbol_table(symbol_table);
    
    if (argc > 1) {
        fclose(yyin);
    }
    return 0;
} 
```

## Step 6: Update Error Handling

You can improve error reporting using line numbers from AST nodes:

```c
void yyerror(const char* s) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}
```

## Step 7: Code Generation/Interpretation

Once you have the AST, you can implement a code generator or interpreter by traversing the AST:

```c
void generate_code(ASTNode *node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            // Generate program header
            printf("# Generated LazyUi Program\n\n");
            
            // Generate code for each declaration
            for (int i = 0; i < node->data.program.declaration_count; i++) {
                generate_code(node->data.program.declarations[i]);
            }
            
            // Generate code for main function
            generate_code(node->data.program.main_function);
            break;
            
        case NODE_VAR_DECLARATION:
            // Generate variable declaration code
            // ...
            break;
            
        // Handle other node types
    }
}
```

## Complete Integration

Once integration is complete, your compiler will:
1. Parse the source code into an AST
2. Build a symbol table of all identifiers
3. Perform semantic analysis to catch errors
4. Generate code or interpret the program

This approach gives you a robust foundation for expanding your compiler with more optimizations and features. 