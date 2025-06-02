/**
 * ast.c - Implementation of Abstract Syntax Tree and Symbol Table for LazyUi compiler
 */

#include "ast.h"

/* Global symbol table */
extern SymbolTable* symbol_table;

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
        exit_scope();
    }
    
    /* Free the global scope */
    if (table->current_scope) {
        SymbolEntry *entry = table->current_scope->entries;
        while (entry) {
            SymbolEntry *next = entry->next;
            if (entry->name) free(entry->name);
            free(entry);
            entry = next;
        }
        free(table->current_scope);
    }
    
    free(table);
}

/**
 * Enter a new scope
 */
void enter_scope(void) {
    Scope* new_scope = (Scope*)malloc(sizeof(Scope));
    new_scope->entries = NULL;
    new_scope->parent = symbol_table->current_scope;
    new_scope->level = symbol_table->current_scope ? symbol_table->current_scope->level + 1 : 0;
    symbol_table->current_scope = new_scope;
}

/**
 * Exit current scope
 */
void exit_scope(void) {
    if (symbol_table && symbol_table->current_scope) {
        Scope* parent = symbol_table->current_scope->parent;
        // Free all symbols in current scope
        SymbolEntry* current = symbol_table->current_scope->entries;
        while (current) {
            SymbolEntry* next = current->next;
            free(current->name);
            free(current);
            current = next;
        }
        free(symbol_table->current_scope);
        symbol_table->current_scope = parent;
    }
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
    
    return node;
}

/**
 * Create a field access node
 */
ASTNode* create_field_access_node(ASTNode* object, char* field_name, int line_number) {
    ASTNode* node = malloc(sizeof(ASTNode));
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
 * Create a try-catch node
 */
ASTNode* create_try_node(ASTNode* try_block, ASTNode* catch_block, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation error for try-catch node\n");
        return NULL;
    }
    
    node->type = NODE_TRY;
    node->line_number = line_number;
    node->data.try_stmt.try_block = try_block;
    node->data.try_stmt.catch_block = catch_block;
    
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
            
        case NODE_TRY:
            free_ast_node(node->data.try_stmt.try_block);
            free_ast_node(node->data.try_stmt.catch_block);
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
void print_ast(ASTNode* node, int level) {
    if (node == NULL) return;

    for (int i = 0; i < level; i++) printf("  ");

    switch (node->type) {
        case NODE_NUMBER:
            printf("Number: %f\n", node->data.number_value);
            break;
        case NODE_STRING:
            printf("String: \"%s\"\n", node->data.string_value);
            break;
        case NODE_IDENTIFIER:
            printf("Identifier: %s\n", node->data.identifier);
            break;
        case NODE_BINARY_OP:
            printf("Binary Operation: ");
            switch (node->data.binary_op.op) {
                case OP_ADD: printf("ADD\n"); break;
                case OP_SUB: printf("SUB\n"); break;
                case OP_MUL: printf("MUL\n"); break;
                case OP_DIV: printf("DIV\n"); break;
                case OP_SUP: printf("SUP\n"); break;
                case OP_INF: printf("INF\n"); break;
                case OP_SUP_EQ: printf("SUP_EQ\n"); break;
                case OP_INF_EQ: printf("INF_EQ\n"); break;
                case OP_EQUAL: printf("EQUAL\n"); break;
                case OP_DIFF: printf("DIFF\n"); break;
                default: printf("UNKNOWN\n"); break;
            }
            print_ast(node->data.binary_op.left, level + 1);
            print_ast(node->data.binary_op.right, level + 1);
            break;
        case NODE_VAR_DECLARATION:
            printf("Variable Declaration: %s (type: %s)\n", 
                   node->data.var_decl.name,
                   symbol_type_to_string(node->data.var_decl.type));
            if (node->data.var_decl.initializer) {
                printf("Initializer:\n");
                print_ast(node->data.var_decl.initializer, level + 1);
            }
            break;
        case NODE_ASSIGNMENT:
            printf("Assignment\n");
            printf("Target:\n");
            print_ast(node->data.assignment.target, level + 1);
            printf("Value:\n");
            print_ast(node->data.assignment.value, level + 1);
            break;
        case NODE_FIELD_ACCESS:
            printf("Field Access: %s\n", node->data.field_access.field_name);
            printf("Object:\n");
            print_ast(node->data.field_access.object, level + 1);
            break;
        case NODE_PRINT:
            printf("Print Statement\n");
            print_ast(node->data.print_stmt.expression, level + 1);
            break;
        case NODE_SEQUENCE:
            printf("Sequence\n");
            print_ast(node->data.sequence.first, level + 1);
            print_ast(node->data.sequence.second, level + 1);
            break;
        case NODE_PROGRAM:
            printf("Program\n");
            printf("Declarations:\n");
            print_ast(node->data.program.declarations, level + 1);
            printf("Main Function:\n");
            print_ast(node->data.program.main_function, level + 1);
            break;
        default:
            printf("Unknown Node Type: %d\n", node->type);
            break;
    }
}

/* ------------------- Semantic Analysis Functions ------------------- */

/* Helper function to check type compatibility */
static int is_type_compatible(SymbolType left_type, SymbolType right_type) {
    if (left_type == right_type) return 1;
    
    // Special cases for type compatibility
    if (left_type == TYPE_RA9M && right_type == TYPE_WA9ILA) return 1;
    if (left_type == TYPE_WA9ILA && right_type == TYPE_RA9M) return 1;
    
    return 0;
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
            SymbolEntry* entry = lookup_symbol(table, node->data.identifier);
            return entry ? entry->type : TYPE_UNKNOWN;
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

/**
 * Perform semantic analysis on the AST
 */
void analyze_ast(ASTNode* node, SymbolTable* table) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            // Analyze declarations
            analyze_ast(node->data.program.declarations, table);
            // Analyze main function
            if (node->data.program.main_function) {
                analyze_ast(node->data.program.main_function, table);
            }
            break;
            
        case NODE_VAR_DECLARATION: {
            /* Check for duplicate declaration in current scope */
            if (lookup_symbol_current_scope(table, node->data.var_decl.name)) {
                fprintf(stderr, "Error at line %d: Variable '%s' already declared in current scope\n",
                        node->line_number, node->data.var_decl.name);
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
                if (node->data.var_decl.type == TYPE_JADWAL) {
                    // For jadwal type, analyze each field assignment
                    ASTNode* field = node->data.var_decl.initializer;
                    while (field) {
                        if (field->type == NODE_SEQUENCE) {
                            analyze_ast(field->data.sequence.first, table);
                            field = field->data.sequence.second;
                        } else {
                            analyze_ast(field, table);
                            break;
                        }
                    }
                } else {
                    analyze_ast(node->data.var_decl.initializer, table);
                    SymbolType init_type = get_expression_type(node->data.var_decl.initializer, table);
                    
                    if (!is_type_compatible(node->data.var_decl.type, init_type)) {
                        fprintf(stderr, "Error at line %d: Type mismatch in initialization of '%s'\n",
                                node->line_number, node->data.var_decl.name);
                    }
                }
            }
            break;
        }
            
        case NODE_FUNCTION_DECLARATION: {
            /* Check for duplicate function declaration */
            if (lookup_symbol_current_scope(table, node->data.func_decl.name)) {
                fprintf(stderr, "Error at line %d: Function '%s' already declared\n",
                        node->line_number, node->data.func_decl.name);
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
                enter_scope();
                
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
                exit_scope();
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
                        fprintf(stderr, "Error at line %d: Arithmetic operation requires numeric operands\n",
                                node->line_number);
                    }
                    break;
                    
                case OP_AND:
                case OP_OR:
                    if (left_type != TYPE_WA9ILA || right_type != TYPE_WA9ILA) {
                        fprintf(stderr, "Error at line %d: Logical operation requires boolean operands\n",
                                node->line_number);
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
                    fprintf(stderr, "Error at line %d: Logical NOT operation requires boolean operand\n",
                            node->line_number);
                }
            }
            break;
            
        case NODE_IDENTIFIER: {
            /* Check if identifier is declared */
            SymbolEntry* entry = lookup_symbol(table, node->data.identifier);
            if (!entry) {
                fprintf(stderr, "Error at line %d: Undefined identifier '%s'\n",
                        node->line_number, node->data.identifier);
            }
            break;
        }
            
        case NODE_ASSIGNMENT: {
            analyze_ast(node->data.assignment.target, table);
            analyze_ast(node->data.assignment.value, table);
            
            SymbolType target_type = get_expression_type(node->data.assignment.target, table);
            SymbolType value_type = get_expression_type(node->data.assignment.value, table);
            
            if (node->data.assignment.target->type == NODE_FIELD_ACCESS) {
                // For field assignments, we only check if the value type is numeric
                if (value_type != TYPE_RA9M) {
                    fprintf(stderr, "Error at line %d: Field value must be numeric\n",
                            node->line_number);
                }
            } else if (!is_type_compatible(target_type, value_type)) {
                fprintf(stderr, "Error at line %d: Type mismatch in assignment\n",
                        node->line_number);
            }
            break;
        }
            
        case NODE_IF:
            analyze_ast(node->data.if_stmt.condition, table);
            
            SymbolType cond_type = get_expression_type(node->data.if_stmt.condition, table);
            if (cond_type != TYPE_WA9ILA) {
                fprintf(stderr, "Error at line %d: Condition must be of boolean type\n",
                        node->line_number);
            }
            
            enter_scope();
            analyze_ast(node->data.if_stmt.then_branch, table);
            exit_scope();
            
            if (node->data.if_stmt.else_branch) {
                enter_scope();
                analyze_ast(node->data.if_stmt.else_branch, table);
                exit_scope();
            }
            break;
            
        case NODE_WHILE:
            analyze_ast(node->data.while_stmt.condition, table);
            
            SymbolType while_cond_type = get_expression_type(node->data.while_stmt.condition, table);
            if (while_cond_type != TYPE_WA9ILA) {
                fprintf(stderr, "Error at line %d: Loop condition must be of boolean type\n",
                        node->line_number);
            }
            
            enter_scope();
            analyze_ast(node->data.while_stmt.body, table);
            exit_scope();
            break;
            
        case NODE_FOR:
            enter_scope();
            
            analyze_ast(node->data.for_stmt.init, table);
            analyze_ast(node->data.for_stmt.condition, table);
            analyze_ast(node->data.for_stmt.update, table);
            
            SymbolType for_cond_type = get_expression_type(node->data.for_stmt.condition, table);
            if (for_cond_type != TYPE_WA9ILA) {
                fprintf(stderr, "Error at line %d: For loop condition must be of boolean type\n",
                        node->line_number);
            }
            
            analyze_ast(node->data.for_stmt.body, table);
            exit_scope();
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
                        fprintf(stderr, "Error at line %d: Return type mismatch\n",
                                node->line_number);
                    }
                }
            }
            break;
        }
            
        case NODE_FUNCTION_CALL: {
            /* Check if function exists */
            SymbolEntry* func = lookup_symbol(table, node->data.func_call.name);
            if (!func) {
                fprintf(stderr, "Error at line %d: Undefined function '%s'\n",
                        node->line_number, node->data.func_call.name);
                break;
            }
            
            if (func->category != SYMBOL_FUNCTION) {
                fprintf(stderr, "Error at line %d: '%s' is not a function\n",
                        node->line_number, node->data.func_call.name);
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
                    fprintf(stderr, "Error at line %d: Type mismatch in argument %d of call to '%s'\n",
                            node->line_number, arg_index + 1, node->data.func_call.name);
                }
                
                param = param->next;
                arg_index++;
            }
            
            if (param) {
                fprintf(stderr, "Error at line %d: Too few arguments in call to '%s'\n",
                        node->line_number, node->data.func_call.name);
            }
            
            if (arg_index < node->data.func_call.arg_count) {
                fprintf(stderr, "Error at line %d: Too many arguments in call to '%s'\n",
                        node->line_number, node->data.func_call.name);
            }
            break;
        }
            
        case NODE_SEQUENCE:
            analyze_ast(node->data.sequence.first, table);
            analyze_ast(node->data.sequence.second, table);
            break;
            
        case NODE_ARRAY_ACCESS:
            analyze_ast(node->data.array_access.array, table);
            analyze_ast(node->data.array_access.index, table);
            
            SymbolType array_type = get_expression_type(node->data.array_access.array, table);
            SymbolType index_type = get_expression_type(node->data.array_access.index, table);
            
            if (array_type != TYPE_LISTA) {
                fprintf(stderr, "Error at line %d: Array access on non-array type\n",
                        node->line_number);
            }
            
            if (index_type != TYPE_RA9M) {
                fprintf(stderr, "Error at line %d: Array index must be numeric\n",
                        node->line_number);
            }
            break;
            
        case NODE_FIELD_ACCESS: {
            analyze_ast(node->data.field_access.object, table);
            
            SymbolType object_type = get_expression_type(node->data.field_access.object, table);
            if (object_type != TYPE_JADWAL) {
                fprintf(stderr, "Error at line %d: Field access on non-jadwal type\n",
                        node->line_number);
            }
            break;
        }
            
        case NODE_PRINT:
            analyze_ast(node->data.print_stmt.expression, table);
            break;
            
        case NODE_TRY:
            analyze_ast(node->data.try_stmt.try_block, table);
            analyze_ast(node->data.try_stmt.catch_block, table);
            break;
            
        default:
            break;
    }
}
