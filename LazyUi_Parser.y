%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int yylineno;
void yyerror(const char* s);

%}

/* Tokens from lexical analyzer */
%token TK_IDENTIFIANT TK_RA9M TK_KTABA TK_WA9ILA TK_LISTA TK_JADWAL
%token TK_SEMICOLON TK_LBRACKET TK_RBRACKET TK_LBRACE TK_RBRACE TK_COLON
%token TK_AFFECTATION TK_COMMA TK_DOT TK_LPAREN TK_RPAREN TK_FACT
%token TK_NON TK_ET TK_OU TK_EQUAL TK_DIFF TK_SUP TK_INF
%token TK_SUP_EQ TK_INF_EQ TK_INT_DIV TK_NUMBER TK_STRING TK_ILA
%token TK_WILAKAN TK_ILAMAKANCH TK_MN TK_MA7ED TK_TAWZI3 TK_KTEB TK_DAKHAL
%token TK_TAARIF TK_RJE3 TK_MAIN TK_W TK_WLA TK_MACHI TK_L TK_B
%token TK_ADD TK_SUB TK_MUL TK_DIV TK_HITACH TK_FI_HALAT TK_KML_HTAL
%token TK_DIR TK_FI TK_JARRAB TK_L_KOL TK_ZID TK_MSAH TK_HTAL TK_WLALA

%union {
    double number;
    char* string;
}

/* Operator precedence */
%left TK_OU
%left TK_ET
%right TK_NON
%left TK_EQUAL TK_DIFF TK_SUP TK_INF TK_SUP_EQ TK_INF_EQ
%left TK_ADD TK_SUB
%left TK_MUL TK_DIV TK_INT_DIV
%right TK_FACT

%%

programme
    : declarations_variables declarations_fonctions programme_principal
    | declarations_fonctions programme_principal
    | programme_principal
    ;

declarations_variables
    : declaration_variable
    | declarations_variables declaration_variable
    ;

declaration_variable
    : type TK_IDENTIFIANT TK_SEMICOLON
    | type TK_IDENTIFIANT TK_AFFECTATION expression TK_SEMICOLON
    | declaration_liste
    | declaration_jadwal
    ;

type
    : TK_RA9M
    | TK_KTABA
    | TK_WA9ILA
    ;

declaration_liste
    : TK_LISTA TK_IDENTIFIANT TK_AFFECTATION TK_LBRACKET liste_valeurs TK_RBRACKET TK_SEMICOLON
    | TK_LISTA TK_IDENTIFIANT TK_AFFECTATION TK_LBRACKET TK_RBRACKET TK_SEMICOLON
    ;

liste_valeurs
    : expression
    | liste_valeurs TK_COMMA expression
    ;

declaration_jadwal
    : TK_JADWAL TK_IDENTIFIANT TK_LBRACE champs_jadwal TK_RBRACE
    ;

champs_jadwal
    : champ_jadwal
    | champs_jadwal champ_jadwal
    ;

champ_jadwal
    : type TK_IDENTIFIANT TK_SEMICOLON
    ;

declarations_fonctions
    : declaration_fonction
    | declarations_fonctions declaration_fonction
    ;

declaration_fonction
    : TK_TAARIF TK_IDENTIFIANT TK_LPAREN parametres TK_RPAREN TK_LBRACE bloc TK_RBRACE
    | TK_TAARIF TK_IDENTIFIANT TK_LPAREN TK_RPAREN TK_LBRACE bloc TK_RBRACE
    ;

parametres
    : parametre
    | parametres TK_COMMA parametre
    ;

parametre
    : type TK_IDENTIFIANT
    ;

bloc
    : instructions
    | /* empty */
    ;

instructions
    : instruction
    | instructions instruction
    ;

instruction
    : affectation
    | appel_fonction_expr TK_SEMICOLON
    | instruction_condition
    | instruction_boucle
    | instruction_retour
    | operation_jadwal
    | instruction_io
    ;

instruction_retour
    : TK_RJE3 expression TK_SEMICOLON
    ;

programme_principal
    : TK_MAIN TK_LBRACE bloc TK_RBRACE
    ;

affectation
    : TK_IDENTIFIANT TK_AFFECTATION expression TK_SEMICOLON
    | TK_IDENTIFIANT acces_element TK_AFFECTATION expression TK_SEMICOLON
    ;

acces_element
    : TK_DOT TK_IDENTIFIANT
    | TK_LBRACKET expression TK_RBRACKET
    ;

expression
    : expression_logique
    ;

expression_logique
    : expression_comparison
    | expression_logique TK_ET expression_comparison
    | expression_logique TK_OU expression_comparison
    | TK_NON expression_logique
    ;


expression_comparison
    : expression_arithmetique
    | expression_comparison TK_EQUAL expression_comparison
    | expression_comparison TK_DIFF expression_comparison
    | expression_comparison TK_SUP expression_comparison
    | expression_comparison TK_INF expression_comparison
    | expression_comparison TK_SUP_EQ expression_comparison
    | expression_comparison TK_INF_EQ expression_comparison
    ;

expression_arithmetique
    : terme
    | expression_arithmetique TK_ADD terme
    | expression_arithmetique TK_SUB terme
    ;

terme
    : facteur
    | terme TK_MUL facteur
    | terme TK_DIV facteur
    | terme TK_INT_DIV facteur
    ;

facteur
    : valeur
    | TK_LPAREN expression TK_RPAREN
    | TK_FACT facteur
    | appel_fonction_expr
    ;

valeur
    : TK_NUMBER
    | TK_STRING
    | TK_IDENTIFIANT /* Add this to make identifiers a valid value */
    | TK_IDENTIFIANT acces_element /* Add this for struct/array access */
    ;


appel_fonction_expr
    : TK_IDENTIFIANT TK_LPAREN arguments TK_RPAREN
    | TK_IDENTIFIANT TK_LPAREN TK_RPAREN
    ;

arguments
    : expression
    | arguments TK_COMMA expression
    ;

instruction_condition
    : TK_ILA TK_LPAREN expression TK_RPAREN TK_LBRACE bloc TK_RBRACE
    | TK_ILA TK_LPAREN expression TK_RPAREN TK_LBRACE bloc TK_RBRACE TK_ILAMAKANCH TK_LBRACE bloc TK_RBRACE
    | TK_ILA TK_LPAREN expression TK_RPAREN TK_LBRACE bloc TK_RBRACE TK_WILAKAN TK_LPAREN expression TK_RPAREN TK_LBRACE bloc TK_RBRACE
    ;

instruction_boucle
    : TK_MA7ED TK_LPAREN expression TK_RPAREN TK_LBRACE bloc TK_RBRACE
    | TK_MN TK_LPAREN expression TK_RPAREN TK_L TK_LPAREN expression TK_RPAREN TK_B TK_LPAREN expression TK_RPAREN TK_LBRACE bloc TK_RBRACE
    ;

operation_jadwal
    : TK_IDENTIFIANT TK_DOT TK_IDENTIFIANT TK_LPAREN arguments TK_RPAREN TK_SEMICOLON
    ;

instruction_io
    : TK_KTEB TK_LPAREN arguments TK_RPAREN TK_SEMICOLON
    | TK_DAKHAL TK_LPAREN TK_IDENTIFIANT TK_RPAREN TK_SEMICOLON
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    yyparse();
    
    if (argc > 1) {
        fclose(yyin);
    }
    return 0;
} 