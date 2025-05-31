%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

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
ASTNode *ast_root;

// Fonction de débogage
void debug_print(const char* msg) {
    fprintf(stderr, "DEBUG: %s\n", msg);
}

void parser_error(const char* msg) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, msg);
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
%type <ast_node> programme declarations_fonctions declaration_fonction expression expression_arithmetique terme facteur instructions instruction instruction_retour declaration_variable affectation appel_fonction_expr arguments bloc
%type <param_list> parametres parametre

%%

programme
    : declarations_fonctions
    ;

declarations_fonctions
    : declaration_fonction
    | declarations_fonctions declaration_fonction
    ;

declaration_fonction
    : TK_TAARIF TK_RA9M TK_IDENTIFIANT TK_LPAREN parametres TK_RPAREN bloc
    {
        debug_print("Function declaration");
        $$ = create_function_declaration_node($3, TYPE_RA9M, $5, $7, yylineno);
    }
    | TK_TAARIF TK_RA9M TK_IDENTIFIANT TK_LPAREN TK_RPAREN bloc
    {
        debug_print("Function declaration (no params)");
        $$ = create_function_declaration_node($3, TYPE_RA9M, NULL, $6, yylineno);
    }
    ;

parametres
    : parametre
    | parametres TK_COMMA parametre
    ;

parametre
    : TK_RA9M TK_IDENTIFIANT
    {
        debug_print("Found parameter");
        $$ = create_parameter($2, TYPE_RA9M);
    }
    ;

bloc
    : TK_LBRACE instructions TK_RBRACE
    {
        debug_print("Found block");
        $$ = $2;
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
        $$ = create_function_call_node($1, &$3, 1, yylineno);
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