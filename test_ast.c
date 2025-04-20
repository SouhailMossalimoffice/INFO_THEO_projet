/**
 * test_ast.c - Test program for Symbol Table and AST implementation
 */

#include <stdio.h>
#include "ast.h"

int main() {
    printf("Testing Symbol Table and AST Implementation\n");
    printf("-------------------------------------------\n\n");

    // Create a symbol table
    SymbolTable *table = create_symbol_table();
    
    // Test entering and exiting scopes
    printf("1. Testing scopes:\n");
    printf("   - Creating global scope\n");
    
    // Add some symbols to global scope
    add_symbol(table, "globalVar1", TYPE_RA9M, SYMBOL_VARIABLE, 1);
    add_symbol(table, "globalVar2", TYPE_KTABA, SYMBOL_VARIABLE, 2);
    
    // Enter a new scope (e.g., function scope)
    printf("   - Entering function scope\n");
    enter_scope(table);
    
    // Add some symbols to the function scope
    add_symbol(table, "localVar1", TYPE_RA9M, SYMBOL_VARIABLE, 5);
    add_symbol(table, "localVar2", TYPE_WA9ILA, SYMBOL_VARIABLE, 6);
    
    // Enter another nested scope (e.g., block scope)
    printf("   - Entering block scope\n");
    enter_scope(table);
    
    // Add symbols to the block scope
    add_symbol(table, "blockVar", TYPE_LISTA, SYMBOL_VARIABLE, 10);
    
    // Test symbol lookup
    printf("\n2. Testing symbol lookup:\n");
    
    SymbolEntry *entry1 = lookup_symbol(table, "globalVar1");
    if (entry1) {
        printf("   - Found symbol 'globalVar1': type=%s, line=%d, scope=%d\n",
               symbol_type_to_string(entry1->type), entry1->line_defined, entry1->scope_level);
    } else {
        printf("   - Failed to find 'globalVar1'\n");
    }
    
    SymbolEntry *entry2 = lookup_symbol(table, "localVar1");
    if (entry2) {
        printf("   - Found symbol 'localVar1': type=%s, line=%d, scope=%d\n",
               symbol_type_to_string(entry2->type), entry2->line_defined, entry2->scope_level);
    } else {
        printf("   - Failed to find 'localVar1'\n");
    }
    
    SymbolEntry *entry3 = lookup_symbol(table, "blockVar");
    if (entry3) {
        printf("   - Found symbol 'blockVar': type=%s, line=%d, scope=%d\n",
               symbol_type_to_string(entry3->type), entry3->line_defined, entry3->scope_level);
    } else {
        printf("   - Failed to find 'blockVar'\n");
    }
    
    SymbolEntry *entry4 = lookup_symbol(table, "nonExistentVar");
    if (entry4) {
        printf("   - Incorrectly found 'nonExistentVar'\n");
    } else {
        printf("   - Correctly did not find 'nonExistentVar'\n");
    }
    
    // Test local scope lookup
    printf("\n3. Testing local scope lookup:\n");
    SymbolEntry *local_entry = lookup_symbol_current_scope(table, "globalVar1");
    if (local_entry) {
        printf("   - Incorrectly found 'globalVar1' in local scope\n");
    } else {
        printf("   - Correctly did not find 'globalVar1' in local scope\n");
    }
    
    // Print the entire symbol table
    printf("\n4. Symbol Table Contents:\n");
    print_symbol_table(table);
    
    // Test exiting scopes
    printf("\n5. Testing scope exit:\n");
    printf("   - Exiting block scope\n");
    exit_scope(table);
    
    // Verify that blockVar is no longer accessible
    SymbolEntry *after_exit = lookup_symbol(table, "blockVar");
    if (after_exit) {
        printf("   - Incorrectly found 'blockVar' after exiting its scope\n");
    } else {
        printf("   - Correctly did not find 'blockVar' after exiting its scope\n");
    }
    
    // Test AST creation
    printf("\n6. Testing AST creation:\n");
    
    // Create some AST nodes for expressions
    printf("   - Creating AST nodes\n");
    ASTNode *num1 = create_number_node(10.5, 15);
    ASTNode *num2 = create_number_node(5.2, 15);
    ASTNode *binary_op = create_binary_op_node(OP_ADD, num1, num2, 15);
    
    // Create variable declaration with initializer
    ASTNode *var_decl = create_var_declaration_node("result", TYPE_RA9M, binary_op, 15);
    
    // Print the AST
    printf("\n7. AST Structure:\n");
    print_ast(var_decl, 0);
    
    // Test semantic analysis
    printf("\n8. Testing semantic analysis:\n");
    printf("   - Analyzing variable declaration\n");
    analyze_ast(var_decl, table);
    
    // Verify the symbol was added to the current scope
    SymbolEntry *result_var = lookup_symbol(table, "result");
    if (result_var) {
        printf("   - Successfully added 'result' variable to symbol table\n");
    } else {
        printf("   - Failed to add 'result' variable to symbol table\n");
    }
    
    // Clean up
    printf("\n9. Cleaning up resources:\n");
    printf("   - Freeing AST nodes\n");
    free_ast_node(var_decl); // This will free all children nodes recursively
    
    printf("   - Freeing symbol table\n");
    free_symbol_table(table);
    
    printf("\nTest completed successfully!\n");
    
    return 0;
} 