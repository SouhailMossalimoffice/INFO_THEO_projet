%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

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

%%  

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
