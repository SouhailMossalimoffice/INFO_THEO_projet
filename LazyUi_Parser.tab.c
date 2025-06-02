/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
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

/* Line 371 of yacc.c  */
#line 172 "LazyUi_Parser.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "LazyUi_Parser.tab.h".  */
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
     TK_WLALA = 318
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 105 "LazyUi_Parser.y"

    double number;
    char* string;
    struct ASTNode* ast_node;
    struct Parameter* param_list;


/* Line 387 of yacc.c  */
#line 286 "LazyUi_Parser.tab.c"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 314 "LazyUi_Parser.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNRULES -- Number of states.  */
#define YYNSTATES  154

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

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
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    18,    25,    27,    31,
      34,    35,    37,    40,    42,    44,    46,    49,    51,    53,
      55,    57,    59,    65,    71,    75,    81,    87,    90,    94,
      96,   100,   102,   106,   108,   110,   112,   114,   119,   124,
     131,   135,   137,   141,   145,   149,   153,   157,   161,   163,
     167,   171,   173,   177,   181,   183,   185,   189,   191,   196,
     200,   202,   206,   210,   216,   224,   230,   236,   239,   242,
     245,   249,   251,   255
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      65,     0,    -1,    66,    -1,    67,    -1,    66,    67,    -1,
      41,     6,     3,    20,    68,    21,    86,    -1,    41,     6,
       3,    20,    21,    86,    -1,    69,    -1,    68,    18,    69,
      -1,     6,     3,    -1,    -1,    71,    -1,    70,    71,    -1,
      79,    -1,    73,    -1,    78,    -1,    84,    11,    -1,    72,
      -1,    87,    -1,    88,    -1,    89,    -1,    90,    -1,    39,
      20,    76,    21,    11,    -1,     6,     3,    17,    76,    11,
      -1,     6,     3,    11,    -1,     9,     3,    17,    74,    11,
      -1,    10,     3,    17,    93,    11,    -1,    12,    13,    -1,
      12,    75,    13,    -1,    76,    -1,    75,    18,    76,    -1,
      80,    -1,    76,    19,     3,    -1,     5,    -1,     4,    -1,
       3,    -1,    77,    -1,     3,    12,    76,    13,    -1,     3,
      17,    76,    11,    -1,    76,    19,     3,    17,    76,    11,
      -1,    42,    76,    11,    -1,    81,    -1,    81,    26,    81,
      -1,    81,    27,    81,    -1,    81,    28,    81,    -1,    81,
      29,    81,    -1,    81,    30,    81,    -1,    81,    31,    81,
      -1,    82,    -1,    81,    49,    82,    -1,    81,    50,    82,
      -1,    83,    -1,    82,    51,    83,    -1,    82,    52,    83,
      -1,     5,    -1,     3,    -1,    20,    76,    21,    -1,    84,
      -1,     3,    20,    85,    21,    -1,     3,    20,    21,    -1,
      76,    -1,    85,    18,    76,    -1,    14,    70,    15,    -1,
      33,    20,    76,    21,    86,    -1,    33,    20,    76,    21,
      86,    35,    86,    -1,    53,    20,    76,    21,    86,    -1,
      47,    20,    76,    21,    86,    -1,    91,    92,    -1,    58,
      86,    -1,    62,    86,    -1,    14,    94,    15,    -1,    95,
      -1,    94,    18,    95,    -1,     3,    17,    76,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   142,   142,   153,   157,   164,   169,   177,   181,   188,
     197,   200,   204,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   223,   231,   236,   241,   246,   254,   259,   267,
     271,   278,   282,   287,   292,   297,   302,   309,   317,   322,
     331,   339,   340,   345,   350,   355,   360,   365,   373,   374,
     379,   387,   388,   393,   401,   406,   411,   412,   416,   424,
     432,   433,   441,   449,   454,   462,   470,   494,   504,   512,
     520,   528,   533,   541
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "TK_WLALA", "$accept", "programme", "declarations_fonctions",
  "declaration_fonction", "parametres", "parametre", "instructions",
  "instruction", "instruction_print", "declaration_variable",
  "array_initializer", "expression_list", "expression", "array_access",
  "affectation", "instruction_retour", "expression_comparison",
  "expression_arithmetique", "terme", "facteur", "appel_fonction_expr",
  "arguments", "bloc", "instruction_if", "instruction_while",
  "instruction_for", "instruction_try", "try_block", "catch_block",
  "jadwal_initializer", "jadwal_fields", "jadwal_field", YY_NULL
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
     315,   316,   317,   318
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    66,    66,    67,    67,    68,    68,    69,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    73,    73,    73,    73,    74,    74,    75,
      75,    76,    76,    76,    76,    76,    76,    77,    78,    78,
      79,    80,    80,    80,    80,    80,    80,    80,    81,    81,
      81,    82,    82,    82,    83,    83,    83,    83,    84,    84,
      85,    85,    86,    87,    87,    88,    89,    90,    91,    92,
      93,    94,    94,    95
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     7,     6,     1,     3,     2,
       0,     1,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     5,     5,     3,     5,     5,     2,     3,     1,
       3,     1,     3,     1,     1,     1,     1,     4,     4,     6,
       3,     1,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     1,     3,     1,     4,     3,
       1,     3,     3,     5,     7,     5,     5,     2,     2,     2,
       3,     1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     4,     0,     0,
       0,     0,     0,     7,     9,    10,     6,     0,     0,    55,
      34,    54,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    17,    14,     0,    36,    15,    13,
      31,    41,    48,    51,    57,    18,    19,    20,    21,     0,
       8,     5,     0,     0,     0,     0,     0,     0,    55,     0,
      57,     0,     0,     0,     0,     0,    68,    62,    12,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      16,     0,    67,     0,     0,    59,    60,     0,    24,     0,
       0,     0,     0,    56,     0,     0,    40,     0,     0,    32,
      55,    54,    42,    43,    44,    45,    46,    47,    49,    50,
      52,    53,    69,    37,    38,     0,    58,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,     0,    61,    23,
      27,     0,    29,    25,     0,     0,    71,    26,    63,    22,
      66,    65,     0,    28,     0,     0,    70,     0,     0,    39,
      30,    73,    72,    64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    12,    13,    32,    33,    34,    35,
     119,   131,    36,    37,    38,    39,    40,    41,    42,    43,
      60,    87,    16,    45,    46,    47,    48,    49,    82,   121,
     135,   136
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -28
static const yytype_int16 yypact[] =
{
     -27,    18,    42,   -27,   -28,    55,   -28,   -28,    63,    26,
     103,   101,    15,   -28,   -28,    46,   -28,   116,   101,    70,
     -28,   113,   130,   144,   145,    64,   131,   132,    64,   133,
     134,   101,     6,   -28,   -28,   -28,   136,   -28,   -28,   -28,
     -28,    47,    19,   -28,   146,   -28,   -28,   -28,   -28,    94,
     -28,   -28,    64,    64,     2,    -9,   141,   142,    98,    93,
     -28,    64,    64,    24,    64,    64,   -28,   -28,   -28,   157,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
     -28,   101,   -28,    12,    43,   -28,   143,    39,   -28,    64,
     149,   150,   160,   -28,   104,   108,   -28,   122,   123,   148,
     147,   -28,    52,    52,    52,    52,    52,    52,    19,    19,
     -28,   -28,   -28,   -28,   -28,    64,   -28,    61,    14,   155,
     165,   158,   -28,   101,   159,   101,   101,    64,   143,   -28,
     -28,    68,   143,   -28,   154,    80,   -28,   -28,   137,   -28,
     -28,   -28,    81,   -28,    64,    64,   -28,   165,   101,   -28,
     143,   143,   -28,   -28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -28,   -28,   -28,   170,   -28,   161,   -28,   151,   -28,   -28,
     -28,   -28,   -24,   -28,   -28,   -28,   -28,    65,    69,    71,
     -12,   -28,   -18,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,    27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -36
static const yytype_int16 yytable[] =
{
      51,    59,    88,    44,    63,    58,    20,    21,    89,    19,
      20,    21,    22,    66,     1,    23,    24,    58,    20,    21,
      44,    67,    25,    85,     5,   113,    25,   130,    83,    84,
      86,    92,    10,    17,    25,    96,    18,    94,    95,    26,
      97,    98,     6,    92,   100,    27,   101,    11,    28,    19,
      20,    21,    22,    29,   114,    23,    24,   115,     8,    30,
     116,    25,    92,   112,    31,   117,    25,    58,    20,    21,
      78,    79,   129,    70,    71,    72,    73,    74,    75,    26,
      92,   143,    52,     9,    25,    27,   144,    53,    28,   -35,
      54,   128,   149,    29,   132,   146,    76,    77,   147,    30,
      92,    76,    77,   142,    31,   138,    14,   140,   141,   -35,
      52,   -35,    92,   -35,    93,    15,   -35,   -35,    54,   -35,
     150,   151,    10,    92,   -33,   123,   -33,    92,   -33,   124,
     153,   -33,   -33,    55,   -33,   102,   103,   104,   105,   106,
     107,    92,    92,   125,   126,   108,   109,    56,    57,   110,
     111,    61,    62,    64,    65,    69,    81,    80,    90,    91,
      99,   118,    92,   122,   120,   127,   133,    54,   134,   137,
     139,   145,   148,     7,   152,     0,     0,     0,    50,     0,
       0,     0,     0,    68
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-28)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      18,    25,    11,    15,    28,     3,     4,     5,    17,     3,
       4,     5,     6,    31,    41,     9,    10,     3,     4,     5,
      32,    15,    20,    21,     6,    13,    20,    13,    52,    53,
      54,    19,     6,    18,    20,    11,    21,    61,    62,    33,
      64,    65,     0,    19,     3,    39,     5,    21,    42,     3,
       4,     5,     6,    47,    11,     9,    10,    18,     3,    53,
      21,    20,    19,    81,    58,    89,    20,     3,     4,     5,
      51,    52,    11,    26,    27,    28,    29,    30,    31,    33,
      19,    13,    12,    20,    20,    39,    18,    17,    42,    19,
      20,   115,    11,    47,   118,    15,    49,    50,    18,    53,
      19,    49,    50,   127,    58,   123,     3,   125,   126,    11,
      12,    13,    19,    15,    21,    14,    18,    19,    20,    21,
     144,   145,     6,    19,    11,    21,    13,    19,    15,    21,
     148,    18,    19,     3,    21,    70,    71,    72,    73,    74,
      75,    19,    19,    21,    21,    76,    77,     3,     3,    78,
      79,    20,    20,    20,    20,    19,    62,    11,    17,    17,
       3,    12,    19,     3,    14,    17,    11,    20,     3,    11,
      11,    17,    35,     3,   147,    -1,    -1,    -1,    17,    -1,
      -1,    -1,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    41,    65,    66,    67,     6,     0,    67,     3,    20,
       6,    21,    68,    69,     3,    14,    86,    18,    21,     3,
       4,     5,     6,     9,    10,    20,    33,    39,    42,    47,
      53,    58,    70,    71,    72,    73,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    87,    88,    89,    90,    91,
      69,    86,    12,    17,    20,     3,     3,     3,     3,    76,
      84,    20,    20,    76,    20,    20,    86,    15,    71,    19,
      26,    27,    28,    29,    30,    31,    49,    50,    51,    52,
      11,    62,    92,    76,    76,    21,    76,    85,    11,    17,
      17,    17,    19,    21,    76,    76,    11,    76,    76,     3,
       3,     5,    81,    81,    81,    81,    81,    81,    82,    82,
      83,    83,    86,    13,    11,    18,    21,    76,    12,    74,
      14,    93,     3,    21,    21,    21,    21,    17,    76,    11,
      13,    75,    76,    11,     3,    94,    95,    11,    86,    11,
      86,    86,    76,    13,    18,    17,    15,    18,    35,    11,
      76,    76,    95,    86
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1792 of yacc.c  */
#line 143 "LazyUi_Parser.y"
    {
        debug_print("Parsing programme");
        ASTNode *main_func = NULL, *decls = NULL;
        extract_main_function((yyvsp[(1) - (1)].ast_node), &decls, &main_func);
        ast_root = create_program_node(decls, main_func, yylineno);
        generate_code_entry(ast_root);
    }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 154 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);
    }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 158 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = create_sequence_node((yyvsp[(1) - (2)].ast_node), (yyvsp[(2) - (2)].ast_node), yylineno);
    }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 165 "LazyUi_Parser.y"
    {
        debug_print("Function declaration with parameters");
        (yyval.ast_node) = create_function_declaration_node((yyvsp[(3) - (7)].string), TYPE_RA9M, (yyvsp[(5) - (7)].param_list), (yyvsp[(7) - (7)].ast_node), yylineno);
    }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 170 "LazyUi_Parser.y"
    {
        debug_print("Function declaration without parameters");
        (yyval.ast_node) = create_function_declaration_node((yyvsp[(3) - (6)].string), TYPE_RA9M, NULL, (yyvsp[(6) - (6)].ast_node), yylineno);
    }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 178 "LazyUi_Parser.y"
    {
        (yyval.param_list) = (yyvsp[(1) - (1)].param_list);
    }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 182 "LazyUi_Parser.y"
    {
        (yyval.param_list) = append_parameter((yyvsp[(1) - (3)].param_list), (yyvsp[(3) - (3)].param_list));
    }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 189 "LazyUi_Parser.y"
    {
        debug_print("Found parameter");
        (yyval.param_list) = create_parameter((yyvsp[(2) - (2)].string), TYPE_RA9M);
    }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 197 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = NULL;
    }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 201 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);
    }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 205 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = create_sequence_node((yyvsp[(1) - (2)].ast_node), (yyvsp[(2) - (2)].ast_node), yylineno);
    }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 211 "LazyUi_Parser.y"
    { debug_print("Reducing: instruction_retour"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 212 "LazyUi_Parser.y"
    { debug_print("Reducing: declaration_variable"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 213 "LazyUi_Parser.y"
    { debug_print("Reducing: affectation"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 214 "LazyUi_Parser.y"
    { debug_print("Reducing: function call"); (yyval.ast_node) = (yyvsp[(1) - (2)].ast_node); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 215 "LazyUi_Parser.y"
    { debug_print("Reducing: print statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 216 "LazyUi_Parser.y"
    { debug_print("Reducing: if statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 217 "LazyUi_Parser.y"
    { debug_print("Reducing: while statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 218 "LazyUi_Parser.y"
    { debug_print("Reducing: for statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 219 "LazyUi_Parser.y"
    { debug_print("Reducing: try statement"); (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 224 "LazyUi_Parser.y"
    {
        debug_print("Found print statement");
        (yyval.ast_node) = create_print_node((yyvsp[(3) - (5)].ast_node), yylineno);
    }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 232 "LazyUi_Parser.y"
    {
        debug_print("Found variable declaration with initialization");
        (yyval.ast_node) = create_var_declaration_node((yyvsp[(2) - (5)].string), TYPE_RA9M, (yyvsp[(4) - (5)].ast_node), yylineno);
    }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 237 "LazyUi_Parser.y"
    {
        debug_print("Found variable declaration without initialization");
        (yyval.ast_node) = create_var_declaration_node((yyvsp[(2) - (3)].string), TYPE_RA9M, NULL, yylineno);
    }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 242 "LazyUi_Parser.y"
    {
        debug_print("Found array declaration");
        (yyval.ast_node) = create_var_declaration_node((yyvsp[(2) - (5)].string), TYPE_LISTA, (yyvsp[(4) - (5)].ast_node), yylineno);
    }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 247 "LazyUi_Parser.y"
    {
        debug_print("Found jadwal declaration");
        (yyval.ast_node) = create_var_declaration_node((yyvsp[(2) - (5)].string), TYPE_JADWAL, (yyvsp[(4) - (5)].ast_node), yylineno);
    }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 255 "LazyUi_Parser.y"
    {
        debug_print("Found empty array initializer");
        (yyval.ast_node) = NULL;
    }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 260 "LazyUi_Parser.y"
    {
        debug_print("Found array initializer with elements");
        (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node);
    }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 268 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);
    }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 272 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = create_sequence_node((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 279 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);
    }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 283 "LazyUi_Parser.y"
    {
        debug_print("Found field access expression");
        (yyval.ast_node) = create_field_access_node((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].string), yylineno);
    }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 288 "LazyUi_Parser.y"
    {
        debug_print("Found number expression");
        (yyval.ast_node) = create_number_node((yyvsp[(1) - (1)].number), yylineno);
    }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 293 "LazyUi_Parser.y"
    {
        debug_print("Found string expression");
        (yyval.ast_node) = create_string_node((yyvsp[(1) - (1)].string), yylineno);
    }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 298 "LazyUi_Parser.y"
    {
        debug_print("Found identifier expression");
        (yyval.ast_node) = create_identifier_node((yyvsp[(1) - (1)].string), yylineno);
    }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 303 "LazyUi_Parser.y"
    {
        (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);
    }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 310 "LazyUi_Parser.y"
    {
        debug_print("Found array access");
        (yyval.ast_node) = create_array_access_node(create_identifier_node((yyvsp[(1) - (4)].string), yylineno), (yyvsp[(3) - (4)].ast_node), yylineno);
    }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 318 "LazyUi_Parser.y"
    {
        debug_print("Found assignment");
        (yyval.ast_node) = create_assignment_node(create_identifier_node((yyvsp[(1) - (4)].string), yylineno), (yyvsp[(3) - (4)].ast_node), yylineno);
    }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 323 "LazyUi_Parser.y"
    {
        debug_print("Found field assignment");
        ASTNode* field_access = create_field_access_node((yyvsp[(1) - (6)].ast_node), (yyvsp[(3) - (6)].string), yylineno);
        (yyval.ast_node) = create_assignment_node(field_access, (yyvsp[(5) - (6)].ast_node), yylineno);
    }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 332 "LazyUi_Parser.y"
    {
        debug_print("Reducing: instruction_retour (rje3)");
        (yyval.ast_node) = create_return_node((yyvsp[(2) - (3)].ast_node), yylineno);
    }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 339 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 341 "LazyUi_Parser.y"
    {
        debug_print("Found equal comparison");
        (yyval.ast_node) = create_binary_op_node(OP_EQ, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 346 "LazyUi_Parser.y"
    {
        debug_print("Found not equal comparison");
        (yyval.ast_node) = create_binary_op_node(OP_NEQ, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 351 "LazyUi_Parser.y"
    {
        debug_print("Found greater than comparison");
        (yyval.ast_node) = create_binary_op_node(OP_GT, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 356 "LazyUi_Parser.y"
    {
        debug_print("Found less than comparison");
        (yyval.ast_node) = create_binary_op_node(OP_LT, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 361 "LazyUi_Parser.y"
    {
        debug_print("Found greater than or equal comparison");
        (yyval.ast_node) = create_binary_op_node(OP_GTE, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 366 "LazyUi_Parser.y"
    {
        debug_print("Found less than or equal comparison");
        (yyval.ast_node) = create_binary_op_node(OP_LTE, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 373 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 375 "LazyUi_Parser.y"
    {
        debug_print("Found addition");
        (yyval.ast_node) = create_binary_op_node(OP_ADD, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 380 "LazyUi_Parser.y"
    {
        debug_print("Found subtraction");
        (yyval.ast_node) = create_binary_op_node(OP_SUB, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 387 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 389 "LazyUi_Parser.y"
    {
        debug_print("Found multiplication");
        (yyval.ast_node) = create_binary_op_node(OP_MUL, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 394 "LazyUi_Parser.y"
    {
        debug_print("Found division");
        (yyval.ast_node) = create_binary_op_node(OP_DIV, (yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 402 "LazyUi_Parser.y"
    {
        debug_print("Found number");
        (yyval.ast_node) = create_number_node((yyvsp[(1) - (1)].number), yylineno);
    }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 407 "LazyUi_Parser.y"
    {
        debug_print("Found identifier");
        (yyval.ast_node) = create_identifier_node((yyvsp[(1) - (1)].string), yylineno);
    }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 411 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 412 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 417 "LazyUi_Parser.y"
    {
        debug_print("Found function call with arguments");
        ASTNode** args = NULL;
        int arg_count = 0;
        flatten_arguments((yyvsp[(3) - (4)].ast_node), &args, &arg_count);
        (yyval.ast_node) = create_function_call_node((yyvsp[(1) - (4)].string), args, arg_count, yylineno);
    }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 425 "LazyUi_Parser.y"
    {
        debug_print("Found function call without arguments");
        (yyval.ast_node) = create_function_call_node((yyvsp[(1) - (3)].string), NULL, 0, yylineno);
    }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 432 "LazyUi_Parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 434 "LazyUi_Parser.y"
    {
        debug_print("Found multiple arguments");
        (yyval.ast_node) = create_sequence_node((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 442 "LazyUi_Parser.y"
    {
        debug_print("Found block");
        (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node);
    }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 450 "LazyUi_Parser.y"
    {
        debug_print("Found if statement");
        (yyval.ast_node) = create_if_node((yyvsp[(3) - (5)].ast_node), (yyvsp[(5) - (5)].ast_node), NULL, yylineno);
    }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 455 "LazyUi_Parser.y"
    {
        debug_print("Found if-else statement");
        (yyval.ast_node) = create_if_node((yyvsp[(3) - (7)].ast_node), (yyvsp[(5) - (7)].ast_node), (yyvsp[(7) - (7)].ast_node), yylineno);
    }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 463 "LazyUi_Parser.y"
    {
        debug_print("Found while statement");
        (yyval.ast_node) = create_while_node((yyvsp[(3) - (5)].ast_node), (yyvsp[(5) - (5)].ast_node), yylineno);
    }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 471 "LazyUi_Parser.y"
    {
        debug_print("Found for statement");
        // For the simple for loop syntax, we'll create a proper initialization
        // and update statement
        ASTNode* init = create_assignment_node(
            create_identifier_node("i", yylineno),
            create_number_node(1, yylineno),
            yylineno
        );
        ASTNode* update = create_assignment_node(
            create_identifier_node("i", yylineno),
            create_binary_op_node(OP_ADD, 
                create_identifier_node("i", yylineno),
                create_number_node(1, yylineno),
                yylineno
            ),
            yylineno
        );
        (yyval.ast_node) = create_for_node(init, (yyvsp[(3) - (5)].ast_node), update, (yyvsp[(5) - (5)].ast_node), yylineno);
    }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 495 "LazyUi_Parser.y"
    {
        debug_print("Found try-catch block");
        enter_scope();  // Enter scope for the entire try-catch block
        (yyval.ast_node) = create_try_node((yyvsp[(1) - (2)].ast_node), (yyvsp[(2) - (2)].ast_node), yylineno);
        exit_scope();   // Exit scope after the entire try-catch block
    }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 505 "LazyUi_Parser.y"
    {
        debug_print("Found try block");
        (yyval.ast_node) = (yyvsp[(2) - (2)].ast_node);
    }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 513 "LazyUi_Parser.y"
    {
        debug_print("Found catch block");
        (yyval.ast_node) = (yyvsp[(2) - (2)].ast_node);
    }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 521 "LazyUi_Parser.y"
    {
        debug_print("Found jadwal initializer");
        (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node);
    }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 529 "LazyUi_Parser.y"
    {
        debug_print("Found single jadwal field");
        (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);
    }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 534 "LazyUi_Parser.y"
    {
        debug_print("Found multiple jadwal fields");
        (yyval.ast_node) = create_sequence_node((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 542 "LazyUi_Parser.y"
    {
        debug_print("Found jadwal field with value");
        ASTNode* field_node = create_field_access_node(NULL, (yyvsp[(1) - (3)].string), yylineno);
        (yyval.ast_node) = create_assignment_node(field_node, (yyvsp[(3) - (3)].ast_node), yylineno);
    }
    break;


/* Line 1792 of yacc.c  */
#line 2277 "LazyUi_Parser.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2055 of yacc.c  */
#line 549 "LazyUi_Parser.y"


void yyerror(const char* s) {
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