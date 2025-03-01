%{
#include <stdio.h>
#include "lex.yy.c"
%}

/* Définition des tokens */
DIGIT   [0-9]+
COLOR   [a-zA-Z]+(-[a-zA-Z0-9]+)?
HEXCOLOR  #[0-9a-fA-F]{3,6}
SIZE    (sm|md|lg|xl)
WEIGHT  (bold|light)
OPTION  (center|between)

%%

"text-"{COLOR}       { printf("TEXT_COLOR: %s\n", yytext); }
"bg-"{COLOR}         { printf("BG_COLOR: %s\n", yytext); }
"border-"{COLOR}     { printf("BORDER_COLOR: %s\n", yytext); }

"text-"{HEXCOLOR}    { printf("TEXT_HEX_COLOR: %s\n", yytext); }
"bg-"{HEXCOLOR}      { printf("BG_HEX_COLOR: %s\n", yytext); }
"border-"{HEXCOLOR}  { printf("BORDER_HEX_COLOR: %s\n", yytext); }

"m-"{DIGIT}          { printf("MARGIN: %s\n", yytext); }
"p-"{DIGIT}          { printf("PADDING: %s\n", yytext); }

"text-"{SIZE}        { printf("TEXT_SIZE: %s\n", yytext); }
"font-"{WEIGHT}      { printf("FONT_WEIGHT: %s\n", yytext); }
"italic"            { printf("ITALIC\n"); }
"underline"         { printf("UNDERLINE\n"); }

"flex"              { printf("DISPLAY_FLEX\n"); }
"grid"              { printf("DISPLAY_GRID\n"); }

"justify-"{OPTION}  { printf("JUSTIFY: %s\n", yytext); }
"items-"{OPTION}    { printf("ITEMS_ALIGN: %s\n", yytext); }

"[()",]"            { printf("SYMBOL: %s\n", yytext); }
[a-zA-Z0-9_-]+      { printf("TEXT: %s\n", yytext); }

[ \t\n]             { /* Ignorer les espaces et nouvelles lignes */ }
.                   { printf("UNKNOWN: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
