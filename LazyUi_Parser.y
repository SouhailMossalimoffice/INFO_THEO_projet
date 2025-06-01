%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"

/* Forward declarations for Bison types */
typedef struct ASTNode ASTNode;
typedef struct Parameter Parameter;
typedef struct Field Field;

/* Structure pour le for header */
struct ForHeaderData {
    ASTNode* init;
    ASTNode* cond;
    ASTNode* update;
};

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int yylineno;
void yyerror(const char* s);

SymbolTable *symbol_table;
ASTNode *ast_root = NULL;

// Fonction de débogage
void debug_print(const char* msg) {
    fprintf(stderr, "DEBUG: %s\n", msg);
}

void parser_error(const char* msg) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, msg);
}

// Helper to append parameter at the end
Parameter* append_parameter(Parameter* list, Parameter* param) {
    if (!list) return param;
    Parameter* curr = list;
    while (curr->next) curr = curr->next;
    curr->next = param;
    return list;
}

// Helper to flatten argument sequence into array (in correct order)
void flatten_arguments(ASTNode* seq, ASTNode*** out_args, int* out_count) {
    int capacity = 8, count = 0;
    ASTNode** args = malloc(sizeof(ASTNode*) * capacity);
    // Collect in order for left-recursive sequence
    while (seq && seq->type == NODE_SEQUENCE) {
        if (count >= capacity) {
            capacity *= 2;
            args = realloc(args, sizeof(ASTNode*) * capacity);
        }
        args[count++] = seq->data.sequence.first;
        seq = seq->data.sequence.second;
    }
    if (seq) {
        if (count >= capacity) {
            capacity *= 2;
            args = realloc(args, sizeof(ASTNode*) * capacity);
        }
        args[count++] = seq;
    }
    // No reversal needed for left-recursive rule
    *out_args = args;
    *out_count = count;
}

// Helper to extract main function from declarations
void extract_main_function(ASTNode* decls, ASTNode** out_decls, ASTNode** out_main) {
    if (!decls) {
        *out_decls = NULL;
        *out_main = NULL;
        return;
    }
    if (decls->type == NODE_FUNCTION_DECLARATION && strcmp(decls->data.func_decl.name, "main") == 0) {
        *out_decls = NULL;
        *out_main = decls;
        return;
    }
    if (decls->type == NODE_SEQUENCE) {
        ASTNode *first = decls->data.sequence.first;
        ASTNode *second = decls->data.sequence.second;
        ASTNode *main_func = NULL;
        ASTNode *rest = NULL;
        extract_main_function(first, &rest, &main_func);
        if (main_func) {
            *out_main = main_func;
            *out_decls = second;
        } else {
            extract_main_function(second, &rest, &main_func);
            *out_main = main_func;
            *out_decls = first;
        }
        return;
    }
    *out_decls = decls;
    *out_main = NULL;
}
%}

%union {
    double number;
    char* string;
    struct ASTNode* ast_node;
    struct Parameter* param_list;
}

/* Tokens from lexical analyzer */
%token <string> TK_IDENTIFIANT TK_STRING
%token <number> TK_NUMBER
%token TK_RA9M TK_KTABA TK_WA9ILA TK_LISTA TK_JADWAL
%token TK_SEMICOLON TK_LBRACKET TK_RBRACKET TK_LBRACE TK_RBRACE TK_COLON
%token TK_AFFECTATION TK_COMMA TK_DOT TK_LPAREN TK_RPAREN TK_FACT
%token TK_NON TK_ET TK_OU TK_EQUAL TK_DIFF TK_SUP TK_INF
%token TK_SUP_EQ TK_INF_EQ TK_INT_DIV TK_ILA
%token TK_WILAKAN TK_ILAMAKANCH TK_MN TK_MA7ED TK_TAWZI3 TK_KTEB TK_DAKHAL
%token TK_TAARIF TK_RJE3 TK_MAIN TK_W TK_WLA TK_MACHI TK_L TK_B
%token TK_ADD TK_SUB TK_MUL TK_DIV TK_HITACH TK_FI_HALAT TK_KML_HTAL
%token TK_DIR TK_FI TK_JARRAB TK_L_KOL TK_ZID TK_MSAH TK_HTAL TK_WLALA

/* Operator precedence */
%left TK_OU
%left TK_ET
%right TK_NON
%left TK_EQUAL TK_DIFF TK_SUP TK_INF TK_SUP_EQ TK_INF_EQ
%left TK_ADD TK_SUB
%left TK_MUL TK_DIV TK_INT_DIV
%right TK_FACT

/* Define types for non-terminals */
%type <ast_node> programme declarations_fonctions declaration_fonction expression expression_arithmetique terme facteur instructions instruction instruction_retour declaration_variable affectation appel_fonction_expr arguments bloc instruction_print instruction_condition instruction_while
%type <param_list> parametres parametre

%%

programme
    : declarations_fonctions
    {
        debug_print("Parsing programme");
        ASTNode *main_func = NULL, *decls = NULL;
        extract_main_function($1, &decls, &main_func);
        ast_root = create_program_node(decls, main_func, yylineno);
        generate_code_entry(ast_root);
    }
    ;

declarations_fonctions
    : declaration_fonction
    {
        $$ = $1;
    }
    | declarations_fonctions declaration_fonction
    {
        $$ = create_sequence_node($1, $2, yylineno);
    }
    ;

declaration_fonction
    : TK_TAARIF TK_RA9M TK_IDENTIFIANT TK_LPAREN parametres TK_RPAREN bloc
    {
        debug_print("Function declaration with parameters");
        $$ = create_function_declaration_node($3, TYPE_RA9M, $5, $7, yylineno);
    }
    | TK_TAARIF TK_RA9M TK_IDENTIFIANT TK_LPAREN TK_RPAREN bloc
    {
        debug_print("Function declaration without parameters");
        $$ = create_function_declaration_node($3, TYPE_RA9M, NULL, $6, yylineno);
    }
    ;

parametres
    : parametre
    {
        $$ = $1;
    }
    | parametres TK_COMMA parametre
    {
        $$ = append_parameter($1, $3);
    }
    ;

parametre
    : TK_RA9M TK_IDENTIFIANT
    {
        debug_print("Found parameter");
        $$ = create_parameter($2, TYPE_RA9M);
    }
    ;

instructions
    : /* empty */
    {
        $$ = NULL;
    }
    | instruction
    {
        $$ = $1;
    }
    | instructions instruction
    {
        $$ = create_sequence_node($1, $2, yylineno);
    }
    ;

instruction
    : instruction_retour { debug_print("Reducing: instruction_retour"); $$ = $1; }
    | declaration_variable { debug_print("Reducing: declaration_variable"); $$ = $1; }
    | affectation { debug_print("Reducing: affectation"); $$ = $1; }
    | appel_fonction_expr TK_SEMICOLON { debug_print("Reducing: function call"); $$ = $1; }
    | instruction_print { debug_print("Reducing: print statement"); $$ = $1; }
    | instruction_condition { debug_print("Reducing: if/else statement"); $$ = $1; }
    | instruction_while { debug_print("Reducing: while statement"); $$ = $1; }
    ;

instruction_print
    : TK_KTEB TK_LPAREN expression TK_RPAREN TK_SEMICOLON
    {
        debug_print("Found print statement");
        $$ = create_print_node($3, yylineno);
    }
    ;

declaration_variable
    : TK_RA9M TK_IDENTIFIANT TK_AFFECTATION expression TK_SEMICOLON
    {
        debug_print("Found variable declaration with initialization");
        $$ = create_var_declaration_node($2, TYPE_RA9M, $4, yylineno);
    }
    ;

affectation
    : TK_IDENTIFIANT TK_AFFECTATION expression TK_SEMICOLON
    {
        debug_print("Found assignment");
        $$ = create_assignment_node(create_identifier_node($1, yylineno), $3, yylineno);
    }
    ;

instruction_retour
    : TK_RJE3 expression TK_SEMICOLON
    {
        debug_print("Reducing: instruction_retour (rje3)");
        $$ = create_return_node($2, yylineno);
    }
    ;

expression
    : expression_arithmetique { $$ = $1; }
    | TK_STRING { $$ = create_string_node($1, yylineno); }
    | expression TK_ADD expression
    {
        debug_print("Found string concatenation or addition");
        $$ = create_binary_op_node(OP_ADD, $1, $3, yylineno);
    }
    | expression TK_SUP expression
    {
        debug_print("Found greater than comparison");
        $$ = create_binary_op_node(OP_GT, $1, $3, yylineno);
    }
    | expression TK_INF expression
    {
        debug_print("Found less than comparison");
        $$ = create_binary_op_node(OP_LT, $1, $3, yylineno);
    }
    | expression TK_EQUAL expression
    {
        debug_print("Found equality comparison");
        $$ = create_binary_op_node(OP_EQ, $1, $3, yylineno);
    }
    | expression TK_DIFF expression
    {
        debug_print("Found inequality comparison");
        $$ = create_binary_op_node(OP_NEQ, $1, $3, yylineno);
    }
    ;

expression_arithmetique
    : terme { $$ = $1; }
    | expression_arithmetique TK_ADD terme
    {
        debug_print("Found addition");
        $$ = create_binary_op_node(OP_ADD, $1, $3, yylineno);
    }
    | expression_arithmetique TK_SUB terme
    {
        debug_print("Found subtraction");
        $$ = create_binary_op_node(OP_SUB, $1, $3, yylineno);
    }
    ;

terme
    : facteur { $$ = $1; }
    | terme TK_MUL facteur
    {
        debug_print("Found multiplication");
        $$ = create_binary_op_node(OP_MUL, $1, $3, yylineno);
    }
    | terme TK_DIV facteur
    {
        debug_print("Found division");
        $$ = create_binary_op_node(OP_DIV, $1, $3, yylineno);
    }
    ;

facteur
    : TK_NUMBER
    {
        debug_print("Found number");
        $$ = create_number_node($1, yylineno);
    }
    | TK_IDENTIFIANT
    {
        debug_print("Found identifier");
        $$ = create_identifier_node($1, yylineno);
    }
    | TK_LPAREN expression TK_RPAREN { $$ = $2; }
    | appel_fonction_expr { $$ = $1; }
    ;

appel_fonction_expr
    : TK_IDENTIFIANT TK_LPAREN arguments TK_RPAREN
    {
        debug_print("Found function call with arguments");
        ASTNode** args = NULL;
        int arg_count = 0;
        flatten_arguments($3, &args, &arg_count);
        $$ = create_function_call_node($1, args, arg_count, yylineno);
    }
    | TK_IDENTIFIANT TK_LPAREN TK_RPAREN
    {
        debug_print("Found function call without arguments");
        $$ = create_function_call_node($1, NULL, 0, yylineno);
    }
    ;

arguments
    : expression { $$ = $1; }
    | arguments TK_COMMA expression
    {
        debug_print("Found multiple arguments");
        $$ = create_sequence_node($1, $3, yylineno);
    }
    ;

bloc
    : TK_LBRACE instructions TK_RBRACE
    {
        debug_print("Found block");
        $$ = $2;
    }
    ;

instruction_condition
    : TK_ILA TK_LPAREN expression TK_RPAREN TK_DIR bloc
    {
        debug_print("Found if statement");
        $$ = create_if_node($3, $6, NULL, yylineno);
    }
    | TK_ILA TK_LPAREN expression TK_RPAREN TK_DIR bloc TK_ILAMAKANCH bloc
    {
        debug_print("Found if-else statement");
        $$ = create_if_node($3, $6, $8, yylineno);
    }
    ;

instruction_while
    : TK_WILAKAN TK_LPAREN expression TK_RPAREN TK_DIR bloc
    {
        debug_print("Found while statement");
        $$ = create_while_node($3, $6, yylineno);
    }
    ;

%%

void yyerror(const char* s) {
    parser_error(s);
}

int main(int argc, char** argv) {
    debug_print("Starting parser");
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    debug_print("Creating symbol table");
    symbol_table = create_symbol_table();
    
    debug_print("Starting parsing");
    int result = yyparse();
    debug_print("Parsing completed");
    
    if (result == 0 && ast_root) {
        debug_print("Analyzing AST");
        analyze_ast(ast_root, symbol_table);
        
        debug_print("Printing AST");
        printf("AST Structure:\n");
        print_ast(ast_root, 0);
        
        debug_print("Printing symbol table");
        printf("Symbol Table:\n");
        print_symbol_table(symbol_table);
        
        debug_print("Generating code");
        generate_code(ast_root);
        
        debug_print("Freeing AST");
        free_ast_node(ast_root);
    }
    
    debug_print("Freeing symbol table");
    free_symbol_table(symbol_table);
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return result;
} 