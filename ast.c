/**
 * ast.c - Implementation of Abstract Syntax Tree and Symbol Table for LazyUi compiler
 */

#include "ast.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward declarations of helper functions */
static void semantic_error(int line, const char* format, ...);
static SymbolType get_expression_type(ASTNode* node, SymbolTable* table);
static int is_type_compatible(SymbolType left, SymbolType right);
static int check_array_element_types(ASTNode* array_literal, SymbolType expected_type);
static SymbolType get_array_element_type(ASTNode* array_literal);

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
SymbolEntry* add_symbol(SymbolTable* table, const char* name, SymbolType type, SymbolCategory category, int line) {
    if (!table || !table->current_scope || !name) {
        return NULL;
    }
    
    /* Check if symbol already exists in current scope */
    SymbolEntry* existing = lookup_symbol_current_scope(table, name);
    if (existing) {
        fprintf(stderr, "Error: Symbol '%s' already defined in current scope at line %d\n", 
                name, existing->line_defined);
        return NULL;
    }
    
    /* Create new symbol entry */
    SymbolEntry* entry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    if (!entry) {
        fprintf(stderr, "Memory allocation error for symbol entry\n");
        return NULL;
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
        SymbolEntry* current = table->current_scope->entries;
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
SymbolEntry* lookup_symbol(SymbolTable* table, const char* name) {
    if (!table || !name) return NULL;
    
    Scope* scope = table->current_scope;
    while (scope) {
        SymbolEntry* entry = scope->entries;
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
SymbolEntry* lookup_symbol_current_scope(SymbolTable* table, const char* name) {
    if (!table || !table->current_scope || !name) return NULL;
    
    SymbolEntry* entry = table->current_scope->entries;
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
ASTNode* create_program_node(ASTNode *declarations, ASTNode *main_function, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for program node\n");
        exit(1);
    }
    node->type = NODE_PROGRAM;
    node->line_number = line;
    node->data.program.declarations = declarations;
    node->data.program.main_function = main_function;
    return node;
}

/**
 * Create a variable declaration node
 */
ASTNode* create_var_declaration_node(char* name, SymbolType type, ASTNode* initializer, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for variable declaration node\n");
        return NULL;
    }
    
    node->type = NODE_VAR_DECLARATION;
    node->line_number = line_number;
    node->data.var_decl.name = strdup(name);
    node->data.var_decl.type = type;
    node->data.var_decl.initializer = initializer;
    node->data.var_decl.symbol = NULL; /* Will be set during semantic analysis */
    
    return node;
}

/**
 * Create a number node
 */
ASTNode* create_number_node(double value, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for number node\n");
        return NULL;
    }
    
    node->type = NODE_NUMBER;
    node->line_number = line_number;
    node->data.number_value = value;
    
    return node;
}

/**
 * Create a string node
 */
ASTNode* create_string_node(char* value, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for string node\n");
        return NULL;
    }
    
    node->type = NODE_STRING;
    node->line_number = line_number;
    node->data.string_value = strdup(value);
    
    return node;
}

/**
 * Create an identifier node
 */
ASTNode* create_identifier_node(char* name, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for identifier node\n");
        return NULL;
    }
    
    node->type = NODE_IDENTIFIER;
    node->line_number = line_number;
    node->data.identifier = strdup(name);
    
    return node;
}

/**
 * Create a binary operation node
 */
ASTNode* create_binary_op_node(OperatorType op, ASTNode* left, ASTNode* right, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for binary operation node\n");
        return NULL;
    }
    
    node->type = NODE_BINARY_OP;
    node->line_number = line_number;
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    
    return node;
}

/**
 * Create a unary operation node
 */
ASTNode* create_unary_op_node(OperatorType op, ASTNode* operand, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for unary operation node\n");
        return NULL;
    }
    
    node->type = NODE_UNARY_OP;
    node->line_number = line_number;
    node->data.unary_op.op = op;
    node->data.unary_op.operand = operand;
    
    return node;
}

/**
 * Create an assignment node
 */
ASTNode* create_assignment_node(ASTNode* target, ASTNode* value, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for assignment node\n");
        return NULL;
    }
    
    node->type = NODE_ASSIGNMENT;
    node->line_number = line_number;
    node->data.assignment.target = target;
    node->data.assignment.value = value;
    
    return node;
}

/**
 * Create a function call node
 */
ASTNode* create_function_call_node(char* name, ASTNode** arguments, int arg_count, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for function call node\n");
        return NULL;
    }
    
    node->type = NODE_FUNCTION_CALL;
    node->line_number = line_number;
    node->data.func_call.name = strdup(name);
    node->data.func_call.arguments = arguments;
    node->data.func_call.arg_count = arg_count;
    node->data.func_call.symbol = NULL; /* Will be set during semantic analysis */
    
    return node;
}

/**
 * Create a function declaration node
 */
ASTNode* create_function_declaration_node(char* name, SymbolType return_type, Parameter* parameters, ASTNode* body, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for function declaration node\n");
        return NULL;
    }
    
    node->type = NODE_FUNCTION_DECLARATION;
    node->line_number = line_number;
    node->data.func_decl.name = strdup(name);
    node->data.func_decl.return_type = return_type;
    node->data.func_decl.parameters = parameters;
    node->data.func_decl.body = body;
    node->data.func_decl.symbol = NULL; /* Will be set during semantic analysis */
    
    return node;
}

/**
 * Create a sequence node
 */
ASTNode* create_sequence_node(ASTNode* first, ASTNode* second, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for sequence node\n");
        return NULL;
    }
    
    node->type = NODE_SEQUENCE;
    node->line_number = line_number;
    node->data.sequence.first = first;
    node->data.sequence.second = second;
    
    return node;
}

/**
 * Create an array access node
 */
ASTNode* create_array_access_node(ASTNode* array, ASTNode* index, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for array access node\n");
        return NULL;
    }
    
    node->type = NODE_ARRAY_ACCESS;
    node->line_number = line_number;
    node->data.array_access.array = array;
    node->data.array_access.index = index;
    node->data.array_access.element_type = TYPE_UNKNOWN;  /* Initialize to unknown */
    
    return node;
}

/**
 * Create a field access node
 */
ASTNode* create_field_access_node(ASTNode* object, char* field_name, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for field access node\n");
        return NULL;
    }
    
    node->type = NODE_FIELD_ACCESS;
    node->line_number = line_number;
    node->data.field_access.object = object;
    node->data.field_access.field_name = strdup(field_name);
    
    return node;
}

/**
 * Create an if node
 */
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for if node\n");
        return NULL;
    }
    
    node->type = NODE_IF;
    node->line_number = line_number;
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.then_branch = then_branch;
    node->data.if_stmt.else_branch = else_branch;
    
    return node;
}

/**
 * Create a while node
 */
ASTNode* create_while_node(ASTNode* condition, ASTNode* body, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for while node\n");
        return NULL;
    }
    
    node->type = NODE_WHILE;
    node->line_number = line_number;
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;
    
    return node;
}

/**
 * Create a for node
 */
ASTNode* create_for_node(ASTNode* init, ASTNode* condition, ASTNode* update, ASTNode* body, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for for node\n");
        return NULL;
    }
    
    node->type = NODE_FOR;
    node->line_number = line_number;
    node->data.for_stmt.init = init;
    node->data.for_stmt.condition = condition;
    node->data.for_stmt.update = update;
    node->data.for_stmt.body = body;
    
    return node;
}

/**
 * Create a return node
 */
ASTNode* create_return_node(ASTNode* value, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for return node\n");
        return NULL;
    }
    
    node->type = NODE_RETURN;
    node->line_number = line_number;
    node->data.return_stmt.value = value;
    
    return node;
}

/**
 * Create a print node
 */
ASTNode* create_print_node(ASTNode *expression, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for print node\n");
        exit(1);
    }
    
    node->type = NODE_PRINT;
    node->line_number = line;
    node->data.print_stmt.expression = expression;
    
    return node;
}

/**
 * Create an array elements node
 */
ASTNode* create_array_elements_node(ASTNode* element, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    node->type = NODE_ARRAY_ELEMENTS;
    node->line_number = element ? element->line_number : 0;
    node->data.array_elements.element = element;
    node->data.array_elements.next = next;
    return node;
}

/**
 * Create an array literal node
 */
ASTNode* create_array_literal_node(ASTNode* elements, int line) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    node->type = NODE_ARRAY_LITERAL;
    node->line_number = line;
    node->data.array_elements.element = elements;
    node->data.array_elements.next = NULL;
    return node;
}

/**
 * Free an AST node and all its children
 */
void free_ast_node(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_STRING:
            if (node->data.string_value) free(node->data.string_value);
            break;
            
        case NODE_IDENTIFIER:
            if (node->data.identifier) free(node->data.identifier);
            break;
            
        case NODE_BINARY_OP:
            free_ast_node(node->data.binary_op.left);
            free_ast_node(node->data.binary_op.right);
            break;
            
        case NODE_UNARY_OP:
            free_ast_node(node->data.unary_op.operand);
            break;
            
        case NODE_VAR_DECLARATION:
            if (node->data.var_decl.name) free(node->data.var_decl.name);
            if (node->data.var_decl.initializer) free_ast_node(node->data.var_decl.initializer);
            break;
            
        case NODE_ASSIGNMENT:
            free_ast_node(node->data.assignment.target);
            free_ast_node(node->data.assignment.value);
            break;
            
        case NODE_IF:
            free_ast_node(node->data.if_stmt.condition);
            free_ast_node(node->data.if_stmt.then_branch);
            if (node->data.if_stmt.else_branch) free_ast_node(node->data.if_stmt.else_branch);
            break;
            
        case NODE_WHILE:
            free_ast_node(node->data.while_stmt.condition);
            free_ast_node(node->data.while_stmt.body);
            break;
            
        case NODE_FOR:
            free_ast_node(node->data.for_stmt.init);
            free_ast_node(node->data.for_stmt.condition);
            free_ast_node(node->data.for_stmt.update);
            free_ast_node(node->data.for_stmt.body);
            break;
            
        case NODE_RETURN:
            free_ast_node(node->data.return_stmt.value);
            break;
            
        case NODE_FUNCTION_CALL:
            if (node->data.func_call.name) free(node->data.func_call.name);
            if (node->data.func_call.arguments) {
                for (int i = 0; i < node->data.func_call.arg_count; i++) {
                    free_ast_node(node->data.func_call.arguments[i]);
                }
                free(node->data.func_call.arguments);
            }
            break;
            
        case NODE_FUNCTION_DECLARATION:
            if (node->data.func_decl.name) free(node->data.func_decl.name);
            if (node->data.func_decl.parameters) {
                Parameter* param = node->data.func_decl.parameters;
                while (param) {
                    Parameter* next = param->next;
                    if (param->name) free(param->name);
                    free(param);
                    param = next;
                }
            }
            if (node->data.func_decl.body) free_ast_node(node->data.func_decl.body);
            break;
            
        case NODE_SEQUENCE:
            free_ast_node(node->data.sequence.first);
            free_ast_node(node->data.sequence.second);
            break;
            
        case NODE_ARRAY_ACCESS:
            free_ast_node(node->data.array_access.array);
            free_ast_node(node->data.array_access.index);
            break;
            
        case NODE_FIELD_ACCESS:
            free_ast_node(node->data.field_access.object);
            if (node->data.field_access.field_name) free(node->data.field_access.field_name);
            break;
            
        case NODE_PRINT:
            free_ast_node(node->data.print_stmt.expression);
            break;
            
        case NODE_ARRAY_LITERAL: {
            // Analyze array elements
            ASTNode* elements = node->data.array_elements.element;
            while (elements) {
                free_ast_node(elements);
                elements = elements->data.array_elements.next;
            }
            break;
        }
            
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
void print_ast(ASTNode* node, int indent) {
    ASTNode *decl;
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            print_indent(indent);
            printf("Program (line %d):\n", node->line_number);
            print_indent(indent + 1);
            printf("Declarations:\n");
            decl = node->data.program.declarations;
            while (decl) {
                if (decl->type == NODE_SEQUENCE) {
                    print_ast(decl->data.sequence.first, indent + 2);
                    decl = decl->data.sequence.second;
                } else {
                    print_ast(decl, indent + 2);
                    break;
                }
            }
            print_indent(indent + 1);
            printf("Main Block:\n");
            if (node->data.program.main_function) {
                print_ast(node->data.program.main_function, indent + 2);
            } else {
                print_indent(indent + 2);
                printf("(none)\n");
            }
            break;
            
        case NODE_VAR_DECLARATION:
            printf("Variable Declaration: %s (type: %s, line %d)\n", 
                   node->data.var_decl.name, 
                   symbol_type_to_string(node->data.var_decl.type),
                   node->line_number);
            if (node->data.var_decl.initializer) {
                print_indent(indent + 1);
                printf("Initial Value:\n");
                print_ast(node->data.var_decl.initializer, indent + 2);
            }
            break;
            
        case NODE_FUNCTION_DECLARATION:
            printf("Function Declaration: %s (return type: %s, line %d)\n",
                   node->data.func_decl.name,
                   symbol_type_to_string(node->data.func_decl.return_type),
                   node->line_number);
            if (node->data.func_decl.parameters) {
                print_indent(indent + 1);
                printf("Parameters:\n");
                Parameter* param = node->data.func_decl.parameters;
                while (param) {
                    print_indent(indent + 2);
                    printf("%s: %s\n", param->name, symbol_type_to_string(param->type));
                    param = param->next;
                }
            }
            if (node->data.func_decl.body) {
                print_indent(indent + 1);
                printf("Body:\n");
                print_ast(node->data.func_decl.body, indent + 2);
            }
            break;
            
        case NODE_BINARY_OP:
            printf("Binary Operation (line %d):\n", node->line_number);
            print_indent(indent + 1);
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
                case OP_LTE:    printf("LESS EQUAL (<=)\n"); break;
                case OP_GTE:    printf("GREATER EQUAL (>=)\n"); break;
                case OP_FACT:   printf("FACTORIAL (!)\n"); break;
                case OP_NOT:    printf("NOT (machi)\n"); break;
                default:        printf("UNKNOWN OPERATOR\n"); break;
            }
            print_indent(indent + 1);
            printf("Left:\n");
            print_ast(node->data.binary_op.left, indent + 2);
            print_indent(indent + 1);
            printf("Right:\n");
            print_ast(node->data.binary_op.right, indent + 2);
            break;
            
        case NODE_UNARY_OP:
            printf("Unary Operation (line %d):\n", node->line_number);
            print_indent(indent + 1);
            switch (node->data.unary_op.op) {
                case OP_NOT:    printf("NOT (machi)\n"); break;
                case OP_FACT:   printf("FACTORIAL (!)\n"); break;
                case OP_ADD:    printf("UNARY PLUS (+)\n"); break;
                case OP_SUB:    printf("UNARY MINUS (-)\n"); break;
                case OP_MUL:    printf("UNARY MULTIPLY (*)\n"); break;
                case OP_DIV:    printf("UNARY DIVIDE (/)\n"); break;
                case OP_INT_DIV: printf("UNARY INTEGER DIVIDE (div)\n"); break;
                case OP_AND:    printf("UNARY AND (w)\n"); break;
                case OP_OR:     printf("UNARY OR (wla)\n"); break;
                case OP_EQ:     printf("UNARY EQUAL (==)\n"); break;
                case OP_NEQ:    printf("UNARY NOT EQUAL (<>)\n"); break;
                case OP_LT:     printf("UNARY LESS THAN (<)\n"); break;
                case OP_GT:     printf("UNARY GREATER THAN (>)\n"); break;
                case OP_LTE:    printf("UNARY LESS EQUAL (<=)\n"); break;
                case OP_GTE:    printf("UNARY GREATER EQUAL (>=)\n"); break;
                default:        printf("UNKNOWN UNARY OPERATOR\n"); break;
            }
            print_indent(indent + 1);
            printf("Operand:\n");
            print_ast(node->data.unary_op.operand, indent + 2);
            break;
            
        case NODE_NUMBER:
            printf("Number: %g (line %d)\n", node->data.number_value, node->line_number);
            break;
            
        case NODE_STRING:
            printf("String: \"%s\" (line %d)\n", node->data.string_value, node->line_number);
            break;
            
        case NODE_IDENTIFIER:
            printf("Identifier: %s (line %d)\n", node->data.identifier, node->line_number);
            break;
            
        case NODE_ASSIGNMENT:
            printf("Assignment (line %d):\n", node->line_number);
            print_indent(indent + 1);
            printf("Target:\n");
            print_ast(node->data.assignment.target, indent + 2);
            print_indent(indent + 1);
            printf("Value:\n");
            print_ast(node->data.assignment.value, indent + 2);
            break;
            
        case NODE_IF:
            printf("If Statement (line %d):\n", node->line_number);
            print_indent(indent + 1);
            printf("Condition:\n");
            print_ast(node->data.if_stmt.condition, indent + 2);
            print_indent(indent + 1);
            printf("Then Branch:\n");
            print_ast(node->data.if_stmt.then_branch, indent + 2);
            if (node->data.if_stmt.else_branch) {
                print_indent(indent + 1);
                printf("Else Branch:\n");
                print_ast(node->data.if_stmt.else_branch, indent + 2);
            }
            break;
            
        case NODE_WHILE:
            printf("While Loop (line %d):\n", node->line_number);
            print_indent(indent + 1);
            printf("Condition:\n");
            print_ast(node->data.while_stmt.condition, indent + 2);
            print_indent(indent + 1);
            printf("Body:\n");
            print_ast(node->data.while_stmt.body, indent + 2);
            break;
            
        case NODE_FOR:
            printf("For Loop (line %d):\n", node->line_number);
            print_indent(indent + 1);
            printf("Initialization:\n");
            print_ast(node->data.for_stmt.init, indent + 2);
            print_indent(indent + 1);
            printf("Condition:\n");
            print_ast(node->data.for_stmt.condition, indent + 2);
            print_indent(indent + 1);
            printf("Update:\n");
            print_ast(node->data.for_stmt.update, indent + 2);
            print_indent(indent + 1);
            printf("Body:\n");
            print_ast(node->data.for_stmt.body, indent + 2);
            break;
            
        case NODE_RETURN:
            printf("Return Statement (line %d):\n", node->line_number);
            if (node->data.return_stmt.value) {
                print_indent(indent + 1);
                printf("Value:\n");
                print_ast(node->data.return_stmt.value, indent + 2);
            }
            break;
            
        case NODE_FUNCTION_CALL:
            printf("Function Call: %s (line %d)\n", node->data.func_call.name, node->line_number);
            if (node->data.func_call.arguments) {
                print_indent(indent + 1);
                printf("Arguments:\n");
                for (int i = 0; i < node->data.func_call.arg_count; i++) {
                    print_ast(node->data.func_call.arguments[i], indent + 2);
                }
            }
            break;
            
        case NODE_SEQUENCE:
            printf("Sequence (line %d):\n", node->line_number);
            print_indent(indent + 1);
            printf("First:\n");
            print_ast(node->data.sequence.first, indent + 2);
            print_indent(indent + 1);
            printf("Second:\n");
            print_ast(node->data.sequence.second, indent + 2);
            break;
            
        case NODE_ARRAY_ACCESS:
            printf("Array Access (line %d):\n", node->line_number);
            print_indent(indent + 1);
            printf("Array:\n");
            print_ast(node->data.array_access.array, indent + 2);
            print_indent(indent + 1);
            printf("Index:\n");
            print_ast(node->data.array_access.index, indent + 2);
            break;
            
        case NODE_FIELD_ACCESS:
            printf("Field Access (line %d):\n", node->line_number);
            print_indent(indent + 1);
            printf("Object:\n");
            print_ast(node->data.field_access.object, indent + 2);
            print_indent(indent + 1);
            printf("Field: %s\n", node->data.field_access.field_name);
            break;
            
        case NODE_PRINT:
            printf("Print Statement (line %d):\n", node->line_number);
            print_indent(indent + 1);
            printf("Expression:\n");
            print_ast(node->data.print_stmt.expression, indent + 2);
            break;
            
        case NODE_ARRAY_LITERAL: {
            // Analyze array elements
            ASTNode* elements = node->data.array_elements.element;
            if (elements) {
                // Get the type of the first element
                SymbolType first_type = get_expression_type(elements, NULL);
                
                // Check that all elements have compatible types
                if (!check_array_element_types(node, first_type)) {
                    semantic_error(node->line_number,
                        "Array elements must have compatible types");
                }
                
                // Analyze each element
                while (elements) {
                    analyze_ast(elements, NULL);
                    elements = elements->data.array_elements.next;
                }
            }
            break;
        }
            
        default:
            printf("Unknown Node Type: %d (line %d)\n", node->type, node->line_number);
            break;
    }
}

/* ------------------- Semantic Analysis Functions ------------------- */

/* Helper function for semantic error reporting */
static void semantic_error(int line, const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Semantic Error at line %d: ", line);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

/* Helper function to check type compatibility */
static int is_type_compatible(SymbolType left, SymbolType right) {
    /* Special case for numeric types */
    if ((left == TYPE_RA9M || left == TYPE_WA9ILA) && 
        (right == TYPE_RA9M || right == TYPE_WA9ILA)) {
        return 1;
    }
    
    /* Special case for array types */
    if (left == TYPE_LISTA && right == TYPE_LISTA) {
        /* For now, consider all arrays compatible */
        /* TODO: In a more sophisticated implementation, we would check element types */
        return 1;
    }
    
    /* For all other types, they must match exactly */
    return left == right;
}

/* Helper function to get expression type */
static SymbolType get_expression_type(ASTNode* node, SymbolTable* table) {
    if (!node) return TYPE_UNKNOWN;
    
    switch (node->type) {
        case NODE_NUMBER:
            return TYPE_RA9M;
            
        case NODE_STRING:
            return TYPE_KTABA;
            
        case NODE_IDENTIFIER: {
            if (!table) return TYPE_UNKNOWN;
            SymbolEntry* entry = lookup_symbol(table, node->data.identifier);
            return entry ? entry->type : TYPE_UNKNOWN;
        }
        
        case NODE_ARRAY_LITERAL:
            return TYPE_LISTA;
            
        case NODE_ARRAY_ACCESS: {
            if (node->data.array_access.element_type != TYPE_UNKNOWN) {
                return node->data.array_access.element_type;
            }
            return TYPE_RA9M; // Default to RA9M if element type is unknown
        }
        
        case NODE_BINARY_OP: {
            SymbolType left_type = get_expression_type(node->data.binary_op.left, table);
            SymbolType right_type = get_expression_type(node->data.binary_op.right, table);
            
            switch (node->data.binary_op.op) {
                case OP_ADD:
                case OP_SUB:
                case OP_MUL:
                case OP_DIV:
                case OP_INT_DIV:
                    if (left_type == TYPE_RA9M && right_type == TYPE_RA9M)
                        return TYPE_RA9M;
                    return TYPE_UNKNOWN;
                    
                case OP_AND:
                case OP_OR:
                    if (left_type == TYPE_WA9ILA && right_type == TYPE_WA9ILA)
                        return TYPE_WA9ILA;
                    return TYPE_UNKNOWN;
                    
                case OP_EQ:
                case OP_NEQ:
                case OP_GT:
                case OP_LT:
                case OP_GTE:
                case OP_LTE:
                    return TYPE_WA9ILA;
                    
                default:
                    return TYPE_UNKNOWN;
            }
        }
        
        case NODE_UNARY_OP: {
            SymbolType operand_type = get_expression_type(node->data.unary_op.operand, table);
            
            switch (node->data.unary_op.op) {
                case OP_NOT:
                    if (operand_type == TYPE_WA9ILA)
                        return TYPE_WA9ILA;
                    return TYPE_UNKNOWN;
                    
                case OP_FACT:
                    if (operand_type == TYPE_RA9M)
                        return TYPE_RA9M;
                    return TYPE_UNKNOWN;
                    
                default:
                    return TYPE_UNKNOWN;
            }
        }
        
        case NODE_FUNCTION_CALL: {
            SymbolEntry* func = lookup_symbol(table, node->data.func_call.name);
            if (func && func->category == SYMBOL_FUNCTION)
                return func->value.func_info.return_type;
            return TYPE_UNKNOWN;
        }
        
        default:
            return TYPE_UNKNOWN;
    }
}

/* Helper function to check array element types */
static int check_array_element_types(ASTNode* array_literal, SymbolType expected_type) {
    if (!array_literal || array_literal->type != NODE_ARRAY_LITERAL) {
        return 0;
    }
    
    ASTNode* current = array_literal->data.array_elements.element;
    while (current) {
        analyze_ast(current, NULL);
        SymbolType element_type = get_expression_type(current, NULL);
        
        if (!is_type_compatible(expected_type, element_type)) {
            semantic_error(current->line_number,
                "Array element type mismatch: expected %s but got %s",
                symbol_type_to_string(expected_type),
                symbol_type_to_string(element_type));
            return 0;
        }
        
        current = current->data.array_elements.next;
    }
    
    return 1;
}

/* Helper function to get array element type */
static SymbolType get_array_element_type(ASTNode* array_literal) {
    if (!array_literal || array_literal->type != NODE_ARRAY_LITERAL) {
        return TYPE_UNKNOWN;
    }
    
    ASTNode* first_element = array_literal->data.array_elements.element;
    if (!first_element) {
        return TYPE_UNKNOWN;
    }
    
    return get_expression_type(first_element, NULL);
}

/**
 * Perform semantic analysis on the AST
 */
void analyze_ast(ASTNode* node, SymbolTable* table) {
    ASTNode *decl;
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            // Analyze declarations
            decl = node->data.program.declarations;
            while (decl) {
                if (decl->type == NODE_SEQUENCE) {
                    analyze_ast(decl->data.sequence.first, table);
                    decl = decl->data.sequence.second;
                } else {
                    analyze_ast(decl, table);
                    break;
                }
            }
            // Analyze main function
            if (node->data.program.main_function) {
                analyze_ast(node->data.program.main_function, table);
            }
            break;
            
        case NODE_VAR_DECLARATION: {
            /* Check for duplicate declaration in current scope */
            if (lookup_symbol_current_scope(table, node->data.var_decl.name)) {
                semantic_error(node->line_number, 
                    "Variable '%s' already declared in current scope", 
                    node->data.var_decl.name);
                break;
            }
            
            /* Add variable to symbol table */
            node->data.var_decl.symbol = add_symbol(
                table,
                node->data.var_decl.name,
                node->data.var_decl.type,
                SYMBOL_VARIABLE,
                node->line_number
            );
            
            /* Check initializer type if present */
            if (node->data.var_decl.initializer) {
                analyze_ast(node->data.var_decl.initializer, table);
                SymbolType init_type = get_expression_type(node->data.var_decl.initializer, table);
                
                if (node->data.var_decl.type == TYPE_LISTA && init_type == TYPE_LISTA) {
                    // For array types, store the element type
                    SymbolType element_type = get_array_element_type(node->data.var_decl.initializer);
                    if (element_type != TYPE_UNKNOWN) {
                        node->data.var_decl.symbol->value.list_info.element_type = element_type;
                    }
                }
                
                if (!is_type_compatible(node->data.var_decl.type, init_type)) {
                    semantic_error(node->line_number,
                        "Type mismatch in initialization of '%s': expected %s but got %s",
                        node->data.var_decl.name,
                        symbol_type_to_string(node->data.var_decl.type),
                        symbol_type_to_string(init_type));
                }
            }
            break;
        }
            
        case NODE_FUNCTION_DECLARATION: {
            /* Check for duplicate function declaration */
            if (lookup_symbol_current_scope(table, node->data.func_decl.name)) {
                semantic_error(node->line_number,
                    "Function '%s' already declared",
                    node->data.func_decl.name);
                break;
            }
            
            /* Add function to symbol table */
            node->data.func_decl.symbol = add_symbol(
                table,
                node->data.func_decl.name,
                TYPE_FUNCTION,
                SYMBOL_FUNCTION,
                node->line_number
            );
            
            if (node->data.func_decl.symbol) {
                node->data.func_decl.symbol->value.func_info.return_type = node->data.func_decl.return_type;
                node->data.func_decl.symbol->value.func_info.parameters = node->data.func_decl.parameters;
                
                /* Enter new scope for function body */
                enter_scope(table);
                
                /* Add parameters to symbol table */
                Parameter* param = node->data.func_decl.parameters;
                while (param) {
                    add_symbol(table, param->name, param->type, SYMBOL_PARAMETER, node->line_number);
                    param = param->next;
                }
                
                /* Analyze function body */
                if (node->data.func_decl.body) {
                    analyze_ast(node->data.func_decl.body, table);
                }
                
                /* Exit function scope */
                exit_scope(table);
            }
            break;
        }
            
        case NODE_BINARY_OP: {
            analyze_ast(node->data.binary_op.left, table);
            analyze_ast(node->data.binary_op.right, table);
            
            SymbolType left_type = get_expression_type(node->data.binary_op.left, table);
            SymbolType right_type = get_expression_type(node->data.binary_op.right, table);
            
            /* Type checking for operators */
            switch (node->data.binary_op.op) {
                case OP_ADD:
                case OP_SUB:
                case OP_MUL:
                case OP_DIV:
                case OP_INT_DIV:
                    if (left_type != TYPE_RA9M || right_type != TYPE_RA9M) {
                        semantic_error(node->line_number,
                            "Arithmetic operation requires numeric operands, got %s and %s",
                            symbol_type_to_string(left_type),
                            symbol_type_to_string(right_type));
                    }
                    break;
                    
                case OP_AND:
                case OP_OR:
                    if (left_type != TYPE_WA9ILA || right_type != TYPE_WA9ILA) {
                        semantic_error(node->line_number,
                            "Logical operation requires boolean operands, got %s and %s",
                            symbol_type_to_string(left_type),
                            symbol_type_to_string(right_type));
                    }
                    break;
                    
                default:
                    break;
            }
            break;
        }
            
        case NODE_UNARY_OP:
            analyze_ast(node->data.unary_op.operand, table);
            
            if (node->data.unary_op.op == OP_NOT) {
                SymbolType operand_type = get_expression_type(node->data.unary_op.operand, table);
                if (operand_type != TYPE_WA9ILA) {
                    semantic_error(node->line_number,
                        "Logical NOT operation requires boolean operand, got %s",
                        symbol_type_to_string(operand_type));
                }
            }
            break;
            
        case NODE_IDENTIFIER: {
            /* Check if identifier is declared */
            SymbolEntry* entry = lookup_symbol(table, node->data.identifier);
            if (!entry) {
                semantic_error(node->line_number,
                    "Undefined identifier '%s'",
                    node->data.identifier);
            }
            break;
        }
            
        case NODE_ASSIGNMENT: {
            analyze_ast(node->data.assignment.target, table);
            analyze_ast(node->data.assignment.value, table);
            
            SymbolType target_type = get_expression_type(node->data.assignment.target, table);
            SymbolType value_type = get_expression_type(node->data.assignment.value, table);
            
            if (!is_type_compatible(target_type, value_type)) {
                semantic_error(node->line_number,
                    "Type mismatch in assignment: cannot assign %s to %s",
                    symbol_type_to_string(value_type),
                    symbol_type_to_string(target_type));
            }
            break;
        }
            
        case NODE_IF:
            analyze_ast(node->data.if_stmt.condition, table);
            
            SymbolType cond_type = get_expression_type(node->data.if_stmt.condition, table);
            if (cond_type != TYPE_WA9ILA) {
                semantic_error(node->line_number,
                    "Condition must be of boolean type, got %s",
                    symbol_type_to_string(cond_type));
            }
            
            enter_scope(table);
            analyze_ast(node->data.if_stmt.then_branch, table);
            exit_scope(table);
            
            if (node->data.if_stmt.else_branch) {
                enter_scope(table);
                analyze_ast(node->data.if_stmt.else_branch, table);
                exit_scope(table);
            }
            break;
            
        case NODE_WHILE:
            analyze_ast(node->data.while_stmt.condition, table);
            
            SymbolType while_cond_type = get_expression_type(node->data.while_stmt.condition, table);
            if (while_cond_type != TYPE_WA9ILA) {
                semantic_error(node->line_number,
                    "Loop condition must be of boolean type, got %s",
                    symbol_type_to_string(while_cond_type));
            }
            
            enter_scope(table);
            analyze_ast(node->data.while_stmt.body, table);
            exit_scope(table);
            break;
            
        case NODE_FOR:
            enter_scope(table);
            
            analyze_ast(node->data.for_stmt.init, table);
            analyze_ast(node->data.for_stmt.condition, table);
            analyze_ast(node->data.for_stmt.update, table);
            
            SymbolType for_cond_type = get_expression_type(node->data.for_stmt.condition, table);
            if (for_cond_type != TYPE_WA9ILA) {
                semantic_error(node->line_number,
                    "For loop condition must be of boolean type, got %s",
                    symbol_type_to_string(for_cond_type));
            }
            
            analyze_ast(node->data.for_stmt.body, table);
            exit_scope(table);
            break;
            
        case NODE_RETURN: {
            if (node->data.return_stmt.value) {
                analyze_ast(node->data.return_stmt.value, table);
                
                /* Find enclosing function's return type */
                Scope* scope = table->current_scope;
                SymbolType expected_type = TYPE_UNKNOWN;
                
                while (scope) {
                    SymbolEntry* entry = scope->entries;
                    while (entry) {
                        if (entry->category == SYMBOL_FUNCTION) {
                            expected_type = entry->value.func_info.return_type;
                            goto found_return_type;
                        }
                        entry = entry->next;
                    }
                    scope = scope->parent;
                }
                
            found_return_type:
                {
                    SymbolType actual_type = get_expression_type(node->data.return_stmt.value, table);
                    if (!is_type_compatible(expected_type, actual_type)) {
                        semantic_error(node->line_number,
                            "Return type mismatch: expected %s but got %s",
                            symbol_type_to_string(expected_type),
                            symbol_type_to_string(actual_type));
                    }
                }
            }
            break;
        }
            
        case NODE_FUNCTION_CALL: {
            /* Check if function exists */
            SymbolEntry* func = lookup_symbol(table, node->data.func_call.name);
            if (!func) {
                semantic_error(node->line_number,
                    "Undefined function '%s'",
                    node->data.func_call.name);
                break;
            }
            
            if (func->category != SYMBOL_FUNCTION) {
                semantic_error(node->line_number,
                    "'%s' is not a function",
                    node->data.func_call.name);
                break;
            }
            
            node->data.func_call.symbol = func;
            
            /* Check argument types */
            Parameter* param = func->value.func_info.parameters;
            int arg_index = 0;
            
            while (param && arg_index < node->data.func_call.arg_count) {
                analyze_ast(node->data.func_call.arguments[arg_index], table);
                
                SymbolType arg_type = get_expression_type(node->data.func_call.arguments[arg_index], table);
                if (!is_type_compatible(param->type, arg_type)) {
                    semantic_error(node->line_number,
                        "Type mismatch in argument %d of call to '%s': expected %s but got %s",
                        arg_index + 1,
                        node->data.func_call.name,
                        symbol_type_to_string(param->type),
                        symbol_type_to_string(arg_type));
                }
                
                param = param->next;
                arg_index++;
            }
            
            if (param) {
                semantic_error(node->line_number,
                    "Too few arguments in call to '%s'",
                    node->data.func_call.name);
            }
            
            if (arg_index < node->data.func_call.arg_count) {
                semantic_error(node->line_number,
                    "Too many arguments in call to '%s'",
                    node->data.func_call.name);
            }
            break;
        }
            
        case NODE_SEQUENCE:
            analyze_ast(node->data.sequence.first, table);
            analyze_ast(node->data.sequence.second, table);
            break;
            
        case NODE_FIELD_ACCESS:
            analyze_ast(node->data.field_access.object, table);
            
            SymbolType object_type = get_expression_type(node->data.field_access.object, table);
            if (object_type != TYPE_JADWAL) {
                semantic_error(node->line_number,
                    "Field access on non-jadwal type %s",
                    symbol_type_to_string(object_type));
            }
            break;
            
        case NODE_PRINT:
            analyze_ast(node->data.print_stmt.expression, table);
            break;
            
        case NODE_ARRAY_LITERAL: {
            // Analyze array elements
            ASTNode* elements = node->data.array_elements.element;
            if (elements) {
                // Get the type of the first element
                SymbolType first_type = get_expression_type(elements, table);
                
                // Check that all elements have compatible types
                if (!check_array_element_types(node, first_type)) {
                    semantic_error(node->line_number,
                        "Array elements must have compatible types");
                }
                
                // Analyze each element
                while (elements) {
                    analyze_ast(elements, table);
                    elements = elements->data.array_elements.next;
                }
            }
            break;
        }
            
        default:
            break;
    }
}
