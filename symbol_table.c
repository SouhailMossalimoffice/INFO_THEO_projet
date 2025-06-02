#include "symbol_table.h"

/* Global symbol table definition */
SymbolTable* symbol_table = NULL;

void insert_symbol(SymbolTable* table, const char* name, SymbolType type, SymbolCategory category, int line) {
    if (!table || !name) return;
    
    // Check if symbol already exists
    if (lookup_symbol(table, name)) {
        fprintf(stderr, "Error at line %d: Variable '%s' already declared in current scope\n", line, name);
        return;
    }
    
    SymbolEntry* entry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    if (entry) {
        entry->name = strdup(name);
        entry->type = type;
        entry->category = category;
        entry->line = line;
        entry->next = table->entries;
        table->entries = entry;
    }
}

void enter_scope() {
    SymbolTable* new_scope = (SymbolTable*)malloc(sizeof(SymbolTable));
    new_scope->symbols = NULL;
    new_scope->parent = symbol_table;
    new_scope->level = symbol_table ? symbol_table->level + 1 : 0;
    symbol_table = new_scope;
}

void exit_scope() {
    if (symbol_table) {
        SymbolTable* parent = symbol_table->parent;
        // Free all symbols in current scope
        SymbolEntry* current = symbol_table->symbols;
        while (current) {
            SymbolEntry* next = current->next;
            free(current->name);
            free(current);
            current = next;
        }
        free(symbol_table);
        symbol_table = parent;
    }
} 