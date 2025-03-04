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


[ \t\n]+        ; /* Ignorer les espaces et les retours à la ligne */

%%

int yywrap() { return 1; }

int main() {
    yylex();
    return 0;
}
