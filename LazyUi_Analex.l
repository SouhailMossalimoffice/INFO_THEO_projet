%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LazyUi_Parser.tab.h"

extern int yylineno;
%}

%option noyywrap
%option case-insensitive

%%

"w"             { return TK_ET; }
"wla"           { return TK_OU; }
"machi"         { return TK_NON; }
"+"             { return TK_ADD; }
"-"             { return TK_SUB; }
"*"             { return TK_MUL; }
"/"             { return TK_DIV; }
"!"             { return TK_FACT; }
"div"           { return TK_INT_DIV; }
">"             { return TK_SUP; }
">="            { return TK_SUP_EQ; }
"<"             { return TK_INF; }
"<="            { return TK_INF_EQ; }
"<>"            { return TK_DIFF; }
"=="            { return TK_EQUAL; }
":="            { return TK_AFFECTATION; }
"wa9ila"        { return TK_WA9ILA; }
"hitach"        { return TK_HITACH; }
"fi_halat"      { return TK_FI_HALAT; }
"ktaba"         { return TK_KTABA; }
"kml_htal"      { return TK_KML_HTAL; }
"kteb"          { return TK_KTEB; }
"ila"           { return TK_ILA; }
"ilamakanch"    { return TK_ILAMAKANCH; }
"dir"           { return TK_DIR; }
"ra9m"          { return TK_RA9M; }
"dakhal"        { return TK_DAKHAL; }
"mn"            { return TK_MN; }
"l"             { return TK_L; }
"b"             { return TK_B; }
"ma7ed"         { return TK_MA7ED; }
"htal"          { return TK_HTAL; }
"wlala"         { return TK_WLALA; }
"tawzi3"        { return TK_TAWZI3; }
"Jadwal"        { return TK_JADWAL; }
"rja3"          { return TK_RJE3; }
"jarrab"        { return TK_JARRAB; }
"l_kol"         { return TK_L_KOL; }
"fi"            { return TK_FI; }
"wilakan"       { return TK_WILAKAN; }
"lista"         { return TK_LISTA; }
"taarif"        { return TK_TAARIF; }
"zid"           { return TK_ZID; }
"msah"          { return TK_MSAH; }
"main"          { return TK_MAIN; }

[ \t\n]+       ;  /* Ignorer les espaces et nouvelles lignes */

[a-zA-Z_][a-zA-Z0-9_]*   { yylval.string = strdup(yytext); return TK_IDENTIFIANT; }
[0-9]+(\.[0-9]+)?   { yylval.number = atof(yytext); return TK_NUMBER; }
\"[^\"]*\"   { yylval.string = strdup(yytext); return TK_STRING; }
"--".*       ;  /* Commentaire de fin de ligne */
"/--".*"--/" ;  /* Commentaire multi-lignes */

":"    { return TK_COLON; }
"{"    { return TK_LBRACE; }
"}"    { return TK_RBRACE; }
"("    { return TK_LPAREN; }
")"    { return TK_RPAREN; }
","    { return TK_COMMA; }
";"    { return TK_SEMICOLON; }
"["    { return TK_LBRACKET; }
"]"    { return TK_RBRACKET; }
"."    { return TK_DOT; }

.       { printf("SYMBOLE NON RECONNU: %s\n", yytext); }

%%
