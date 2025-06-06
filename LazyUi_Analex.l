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
%option yylineno

%x STRING
%x COMMENT_LINE
%x COMMENT_BLOCK

%%

"taarif"        { debug_print("Found TK_TAARIF"); return TK_TAARIF; }
"ra9m"          { debug_print("Found TK_RA9M"); return TK_RA9M; }
"raje3"         { debug_print("Found TK_RJE3"); return TK_RJE3; }
"kteb"          { debug_print("Found TK_KTEB"); return TK_KTEB; }
"ila"           { debug_print("Found TK_ILA"); return TK_ILA; }
"dir"           { debug_print("Found TK_DIR"); return TK_DIR; }
"ilamakanch"    { debug_print("Found TK_ILAMAKANCH"); return TK_ILAMAKANCH; }
"wilakan"       { debug_print("Found TK_WILAKAN"); return TK_WILAKAN; }
"ktaba"         { debug_print("Found TK_KTABA"); return TK_KTABA; }
"wa9ila"        { debug_print("Found TK_WA9ILA"); return TK_WA9ILA; }
"lista"         { debug_print("Found TK_LISTA"); return TK_LISTA; }
"wla"           { debug_print("Found TK_WLA"); return TK_WLA; }

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

">="            { debug_print("Found TK_SUP_EQ"); return TK_SUP_EQ; }
"<="            { debug_print("Found TK_INF_EQ"); return TK_INF_EQ; }
">"             { debug_print("Found TK_SUP"); return TK_SUP; }
"<"             { debug_print("Found TK_INF"); return TK_INF; }
"=="            { debug_print("Found TK_EQUAL"); return TK_EQUAL; }
"!="            { debug_print("Found TK_DIFF"); return TK_DIFF; }

"true"          { debug_print("Found boolean true"); yylval.number = 1; return TK_NUMBER; }
"false"         { debug_print("Found boolean false"); yylval.number = 0; return TK_NUMBER; }

\"              { string_buf_ptr = string_buf; BEGIN(STRING); }
<STRING>[^\"\n\\]*  { 
    char *yptr = yytext;
    while (*yptr) {
        *string_buf_ptr++ = *yptr++;
    }
}
<STRING>\\n    { *string_buf_ptr++ = '\n'; }
<STRING>\\t    { *string_buf_ptr++ = '\t'; }
<STRING>\\\"   { *string_buf_ptr++ = '\"'; }
<STRING>\\\\   { *string_buf_ptr++ = '\\'; }
<STRING>\"     { 
    *string_buf_ptr = '\0';
    BEGIN(INITIAL);
    yylval.string = strdup(string_buf);
    debug_print("Found string literal");
    return TK_STRING;
}
<STRING>\n     { 
    lexer_error("Unterminated string literal");
    BEGIN(INITIAL);
}

.               { printf("UNRECOGNIZED: %s (ASCII: %d)\n", yytext, yytext[0]); }

%%
