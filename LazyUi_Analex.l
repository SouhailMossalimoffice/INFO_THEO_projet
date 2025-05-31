%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LazyUi_Parser.tab.h"

extern int yylineno;
// extern YYSTYPE yylval; // Désactivé pour test lexical pur

#define MAX_STRING_LEN 1024
char string_buf[MAX_STRING_LEN];
char *string_buf_ptr;

static void debug_print(const char* msg) {
    fprintf(stderr, "DEBUG: %s\n", msg);
}

static void lexer_error(const char* msg) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, msg);
}
%}

%option noyywrap

%x STRING
%x COMMENT_LINE
%x COMMENT_BLOCK

%%

"taarif"        { debug_print("Found TK_TAARIF"); return TK_TAARIF; }
"ra9m"          { debug_print("Found TK_RA9M"); return TK_RA9M; }
"rje3"          { debug_print("Found TK_RJE3"); return TK_RJE3; }
"kteb"          { debug_print("Found TK_KTEB"); return TK_KTEB; }

"+"             { debug_print("Found TK_ADD"); return TK_ADD; }
"-"             { debug_print("Found TK_SUB"); return TK_SUB; }
"*"             { debug_print("Found TK_MUL"); return TK_MUL; }
"/"             { debug_print("Found TK_DIV"); return TK_DIV; }

":="            { debug_print("Found TK_AFFECTATION"); return TK_AFFECTATION; }
"="             { debug_print("Found TK_AFFECTATION"); return TK_AFFECTATION; }

[ \t\r\n]+      { /* Ignore whitespace */ }

"//".*          { /* Ignore single-line comments */ }

[a-zA-Z_][a-zA-Z0-9_]*   { 
    debug_print("Found identifier");
    yylval.string = strdup(yytext);
    return TK_IDENTIFIANT; 
}

[0-9]+(\.[0-9]+)?   { 
    debug_print("Found number");
    yylval.number = atof(yytext);
    return TK_NUMBER; 
}

":"             { debug_print("Found TK_COLON"); return TK_COLON; }
"{"             { debug_print("Found TK_LBRACE"); return TK_LBRACE; }
"}"             { debug_print("Found TK_RBRACE"); return TK_RBRACE; }
"("             { debug_print("Found TK_LPAREN"); return TK_LPAREN; }
")"             { debug_print("Found TK_RPAREN"); return TK_RPAREN; }
","             { debug_print("Found TK_COMMA"); return TK_COMMA; }
";"             { debug_print("Found TK_SEMICOLON"); return TK_SEMICOLON; }

.               { printf("UNRECOGNIZED: %s (ASCII: %d)\n", yytext, yytext[0]); }

%%
