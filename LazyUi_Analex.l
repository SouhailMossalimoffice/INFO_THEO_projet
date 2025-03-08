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

wakila|hitach|fi_halat|ktaba|kml_htal|kteb|ila|ilamakanch|dir|rakm|dakhal  { printf("mot-clé: %s\n", yytext); }
w|wla|machi|mn|l|b|mahed|htal|wlala|tawzie|Jadwal|rjae|jarrab|l_kol|fi { printf("mot-clé: %s\n", yytext); }
wilakan|lista|taarif|zid|msah  { printf("mot-clé: %s\n", yytext); }


[ \t\n]+   ;  /* Ignorer les espaces et nouvelles lignes */

[a-zA-Z_][a-zA-Z0-9_]*   { printf("Identificateur: %s\n", yytext); }
[0-9]*   { printf("nombre: %s\n", yytext); }
\"[^\"]*\"   { printf("STRING: %s\n", yytext); }
"%%".*   { printf("COMMENTAIRE: %s\n", yytext); }
"/%".*"%/"   { printf("COMMENTAIRE MULTI_LIGNE: %s\n", yytext); }





":"    { printf("Separateur: %s\n", yytext); }
"{"    { printf("Separateur: %s\n", yytext); }
"}"    { printf("Separateur: %s\n", yytext); }
"("    { printf("Separateur: %s\n", yytext); }
")"    { printf("Separateur: %s\n", yytext); }
","    { printf("Separateur: %s\n", yytext); }
";"    { printf("Separateur: %s\n", yytext); }


.   { printf("SYMBOLE NON RECONNU: %s\n", yytext); }


%%

int yywrap() { return 1; }

int main() {
    yylex();
    return 0;
}
