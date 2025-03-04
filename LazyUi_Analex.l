%{
#include <stdio.h>
%}

%%
"w"     { printf("TOKEN_ET \n"); }
"wla"   { printf("TOKEN_OU \n"); }
"machi" { printf("TOKEN_NON \n"); }

" + "     { printf("TOKEN_ADD \n"); }
"-"     { printf("TOKEN_SUB \n"); }
"*"     { printf("TOKEN_MUL \n"); }
"/"     { printf("TOKEN_DIV \n"); }
"!"     { printf("TOKEN_FACT \n"); }
"div"   { printf("TOKEN_INT_DIV \n"); }

">"     { printf("TOKEN_SUP \n"); }
">="    { printf("TOKEN_SUP_EQ \n"); }
"<"     { printf("TOKEN_INF \n"); }
"<="    { printf("TOKEN_INF_EQ \n"); }
"<>"    { printf("TOKEN_DIFF \n"); }
"=="    { printf("TOKEN_EGAL \n"); }

":="    { printf("TOKEN_AFFECTATION\n"); }

wa9ila|hitach|fi_halat|ktaba|kml_htal|kteb|ila|ilamakanch|dir|ra9m|dakhal|
w|wla|machi|mn|l|b|mahed|htal|wlala|tawzi3|Jadwal|rja3|jarrab|l_kol|fi|
wilakan|lista  { printf("mot-clé: %s\n", yytext); }

[ \t\n]+   ;  /* Ignorer les espaces et nouvelles lignes */

[a-zA-Z_][a-zA-Z0-9_]*   { printf("Identificateur: %s\n", yytext); }

":"    { printf("Separateur: %s\n", yytext); }
"{"    { printf("Separateur: %s\n", yytext); }
"}"    { printf("Separateur: %s\n", yytext); }
"("    { printf("Separateur: %s\n", yytext); }
")"    { printf("Separateur: %s\n", yytext); }
","    { printf("Separateur: %s\n", yytext); }
";"    { printf("Separateur: %s\n", yytext); }

[ \t\n]+   ;  /* Ignorer les espaces et sauts de ligne */

.   { printf("SYMBOLE NON RECONNU: %s\n", yytext); }

[ \t\n]+        ; /* Ignorer les espaces et les retours à la ligne */

%%

int yywrap() { return 1; }

int main() {
    yylex();
    return 0;
}
