/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GE = 258,
     LE = 259,
     NE = 260,
     UMINUS = 261,
     NUMBER = 262,
     VARIABLE = 263,
     VECVAR = 264,
     FUNC = 265,
     STR = 266,
     MARKER = 267,
     ELEMENT = 268,
     DRIFT = 269,
     DIPOLE = 270,
     SBEND = 271,
     QUADRUPOLE = 272,
     SEXTUPOLE = 273,
     OCTUPOLE = 274,
     MULTIPOLE = 275,
     SOLENOID = 276,
     COLLIMATOR = 277,
     LINE = 278,
     SEQUENCE = 279,
     PERIOD = 280,
     APERTURE = 281,
     FILENAME = 282,
     BEAM = 283,
     OPTION = 284,
     PRINT = 285,
     RANGE = 286,
     STOP = 287,
     USE = 288,
     VALUE = 289,
     ECHO = 290,
     PRINTF = 291,
     IF = 292,
     ELSE = 293,
     BEGN = 294,
     END = 295
   };
#endif
#define GE 258
#define LE 259
#define NE 260
#define UMINUS 261
#define NUMBER 262
#define VARIABLE 263
#define VECVAR 264
#define FUNC 265
#define STR 266
#define MARKER 267
#define ELEMENT 268
#define DRIFT 269
#define DIPOLE 270
#define SBEND 271
#define QUADRUPOLE 272
#define SEXTUPOLE 273
#define OCTUPOLE 274
#define MULTIPOLE 275
#define SOLENOID 276
#define COLLIMATOR 277
#define LINE 278
#define SEQUENCE 279
#define PERIOD 280
#define APERTURE 281
#define FILENAME 282
#define BEAM 283
#define OPTION 284
#define PRINT 285
#define RANGE 286
#define STOP 287
#define USE 288
#define VALUE 289
#define ECHO 290
#define PRINTF 291
#define IF 292
#define ELSE 293
#define BEGN 294
#define END 295




/* Copy the first part of user declarations.  */
#line 7 "parser.y"


  const int DEBUG = 1; // print debug info like parsing output etc.
  const int ECHO_GRAMMAR = 0; // print grammar rule expamsion (for debugging)
  const int VERBOSE = 1; // print warnings and errors
  const int VERBOSE_EXPAND = 1; // print the process of line expansion 
  const int INTERACTIVE = 1; // print output of commands (like in interactive mode)

#include "parser.h"

  int execute = 1;



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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 22 "parser.y"
typedef union YYSTYPE {
  double dval;
  int ival;
  struct symtab *symp;
  char *str;
  struct Array *array;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 178 "parser.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 202 "parser.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYLTYPE_IS_TRIVIAL) && YYLTYPE_IS_TRIVIAL \
             && defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   290

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  28
/* YYNRULES -- Number of rules. */
#define YYNRULES  95
/* YYNRULES -- Number of states. */
#define YYNSTATES  176

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      49,    50,     5,     3,    52,     4,     2,     6,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    48,
       8,    53,     9,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     7,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,    55,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     8,    11,    16,    18,    22,    27,
      28,    30,    32,    34,    38,    42,    46,    50,    54,    58,
      62,    66,    70,    74,    76,    79,    82,    85,    88,    91,
      94,    97,    98,   104,   110,   114,   118,   124,   126,   127,
     131,   133,   135,   137,   139,   141,   143,   148,   152,   156,
     160,   164,   168,   171,   175,   181,   185,   189,   193,   197,
     201,   205,   209,   213,   215,   217,   221,   225,   229,   233,
     237,   241,   245,   249,   253,   254,   258,   260,   262,   266,
     268,   272,   276,   280,   284,   288,   291,   294,   298,   308,
     309,   315,   316,   322,   326,   332
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      57,     0,    -1,    -1,    57,    58,    48,    -1,    59,    58,
      -1,    59,    58,    45,    58,    -1,    60,    -1,    46,    57,
      47,    -1,    44,    49,    75,    50,    -1,    -1,    74,    -1,
      80,    -1,    61,    -1,    15,    51,    62,    -1,    15,    51,
      63,    -1,    15,    51,    64,    -1,    15,    51,    65,    -1,
      15,    51,    66,    -1,    15,    51,    67,    -1,    15,    51,
      68,    -1,    15,    51,    71,    -1,    15,    51,    72,    -1,
      15,    51,    69,    -1,    19,    -1,    21,    70,    -1,    23,
      70,    -1,    24,    70,    -1,    25,    70,    -1,    26,    70,
      -1,    27,    70,    -1,    15,    70,    -1,    -1,    70,    52,
      15,    53,    75,    -1,    70,    52,    15,    53,    77,    -1,
      15,    53,    77,    -1,    15,    53,    75,    -1,    30,    53,
      49,    73,    50,    -1,    31,    -1,    -1,    73,    52,    15,
      -1,    15,    -1,    75,    -1,    77,    -1,    76,    -1,    14,
      -1,    15,    -1,    17,    49,    75,    50,    -1,    75,     3,
      75,    -1,    75,     4,    75,    -1,    75,     5,    75,    -1,
      75,     6,    75,    -1,    75,     7,    75,    -1,     4,    75,
      -1,    49,    75,    50,    -1,     8,    77,    52,    77,     9,
      -1,    75,     8,    75,    -1,    75,    11,    75,    -1,    75,
       9,    75,    -1,    75,    10,    75,    -1,    75,    12,    75,
      -1,    15,    53,    75,    -1,    15,    53,    77,    -1,    16,
      53,    77,    -1,    16,    -1,    78,    -1,    77,     3,    77,
      -1,    77,     4,    77,    -1,    77,     3,    75,    -1,    77,
       5,    75,    -1,    77,     6,    75,    -1,    75,     3,    77,
      -1,    75,     4,    77,    -1,    75,     5,    77,    -1,    54,
      79,    55,    -1,    -1,    79,    52,    75,    -1,    75,    -1,
      39,    -1,    35,    52,    83,    -1,    37,    -1,    37,    52,
      30,    -1,    37,    52,    36,    -1,    37,    52,    15,    -1,
      37,    52,    16,    -1,    40,    52,    81,    -1,    36,    82,
      -1,    42,    18,    -1,    32,    53,    15,    -1,    32,    53,
      15,    52,    38,    53,    15,     6,    15,    -1,    -1,    82,
      52,    15,    53,    14,    -1,    -1,    83,    52,    15,    53,
      14,    -1,    15,    53,    14,    -1,    83,    52,    15,    53,
      18,    -1,    15,    53,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    53,    53,    54,    61,    62,    64,    65,    68,    71,
      72,    73,    74,    79,    88,    97,   106,   116,   126,   136,
     146,   156,   162,   176,   178,   181,   184,   187,   190,   193,
     199,   221,   222,   239,   261,   283,   291,   294,   297,   298,
     313,   331,   339,   352,   373,   374,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   402,   403,   404,   405,   406,
     409,   416,   429,   443,   459,   480,   503,   526,   547,   567,
     587,   607,   627,   650,   674,   675,   680,   687,   688,   689,
     690,   691,   692,   700,   715,   716,   717,   721,   731,   743,
     744,   753,   754,   759,   764,   769
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'+'", "'-'", "'*'", "'/'", "'^'", "'<'",
  "'>'", "GE", "LE", "NE", "UMINUS", "NUMBER", "VARIABLE", "VECVAR",
  "FUNC", "STR", "MARKER", "ELEMENT", "DRIFT", "DIPOLE", "SBEND",
  "QUADRUPOLE", "SEXTUPOLE", "OCTUPOLE", "MULTIPOLE", "SOLENOID",
  "COLLIMATOR", "LINE", "SEQUENCE", "PERIOD", "APERTURE", "FILENAME",
  "BEAM", "OPTION", "PRINT", "RANGE", "STOP", "USE", "VALUE", "ECHO",
  "PRINTF", "IF", "ELSE", "BEGN", "END", "';'", "'('", "')'", "':'", "','",
  "'='", "'{'", "'}'", "$accept", "input", "stmt", "if_clause",
  "atomic_stmt", "decl", "marker", "drift", "sbend", "quad", "sextupole",
  "octupole", "multipole", "extension", "parameters", "line", "sequence",
  "element_seq", "expr", "aexpr", "assignment", "vecexpr", "vect",
  "numbers", "command", "use_parameters", "option_parameters",
  "beam_parameters", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,    43,    45,    42,    47,    94,    60,    62,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,    59,    40,
      41,    58,    44,    61,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    56,    57,    57,    58,    58,    58,    58,    59,    60,
      60,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    70,    70,    70,    70,    71,    72,    73,    73,
      73,    74,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      76,    76,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    78,    79,    79,    79,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    81,    81,    82,
      82,    83,    83,    83,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     3,     2,     4,     1,     3,     4,     0,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     2,     2,     2,     2,     2,     2,
       2,     0,     5,     5,     3,     3,     5,     1,     0,     3,
       1,     1,     1,     1,     1,     1,     4,     3,     3,     3,
       3,     3,     2,     3,     5,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     3,     1,     1,     3,     1,
       3,     3,     3,     3,     3,     2,     2,     3,     9,     0,
       5,     0,     5,     3,     5,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     9,     1,     0,     0,    44,    45,    63,     0,     0,
      89,    79,    77,     0,     0,     0,     2,     0,    74,     0,
       9,     6,    12,    10,    41,    43,    42,    64,    11,    45,
      52,    63,     0,     0,     0,     0,     0,     0,    91,    85,
       0,     0,    86,     0,     9,     0,    76,     0,     3,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    23,
      31,    31,    31,    31,    31,    31,     0,    37,    13,    14,
      15,    16,    17,    18,    19,    22,    20,    21,    60,    61,
      62,     0,     0,    78,     0,    82,    83,    80,    81,     0,
      84,     0,     7,    53,     0,    73,     9,    47,    70,    48,
      71,    49,    72,    50,    51,    55,    57,    58,    56,    59,
      67,    65,    66,    68,    69,    47,    48,    49,     0,     0,
      30,    24,    25,    26,    27,    28,    29,     0,    46,     0,
       0,     0,     0,     8,    75,     5,    54,     0,     0,    38,
      93,    95,     0,     0,    87,    35,    34,     0,    40,     0,
       0,    90,     0,     0,    36,     0,    92,    94,     0,    32,
      33,    39,     0,     0,     0,    88
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,    19,    20,    21,    22,    78,    79,    80,    81,
      82,    83,    84,    85,   130,    86,    87,   159,    23,    24,
      25,    26,    27,    47,    28,   100,    39,    93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -50
static const short yypact[] =
{
     -50,    70,   -50,   176,    22,   -50,   -48,   -49,    26,   -32,
     -50,    27,   -50,    45,    81,    51,   -50,   176,   176,    56,
     133,   -50,   -50,   -50,   260,   -50,    90,   -50,   -50,   -50,
     -50,   -50,   260,    13,   213,    22,    22,   176,    87,    59,
      -9,    71,   -50,   176,   117,   192,   270,    25,   -50,    63,
      22,    22,    22,   176,   176,   176,   176,   176,   176,   176,
      22,    22,   176,   176,   176,   176,   176,    22,    98,   -50,
      98,    98,    98,    98,    98,    98,    62,   -50,   -50,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   260,    90,
      90,   202,    64,    66,   105,   -50,   -50,   -50,   -50,    69,
     -50,   212,   -50,   -50,   176,   -50,   133,   248,    84,   248,
      84,     1,   -50,     1,   -50,   -50,   -50,   -50,   -50,   -50,
     248,    84,    84,     1,     1,   278,   278,     1,    19,    73,
      75,    75,    75,    75,    75,    75,    75,    74,   -50,    54,
     113,    76,   115,   -50,   270,   -50,   -50,    22,   120,   121,
     -50,   -50,    85,   125,    88,   260,    90,    89,   -50,   -21,
      55,   -50,   107,    22,   -50,   128,   -50,   -50,    93,   260,
      90,   -50,   136,   149,   143,   -50
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -50,   146,   -18,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,   -50,   -50,   -29,   -50,   -50,   -50,   -50,    -3,
     -50,    31,   -50,   -50,   -50,   -50,   -50,   -50
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      30,    32,    49,    34,    36,    35,    95,    96,    54,    55,
      56,    57,    58,    59,    45,    46,    60,    61,    62,    63,
      38,    97,    60,    61,    62,    63,     3,    98,   146,   164,
       4,   165,    88,    32,    91,    33,     5,    29,    31,     8,
     101,   131,   132,   133,   134,   135,   136,   107,   109,   111,
     113,   114,   115,   116,   117,   118,   119,   120,    32,   123,
     124,   125,   126,   127,    32,    67,    89,    90,   150,   166,
       2,    17,   151,   167,     3,    37,    18,   104,     4,    40,
     105,   108,   110,   112,     5,     6,     7,     8,   145,    62,
      63,   121,   122,    60,    61,    62,    63,    41,   128,    42,
      43,   144,    92,    99,    48,     9,    10,    11,   106,    12,
      13,    94,    14,   129,    15,   137,    16,   139,   140,    17,
     141,     3,   142,   149,    18,     4,   147,   148,   152,   153,
     154,     5,     6,     7,     8,   157,   158,     3,   160,   161,
     162,     4,   163,   171,   155,   168,   172,     5,     6,     7,
       8,   173,     9,    10,    11,   174,    12,    13,   175,    14,
     169,    15,    44,    16,   102,     0,    17,     0,     9,    10,
      11,    18,    12,    13,     0,    14,     0,    15,   156,    16,
       3,     0,    17,     0,     4,     0,     0,    18,     0,     0,
       5,    29,     0,     8,   170,    64,    65,    66,    53,    54,
      55,    56,    57,    58,    59,    64,    65,    66,    53,    54,
      55,    56,    57,    58,    59,    64,    65,    66,    53,    54,
      55,    56,    57,    58,    59,    17,     0,     0,    68,     0,
       0,     0,    69,     0,    70,     0,    71,    72,    73,    74,
      75,     0,   103,    76,    77,     0,     0,     0,     0,     0,
       0,     0,   138,    52,    53,    54,    55,    56,    57,    58,
      59,     0,   143,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    64,    65,    66,    53,    54,    55,    56,
      57,    58,    59,    66,    53,    54,    55,    56,    57,    58,
      59
};

static const short yycheck[] =
{
       3,     4,    20,    51,    53,    53,    15,    16,     7,     8,
       9,    10,    11,    12,    17,    18,     3,     4,     5,     6,
      52,    30,     3,     4,     5,     6,     4,    36,     9,    50,
       8,    52,    35,    36,    37,     4,    14,    15,    16,    17,
      43,    70,    71,    72,    73,    74,    75,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    52,    35,    36,    14,    14,
       0,    49,    18,    18,     4,    49,    54,    52,     8,    52,
      55,    50,    51,    52,    14,    15,    16,    17,   106,     5,
       6,    60,    61,     3,     4,     5,     6,    52,    67,    18,
      49,   104,    15,    32,    48,    35,    36,    37,    45,    39,
      40,    52,    42,    15,    44,    53,    46,    53,    52,    49,
      15,     4,    53,    49,    54,     8,    53,    52,    15,    53,
      15,    14,    15,    16,    17,    15,    15,     4,    53,    14,
      52,     8,    53,    15,   147,    38,    53,    14,    15,    16,
      17,    15,    35,    36,    37,     6,    39,    40,    15,    42,
     163,    44,    16,    46,    47,    -1,    49,    -1,    35,    36,
      37,    54,    39,    40,    -1,    42,    -1,    44,   147,    46,
       4,    -1,    49,    -1,     8,    -1,    -1,    54,    -1,    -1,
      14,    15,    -1,    17,   163,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    49,    -1,    -1,    15,    -1,
      -1,    -1,    19,    -1,    21,    -1,    23,    24,    25,    26,
      27,    -1,    50,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    50,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     5,     6,     7,     8,     9,    10,    11,
      12
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    57,     0,     4,     8,    14,    15,    16,    17,    35,
      36,    37,    39,    40,    42,    44,    46,    49,    54,    58,
      59,    60,    61,    74,    75,    76,    77,    78,    80,    15,
      75,    16,    75,    77,    51,    53,    53,    49,    52,    82,
      52,    52,    18,    49,    57,    75,    75,    79,    48,    58,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       3,     4,     5,     6,     3,     4,     5,    52,    15,    19,
      21,    23,    24,    25,    26,    27,    30,    31,    62,    63,
      64,    65,    66,    67,    68,    69,    71,    72,    75,    77,
      77,    75,    15,    83,    52,    15,    16,    30,    36,    32,
      81,    75,    47,    50,    52,    55,    45,    75,    77,    75,
      77,    75,    77,    75,    75,    75,    75,    75,    75,    75,
      75,    77,    77,    75,    75,    75,    75,    75,    77,    15,
      70,    70,    70,    70,    70,    70,    70,    53,    50,    53,
      52,    15,    53,    50,    75,    58,     9,    53,    52,    49,
      14,    18,    15,    53,    15,    75,    77,    15,    15,    73,
      53,    14,    52,    53,    50,    52,    14,    18,    38,    75,
      77,    15,    53,    15,     6,    15
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value, Location);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yytype, yyvaluep, yylocationp)
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  YYLTYPE *yylerrsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
  yylsp = yyls;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, yylsp - yylen, yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 55 "parser.y"
    { 
	 if(ECHO_GRAMMAR) printf("input -> input stmt ';' \n");
       ;}
    break;

  case 4:
#line 61 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> IF '(' aexpr ')' stmt\n" ); execute = 1;;}
    break;

  case 5:
#line 63 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> IF '(' bool_expr ')' ELSE stmt \n" ); ;}
    break;

  case 6:
#line 64 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> atomic_stmt \n"); ;}
    break;

  case 7:
#line 65 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> '{' stmt ';' atomic_stmt '}' \n"); ;}
    break;

  case 8:
#line 68 "parser.y"
    {if( (yyvsp[-1].dval > 0) && (execute > 0) ) execute = 1; else execute = 0;;}
    break;

  case 10:
#line 72 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> expr\n"); ;}
    break;

  case 11:
#line 73 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> command"); ;}
    break;

  case 12:
#line 74 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> decl\n"); ;}
    break;

  case 13:
#line 80 "parser.y"
    {
	 if(execute)  {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE : marker\n");
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_MARKER);
	   params.flush();
	 }
       ;}
    break;

  case 14:
#line 89 "parser.y"
    {
	 if(execute) {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE : drift\n");
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_DRIFT);
	   params.flush();
	 }
       ;}
    break;

  case 15:
#line 98 "parser.y"
    {  
	 if(execute) {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE : sbend\n");
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_SBEND);
	   params.flush();
	 }
       ;}
    break;

  case 16:
#line 107 "parser.y"
    {
	 if(execute)       
	   {
	     if(ECHO_GRAMMAR) printf("decl -> VARIABLE : quad %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_QUAD);
	     params.flush();
	   }
       ;}
    break;

  case 17:
#line 117 "parser.y"
    {
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("decl -> VARIABLE : sext %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_SEXT);
	     params.flush();
	   }
       ;}
    break;

  case 18:
#line 127 "parser.y"
    {
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("VARIABLE : octupole %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_OCTUPOLE);
	     params.flush();
	   }
       ;}
    break;

  case 19:
#line 137 "parser.y"
    {
	 if(execute)
	   {	 
	     if(ECHO_GRAMMAR) printf("VARIABLE : multipole %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_MULT);
	     params.flush();	 
	   }
       ;}
    break;

  case 20:
#line 147 "parser.y"
    {
	 if(execute)
	   {
	     // create entry in the main table and add pointer to the parsed sequence
	     if(ECHO_GRAMMAR) printf("VARIABLE : LINE %s\n",yyvsp[-2].symp->name);
	     write_table(params,yyvsp[-2].symp->name,_LINE,new list<struct Element>(tmp_list));
	     tmp_list.erase(tmp_list.begin(), tmp_list.end());
	   }
       ;}
    break;

  case 21:
#line 157 "parser.y"
    {
	 if(execute)
	   {
	   }
       ;}
    break;

  case 22:
#line 163 "parser.y"
    {
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("decl -> VARIABLE : VARIABLE, %s  :  %s\n",yyvsp[-2].symp->name, typestr(yyvsp[0].ival));
	     if(yyvsp[0].ival != _NONE)
	       {
		 write_table(params,yyvsp[-2].symp->name,yyvsp[0].ival);
	       }
	     params.flush();
	   }
       ;}
    break;

  case 29:
#line 194 "parser.y"
    {
  if(DEBUG) print(params);
;}
    break;

  case 30:
#line 200 "parser.y"
    {
	      if(execute)
		{	 
		  if(ECHO_GRAMMAR) printf("extension : VARIABLE parameters   -- %s \n",yyvsp[-1].symp->name);
		  list<struct Element>::iterator it = element_lookup(yyvsp[-1].symp->name);
		  if(it == NULL)
		    {
		      if(VERBOSE) printf("type %s has not been defined\n",yyvsp[-1].symp->name);
		      yyval.ival = _NONE;
		    }
		  else
		    {
		      // inherit properties from the base type
		      yyval.ival = (*it).type;
		      inherit_properties(*it);
		    }
		  
		}
	    ;}
    break;

  case 32:
#line 223 "parser.y"
    {
	      if(execute)
		{
		  if(DEBUG) printf("parameters, VARIABLE(%s) = aexpr(%.10g)\n",yyvsp[-2].symp->name,yyvsp[0].dval);
		  if(!strcmp(yyvsp[-2].symp->name,"l")) { params.l = yyvsp[0].dval; params.lset = 1;} 
		  else
		    if(!strcmp(yyvsp[-2].symp->name,"k0")) { params.k0 = yyvsp[0].dval; params.k0set = 1;}
		    else 
		      if(!strcmp(yyvsp[-2].symp->name,"k1")) { params.k1 = yyvsp[0].dval; params.k1set = 1;} 
		      else
			if(!strcmp(yyvsp[-2].symp->name,"k2")) { params.k2 = yyvsp[0].dval; params.k2set = 1;}
			else 	
			  if(VERBOSE) printf("Warning : unknown parameter %s at line %d\n",yyvsp[-2].symp->name,yylsp[-2].first_line);
		  
		}
	    ;}
    break;

  case 33:
#line 240 "parser.y"
    {
	       if(execute) 
		 {
		   if(DEBUG) printf("params,VARIABLE = vecexpr (%d)\n",yyvsp[0].array->size);
		   if(!strcmp(yyvsp[-2].symp->name,"knl")) 
		     {
		       params.knlset = 1;
		       set_vector(params.knl,yyvsp[0].array);
		       delete[] yyvsp[0].array->data;
		     } 
		   else
		     if(!strcmp(yyvsp[-2].symp->name,"ksl")) 
		       {
			 params.kslset = 1;
			 set_vector(params.ksl,yyvsp[0].array);
			 delete[] yyvsp[0].array->data;
		       }
		     else 	  
		       if(VERBOSE) printf("unknown parameter %s\n",yyvsp[-2].symp->name);
		 }
	     ;}
    break;

  case 34:
#line 262 "parser.y"
    {
	       if(execute) 
		 {
		   if(DEBUG) printf("VARIABLE = vecexpr\n");
		   if(!strcmp(yyvsp[-2].symp->name,"knl")) 
		     {
		       params.knlset = 1;
		       set_vector(params.knl,yyvsp[0].array);
		       delete[] yyvsp[0].array->data;
		     } 
		   else
		     if(!strcmp(yyvsp[-2].symp->name,"ksl")) 
		       {
			 params.kslset = 1;
			 set_vector(params.ksl,yyvsp[0].array);
			 delete[] yyvsp[0].array->data;
		       }
		     else 	  
		       if(VERBOSE) printf("unknown parameter %s\n",yyvsp[-2].symp->name);
		 }         
	     ;}
    break;

  case 35:
#line 284 "parser.y"
    {
	      if(execute)
		{
		  if(DEBUG) printf("VARIABLE = aexpr(%.10g)\n",yyvsp[0].dval);
		}
	    ;}
    break;

  case 39:
#line 299 "parser.y"
    {
		if(execute)
		  {
		    if(DEBUG) printf("matched sequence element, %s\n",yyvsp[0].symp->name);
		    // add to temporary element sequence
		    {
		      struct Element e;
		      e.name = yyvsp[0].symp->name;
		      e.type = _LINE;
		      e.lst = NULL;
		      tmp_list.push_back(e);
		    }
		  }
	      ;}
    break;

  case 40:
#line 314 "parser.y"
    {
		if(execute)
		  {
		    if(DEBUG) printf("matched last sequence element, %s\n",yyvsp[0].symp->name);
		    // add to temporary element sequence
		    {
		      struct Element e;
		      e.name = yyvsp[0].symp->name;
		      e.type = _LINE;
		      e.lst = NULL;
		      tmp_list.push_back(e);
		    }
		  }
	      ;}
    break;

  case 41:
#line 332 "parser.y"
    { // check type ??
	 if(ECHO_GRAMMAR) printf("expr -> aexpr\n");
	 if(execute) 
	   {
	     if(INTERACTIVE) printf ("\t%.10g\n", yyvsp[0].dval); yyval.dval=yyvsp[0].dval;
	   }
       ;}
    break;

  case 42:
#line 340 "parser.y"
    {
	 if(ECHO_GRAMMAR) printf("expr -> vecexpr\n");
	 if(execute)
	   {
	     if(INTERACTIVE)
	       for(int i=0;i<yyvsp[0].array->size;i++)
		 {
		   printf(" %.10g ",yyvsp[0].array->data[i]);
		 }
	     yyval.dval = 0;
	   } 
       ;}
    break;

  case 43:
#line 353 "parser.y"
    { // check type
	 if(ECHO_GRAMMAR) printf("expr -> assignment\n");
	 if(execute)
	   {
	     if(INTERACTIVE) {
	       if(yyvsp[0].symp->type == _ARRAY)
		 {
		   for(list<double>::iterator it = yyvsp[0].symp->array.begin();
		       it!=yyvsp[0].symp->array.end();it++)
		     printf ("\t%.10g", (*it));
		   printf("\n");
		 }
	       else
		 printf ("\t%.10g\n", yyvsp[0].symp->value);
	     } 
	     yyval.dval=0;
	   }
       ;}
    break;

  case 44:
#line 373 "parser.y"
    { yyval.dval = yyvsp[0].dval;                         ;}
    break;

  case 45:
#line 375 "parser.y"
    { 
	   //check type ??
	   yyval.dval = yyvsp[0].symp->value;        
          ;}
    break;

  case 46:
#line 379 "parser.y"
    { yyval.dval = (*(yyvsp[-3].symp->funcptr))(yyvsp[-1].dval);       ;}
    break;

  case 47:
#line 380 "parser.y"
    { yyval.dval = yyvsp[-2].dval + yyvsp[0].dval;                    ;}
    break;

  case 48:
#line 381 "parser.y"
    { yyval.dval = yyvsp[-2].dval - yyvsp[0].dval;                    ;}
    break;

  case 49:
#line 382 "parser.y"
    { yyval.dval = yyvsp[-2].dval * yyvsp[0].dval;                    ;}
    break;

  case 50:
#line 383 "parser.y"
    { yyval.dval = yyvsp[-2].dval / yyvsp[0].dval;                    ;}
    break;

  case 51:
#line 384 "parser.y"
    { yyval.dval = pow(yyvsp[-2].dval,yyvsp[0].dval);                 ;}
    break;

  case 52:
#line 385 "parser.y"
    { yyval.dval = -yyvsp[0].dval; ;}
    break;

  case 53:
#line 386 "parser.y"
    { yyval.dval = yyvsp[-1].dval;                         ;}
    break;

  case 54:
#line 388 "parser.y"
    {
	   if(yyvsp[-3].array->size == yyvsp[-1].array->size)
	     {
	       yyval.dval = 0;
	       for(int i=0;i<yyvsp[-3].array->size;i++)
		 yyval.dval += yyvsp[-3].array->data[i] * yyvsp[-1].array->data[i];
	     }
	   else
	     {
	       if(VERBOSE) printf("vector dimensions do not match");
	       yyval.dval = _undefined;
	     }
         ;}
    break;

  case 55:
#line 402 "parser.y"
    { yyval.dval = (yyvsp[-2].dval < yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 56:
#line 403 "parser.y"
    { yyval.dval = (yyvsp[-2].dval <= yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 57:
#line 404 "parser.y"
    { yyval.dval = (yyvsp[-2].dval > yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 58:
#line 405 "parser.y"
    { yyval.dval = (yyvsp[-2].dval >= yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 59:
#line 406 "parser.y"
    { yyval.dval = (yyvsp[-2].dval != yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 60:
#line 410 "parser.y"
    {
		if(execute)
		  {
		    yyvsp[-2].symp->value = yyvsp[0].dval; yyval.symp=yyvsp[-2].symp;       
		  }
	      ;}
    break;

  case 61:
#line 417 "parser.y"
    {
		if(execute)
		  {
		    yyvsp[-2].symp->array.erase(yyvsp[-2].symp->array.begin(),yyvsp[-2].symp->array.end());
		    for(int i=0;i<yyvsp[0].array->size;i++)
		      yyvsp[-2].symp->array.push_back(yyvsp[0].array->data[i]);
		    yyvsp[-2].symp->type = _ARRAY;
		    yyval.symp = yyvsp[-2].symp;
		    delete[] yyvsp[0].array->data;
		    yyvsp[0].array->size = 0;
		  }
              ;}
    break;

  case 62:
#line 430 "parser.y"
    {
		if(execute)
		  {
		    yyvsp[-2].symp->array.erase(yyvsp[-2].symp->array.begin(),yyvsp[-2].symp->array.end());
		    for(int i=0;i<yyvsp[0].array->size;i++)
		      yyvsp[-2].symp->array.push_back(yyvsp[0].array->data[i]);
		    yyval.symp = yyvsp[-2].symp;
		    delete[] yyvsp[0].array->data;
		    yyvsp[0].array->size = 0;
		  }
              ;}
    break;

  case 63:
#line 444 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->data = new double[yyvsp[0].symp->array.size()];
	      yyval.array->size = yyvsp[0].symp->array.size();
	      //array_list.push_back($$);
	      list<double>::iterator it = 0;
	      int i = 0;
	      for(it=yyvsp[0].symp->array.begin();it!=yyvsp[0].symp->array.end();it++)
		{
		  yyval.array->data[i++] = (*it);
		}
	    }
        ;}
    break;

  case 64:
#line 460 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->data = new double[yyvsp[0].array->size];
	      yyval.array->size = yyvsp[0].array->size;
	      //array_list.push_back($$);
	      int i = 0;
	      for(int i=0;i<yyvsp[0].array->size;i++)
		{
		  yyval.array->data[i] = yyvsp[0].array->data[i];
		}
	      
	      
	      // erase data in vect
	      
	      delete[] yyvsp[0].array->data;
	      yyvsp[0].array->size = 0;
	    }
	;}
    break;

  case 65:
#line 481 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = (yyvsp[-2].array->size < yyvsp[0].array->size )? yyvsp[-2].array->size : yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      int i = 0;
	      for(int i=0;i<yyval.array->size;i++)
		{
		  yyval.array->data[i] = yyvsp[-2].array->data[i] + yyvsp[0].array->data[i];
		}
	      
	      
	      // erase data in vect
	      
	      delete[] yyvsp[-2].array->data;
	      delete[] yyvsp[0].array->data;
	      yyvsp[-2].array->size = 0;
	      yyvsp[0].array->size = 0;
	    }
        ;}
    break;

  case 66:
#line 504 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = (yyvsp[-2].array->size < yyvsp[0].array->size )? yyvsp[-2].array->size : yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      int i = 0;
	      for(int i=0;i<yyval.array->size;i++)
		{
		  yyval.array->data[i] = yyvsp[-2].array->data[i] - yyvsp[0].array->data[i];
		}
	      
	      
	      // erase data in vect
	      
	      delete[] yyvsp[-2].array->data;
	      delete[] yyvsp[0].array->data;
	      yyvsp[-2].array->size = 0;
	      yyvsp[0].array->size = 0;
	    }
	;}
    break;

  case 67:
#line 527 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[-2].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      int i = 0;
	      for(int i=0;i<yyval.array->size;i++)
		{
		  yyval.array->data[i] = yyvsp[-2].array->data[i] + yyvsp[0].dval;
		}
	      
	      // erase data in vect
	      
	      delete[] yyvsp[-2].array->data;
	      yyvsp[-2].array->size = 0;
	    }
	;}
    break;

  case 68:
#line 548 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[-2].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      int i = 0;
	      for(int i=0;i<yyval.array->size;i++)
		{
		  yyval.array->data[i] = yyvsp[-2].array->data[i] * yyvsp[0].dval;
		}
	      
	      // erase data in vect
	      
	      delete[] yyvsp[-2].array->data;
	      yyvsp[-2].array->size = 0;
	    }
	;}
    break;

  case 69:
#line 568 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[-2].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      int i = 0;
	      for(int i=0;i<yyval.array->size;i++)
		{
		  yyval.array->data[i] = yyvsp[-2].array->data[i] / yyvsp[0].dval;
		}
	      
	      // erase data in vect
	      
	      delete[] yyvsp[-2].array->data;
	      yyvsp[-2].array->size = 0;
	    }
	;}
    break;

  case 70:
#line 588 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      int i = 0;
	      for(int i=0;i<yyval.array->size;i++)
		{
		  yyval.array->data[i] = yyvsp[0].array->data[i] + yyvsp[-2].dval;
		}
	      
	      // erase data in vect
	      
	      delete[] yyvsp[0].array->data;
	      yyvsp[0].array->size = 0;
	    }
	;}
    break;

  case 71:
#line 608 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      int i = 0;
	      for(int i=0;i<yyval.array->size;i++)
		{
		  yyval.array->data[i] = yyvsp[-2].dval - yyvsp[0].array->data[i];
		}
	      
	      // erase data in vect
	      
	      delete[] yyvsp[0].array->data;
	      yyvsp[0].array->size = 0;
	    }
	;}
    break;

  case 72:
#line 628 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      int i = 0;
	      for(int i=0;i<yyval.array->size;i++)
		{
		  yyval.array->data[i] = yyvsp[-2].dval * yyvsp[0].array->data[i];
		}
	      
	      // erase data in vect
	      
	      delete[] yyvsp[0].array->data;
	      yyvsp[0].array->size = 0;
	    }
	;}
    break;

  case 73:
#line 651 "parser.y"
    {
  if(execute)
    {
      //printf("matched vector of size %d\n",_tmparray.size());
      yyval.array = new struct Array;
      yyval.array->data = new double[_tmparray.size()];
      yyval.array->size = _tmparray.size();
      
      //array_list.push_back(a);
      
      list<double>::iterator it;
      
      int i=0;
      for(it=_tmparray.begin();it!=_tmparray.end();it++)
	{
	  yyval.array->data[i++] = (*it);
	}
      
      _tmparray.erase(_tmparray.begin(),_tmparray.end());
    }
;}
    break;

  case 75:
#line 676 "parser.y"
    {
	    if(execute)
	      _tmparray.push_back(yyvsp[0].dval);
          ;}
    break;

  case 76:
#line 681 "parser.y"
    {
	   if(execute)
	     _tmparray.push_back(yyvsp[0].dval);
        ;}
    break;

  case 77:
#line 687 "parser.y"
    { if(execute) quit(); ;}
    break;

  case 79:
#line 689 "parser.y"
    { if(execute) print( element_list ); ;}
    break;

  case 80:
#line 690 "parser.y"
    { if(execute) print( beamline_list); ;}
    break;

  case 81:
#line 691 "parser.y"
    { if(execute) print(options); ;}
    break;

  case 82:
#line 693 "parser.y"
    {
	    if(execute)
	      {
		printf("\t");
		printf("\t%.10g\n",yyvsp[0].symp->value);
	      }
	  ;}
    break;

  case 83:
#line 701 "parser.y"
    {
	    if(execute)
	      {
		printf("\t");
		
		list<double>::iterator it;
		for(it=yyvsp[0].symp->array.begin();it!=yyvsp[0].symp->array.end();it++)
		  {
		    printf("  %.10g ",(*it));
		  }
		
		printf("\n");
	      } 
	  ;}
    break;

  case 84:
#line 715 "parser.y"
    { if(execute) expand_line(current_line,current_start, current_end);;}
    break;

  case 86:
#line 717 "parser.y"
    { if(execute) printf("%s\n",yyvsp[0].str); ;}
    break;

  case 87:
#line 722 "parser.y"
    {
		    if(execute)
		      {
			yyval.str = yyvsp[0].symp->name;
			current_line = yyvsp[0].symp->name;
			current_start = NULL;
			current_end = NULL;
		      }
                  ;}
    break;

  case 88:
#line 732 "parser.y"
    {
		    if(execute)
		      {
			yyval.str = yyvsp[-6].symp->name;
			current_line = yyvsp[-6].symp->name;
			current_start = yyvsp[-2].symp->name;
			current_end = yyvsp[0].symp->name;
		      }
		  ;}
    break;

  case 90:
#line 745 "parser.y"
    {
		      if(execute)
			{
			  if(!strcmp(yyvsp[-2].symp->name,"echo")) options.echo = (int)yyvsp[0].dval;
			}
		    ;}
    break;

  case 92:
#line 755 "parser.y"
    {
		    if(execute)
		      if(!strcmp(yyvsp[-2].symp->name,"nparticles")) options.nparticles = (int)yyvsp[0].dval;
		  ;}
    break;

  case 93:
#line 760 "parser.y"
    {
		    if(execute)
		      if(!strcmp(yyvsp[-2].symp->name,"nparticles")) options.nparticles = (int)yyvsp[0].dval;
		  ;}
    break;

  case 94:
#line 765 "parser.y"
    {
		    if(execute)
		      if(!strcmp(yyvsp[-2].symp->name,"particle")) strcpy(options.particle,yyvsp[0].str);
		  ;}
    break;

  case 95:
#line 770 "parser.y"
    {
		    if(execute)
		      if(!strcmp(yyvsp[-2].symp->name,"particle")) strcpy(options.particle ,yyvsp[0].str);
		  ;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 2189 "parser.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }

  yylerrsp = yylsp;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp, yylsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	  *++yylerrsp = yylloc;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  yylerrsp = yylsp;
  *++yylerrsp = yyloc;
  yylsp -= yylen;
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
  YYLLOC_DEFAULT (yyloc, yylsp, yylerrsp - yylsp);
  *++yylsp = yyloc;

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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 776 "parser.y"




int yyerror(char *s)
{
  printf(s);
}

int yywrap()
{
	return 1;
}




