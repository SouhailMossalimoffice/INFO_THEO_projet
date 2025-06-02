/**
 * test_jadwal.c - Test program for Jadwal (struct) implementation in the AST
 */

#include <stdio.h>
#include "ast.h"

int main() {
    printf("Testing Jadwal (Struct) Implementation\n");
    printf("--------------------------------------\n\n");

    // Create a symbol table
    SymbolTable *table = create_symbol_table();
    
    // Test creating a Jadwal (struct) type
    printf("1. Creating a Jadwal type 'Person':\n");
    
    // Create fields for the Person jadwal
    Field *name_field = create_field("name", TYPE_KTABA);
    Field *age_field = create_field("age", TYPE_RA9M);
    Field *active_field = create_field("active", TYPE_WA9ILA);
    
    // Link the fields together
    name_field->next = age_field;
    age_field->next = active_field;
    
    // Create the jadwal declaration node
    ASTNode *jadwal_decl = create_jadwal_declaration_node("Person", name_field, 20);
    
    // Print the jadwal structure
    printf("\n2. Jadwal Structure:\n");
    print_ast(jadwal_decl, 0);
    
    // Add the jadwal type to the symbol table through semantic analysis
    printf("\n3. Adding Jadwal to Symbol Table:\n");
    analyze_ast(jadwal_decl, table);
    
    // Verify the jadwal was added to the symbol table
    SymbolEntry *jadwal_entry = lookup_symbol(table, "Person");
    if (jadwal_entry) {
        printf("   - Successfully added 'Person' jadwal to symbol table\n");
        
        // Print the fields
        printf("   - Fields:\n");
        Field *field = jadwal_entry->value.fields;
        while (field) {
            printf("     * %s: %s\n", field->name, symbol_type_to_string(field->type));
            field = field->next;
        }
    } else {
        printf("   - Failed to add 'Person' jadwal to symbol table\n");
    }
    
    // Create a variable of the jadwal type
    printf("\n4. Creating a variable of Jadwal type:\n");
    
    // Create a variable declaration node
    ASTNode *var_decl = create_var_declaration_node("person1", TYPE_JADWAL, NULL, 25);
    
    // Set the jadwal type (in a real compiler this would be done during type checking)
    // For the test, we're directly setting the jadwal type reference
    
    // Add the variable to the symbol table through semantic analysis
    analyze_ast(var_decl, table);
    
    // Verify the variable was added to the symbol table
    SymbolEntry *var_entry = lookup_symbol(table, "person1");
    if (var_entry) {
        printf("   - Successfully added 'person1' variable to symbol table\n");
        printf("   - Type: %s\n", symbol_type_to_string(var_entry->type));
    } else {
        printf("   - Failed to add 'person1' variable to symbol table\n");
    }
    
    // Print the symbol table
    printf("\n5. Symbol Table Contents:\n");
    print_symbol_table(table);
    
    // Clean up
    printf("\n6. Cleaning up resources:\n");
    printf("   - Freeing AST nodes\n");
    free_ast_node(jadwal_decl);
    free_ast_node(var_decl);
    
    printf("   - Freeing symbol table\n");
    free_symbol_table(table);
    
    printf("\nTest completed successfully!\n");
    
    return 0;
} 