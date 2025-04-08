/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_LAZYUI_PARSER_TAB_H_INCLUDED
# define YY_YY_LAZYUI_PARSER_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_IDENTIFIANT = 258,
     TK_RA9M = 259,
     TK_KTABA = 260,
     TK_WA9ILA = 261,
     TK_LISTA = 262,
     TK_JADWAL = 263,
     TK_SEMICOLON = 264,
     TK_LBRACKET = 265,
     TK_RBRACKET = 266,
     TK_LBRACE = 267,
     TK_RBRACE = 268,
     TK_COLON = 269,
     TK_AFFECTATION = 270,
     TK_COMMA = 271,
     TK_DOT = 272,
     TK_LPAREN = 273,
     TK_RPAREN = 274,
     TK_FACT = 275,
     TK_NON = 276,
     TK_ET = 277,
     TK_OU = 278,
     TK_EQUAL = 279,
     TK_DIFF = 280,
     TK_SUP = 281,
     TK_INF = 282,
     TK_SUP_EQ = 283,
     TK_INF_EQ = 284,
     TK_INT_DIV = 285,
     TK_NUMBER = 286,
     TK_STRING = 287,
     TK_ILA = 288,
     TK_WILAKAN = 289,
     TK_ILAMAKANCH = 290,
     TK_MN = 291,
     TK_MA7ED = 292,
     TK_TAWZI3 = 293,
     TK_KTEB = 294,
     TK_DAKHAL = 295,
     TK_TAARIF = 296,
     TK_RJE3 = 297,
     TK_MAIN = 298,
     TK_W = 299,
     TK_WLA = 300,
     TK_MACHI = 301,
     TK_L = 302,
     TK_B = 303,
     TK_ADD = 304,
     TK_SUB = 305,
     TK_MUL = 306,
     TK_DIV = 307,
     TK_HITACH = 308,
     TK_FI_HALAT = 309,
     TK_KML_HTAL = 310,
     TK_DIR = 311,
     TK_FI = 312,
     TK_JARRAB = 313,
     TK_L_KOL = 314,
     TK_ZID = 315,
     TK_MSAH = 316,
     TK_HTAL = 317,
     TK_WLALA = 318
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 25 "LazyUi_Parser.y"

    double number;
    char* string;


/* Line 2058 of yacc.c  */
#line 126 "LazyUi_Parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_LAZYUI_PARSER_TAB_H_INCLUDED  */
