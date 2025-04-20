/**
 * ast.h - Abstract Syntax Tree and Symbol Table definitions for LazyUi compiler
 */

#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Symbol types corresponding to language types */
typedef enum {
    TYPE_UNKNOWN,
    TYPE_RA9M,      /* Number type */
    TYPE_KTABA,     /* String type */
    TYPE_WA9ILA,    /* Boolean type */
    TYPE_LISTA,     /* List type */
    TYPE_JADWAL,    /* Table/structure type */
    TYPE_FUNCTION   /* Function type */
} SymbolType;

/* Symbol categories */
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_PARAMETER,
    SYMBOL_FIELD     /* Field within a jadwal */
} SymbolCategory;

/**
 * Parameter structure for function symbols
 */
typedef struct Parameter {
    char *name;
    SymbolType type;
    struct Parameter *next;
} Parameter;

/**
 * Field structure for jadwal (struct) symbols
 */
typedef struct Field {
    char *name;
    SymbolType type;
    struct Field *next;
} Field;

/**
 * Symbol table entry structure
 */
typedef struct SymbolEntry {
    char *name;
    SymbolType type;
    SymbolCategory category;
    int line_defined;
    int scope_level;
    
    /* Value storage */
    union {
        double num_value;
        char *str_value;
        int bool_value;
        
        /* For LISTA type */
        struct {
            SymbolType element_type;
            int size;
        } list_info;
        
        /* For JADWAL type */
        Field *fields;
        
        /* For FUNCTION type */
        struct {
            SymbolType return_type;
            Parameter *parameters;
        } func_info;
    } value;
    
    struct SymbolEntry *next;
} SymbolEntry;

/**
 * Scope structure for nested scopes management
 */
typedef struct Scope {
    SymbolEntry *entries;
    struct Scope *parent;
    int level;
} Scope;

/**
 * Symbol table structure
 */
typedef struct {
    Scope *current_scope;
} SymbolTable;

/* AST node types */
typedef enum {
    /* Declarations */
    NODE_PROGRAM,
    NODE_VAR_DECLARATION,
    NODE_FUNC_DECLARATION,
    NODE_LIST_DECLARATION,
    NODE_JADWAL_DECLARATION,
    
    /* Statements */
    NODE_ASSIGN,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_RETURN,
    NODE_BLOCK,
    NODE_FUNC_CALL,
    
    /* Expressions */
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_IDENTIFIER,
    NODE_NUMBER,
    NODE_STRING,
    NODE_ARRAY_ACCESS,
    NODE_FIELD_ACCESS
} ASTNodeType;

/**
 * Binary operation types
 */
typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_INT_DIV,
    OP_AND,
    OP_OR,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE
} BinaryOpType;

/**
 * Unary operation types
 */
typedef enum {
    OP_NEG,
    OP_NOT,
    OP_FACT
} UnaryOpType;

/* Forward declaration for AST node */
typedef struct ASTNode ASTNode;

/**
 * AST node structure
 */
struct ASTNode {
    ASTNodeType type;
    
    union {
        /* For number literals */
        double number_value;
        
        /* For string literals */
        char *string_value;
        
        /* For identifiers */
        struct {
            char *name;
            SymbolEntry *symbol;
        } identifier;
        
        /* For variable declarations */
        struct {
            char *name;
            SymbolType var_type;
            ASTNode *init_expr;
            SymbolEntry *symbol;
        } var_decl;
        
        /* For list declarations */
        struct {
            char *name;
            SymbolType element_type;
            ASTNode **elements;
            int num_elements;
            SymbolEntry *symbol;
        } list_decl;
        
        /* For jadwal declarations */
        struct {
            char *name;
            Field *fields;
            SymbolEntry *symbol;
        } jadwal_decl;
        
        /* For function declarations */
        struct {
            char *name;
            SymbolType return_type;
            Parameter *parameters;
            ASTNode *body;
            SymbolEntry *symbol;
        } func_decl;
        
        /* For binary operations */
        struct {
            BinaryOpType op;
            ASTNode *left;
            ASTNode *right;
        } binary_op;
        
        /* For unary operations */
        struct {
            UnaryOpType op;
            ASTNode *operand;
        } unary_op;
        
        /* For assignments */
        struct {
            ASTNode *target;
            ASTNode *value;
        } assign;
        
        /* For array access */
        struct {
            ASTNode *array;
            ASTNode *index;
        } array_access;
        
        /* For field access */
        struct {
            ASTNode *record;
            char *field_name;
        } field_access;
        
        /* For if statements */
        struct {
            ASTNode *condition;
            ASTNode *if_body;
            ASTNode *else_body; /* Can be NULL if no else clause */
        } if_stmt;
        
        /* For loop statements */
        struct {
            ASTNode *init;     /* Used in for loops */
            ASTNode *condition;
            ASTNode *update;   /* Used in for loops */
            ASTNode *body;
        } loop;
        
        /* For blocks of statements */
        struct {
            ASTNode **statements;
            int statement_count;
        } block;
        
        /* For function calls */
        struct {
            char *func_name;
            ASTNode **args;
            int arg_count;
            SymbolEntry *symbol;
        } func_call;
        
        /* For return statements */
        struct {
            ASTNode *expr;
        } return_stmt;
        
        /* For program */
        struct {
            ASTNode **declarations;
            int declaration_count;
            ASTNode *main_function;
        } program;
    } data;
    
    int line_number;
};

/* Function declarations for symbol table management */
SymbolTable* create_symbol_table();
void free_symbol_table(SymbolTable *table);
void enter_scope(SymbolTable *table);
void exit_scope(SymbolTable *table);
SymbolEntry* add_symbol(SymbolTable *table, char *name, SymbolType type, SymbolCategory category, int line);
SymbolEntry* lookup_symbol(SymbolTable *table, char *name);
SymbolEntry* lookup_symbol_current_scope(SymbolTable *table, char *name);

/* Function declarations for AST node creation and management */
ASTNode* create_program_node(ASTNode **declarations, int declaration_count, ASTNode *main_function, int line);
ASTNode* create_var_declaration_node(char *name, SymbolType type, ASTNode *init_expr, int line);
ASTNode* create_list_declaration_node(char *name, SymbolType element_type, ASTNode **elements, int num_elements, int line);
ASTNode* create_jadwal_declaration_node(char *name, Field *fields, int line);
ASTNode* create_function_declaration_node(char *name, SymbolType return_type, Parameter *parameters, ASTNode *body, int line);
ASTNode* create_binary_op_node(BinaryOpType op, ASTNode *left, ASTNode *right, int line);
ASTNode* create_unary_op_node(UnaryOpType op, ASTNode *operand, int line);
ASTNode* create_number_node(double value, int line);
ASTNode* create_string_node(char *value, int line);
ASTNode* create_identifier_node(char *name, int line);
ASTNode* create_assignment_node(ASTNode *target, ASTNode *value, int line);
ASTNode* create_array_access_node(ASTNode *array, ASTNode *index, int line);
ASTNode* create_field_access_node(ASTNode *record, char *field_name, int line);
ASTNode* create_if_node(ASTNode *condition, ASTNode *if_body, ASTNode *else_body, int line);
ASTNode* create_while_node(ASTNode *condition, ASTNode *body, int line);
ASTNode* create_for_node(ASTNode *init, ASTNode *condition, ASTNode *update, ASTNode *body, int line);
ASTNode* create_block_node(ASTNode **statements, int statement_count, int line);
ASTNode* create_function_call_node(char *func_name, ASTNode **args, int arg_count, int line);
ASTNode* create_return_node(ASTNode *expr, int line);

/* Function to free an AST node and all its children */
void free_ast_node(ASTNode *node);

/* Utility functions */
Parameter* create_parameter(char *name, SymbolType type);
void free_parameters(Parameter *param);
Field* create_field(char *name, SymbolType type);
void free_fields(Field *field);
char* symbol_type_to_string(SymbolType type);

/* Function for semantic analysis */
void analyze_ast(ASTNode *node, SymbolTable *table);

/* Debug functions */
void print_symbol_table(SymbolTable *table);
void print_ast(ASTNode *node, int indent);

#endif /* AST_H */ 