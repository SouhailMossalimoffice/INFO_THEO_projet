/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_IDENTIFIANT = 258,
     TK_STRING = 259,
     TK_NUMBER = 260,
     TK_RA9M = 261,
     TK_KTABA = 262,
     TK_WA9ILA = 263,
     TK_LISTA = 264,
     TK_JADWAL = 265,
     TK_SEMICOLON = 266,
     TK_LBRACKET = 267,
     TK_RBRACKET = 268,
     TK_LBRACE = 269,
     TK_RBRACE = 270,
     TK_COLON = 271,
     TK_AFFECTATION = 272,
     TK_COMMA = 273,
     TK_DOT = 274,
     TK_LPAREN = 275,
     TK_RPAREN = 276,
     TK_FACT = 277,
     TK_NON = 278,
     TK_ET = 279,
     TK_OU = 280,
     TK_EQUAL = 281,
     TK_DIFF = 282,
     TK_SUP = 283,
     TK_INF = 284,
     TK_SUP_EQ = 285,
     TK_INF_EQ = 286,
     TK_INT_DIV = 287,
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
     TK_WLALA = 318,
     TK_KTIB = 319
   };
#endif
/* Tokens.  */
#define TK_IDENTIFIANT 258
#define TK_STRING 259
#define TK_NUMBER 260
#define TK_RA9M 261
#define TK_KTABA 262
#define TK_WA9ILA 263
#define TK_LISTA 264
#define TK_JADWAL 265
#define TK_SEMICOLON 266
#define TK_LBRACKET 267
#define TK_RBRACKET 268
#define TK_LBRACE 269
#define TK_RBRACE 270
#define TK_COLON 271
#define TK_AFFECTATION 272
#define TK_COMMA 273
#define TK_DOT 274
#define TK_LPAREN 275
#define TK_RPAREN 276
#define TK_FACT 277
#define TK_NON 278
#define TK_ET 279
#define TK_OU 280
#define TK_EQUAL 281
#define TK_DIFF 282
#define TK_SUP 283
#define TK_INF 284
#define TK_SUP_EQ 285
#define TK_INF_EQ 286
#define TK_INT_DIV 287
#define TK_ILA 288
#define TK_WILAKAN 289
#define TK_ILAMAKANCH 290
#define TK_MN 291
#define TK_MA7ED 292
#define TK_TAWZI3 293
#define TK_KTEB 294
#define TK_DAKHAL 295
#define TK_TAARIF 296
#define TK_RJE3 297
#define TK_MAIN 298
#define TK_W 299
#define TK_WLA 300
#define TK_MACHI 301
#define TK_L 302
#define TK_B 303
#define TK_ADD 304
#define TK_SUB 305
#define TK_MUL 306
#define TK_DIV 307
#define TK_HITACH 308
#define TK_FI_HALAT 309
#define TK_KML_HTAL 310
#define TK_DIR 311
#define TK_FI 312
#define TK_JARRAB 313
#define TK_L_KOL 314
#define TK_ZID 315
#define TK_MSAH 316
#define TK_HTAL 317
#define TK_WLALA 318
#define TK_KTIB 319




/* Copy the first part of user declarations.  */
#line 1 "LazyUi_Parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"

/* Forward declarations for Bison types */
typedef struct ASTNode ASTNode;
typedef struct Parameter Parameter;
typedef struct Field Field;

/* Structure pour le for header */
struct ForHeaderData {
    ASTNode* init;
    ASTNode* cond;
    ASTNode* update;
};

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int yylineno;
void yyerror(const char* s);

SymbolTable *symbol_table;
ASTNode *ast_root = NULL;

// Fonction de débogage
void debug_print(const char* msg) {
    fprintf(stderr, "DEBUG: %s\n", msg);
}

void parser_error(const char* msg) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, msg);
}

// Helper to append parameter at the end
Parameter* append_parameter(Parameter* list, Parameter* param) {
    if (!list) return param;
    Parameter* curr = list;
    while (curr->next) curr = curr->next;
    curr->next = param;
    return list;
}

// Helper to flatten argument sequence into array (in correct order)
void flatten_arguments(ASTNode* seq, ASTNode*** out_args, int* out_count) {
    int capacity = 8, count = 0;
    ASTNode** args = malloc(sizeof(ASTNode*) * capacity);
    // Collect in order for left-recursive sequence
    while (seq && seq->type == NODE_SEQUENCE) {
        if (count >= capacity) {
            capacity *= 2;
            args = realloc(args, sizeof(ASTNode*) * capacity);
        }
        args[count++] = seq->data.sequence.first;
        seq = seq->data.sequence.second;
    }
    if (seq) {
        if (count >= capacity) {
            capacity *= 2;
            args = realloc(args, sizeof(ASTNode*) * capacity);
        }
        args[count++] = seq;
    }
    // No reversal needed for left-recursive rule
    *out_args = args;
    *out_count = count;
}

// Helper to extract main function from declarations
void extract_main_function(ASTNode* decls, ASTNode** out_decls, ASTNode** out_main) {
    if (!decls) {
        *out_decls = NULL;
        *out_main = NULL;
        return;
    }
    if (decls->type == NODE_FUNCTION_DECLARATION && strcmp(decls->data.func_decl.name, "main") == 0) {
        *out_decls = NULL;
        *out_main = decls;
        return;
    }
    if (decls->type == NODE_SEQUENCE) {
        ASTNode *first = decls->data.sequence.first;
        ASTNode *second = decls->data.sequence.second;
        ASTNode *main_func = NULL;
        ASTNode *rest = NULL;
        extract_main_function(first, &rest, &main_func);
        if (main_func) {
            *out_main = main_func;
            *out_decls = second;
        } else {
            extract_main_function(second, &rest, &main_func);
            *out_main = main_func;
            *out_decls = first;
        }
        return;
    }
    *out_decls = decls;
    *out_main = NULL;
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 105 "LazyUi_Parser.y"
{
    double number;
    char* string;
    struct ASTNode* ast_node;
    struct Parameter* param_list;
}
/* Line 193 of yacc.c.  */
#line 335 "LazyUi_Parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 348 "LazyUi_Parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   201

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    18,    25,    27,    31,
      34,    35,    37,    40,    42,    44,    46,    48,    50,    52,
      54,    57,    63,    67,    71,    73,    79,    85,    91,    97,
     102,   104,   106,   110,   114,   118,   122,   126,   130,   131,
     133,   137,   139,   143,   147,   149,   153,   157,   159,   161,
     166,   170,   172,   177,   181,   183,   187,   191,   198,   207,
     216
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      66,     0,    -1,    67,    -1,    68,    -1,    67,    68,    -1,
      41,     6,     3,    20,    69,    21,    86,    -1,    41,     6,
       3,    20,    21,    86,    -1,    70,    -1,    69,    18,    70,
      -1,     6,     3,    -1,    -1,    72,    -1,    71,    72,    -1,
      77,    -1,    78,    -1,    73,    -1,    75,    -1,    87,    -1,
      88,    -1,    74,    -1,    84,    11,    -1,    39,    20,    79,
      21,    11,    -1,    42,    79,    11,    -1,    64,    76,    11,
      -1,     4,    -1,     6,     3,    17,    79,    11,    -1,     7,
       3,    17,    79,    11,    -1,     8,     3,    17,    79,    11,
      -1,     9,     3,    17,    79,    11,    -1,     3,    17,    79,
      11,    -1,    81,    -1,     4,    -1,    12,    80,    13,    -1,
      79,    49,    79,    -1,    79,    28,    79,    -1,    79,    29,
      79,    -1,    79,    26,    79,    -1,    79,    27,    79,    -1,
      -1,    79,    -1,    80,    18,    79,    -1,    82,    -1,    81,
      49,    82,    -1,    81,    50,    82,    -1,    83,    -1,    82,
      51,    83,    -1,    82,    52,    83,    -1,     5,    -1,     3,
      -1,     3,    12,    79,    13,    -1,    20,    79,    21,    -1,
      84,    -1,     3,    20,    85,    21,    -1,     3,    20,    21,
      -1,    79,    -1,    85,    18,    79,    -1,    14,    71,    15,
      -1,    33,    20,    79,    21,    56,    86,    -1,    33,    20,
      79,    21,    56,    86,    35,    86,    -1,    33,    20,    79,
      21,    56,    86,    45,    86,    -1,    34,    20,    79,    21,
      56,    86,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   145,   145,   156,   160,   167,   172,   180,   184,   191,
     200,   203,   207,   214,   215,   216,   217,   218,   219,   220,
     221,   225,   233,   241,   245,   249,   251,   253,   255,   259,
     267,   268,   269,   274,   279,   284,   289,   294,   302,   303,
     304,   308,   309,   314,   322,   323,   328,   336,   341,   346,
     351,   352,   356,   364,   372,   373,   381,   389,   394,   399,
     407
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_IDENTIFIANT", "TK_STRING",
  "TK_NUMBER", "TK_RA9M", "TK_KTABA", "TK_WA9ILA", "TK_LISTA", "TK_JADWAL",
  "TK_SEMICOLON", "TK_LBRACKET", "TK_RBRACKET", "TK_LBRACE", "TK_RBRACE",
  "TK_COLON", "TK_AFFECTATION", "TK_COMMA", "TK_DOT", "TK_LPAREN",
  "TK_RPAREN", "TK_FACT", "TK_NON", "TK_ET", "TK_OU", "TK_EQUAL",
  "TK_DIFF", "TK_SUP", "TK_INF", "TK_SUP_EQ", "TK_INF_EQ", "TK_INT_DIV",
  "TK_ILA", "TK_WILAKAN", "TK_ILAMAKANCH", "TK_MN", "TK_MA7ED",
  "TK_TAWZI3", "TK_KTEB", "TK_DAKHAL", "TK_TAARIF", "TK_RJE3", "TK_MAIN",
  "TK_W", "TK_WLA", "TK_MACHI", "TK_L", "TK_B", "TK_ADD", "TK_SUB",
  "TK_MUL", "TK_DIV", "TK_HITACH", "TK_FI_HALAT", "TK_KML_HTAL", "TK_DIR",
  "TK_FI", "TK_JARRAB", "TK_L_KOL", "TK_ZID", "TK_MSAH", "TK_HTAL",
  "TK_WLALA", "TK_KTIB", "$accept", "programme", "declarations_fonctions",
  "declaration_fonction", "parametres", "parametre", "instructions",
  "instruction", "instruction_print", "instruction_retour",
  "instruction_ktib", "string_literal", "declaration_variable",
  "affectation", "expression", "array_elements", "expression_arithmetique",
  "terme", "facteur", "appel_fonction_expr", "arguments", "bloc",
  "instruction_condition", "instruction_while", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    67,    67,    68,    68,    69,    69,    70,
      71,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    74,    75,    76,    77,    77,    77,    77,    78,
      79,    79,    79,    79,    79,    79,    79,    79,    80,    80,
      80,    81,    81,    81,    82,    82,    82,    83,    83,    83,
      83,    83,    84,    84,    85,    85,    86,    87,    87,    87,
      88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     7,     6,     1,     3,     2,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     5,     3,     3,     1,     5,     5,     5,     5,     4,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     1,
       3,     1,     3,     3,     1,     3,     3,     1,     1,     4,
       3,     1,     4,     3,     1,     3,     3,     6,     8,     8,
       6
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     4,     0,     0,
       0,     0,     0,     7,     9,    10,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,    15,    19,    16,    13,    14,     0,    17,    18,     8,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,    31,    47,    38,     0,     0,    30,    41,    44,    51,
      24,     0,    56,    12,    20,     0,    53,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,     0,     0,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,    29,     0,    52,     0,     0,     0,     0,     0,     0,
       0,     0,    32,     0,    50,    36,    37,    34,    35,    33,
      42,    43,    45,    46,    55,    25,    26,    27,    28,     0,
       0,    21,    49,    40,    57,    60,     0,     0,    58,    59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    12,    13,    29,    30,    31,    32,
      33,    61,    34,    35,    55,    78,    56,    57,    58,    59,
      68,    16,    37,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -41
static const yytype_int16 yypact[] =
{
     -17,    56,    79,   -17,   -41,   107,   -41,   -41,    99,    29,
     125,   115,    37,   -41,   -41,    14,   -41,    93,   115,    67,
     128,   129,   130,   132,   110,   116,   117,    78,   135,    31,
     -41,   -41,   -41,   -41,   -41,   -41,   136,   -41,   -41,   -41,
     -41,    78,     7,   140,   141,   143,   144,    78,    78,    78,
      60,   -41,   -41,    78,    78,    40,    11,    34,   -41,   -41,
     -41,   151,   -41,   -41,   -41,    48,   -41,   -23,    73,    78,
      78,    78,    78,   123,   127,   138,    78,   -23,    36,   152,
     -41,    78,    78,    78,    78,    78,    13,    13,    13,    13,
     -41,   -41,    78,   -41,    77,    85,    89,    96,    90,   112,
     158,   114,   -41,    78,   -41,   121,   121,   121,   121,   -41,
      34,    34,   -41,   -41,   -23,   -41,   -41,   -41,   -41,   115,
     115,   -41,   -41,   -23,   -20,   -41,   115,   115,   -41,   -41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -41,   -41,   -41,   168,   -41,   157,   -41,   146,   -41,   -41,
     -41,   -41,   -41,   -41,   -40,   -41,   -41,     6,    32,    42,
     -41,   -18,   -41,   -41
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      40,    65,    67,    81,    82,    83,    84,    73,    74,    75,
      50,    51,    52,    77,    79,   126,    50,    19,    52,    53,
      20,    21,    22,    23,     1,   127,    85,    54,    66,    94,
      95,    96,    97,    54,    19,    10,   101,    20,    21,    22,
      23,   105,   106,   107,   108,   109,    62,    24,    25,   102,
      11,    80,   114,    26,   103,    17,    27,    36,    18,    91,
      86,    87,     5,   123,    24,    25,    81,    82,    83,    84,
      26,    36,    76,    27,    81,    82,    83,    84,    28,     6,
      42,    50,    51,    52,    41,    88,    89,    42,   115,    85,
      53,    92,   110,   111,    93,    28,   116,    85,    54,    10,
     117,   124,   125,    81,    82,    83,    84,   118,   128,   129,
       8,    81,    82,    83,    84,    81,    82,    83,    84,     9,
     112,   113,    81,    82,    83,    84,    85,   122,    14,    15,
      47,    43,    44,    45,    85,    46,    48,    49,    85,    60,
      81,    82,    83,    84,    98,    85,   119,    64,    99,    81,
      82,    83,    84,    81,    82,    83,    84,    69,    70,   100,
      71,    72,    90,    85,    81,    82,    83,    84,   120,   121,
      85,     7,    85,   104,    39,    63,    85,     0,    81,    82,
      83,    84,     0,     0,     0,     0,     0,    85,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85
};

static const yytype_int8 yycheck[] =
{
      18,    41,    42,    26,    27,    28,    29,    47,    48,    49,
       3,     4,     5,    53,    54,    35,     3,     3,     5,    12,
       6,     7,     8,     9,    41,    45,    49,    20,    21,    69,
      70,    71,    72,    20,     3,     6,    76,     6,     7,     8,
       9,    81,    82,    83,    84,    85,    15,    33,    34,    13,
      21,    11,    92,    39,    18,    18,    42,    15,    21,    11,
      49,    50,     6,   103,    33,    34,    26,    27,    28,    29,
      39,    29,    12,    42,    26,    27,    28,    29,    64,     0,
      20,     3,     4,     5,    17,    51,    52,    20,    11,    49,
      12,    18,    86,    87,    21,    64,    11,    49,    20,     6,
      11,   119,   120,    26,    27,    28,    29,    11,   126,   127,
       3,    26,    27,    28,    29,    26,    27,    28,    29,    20,
      88,    89,    26,    27,    28,    29,    49,    13,     3,    14,
      20,     3,     3,     3,    49,     3,    20,    20,    49,     4,
      26,    27,    28,    29,    21,    49,    56,    11,    21,    26,
      27,    28,    29,    26,    27,    28,    29,    17,    17,    21,
      17,    17,    11,    49,    26,    27,    28,    29,    56,    11,
      49,     3,    49,    21,    17,    29,    49,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    41,    66,    67,    68,     6,     0,    68,     3,    20,
       6,    21,    69,    70,     3,    14,    86,    18,    21,     3,
       6,     7,     8,     9,    33,    34,    39,    42,    64,    71,
      72,    73,    74,    75,    77,    78,    84,    87,    88,    70,
      86,    17,    20,     3,     3,     3,     3,    20,    20,    20,
       3,     4,     5,    12,    20,    79,    81,    82,    83,    84,
       4,    76,    15,    72,    11,    79,    21,    79,    85,    17,
      17,    17,    17,    79,    79,    79,    12,    79,    80,    79,
      11,    26,    27,    28,    29,    49,    49,    50,    51,    52,
      11,    11,    18,    21,    79,    79,    79,    79,    21,    21,
      21,    79,    13,    18,    21,    79,    79,    79,    79,    79,
      82,    82,    83,    83,    79,    11,    11,    11,    11,    56,
      56,    11,    13,    79,    86,    86,    35,    45,    86,    86
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 146 "LazyUi_Parser.y"
    {
        debug_print("Parsing programme");
        ASTNode *main_func = NULL, *decls = NULL;
        extract_main_function((yyvsp[(1) - (1)].ast_node), &decls, &main_func);
        ast_root = create_program_node(decls, main_func, yylineno);
        generate_code_entry(ast_root);
    ;}
    break;

  case 3:
#line 157 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);
    ;}
    break;

  case 4:
#line 161 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = create_sequence_node((yyvsp[(1) - (2)].ast_node), (yyvsp[(2) - (2)].ast_node), yylineno);
    ;}
    break;

  case 5:
#line 168 "LazyUi_Parser.y"
    {
        debug_print("Function declaration with parameters");
        (yyval.ast_node) = create_function_declaration_node((yyvsp[(3) - (7)].string), TYPE_RA9M, (yyvsp[(5) - (7)].param_list), (yyvsp[(7) - (7)].ast_node), yylineno);
    ;}
    break;

  case 6:
#line 173 "LazyUi_Parser.y"
    {
        debug_print("Function declaration without parameters");
        (yyval.ast_node) = create_function_declaration_node((yyvsp[(3) - (6)].string), TYPE_RA9M, NULL, (yyvsp[(6) - (6)].ast_node), yylineno);
    ;}
    break;

  case 7:
#line 181 "LazyUi_Parser.y"
    {
        (yyval.param_list) = (yyvsp[(1) - (1)].param_list);
    ;}
    break;

  case 8:
#line 185 "LazyUi_Parser.y"
    {
        (yyval.param_list) = append_parameter((yyvsp[(1) - (3)].param_list), (yyvsp[(3) - (3)].param_list));
    ;}
    break;

  case 9:
#line 192 "LazyUi_Parser.y"
    {
        debug_print("Found parameter");
        (yyval.param_list) = create_parameter((yyvsp[(2) - (2)].string), TYPE_RA9M);
    ;}
    break;

  case 10:
#line 200 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = NULL;
    ;}
    break;

  case 11:
#line 204 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);
    ;}
    break;

  case 12:
#line 208 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = create_sequence_node((yyvsp[(1) - (2)].ast_node), (yyvsp[(2) - (2)].ast_node), yylineno);
    ;}
    break;

  case 13:
#line 214 "LazyUi_Parser.y"
    { debug_print("Reducing: declaration_variable"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 14:
#line 215 "LazyUi_Parser.y"
    { debug_print("Reducing: affectation"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 15:
#line 216 "LazyUi_Parser.y"
    { debug_print("Reducing: print statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 16:
#line 217 "LazyUi_Parser.y"
    { debug_print("Reducing: ktib statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 17:
#line 218 "LazyUi_Parser.y"
    { debug_print("Reducing: if/else statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 18:
#line 219 "LazyUi_Parser.y"
    { debug_print("Reducing: while statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 19:
#line 220 "LazyUi_Parser.y"
    { debug_print("Reducing: return statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 20:
#line 221 "LazyUi_Parser.y"
    { debug_print("Reducing: function call"); (yyval.ast_node) = (yyvsp[(1) - (2)].ast_node); ;}
    break;

  case 21:
#line 226 "LazyUi_Parser.y"
    {
        debug_print("Found print statement");
        (yyval.ast_node) = create_print_node((yyvsp[(3) - (5)].ast_node), yylineno);
    ;}
    break;

  case 22:
#line 234 "LazyUi_Parser.y"
    {
        debug_print("Reducing: instruction_retour (rje3)");
        (yyval.ast_node) = create_return_node((yyvsp[(2) - (3)].ast_node), yylineno);
    ;}
    break;

  case 23:
#line 241 "LazyUi_Parser.y"
    { (yyval.ast_node) = create_print_node(create_string_node((yyvsp[(2) - (3)].string), yylineno), yylineno); ;}
    break;

  case 24:
#line 245 "LazyUi_Parser.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); ;}
    break;

  case 25:
#line 250 "LazyUi_Parser.y"
    { debug_print("Found ra9m variable declaration"); (yyval.ast_node) = create_var_declaration_node((yyvsp[(2) - (5)].string), TYPE_RA9M, (yyvsp[(4) - (5)].ast_node), yylineno); ;}
    break;

  case 26:
#line 252 "LazyUi_Parser.y"
    { debug_print("Found ktaba variable declaration"); (yyval.ast_node) = create_var_declaration_node((yyvsp[(2) - (5)].string), TYPE_KTABA, (yyvsp[(4) - (5)].ast_node), yylineno); ;}
    break;

  case 27:
#line 254 "LazyUi_Parser.y"
    { debug_print("Found wa9ila variable declaration"); (yyval.ast_node) = create_var_declaration_node((yyvsp[(2) - (5)].string), TYPE_WA9ILA, (yyvsp[(4) - (5)].ast_node), yylineno); ;}
    break;

  case 28:
#line 256 "LazyUi_Parser.y"
    { debug_print("Found lista variable declaration"); (yyval.ast_node) = create_var_declaration_node((yyvsp[(2) - (5)].string), TYPE_LISTA, (yyvsp[(4) - (5)].ast_node), yylineno); ;}
    break;

  case 29:
#line 260 "LazyUi_Parser.y"
    {
        debug_print("Found assignment");
        (yyval.ast_node) = create_assignment_node(create_identifier_node((yyvsp[(1) - (4)].string), yylineno), (yyvsp[(3) - (4)].ast_node), yylineno);
    ;}
    break;

  case 30:
#line 267 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 31:
#line 268 "LazyUi_Parser.y"
    { (yyval.ast_node) = create_string_node((yyvsp[(1) - (1)].string), yylineno); ;}
    break;

  case 32:
#line 270 "LazyUi_Parser.y"
    {
        debug_print("Found array literal");
        (yyval.ast_node) = create_array_literal_node((yyvsp[(2) - (3)].ast_node), yylineno);
    ;}
    break;

  case 33:
#line 275 "LazyUi_Parser.y"
    {
        debug_print("Found string concatenation or addition");
        (yyval.ast_node) = create_binary_op_node(OP_ADD, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 34:
#line 280 "LazyUi_Parser.y"
    {
        debug_print("Found greater than comparison");
        (yyval.ast_node) = create_binary_op_node(OP_GT, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 35:
#line 285 "LazyUi_Parser.y"
    {
        debug_print("Found less than comparison");
        (yyval.ast_node) = create_binary_op_node(OP_LT, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 36:
#line 290 "LazyUi_Parser.y"
    {
        debug_print("Found equality comparison");
        (yyval.ast_node) = create_binary_op_node(OP_EQ, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 37:
#line 295 "LazyUi_Parser.y"
    {
        debug_print("Found inequality comparison");
        (yyval.ast_node) = create_binary_op_node(OP_NEQ, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 38:
#line 302 "LazyUi_Parser.y"
    { (yyval.ast_node) = NULL; ;}
    break;

  case 39:
#line 303 "LazyUi_Parser.y"
    { (yyval.ast_node) = create_array_elements_node((yyvsp[(1) - (1)].ast_node), NULL); ;}
    break;

  case 40:
#line 304 "LazyUi_Parser.y"
    { (yyval.ast_node) = create_array_elements_node((yyvsp[(3) - (3)].ast_node), (yyvsp[(1) - (3)].ast_node)); ;}
    break;

  case 41:
#line 308 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 42:
#line 310 "LazyUi_Parser.y"
    {
        debug_print("Found addition");
        (yyval.ast_node) = create_binary_op_node(OP_ADD, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 43:
#line 315 "LazyUi_Parser.y"
    {
        debug_print("Found subtraction");
        (yyval.ast_node) = create_binary_op_node(OP_SUB, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 44:
#line 322 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 45:
#line 324 "LazyUi_Parser.y"
    {
        debug_print("Found multiplication");
        (yyval.ast_node) = create_binary_op_node(OP_MUL, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 46:
#line 329 "LazyUi_Parser.y"
    {
        debug_print("Found division");
        (yyval.ast_node) = create_binary_op_node(OP_DIV, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 47:
#line 337 "LazyUi_Parser.y"
    {
        debug_print("Found number");
        (yyval.ast_node) = create_number_node((yyvsp[(1) - (1)].number), yylineno);
    ;}
    break;

  case 48:
#line 342 "LazyUi_Parser.y"
    {
        debug_print("Found identifier");
        (yyval.ast_node) = create_identifier_node((yyvsp[(1) - (1)].string), yylineno);
    ;}
    break;

  case 49:
#line 347 "LazyUi_Parser.y"
    {
        debug_print("Found array access");
        (yyval.ast_node) = create_array_access_node(create_identifier_node((yyvsp[(1) - (4)].string), yylineno), (yyvsp[(3) - (4)].ast_node), yylineno);
    ;}
    break;

  case 50:
#line 351 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node); ;}
    break;

  case 51:
#line 352 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 52:
#line 357 "LazyUi_Parser.y"
    {
        debug_print("Found function call with arguments");
        ASTNode** args = NULL;
        int arg_count = 0;
        flatten_arguments((yyvsp[(3) - (4)].ast_node), &args, &arg_count);
        (yyval.ast_node) = create_function_call_node((yyvsp[(1) - (4)].string), args, arg_count, yylineno);
    ;}
    break;

  case 53:
#line 365 "LazyUi_Parser.y"
    {
        debug_print("Found function call without arguments");
        (yyval.ast_node) = create_function_call_node((yyvsp[(1) - (3)].string), NULL, 0, yylineno);
    ;}
    break;

  case 54:
#line 372 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 55:
#line 374 "LazyUi_Parser.y"
    {
        debug_print("Found multiple arguments");
        (yyval.ast_node) = create_sequence_node((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    ;}
    break;

  case 56:
#line 382 "LazyUi_Parser.y"
    {
        debug_print("Found block");
        (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node);
    ;}
    break;

  case 57:
#line 390 "LazyUi_Parser.y"
    {
        debug_print("Found if statement");
        (yyval.ast_node) = create_if_node((yyvsp[(3) - (6)].ast_node), (yyvsp[(6) - (6)].ast_node), NULL, yylineno);
    ;}
    break;

  case 58:
#line 395 "LazyUi_Parser.y"
    {
        debug_print("Found if-else statement with ilamakanch");
        (yyval.ast_node) = create_if_node((yyvsp[(3) - (8)].ast_node), (yyvsp[(6) - (8)].ast_node), (yyvsp[(8) - (8)].ast_node), yylineno);
    ;}
    break;

  case 59:
#line 400 "LazyUi_Parser.y"
    {
        debug_print("Found if-else statement with wla");
        (yyval.ast_node) = create_if_node((yyvsp[(3) - (8)].ast_node), (yyvsp[(6) - (8)].ast_node), (yyvsp[(8) - (8)].ast_node), yylineno);
    ;}
    break;

  case 60:
#line 408 "LazyUi_Parser.y"
    {
        debug_print("Found while statement");
        (yyval.ast_node) = create_while_node((yyvsp[(3) - (6)].ast_node), (yyvsp[(6) - (6)].ast_node), yylineno);
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2080 "LazyUi_Parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 414 "LazyUi_Parser.y"


void yyerror(const char* s) {
    int tok = yylex();
    fprintf(stderr, "Error at line %d: %s. Next token: %d\n", yylineno, s, tok);
    parser_error(s);
}

int main(int argc, char** argv) {
    debug_print("Starting parser");
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    debug_print("Creating symbol table");
    symbol_table = create_symbol_table();
    
    debug_print("Starting parsing");
    int result = yyparse();
    debug_print("Parsing completed");
    
    if (result == 0 && ast_root) {
        debug_print("Analyzing AST");
        analyze_ast(ast_root, symbol_table);
        
        debug_print("Printing AST");
        printf("AST Structure:\n");
        print_ast(ast_root, 0);
        
        debug_print("Printing symbol table");
        printf("Symbol Table:\n");
        print_symbol_table(symbol_table);
        
        debug_print("Generating code");
        generate_code(ast_root);
        
        debug_print("Freeing AST");
        free_ast_node(ast_root);
    }
    
    debug_print("Freeing symbol table");
    free_symbol_table(symbol_table);
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return result;
} 
