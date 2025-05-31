#include <stdio.h>
#include <stdlib.h>
#include "LazyUi_Parser.tab.h"

extern int yylex();
extern FILE* yyin;
extern int yylineno;
extern char* yytext;

const char* token_to_string(int token) {
    switch(token) {
        case TK_ET: return "TK_ET";
        case TK_OU: return "TK_OU";
        case TK_NON: return "TK_NON";
        case TK_ADD: return "TK_ADD";
        case TK_SUB: return "TK_SUB";
        case TK_MUL: return "TK_MUL";
        case TK_DIV: return "TK_DIV";
        case TK_FACT: return "TK_FACT";
        case TK_INT_DIV: return "TK_INT_DIV";
        case TK_SUP: return "TK_SUP";
        case TK_SUP_EQ: return "TK_SUP_EQ";
        case TK_INF: return "TK_INF";
        case TK_INF_EQ: return "TK_INF_EQ";
        case TK_DIFF: return "TK_DIFF";
        case TK_EQUAL: return "TK_EQUAL";
        case TK_AFFECTATION: return "TK_AFFECTATION";
        case TK_WA9ILA: return "TK_WA9ILA";
        case TK_HITACH: return "TK_HITACH";
        case TK_FI_HALAT: return "TK_FI_HALAT";
        case TK_KTABA: return "TK_KTABA";
        case TK_KML_HTAL: return "TK_KML_HTAL";
        case TK_KTEB: return "TK_KTEB";
        case TK_ILA: return "TK_ILA";
        case TK_ILAMAKANCH: return "TK_ILAMAKANCH";
        case TK_DIR: return "TK_DIR";
        case TK_RA9M: return "TK_RA9M";
        case TK_DAKHAL: return "TK_DAKHAL";
        case TK_MN: return "TK_MN";
        case TK_L: return "TK_L";
        case TK_B: return "TK_B";
        case TK_MA7ED: return "TK_MA7ED";
        case TK_HTAL: return "TK_HTAL";
        case TK_WLALA: return "TK_WLALA";
        case TK_TAWZI3: return "TK_TAWZI3";
        case TK_JADWAL: return "TK_JADWAL";
        case TK_RJE3: return "TK_RJE3";
        case TK_JARRAB: return "TK_JARRAB";
        case TK_L_KOL: return "TK_L_KOL";
        case TK_FI: return "TK_FI";
        case TK_WILAKAN: return "TK_WILAKAN";
        case TK_LISTA: return "TK_LISTA";
        case TK_TAARIF: return "TK_TAARIF";
        case TK_ZID: return "TK_ZID";
        case TK_MSAH: return "TK_MSAH";
        case TK_MAIN: return "TK_MAIN";
        case TK_IDENTIFIANT: return "TK_IDENTIFIANT";
        case TK_NUMBER: return "TK_NUMBER";
        case TK_STRING: return "TK_STRING";
        case TK_COLON: return "TK_COLON";
        case TK_LBRACE: return "TK_LBRACE";
        case TK_RBRACE: return "TK_RBRACE";
        case TK_LPAREN: return "TK_LPAREN";
        case TK_RPAREN: return "TK_RPAREN";
        case TK_COMMA: return "TK_COMMA";
        case TK_SEMICOLON: return "TK_SEMICOLON";
        case TK_LBRACKET: return "TK_LBRACKET";
        case TK_RBRACKET: return "TK_RBRACKET";
        case TK_DOT: return "TK_DOT";
        default: return "UNKNOWN_TOKEN";
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    yyin = file;
    int token;
    
    printf("Token Analysis:\n");
    printf("---------------\n");
    
    while ((token = yylex()) != 0) {
        printf("Line %d: Token %s", yylineno, token_to_string(token));
        
        if (token == TK_IDENTIFIANT || token == TK_STRING) {
            printf(" (Value: %s)", yytext);
        } else if (token == TK_NUMBER) {
            printf(" (Value: %s)", yytext);
        }
        
        printf("\n");
    }

    fclose(file);
    return 0;
} 