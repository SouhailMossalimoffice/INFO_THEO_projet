/**
 * ast.c - Implementation of Abstract Syntax Tree and Symbol Table for LazyUi compiler
 */

#include "ast.h"

/* ------------------- Symbol Table Management Functions ------------------- */

/**
 * Create a new symbol table
 */
SymbolTable* create_symbol_table() {
    SymbolTable *table = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!table) {
        fprintf(stderr, "Memory allocation error for symbol table\n");
        exit(1);
    }
    
    /* Create the global scope */
    Scope *global_scope = (Scope*)malloc(sizeof(Scope));
    if (!global_scope) {
        fprintf(stderr, "Memory allocation error for global scope\n");
        exit(1);
    }
    
    global_scope->entries = NULL;
    global_scope->parent = NULL;
    global_scope->level = 0;
    
    table->current_scope = global_scope;
    
    return table;
}

/**
 * Free all memory associated with a symbol table
 */
void free_symbol_table(SymbolTable *table) {
    if (!table) return;
    
    /* Move back to global scope first */
    while (table->current_scope && table->current_scope->parent) {
        exit_scope(table);
    }
    
    /* Free global scope */
    Scope *global_scope = table->current_scope;
    if (global_scope) {
        SymbolEntry *entry = global_scope->entries;
        while (entry) {
            SymbolEntry *next = entry->next;
            
            /* Free allocated memory based on type */
            if (entry->name) {
                free(entry->name);
            }
            
            if (entry->type == TYPE_KTABA && entry->value.str_value) {
                free(entry->value.str_value);
            }
            
            if (entry->type == TYPE_LISTA) {
                /* Free list elements if needed */
                /* Note: In a full implementation, you would need to free the list elements */
            }
            
            if (entry->type == TYPE_JADWAL && entry->value.fields) {
                free_fields(entry->value.fields);
            }
            
            if (entry->type == TYPE_FUNCTION && entry->value.func_info.parameters) {
                free_parameters(entry->value.func_info.parameters);
            }
            
            free(entry);
            entry = next;
        }
        
        free(global_scope);
    }
    
    free(table);
}

/**
 * Enter a new scope
 */
void enter_scope(SymbolTable *table) {
    if (!table) return;
    
    Scope *new_scope = (Scope*)malloc(sizeof(Scope));
    if (!new_scope) {
        fprintf(stderr, "Memory allocation error for new scope\n");
        exit(1);
    }
    
    new_scope->entries = NULL;
    new_scope->parent = table->current_scope;
    new_scope->level = table->current_scope ? table->current_scope->level + 1 : 0;
    
    table->current_scope = new_scope;
}

/**
 * Exit current scope
 */
void exit_scope(SymbolTable *table) {
    if (!table || !table->current_scope || !table->current_scope->parent) {
        return; /* Cannot exit global scope */
    }
    
    Scope *old_scope = table->current_scope;
    table->current_scope = old_scope->parent;
    
    /* Free all symbols in the old scope */
    SymbolEntry *entry = old_scope->entries;
    while (entry) {
        SymbolEntry *next = entry->next;
        
        /* Free allocated memory based on type */
        if (entry->name) {
            free(entry->name);
        }
        
        if (entry->type == TYPE_KTABA && entry->value.str_value) {
            free(entry->value.str_value);
        }
        
        if (entry->type == TYPE_JADWAL && entry->value.fields) {
            free_fields(entry->value.fields);
        }
        
        if (entry->type == TYPE_FUNCTION && entry->value.func_info.parameters) {
            free_parameters(entry->value.func_info.parameters);
        }
        
        free(entry);
        entry = next;
    }
    
    free(old_scope);
}

/**
 * Add a symbol to the current scope
 */
SymbolEntry* add_symbol(SymbolTable *table, char *name, SymbolType type, SymbolCategory category, int line) {
    if (!table || !table->current_scope || !name) {
        return NULL;
    }
    
    /* Check if symbol already exists in current scope */
    SymbolEntry *existing = lookup_symbol_current_scope(table, name);
    if (existing) {
        fprintf(stderr, "Error: Symbol '%s' already defined in current scope at line %d\n", 
                name, existing->line_defined);
        return NULL;
    }
    
    /* Create new symbol entry */
    SymbolEntry *entry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    if (!entry) {
        fprintf(stderr, "Memory allocation error for symbol entry\n");
        exit(1);
    }
    
    entry->name = strdup(name);
    entry->type = type;
    entry->category = category;
    entry->line_defined = line;
    entry->scope_level = table->current_scope->level;
    entry->next = NULL;
    
    /* Initialize value to default based on type */
    switch (type) {
        case TYPE_RA9M:
            entry->value.num_value = 0.0;
            break;
        case TYPE_KTABA:
            entry->value.str_value = NULL;
            break;
        case TYPE_WA9ILA:
            entry->value.bool_value = 0;
            break;
        case TYPE_LISTA:
            entry->value.list_info.element_type = TYPE_UNKNOWN;
            entry->value.list_info.size = 0;
            break;
        case TYPE_JADWAL:
            entry->value.fields = NULL;
            break;
        case TYPE_FUNCTION:
            entry->value.func_info.return_type = TYPE_UNKNOWN;
            entry->value.func_info.parameters = NULL;
            break;
        default:
            break;
    }
    
    /* Add to current scope */
    if (!table->current_scope->entries) {
        table->current_scope->entries = entry;
    } else {
        SymbolEntry *current = table->current_scope->entries;
        while (current->next) {
            current = current->next;
        }
        current->next = entry;
    }
    
    return entry;
}

/**
 * Look up a symbol in current scope and all parent scopes
 */
SymbolEntry* lookup_symbol(SymbolTable *table, char *name) {
    if (!table || !name) return NULL;
    
    Scope *scope = table->current_scope;
    while (scope) {
        SymbolEntry *entry = scope->entries;
        while (entry) {
            if (strcmp(entry->name, name) == 0) {
                return entry;
            }
            entry = entry->next;
        }
        scope = scope->parent;
    }
    
    return NULL;
}

/**
 * Look up a symbol in current scope only
 */
SymbolEntry* lookup_symbol_current_scope(SymbolTable *table, char *name) {
    if (!table || !table->current_scope || !name) return NULL;
    
    SymbolEntry *entry = table->current_scope->entries;
    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    
    return NULL;
}

/* ------------------- Utility Functions ------------------- */

/**
 * Create a new parameter
 */
Parameter* create_parameter(char *name, SymbolType type) {
    Parameter *param = (Parameter*)malloc(sizeof(Parameter));
    if (!param) {
        fprintf(stderr, "Memory allocation error for parameter\n");
        exit(1);
    }
    
    param->name = strdup(name);
    param->type = type;
    param->next = NULL;
    
    return param;
}

/**
 * Free a linked list of parameters
 */
void free_parameters(Parameter *param) {
    while (param) {
        Parameter *next = param->next;
        free(param->name);
        free(param);
        param = next;
    }
}

/**
 * Create a new field for a jadwal
 */
Field* create_field(char *name, SymbolType type) {
    Field *field = (Field*)malloc(sizeof(Field));
    if (!field) {
        fprintf(stderr, "Memory allocation error for field\n");
        exit(1);
    }
    
    field->name = strdup(name);
    field->type = type;
    field->next = NULL;
    
    return field;
}

/**
 * Free a linked list of fields
 */
void free_fields(Field *field) {
    while (field) {
        Field *next = field->next;
        free(field->name);
        free(field);
        field = next;
    }
}

/**
 * Convert symbol type to string representation
 */
char* symbol_type_to_string(SymbolType type) {
    switch (type) {
        case TYPE_RA9M:      return "ra9m";
        case TYPE_KTABA:     return "ktaba";
        case TYPE_WA9ILA:    return "wa9ila";
        case TYPE_LISTA:     return "lista";
        case TYPE_JADWAL:    return "jadwal";
        case TYPE_FUNCTION:  return "function";
        default:             return "unknown";
    }
}

/* ------------------- AST Node Creation Functions ------------------- */

/**
 * Create a program node
 */
ASTNode* create_program_node(ASTNode **declarations, int declaration_count, ASTNode *main_function, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_PROGRAM;
    node->data.program.declarations = declarations;
    node->data.program.declaration_count = declaration_count;
    node->data.program.main_function = main_function;
    node->line_number = line;
    
    return node;
}

/**
 * Create a variable declaration node
 */
ASTNode* create_var_declaration_node(char *name, SymbolType type, ASTNode *init_expr, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_VAR_DECLARATION;
    node->data.var_decl.name = strdup(name);
    node->data.var_decl.var_type = type;
    node->data.var_decl.init_expr = init_expr;
    node->data.var_decl.symbol = NULL; /* Will be set during semantic analysis */
    node->line_number = line;
    
    return node;
}

/**
 * Create a number literal node
 */
ASTNode* create_number_node(double value, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_NUMBER;
    node->data.number_value = value;
    node->line_number = line;
    
    return node;
}

/**
 * Create a string literal node
 */
ASTNode* create_string_node(char *value, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_STRING;
    node->data.string_value = strdup(value);
    node->line_number = line;
    
    return node;
}

/**
 * Create an identifier node
 */
ASTNode* create_identifier_node(char *name, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_IDENTIFIER;
    node->data.identifier.name = strdup(name);
    node->data.identifier.symbol = NULL; /* Will be set during semantic analysis */
    node->line_number = line;
    
    return node;
}

/**
 * Create a binary operation node
 */
ASTNode* create_binary_op_node(BinaryOpType op, ASTNode *left, ASTNode *right, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_BINARY_OP;
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->line_number = line;
    
    return node;
}

/**
 * Create a unary operation node
 */
ASTNode* create_unary_op_node(UnaryOpType op, ASTNode *operand, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_UNARY_OP;
    node->data.unary_op.op = op;
    node->data.unary_op.operand = operand;
    node->line_number = line;
    
    return node;
}

/**
 * Create an assignment node
 */
ASTNode* create_assignment_node(ASTNode *target, ASTNode *value, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_ASSIGN;
    node->data.assign.target = target;
    node->data.assign.value = value;
    node->line_number = line;
    
    return node;
}

/**
 * Create a list declaration node
 */
ASTNode* create_list_declaration_node(char *name, SymbolType element_type, ASTNode **elements, int num_elements, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_LIST_DECLARATION;
    node->data.list_decl.name = strdup(name);
    node->data.list_decl.element_type = element_type;
    node->data.list_decl.elements = elements;
    node->data.list_decl.num_elements = num_elements;
    node->data.list_decl.symbol = NULL; /* Will be set during semantic analysis */
    node->line_number = line;
    
    return node;
}

/**
 * Create a jadwal declaration node
 */
ASTNode* create_jadwal_declaration_node(char *name, Field *fields, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for AST node\n");
        exit(1);
    }
    
    node->type = NODE_JADWAL_DECLARATION;
    node->data.jadwal_decl.name = strdup(name);
    node->data.jadwal_decl.fields = fields;
    node->data.jadwal_decl.symbol = NULL; /* Will be set during semantic analysis */
    node->line_number = line;
    
    return node;
}

/**
 * Free an AST node and all its children
 */
void free_ast_node(ASTNode *node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            if (node->data.program.declarations) {
                for (int i = 0; i < node->data.program.declaration_count; i++) {
                    free_ast_node(node->data.program.declarations[i]);
                }
                free(node->data.program.declarations);
            }
            if (node->data.program.main_function) {
                free_ast_node(node->data.program.main_function);
            }
            break;
            
        case NODE_VAR_DECLARATION:
            if (node->data.var_decl.name) free(node->data.var_decl.name);
            if (node->data.var_decl.init_expr) free_ast_node(node->data.var_decl.init_expr);
            break;
            
        case NODE_LIST_DECLARATION:
            if (node->data.list_decl.name) free(node->data.list_decl.name);
            if (node->data.list_decl.elements) {
                for (int i = 0; i < node->data.list_decl.num_elements; i++) {
                    free_ast_node(node->data.list_decl.elements[i]);
                }
                free(node->data.list_decl.elements);
            }
            break;
            
        case NODE_JADWAL_DECLARATION:
            if (node->data.jadwal_decl.name) free(node->data.jadwal_decl.name);
            if (node->data.jadwal_decl.fields) free_fields(node->data.jadwal_decl.fields);
            break;
            
        case NODE_FUNC_DECLARATION:
            if (node->data.func_decl.name) free(node->data.func_decl.name);
            if (node->data.func_decl.parameters) free_parameters(node->data.func_decl.parameters);
            if (node->data.func_decl.body) free_ast_node(node->data.func_decl.body);
            break;
            
        case NODE_BINARY_OP:
            if (node->data.binary_op.left) free_ast_node(node->data.binary_op.left);
            if (node->data.binary_op.right) free_ast_node(node->data.binary_op.right);
            break;
            
        case NODE_UNARY_OP:
            if (node->data.unary_op.operand) free_ast_node(node->data.unary_op.operand);
            break;
            
        case NODE_STRING:
            if (node->data.string_value) free(node->data.string_value);
            break;
            
        case NODE_IDENTIFIER:
            if (node->data.identifier.name) free(node->data.identifier.name);
            break;
            
        case NODE_ASSIGN:
            if (node->data.assign.target) free_ast_node(node->data.assign.target);
            if (node->data.assign.value) free_ast_node(node->data.assign.value);
            break;
            
        case NODE_ARRAY_ACCESS:
            if (node->data.array_access.array) free_ast_node(node->data.array_access.array);
            if (node->data.array_access.index) free_ast_node(node->data.array_access.index);
            break;
            
        case NODE_FIELD_ACCESS:
            if (node->data.field_access.record) free_ast_node(node->data.field_access.record);
            if (node->data.field_access.field_name) free(node->data.field_access.field_name);
            break;
            
        case NODE_IF:
            if (node->data.if_stmt.condition) free_ast_node(node->data.if_stmt.condition);
            if (node->data.if_stmt.if_body) free_ast_node(node->data.if_stmt.if_body);
            if (node->data.if_stmt.else_body) free_ast_node(node->data.if_stmt.else_body);
            break;
            
        case NODE_WHILE:
        case NODE_FOR:
            if (node->data.loop.init) free_ast_node(node->data.loop.init);
            if (node->data.loop.condition) free_ast_node(node->data.loop.condition);
            if (node->data.loop.update) free_ast_node(node->data.loop.update);
            if (node->data.loop.body) free_ast_node(node->data.loop.body);
            break;
            
        case NODE_BLOCK:
            if (node->data.block.statements) {
                for (int i = 0; i < node->data.block.statement_count; i++) {
                    free_ast_node(node->data.block.statements[i]);
                }
                free(node->data.block.statements);
            }
            break;
            
        case NODE_FUNC_CALL:
            if (node->data.func_call.func_name) free(node->data.func_call.func_name);
            if (node->data.func_call.args) {
                for (int i = 0; i < node->data.func_call.arg_count; i++) {
                    free_ast_node(node->data.func_call.args[i]);
                }
                free(node->data.func_call.args);
            }
            break;
            
        case NODE_RETURN:
            if (node->data.return_stmt.expr) free_ast_node(node->data.return_stmt.expr);
            break;
            
        default:
            break;
    }
    
    free(node);
}

/* ------------------- Debug Functions ------------------- */

/**
 * Print the symbol table for debugging
 */
void print_symbol_table(SymbolTable *table) {
    if (!table) {
        printf("Symbol table is NULL\n");
        return;
    }
    
    printf("Symbol Table:\n");
    
    Scope *scope = table->current_scope;
    while (scope) {
        printf("Scope Level %d:\n", scope->level);
        
        SymbolEntry *entry = scope->entries;
        if (!entry) {
            printf("  (empty)\n");
        }
        
        while (entry) {
            printf("  %s: type=%s, category=", entry->name, symbol_type_to_string(entry->type));
            
            switch (entry->category) {
                case SYMBOL_VARIABLE:
                    printf("variable");
                    break;
                case SYMBOL_FUNCTION:
                    printf("function");
                    break;
                case SYMBOL_PARAMETER:
                    printf("parameter");
                    break;
                case SYMBOL_FIELD:
                    printf("field");
                    break;
                default:
                    printf("unknown");
                    break;
            }
            
            printf(", line=%d\n", entry->line_defined);
            entry = entry->next;
        }
        
        scope = scope->parent;
        if (scope) {
            printf("\n");
        }
    }
}

/**
 * Helper function to print indentation
 */
static void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

/**
 * Print the AST for debugging
 */
void print_ast(ASTNode *node, int indent) {
    if (!node) {
        print_indent(indent);
        printf("NULL\n");
        return;
    }
    
    print_indent(indent);
    
    switch (node->type) {
        case NODE_PROGRAM:
            printf("Program (line %d)\n", node->line_number);
            print_indent(indent + 1);
            printf("Declarations (%d):\n", node->data.program.declaration_count);
            for (int i = 0; i < node->data.program.declaration_count; i++) {
                print_ast(node->data.program.declarations[i], indent + 2);
            }
            print_indent(indent + 1);
            printf("Main Function:\n");
            if (node->data.program.main_function) {
                print_ast(node->data.program.main_function, indent + 2);
            } else {
                print_indent(indent + 2);
                printf("NULL\n");
            }
            break;
            
        case NODE_VAR_DECLARATION:
            printf("Variable Declaration: %s (type: %s, line %d)\n", 
                   node->data.var_decl.name, 
                   symbol_type_to_string(node->data.var_decl.var_type),
                   node->line_number);
            if (node->data.var_decl.init_expr) {
                print_indent(indent + 1);
                printf("Initial Value:\n");
                print_ast(node->data.var_decl.init_expr, indent + 2);
            }
            break;
            
        case NODE_BINARY_OP:
            printf("Binary Operation (line %d): ", node->line_number);
            switch (node->data.binary_op.op) {
                case OP_ADD:    printf("ADD (+)\n"); break;
                case OP_SUB:    printf("SUBTRACT (-)\n"); break;
                case OP_MUL:    printf("MULTIPLY (*)\n"); break;
                case OP_DIV:    printf("DIVIDE (/)\n"); break;
                case OP_INT_DIV: printf("INTEGER DIVIDE (div)\n"); break;
                case OP_AND:    printf("AND (w)\n"); break;
                case OP_OR:     printf("OR (wla)\n"); break;
                case OP_EQ:     printf("EQUAL (==)\n"); break;
                case OP_NEQ:    printf("NOT EQUAL (<>)\n"); break;
                case OP_LT:     printf("LESS THAN (<)\n"); break;
                case OP_GT:     printf("GREATER THAN (>)\n"); break;
                case OP_LE:     printf("LESS EQUAL (<=)\n"); break;
                case OP_GE:     printf("GREATER EQUAL (>=)\n"); break;
                default:        printf("UNKNOWN\n"); break;
            }
            print_indent(indent + 1);
            printf("Left Operand:\n");
            print_ast(node->data.binary_op.left, indent + 2);
            print_indent(indent + 1);
            printf("Right Operand:\n");
            print_ast(node->data.binary_op.right, indent + 2);
            break;
            
        case NODE_UNARY_OP:
            printf("Unary Operation (line %d): ", node->line_number);
            switch (node->data.unary_op.op) {
                case OP_NEG:  printf("NEGATE (-)\n"); break;
                case OP_NOT:  printf("NOT (machi)\n"); break;
                case OP_FACT: printf("FACTORIAL (!)\n"); break;
                default:      printf("UNKNOWN\n"); break;
            }
            print_indent(indent + 1);
            printf("Operand:\n");
            print_ast(node->data.unary_op.operand, indent + 2);
            break;
            
        case NODE_NUMBER:
            printf("Number: %f (line %d)\n", node->data.number_value, node->line_number);
            break;
            
        case NODE_STRING:
            printf("String: %s (line %d)\n", node->data.string_value, node->line_number);
            break;
            
        case NODE_IDENTIFIER:
            printf("Identifier: %s (line %d)\n", node->data.identifier.name, node->line_number);
            break;
            
        case NODE_JADWAL_DECLARATION:
            printf("Jadwal Declaration: %s (line %d)\n", 
                   node->data.jadwal_decl.name, node->line_number);
            if (node->data.jadwal_decl.fields) {
                print_indent(indent + 1);
                printf("Fields:\n");
                Field *field = node->data.jadwal_decl.fields;
                while (field) {
                    print_indent(indent + 2);
                    printf("%s: %s\n", field->name, symbol_type_to_string(field->type));
                    field = field->next;
                }
            }
            break;
            
        default:
            printf("Unknown node type: %d (line %d)\n", node->type, node->line_number);
            break;
    }
}

/* ------------------- Semantic Analysis Functions ------------------- */

/**
 * Perform semantic analysis on the AST
 */
void analyze_ast(ASTNode *node, SymbolTable *table) {
    if (!node || !table) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            /* Enter global scope for program */
            for (int i = 0; i < node->data.program.declaration_count; i++) {
                analyze_ast(node->data.program.declarations[i], table);
            }
            if (node->data.program.main_function) {
                analyze_ast(node->data.program.main_function, table);
            }
            break;
            
        case NODE_VAR_DECLARATION:
            /* Add variable to symbol table */
            node->data.var_decl.symbol = add_symbol(
                table, 
                node->data.var_decl.name, 
                node->data.var_decl.var_type, 
                SYMBOL_VARIABLE, 
                node->line_number
            );
            
            /* Analyze initializer if present */
            if (node->data.var_decl.init_expr) {
                analyze_ast(node->data.var_decl.init_expr, table);
                /* Type checking would happen here in a full implementation */
            }
            break;
            
        case NODE_JADWAL_DECLARATION:
            /* Add jadwal to symbol table */
            node->data.jadwal_decl.symbol = add_symbol(
                table, 
                node->data.jadwal_decl.name, 
                TYPE_JADWAL, 
                SYMBOL_VARIABLE, 
                node->line_number
            );
            
            /* Set fields for the jadwal type */
            if (node->data.jadwal_decl.symbol) {
                /* We need to duplicate the fields to avoid double-free issues */
                Field *orig_field = node->data.jadwal_decl.fields;
                Field *prev_field = NULL;
                Field *first_field = NULL;
                
                while (orig_field) {
                    Field *new_field = create_field(orig_field->name, orig_field->type);
                    
                    if (!first_field) {
                        first_field = new_field;
                    }
                    
                    if (prev_field) {
                        prev_field->next = new_field;
                    }
                    
                    prev_field = new_field;
                    orig_field = orig_field->next;
                }
                
                node->data.jadwal_decl.symbol->value.fields = first_field;
            }
            break;
            
        case NODE_IDENTIFIER:
            /* Look up identifier in symbol table */
            node->data.identifier.symbol = lookup_symbol(table, node->data.identifier.name);
            if (!node->data.identifier.symbol) {
                fprintf(stderr, "Error: Undefined identifier '%s' at line %d\n", 
                        node->data.identifier.name, node->line_number);
            }
            break;
            
        /* Additional case handlers would be implemented for a full compiler */
            
        default:
            /* Handle other node types as needed */
            break;
    }
} 