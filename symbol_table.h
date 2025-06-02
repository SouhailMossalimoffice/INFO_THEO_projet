#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ast.h"

/* Global symbol table */
extern SymbolTable* symbol_table;

// Function declarations
void insert_symbol(SymbolTable* table, const char* name, SymbolType type, SymbolCategory category, int line);
void enter_scope(void);
void exit_scope(void);
SymbolEntry* lookup_symbol(SymbolTable* table, const char* name);
SymbolEntry* lookup_symbol_current_scope(SymbolTable* table, const char* name);

#endif // SYMBOL_TABLE_H 