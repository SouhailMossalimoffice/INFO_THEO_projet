%{
#include <stdio.h>
#include <stdlib.h>
%}

%%


%%  

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
