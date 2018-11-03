/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "parser.tab.bison" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 92 "parser.bison" /* yacc.c:355  */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
CommandList* root;

#line 107 "parser.tab.bison" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    INT = 259,
    FLOAT = 260,
    PLUS = 261,
    SUB = 262,
    MUL = 263,
    DIV = 264,
    OR = 265,
    AND = 266,
    NOT = 267,
    EQU = 268,
    DIF = 269,
    LES = 270,
    LOQ = 271,
    GRE = 272,
    GOQ = 273,
    IF = 274,
    ELSE = 275,
    WHILE = 276,
    INTD = 277,
    FLOATD = 278,
    SCAN = 279,
    PRINT = 280,
    VAR = 281,
    SEMICOLON = 282,
    EQUAL = 283,
    OPENPARENTHESIS = 284,
    CLOSEPARENTHESIS = 285,
    OPENCURLYBRACKETS = 286,
    CLOSECURLYBRACKETS = 287,
    COMMA = 288,
    TYPES = 289,
    MOD = 290,
    NO_ELSE = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 52 "parser.bison" /* yacc.c:355  */

  int intValue;
  float floatValue;
  char* stringValue;
  char* typesValue;
  CommandList* commandList;
  Command* cmdType;
  IFexpression* ifExpression;
  WHILEexpression* whileExpression;
  PRINTF_EXP* printf_exp;
  SCANF_EXP* scan_expr;
  varList* varList;
  DeclarationList* list_decl;
  ScanDeclarationList* scan_list;
  ASG* assignment;
  DECL* declaration;
  Expr* exprValue;
  BoolExpr* boolExpr;

#line 176 "parser.tab.bison" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 193 "parser.tab.bison" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   142

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  47
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    37,     2,
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
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   109,   113,   119,   123,   127,   131,   135,
     142,   148,   153,   157,   161,   165,   169,   173,   179,   183,
     189,   195,   201,   205,   211,   215,   221,   225,   229,   233,
     239,   243,   247,   251,   255,   259,   263,   267,   272,   276,
     280,   284,   288,   292,   296,   300,   304,   308
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "INT", "FLOAT", "PLUS", "SUB",
  "MUL", "DIV", "OR", "AND", "NOT", "EQU", "DIF", "LES", "LOQ", "GRE",
  "GOQ", "IF", "ELSE", "WHILE", "INTD", "FLOATD", "SCAN", "PRINT", "VAR",
  "SEMICOLON", "EQUAL", "OPENPARENTHESIS", "CLOSEPARENTHESIS",
  "OPENCURLYBRACKETS", "CLOSECURLYBRACKETS", "COMMA", "TYPES", "MOD",
  "NO_ELSE", "'&'", "$accept", "program", "list", "cmd", "printf", "scanf",
  "if_expr", "while_expr", "atr", "decl", "list_scan_var", "var_dec",
  "list_var", "expr", "bexpr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    38
};
# endif

#define YYPACT_NINF -61

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-61)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -18,     9,    29,     1,   -61,   -11,     5,   117,     3,    20,
      25,    25,    23,    24,    27,   117,    28,    30,   -61,   -61,
      35,    34,    34,    33,    49,    53,   -61,   -61,    32,    54,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,    34,    36,     0,
      37,    74,    36,    25,    25,    63,    64,   -61,    15,    36,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      34,    34,    70,    84,    19,   -61,   -61,    50,    25,   -61,
       2,     2,   -61,   -61,    19,    19,    19,    19,    19,    19,
     -61,   -61,   -61,   117,    78,   117,   -61,    43,    26,    69,
      68,    95,    79,   -61,    77,   -61,   -61,    82,   117,   -61,
     -61,    50,   106,    80,   -61,   117,   -61,   -61,    81,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     4,     0,     0,     5,     6,
       0,     0,     0,    21,    29,    26,    24,    25,     0,     0,
       2,     3,     8,     9,     7,    30,    31,     0,     0,    41,
       0,     0,     0,     0,     0,     0,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    28,    27,     0,     0,    32,
      33,    34,    35,    36,    42,    43,    44,    45,    46,    47,
      37,    38,    39,     0,    12,     0,    18,     0,     0,     0,
       0,     0,     0,    21,    23,    11,    10,    14,     0,    13,
      19,     0,     0,     0,    22,     0,    15,    17,     0,    16
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -15,   -60,   -61,   -61,   -61,   -61,   -61,    45,
      21,   -61,   -10,    22,   -17
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    14,    15,    16,    17,    18,    19,    24,    25,
      88,    20,    26,    39,    40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      31,    27,    84,    86,     1,    41,    49,    50,    51,    52,
      51,    52,     3,    53,    54,    55,    56,    57,    58,     6,
      47,    49,    50,    51,    52,    49,    50,    51,    52,     4,
       5,    99,    21,    65,    66,    59,     7,    59,    35,    36,
      35,    36,   106,    81,    82,    69,    37,    60,    61,    22,
      59,    23,    28,    29,    59,    32,    95,    33,    89,    30,
      48,    42,    34,    38,    64,    38,    45,    62,    90,    93,
      92,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    43,   103,    60,    61,    44,    87,    46,     8,
     108,     9,    10,    11,    12,    13,    67,    68,    91,    96,
      97,    83,   102,     8,    63,     9,    10,    11,    12,    13,
     101,   100,   107,   109,     8,    85,     9,    10,    11,    12,
      13,     0,   104,     0,     0,     8,    98,     9,    10,    11,
      12,    13,    94,     0,     0,     0,     8,   105,     9,    10,
      11,    12,    13
};

static const yytype_int8 yycheck[] =
{
      15,    11,    62,    63,    22,    22,     6,     7,     8,     9,
       8,     9,     3,    13,    14,    15,    16,    17,    18,    30,
      37,     6,     7,     8,     9,     6,     7,     8,     9,     0,
      29,    91,    29,    43,    44,    35,    31,    35,     4,     5,
       4,     5,   102,    60,    61,    30,    12,    10,    11,    29,
      35,    26,    29,    29,    35,    27,    30,    27,    68,    32,
      38,    28,    27,    29,    42,    29,    34,    30,    83,    26,
      85,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    33,    98,    10,    11,    33,    37,    34,    19,
     105,    21,    22,    23,    24,    25,    33,    33,    20,    30,
      32,    31,    20,    19,    30,    21,    22,    23,    24,    25,
      33,    32,    32,    32,    19,    31,    21,    22,    23,    24,
      25,    -1,   101,    -1,    -1,    19,    31,    21,    22,    23,
      24,    25,    87,    -1,    -1,    -1,    19,    31,    21,    22,
      23,    24,    25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    22,    39,     3,     0,    29,    30,    31,    19,    21,
      22,    23,    24,    25,    40,    41,    42,    43,    44,    45,
      49,    29,    29,    26,    46,    47,    50,    50,    29,    29,
      32,    40,    27,    27,    27,     4,     5,    12,    29,    51,
      52,    52,    28,    33,    33,    34,    34,    52,    51,     6,
       7,     8,     9,    13,    14,    15,    16,    17,    18,    35,
      10,    11,    30,    30,    51,    50,    50,    33,    33,    30,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    52,    52,    31,    41,    31,    41,    37,    48,    50,
      40,    20,    40,    26,    47,    30,    30,    32,    31,    41,
      32,    33,    20,    40,    48,    31,    41,    32,    40,    32
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      42,    43,    44,    44,    44,    44,    44,    44,    45,    45,
      46,    47,    48,    48,    49,    49,    50,    50,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     7,     2,     1,     1,     1,     2,     2,     2,
       6,     6,     5,     7,     7,     9,    11,     9,     5,     7,
       3,     1,     4,     2,     2,     2,     1,     3,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     3,     3,     3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
    default: /* Avoid compiler warnings. */
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
                  (unsigned long) yystacksize));

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 106 "parser.bison" /* yacc.c:1666  */
    { root = (yyvsp[-1].commandList); }
#line 1344 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 3:
#line 109 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.commandList) = ast_commandList((yyvsp[-1].cmdType), (yyvsp[0].commandList));
  }
#line 1352 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 4:
#line 113 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.commandList) = ast_commandList((yyvsp[0].cmdType), NULL);
  }
#line 1360 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 5:
#line 119 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.cmdType) = if_declaration((yyvsp[0].ifExpression));
  }
#line 1368 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 6:
#line 123 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.cmdType) = while_declaration((yyvsp[0].whileExpression));
  }
#line 1376 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 7:
#line 127 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.cmdType) = variable_declaration((yyvsp[-1].varList));
  }
#line 1384 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 8:
#line 131 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.cmdType) = printf_declaration((yyvsp[-1].printf_exp));
  }
#line 1392 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 9:
#line 135 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.cmdType) = scanf_declaration((yyvsp[-1].scan_expr));
  }
#line 1400 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 10:
#line 142 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.printf_exp) = ast_printf((yyvsp[-3].typesValue),(yyvsp[-1].list_decl));
  }
#line 1408 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 11:
#line 148 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.scan_expr) = ast_scanf((yyvsp[-3].typesValue),(yyvsp[-1].scan_list));
  }
#line 1416 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 12:
#line 153 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.ifExpression) = if_command((yyvsp[-2].boolExpr), (yyvsp[0].cmdType), NULL);
  }
#line 1424 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 13:
#line 157 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.ifExpression) = if_command((yyvsp[-4].boolExpr), (yyvsp[-2].cmdType), (yyvsp[0].cmdType));
  }
#line 1432 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 14:
#line 161 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.ifExpression) = if_commands((yyvsp[-4].boolExpr),(yyvsp[-1].commandList));
  }
#line 1440 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 15:
#line 165 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.ifExpression) = if_else_command((yyvsp[-6].boolExpr), (yyvsp[-3].commandList), (yyvsp[0].cmdType));
  }
#line 1448 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 16:
#line 169 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.ifExpression) = if_else_commands((yyvsp[-8].boolExpr), (yyvsp[-5].commandList), (yyvsp[-1].commandList));
  }
#line 1456 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 17:
#line 173 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.ifExpression) = if_else_command((yyvsp[-6].boolExpr), (yyvsp[-4].cmdType), (yyvsp[-1].commandList));
  }
#line 1464 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 18:
#line 179 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.whileExpression) = while_command((yyvsp[-2].boolExpr), (yyvsp[0].cmdType));
  }
#line 1472 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 19:
#line 183 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.whileExpression) = while_command((yyvsp[-4].boolExpr), (yyvsp[-1].commandList));
  }
#line 1480 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 20:
#line 189 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.assignment) = var_assignment((yyvsp[-2].stringValue),(yyvsp[0].exprValue));
  }
#line 1488 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 21:
#line 195 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.declaration) = var_declaration((yyvsp[0].stringValue));
  }
#line 1496 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 22:
#line 201 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.scan_list) = ast_scanlist((yyvsp[-2].declaration),(yyvsp[0].scan_list));
  }
#line 1504 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 23:
#line 205 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.scan_list) = ast_scanlist((yyvsp[0].declaration),NULL);
  }
#line 1512 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 24:
#line 211 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.varList) = ast_varlist(INTD, (yyvsp[0].list_decl));
  }
#line 1520 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 25:
#line 215 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.varList) = ast_varlist(FLOATD, (yyvsp[0].list_decl));
  }
#line 1528 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 26:
#line 221 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.list_decl) = ast_declaration((yyvsp[0].declaration), NULL);
  }
#line 1536 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 27:
#line 225 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.list_decl) = ast_declaration((yyvsp[-2].declaration), (yyvsp[0].list_decl));
  }
#line 1544 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 28:
#line 229 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.list_decl) = ast_assignment((yyvsp[-2].assignment), (yyvsp[0].list_decl));
  }
#line 1552 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 29:
#line 233 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.list_decl) = ast_assignment((yyvsp[0].assignment), NULL);
  }
#line 1560 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 30:
#line 239 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.exprValue) = ast_integer((yyvsp[0].intValue));
  }
#line 1568 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 31:
#line 243 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.exprValue) = ast_float((yyvsp[0].floatValue));
  }
#line 1576 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 32:
#line 247 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.exprValue) = ast_pexpr((yyvsp[-1].exprValue));
  }
#line 1584 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 33:
#line 251 "parser.bison" /* yacc.c:1666  */
    { 
    (yyval.exprValue) = ast_operation(PLUS, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1592 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 34:
#line 255 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.exprValue) = ast_operation(SUB, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1600 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 35:
#line 259 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.exprValue) = ast_operation(MUL, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1608 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 36:
#line 263 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.exprValue) = ast_operation(DIV, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1616 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 37:
#line 267 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.exprValue) = ast_operation(MOD, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1624 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 38:
#line 272 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_boolOperation(OR, (yyvsp[-2].boolExpr), (yyvsp[0].boolExpr));
  }
#line 1632 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 39:
#line 276 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_boolOperation(AND, (yyvsp[-2].boolExpr), (yyvsp[0].boolExpr));
  }
#line 1640 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 40:
#line 280 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_boolOperation(NOT,(yyvsp[0].boolExpr), NULL);
  }
#line 1648 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 41:
#line 284 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_singleExpr((yyvsp[0].exprValue));
  }
#line 1656 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 42:
#line 288 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_boolOperation2(EQU, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1664 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 43:
#line 292 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_boolOperation2(DIF, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1672 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 44:
#line 296 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_boolOperation2(LES, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1680 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 45:
#line 300 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_boolOperation2(LOQ, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1688 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 46:
#line 304 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_boolOperation2(GRE, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1696 "parser.tab.bison" /* yacc.c:1666  */
    break;

  case 47:
#line 308 "parser.bison" /* yacc.c:1666  */
    {
    (yyval.boolExpr) = ast_boolOperation2(GOQ, (yyvsp[-2].exprValue), (yyvsp[0].exprValue));
  }
#line 1704 "parser.tab.bison" /* yacc.c:1666  */
    break;


#line 1708 "parser.tab.bison" /* yacc.c:1666  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 312 "parser.bison" /* yacc.c:1910  */


void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

