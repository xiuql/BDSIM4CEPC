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
#define YYLSP_NEEDED 0



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
     UPLUS = 262,
     NUMBER = 263,
     VARIABLE = 264,
     VECVAR = 265,
     FUNC = 266,
     STR = 267,
     MARKER = 268,
     ELEMENT = 269,
     DRIFT = 270,
     DIPOLE = 271,
     SBEND = 272,
     QUADRUPOLE = 273,
     SEXTUPOLE = 274,
     OCTUPOLE = 275,
     MULTIPOLE = 276,
     SOLENOID = 277,
     COLLIMATOR = 278,
     RCOL = 279,
     ECOL = 280,
     LINE = 281,
     SEQUENCE = 282,
     SPOILER = 283,
     ABSORBER = 284,
     LASER = 285,
     TRANSFORM3D = 286,
     PERIOD = 287,
     APERTURE = 288,
     FILENAME = 289,
     GAS = 290,
     PIPE = 291,
     BEAM = 292,
     OPTION = 293,
     PRINT = 294,
     RANGE = 295,
     STOP = 296,
     USE = 297,
     VALUE = 298,
     ECHO = 299,
     PRINTF = 300,
     SAMPLE = 301,
     CSAMPLE = 302,
     IF = 303,
     ELSE = 304,
     BEGN = 305,
     END = 306,
     FOR = 307,
     CUT = 308
   };
#endif
#define GE 258
#define LE 259
#define NE 260
#define UMINUS 261
#define UPLUS 262
#define NUMBER 263
#define VARIABLE 264
#define VECVAR 265
#define FUNC 266
#define STR 267
#define MARKER 268
#define ELEMENT 269
#define DRIFT 270
#define DIPOLE 271
#define SBEND 272
#define QUADRUPOLE 273
#define SEXTUPOLE 274
#define OCTUPOLE 275
#define MULTIPOLE 276
#define SOLENOID 277
#define COLLIMATOR 278
#define RCOL 279
#define ECOL 280
#define LINE 281
#define SEQUENCE 282
#define SPOILER 283
#define ABSORBER 284
#define LASER 285
#define TRANSFORM3D 286
#define PERIOD 287
#define APERTURE 288
#define FILENAME 289
#define GAS 290
#define PIPE 291
#define BEAM 292
#define OPTION 293
#define PRINT 294
#define RANGE 295
#define STOP 296
#define USE 297
#define VALUE 298
#define ECHO 299
#define PRINTF 300
#define SAMPLE 301
#define CSAMPLE 302
#define IF 303
#define ELSE 304
#define BEGN 305
#define END 306
#define FOR 307
#define CUT 308




/* Copy the first part of user declarations.  */
#line 7 "parser.y"


  const int DEBUG = 0; // print debug info like parsing output etc.
  const int ECHO_GRAMMAR = 0; // print grammar rule expamsion (for debugging)
  const int VERBOSE = 0; // print warnings and errors
  const int VERBOSE_EXPAND = 0; // print the process of line expansion 
  const int INTERACTIVE = 0; // print output of commands (like in interactive mode)

#include "parser.h"

  int execute = 1;
  int element_count = 1; // for samplers , ranges etc.



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
#line 23 "parser.y"
typedef union YYSTYPE {
  double dval;
  int ival;
  struct symtab *symp;
  char *str;
  struct Array *array;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 205 "parser.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 217 "parser.tab.c"

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
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   459

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  36
/* YYNRULES -- Number of rules. */
#define YYNRULES  133
/* YYNRULES -- Number of states. */
#define YYNSTATES  258

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      62,    63,     5,     3,    65,     4,     2,     6,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    64,    61,
       8,    66,     9,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    67,     2,    68,     7,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,     2,    70,     2,     2,     2,     2,
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
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     8,    11,    16,    18,    22,    27,
      28,    30,    32,    34,    38,    42,    46,    50,    54,    58,
      62,    66,    70,    74,    78,    82,    86,    90,    94,    96,
      99,   102,   105,   108,   111,   114,   117,   120,   123,   126,
     129,   132,   133,   139,   145,   149,   153,   159,   163,   169,
     171,   172,   176,   182,   188,   190,   194,   198,   200,   202,
     204,   206,   208,   213,   217,   221,   225,   229,   233,   236,
     239,   243,   249,   253,   257,   261,   265,   269,   274,   278,
     282,   286,   288,   290,   294,   298,   302,   306,   310,   314,
     318,   322,   326,   327,   331,   333,   335,   339,   341,   345,
     349,   353,   357,   361,   365,   368,   372,   376,   380,   384,
     394,   398,   405,   409,   413,   419,   425,   429,   431,   435,
     439,   445,   451,   459,   465,   471,   475,   476,   482,   486,
     487,   493,   497,   503
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      72,     0,    -1,    -1,    72,    73,    61,    -1,    74,    73,
      -1,    74,    73,    56,    73,    -1,    75,    -1,    57,    72,
      58,    -1,    55,    62,    95,    63,    -1,    -1,    94,    -1,
     100,    -1,    76,    -1,    16,    64,    77,    -1,    16,    64,
      78,    -1,    16,    64,    79,    -1,    16,    64,    80,    -1,
      16,    64,    81,    -1,    16,    64,    82,    -1,    16,    64,
      85,    -1,    16,    64,    84,    -1,    16,    64,    83,    -1,
      16,    64,    88,    -1,    16,    64,    86,    -1,    16,    64,
      87,    -1,    16,    64,    91,    -1,    16,    64,    92,    -1,
      16,    64,    89,    -1,    20,    -1,    22,    90,    -1,    24,
      90,    -1,    25,    90,    -1,    26,    90,    -1,    27,    90,
      -1,    28,    90,    -1,    32,    90,    -1,    31,    90,    -1,
      37,    90,    -1,    38,    90,    -1,    21,    90,    -1,    16,
      90,    -1,    -1,    90,    65,    16,    66,    95,    -1,    90,
      65,    16,    66,    97,    -1,    16,    66,    97,    -1,    16,
      66,    95,    -1,    90,    65,    16,    66,    19,    -1,    16,
      66,    19,    -1,    33,    66,    62,    93,    63,    -1,    34,
      -1,    -1,    93,    65,    16,    -1,    93,    65,    16,     5,
      15,    -1,    93,    65,    15,     5,    16,    -1,    16,    -1,
      16,     5,    15,    -1,    15,     5,    16,    -1,    95,    -1,
      97,    -1,    96,    -1,    15,    -1,    16,    -1,    18,    62,
      95,    63,    -1,    95,     3,    95,    -1,    95,     4,    95,
      -1,    95,     5,    95,    -1,    95,     6,    95,    -1,    95,
       7,    95,    -1,     4,    95,    -1,     3,    95,    -1,    62,
      95,    63,    -1,     8,    97,    65,    97,     9,    -1,    95,
       8,    95,    -1,    95,    11,    95,    -1,    95,     9,    95,
      -1,    95,    10,    95,    -1,    95,    12,    95,    -1,    16,
      67,    16,    68,    -1,    16,    66,    95,    -1,    16,    66,
      97,    -1,    17,    66,    97,    -1,    17,    -1,    98,    -1,
      97,     3,    97,    -1,    97,     4,    97,    -1,    97,     3,
      95,    -1,    97,     5,    95,    -1,    97,     6,    95,    -1,
      95,     3,    97,    -1,    95,     4,    97,    -1,    95,     5,
      97,    -1,    69,    99,    70,    -1,    -1,    99,    65,    95,
      -1,    95,    -1,    48,    -1,    44,    65,   106,    -1,    46,
      -1,    46,    65,    33,    -1,    46,    65,    45,    -1,    46,
      65,    16,    -1,    46,    65,    17,    -1,    49,    65,   101,
      -1,    45,    65,   105,    -1,    51,    19,    -1,    53,    65,
     102,    -1,    54,    65,   103,    -1,    42,    65,   104,    -1,
      39,    66,    16,    -1,    39,    66,    16,    65,    47,    66,
      16,     6,    16,    -1,    47,    66,    16,    -1,    47,    66,
      16,    67,    15,    68,    -1,    16,    66,    95,    -1,    16,
      66,    19,    -1,   103,    65,    16,    66,    95,    -1,   103,
      65,    16,    66,    19,    -1,   102,    65,   103,    -1,   102,
      -1,    16,    66,    95,    -1,    16,    66,    19,    -1,   104,
      65,    16,    66,    95,    -1,   104,    65,    16,    66,    19,
      -1,   104,    65,    47,    66,    16,     6,    16,    -1,    47,
      66,    16,     6,    16,    -1,   104,    65,    47,    66,    16,
      -1,    47,    66,    16,    -1,    -1,   105,    65,    16,    66,
      95,    -1,    16,    66,    95,    -1,    -1,   106,    65,    16,
      66,    95,    -1,    16,    66,    95,    -1,   106,    65,    16,
      66,    19,    -1,    16,    66,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    60,    60,    61,    68,    69,    71,    72,    75,    78,
      79,    80,    81,    86,    95,   104,   113,   123,   133,   143,
     153,   163,   173,   183,   193,   203,   213,   219,   233,   235,
     238,   241,   244,   247,   250,   256,   259,   262,   265,   268,
     271,   293,   294,   346,   368,   390,   397,   430,   463,   466,
     469,   470,   485,   501,   517,   532,   548,   567,   575,   588,
     609,   610,   615,   616,   617,   618,   619,   620,   621,   622,
     623,   624,   639,   640,   641,   642,   643,   644,   651,   664,
     677,   691,   707,   728,   751,   774,   795,   815,   835,   855,
     875,   898,   922,   923,   928,   935,   936,   937,   938,   939,
     940,   948,   963,   964,   965,   966,   976,   986,  1000,  1010,
    1024,  1030,  1041,  1053,  1061,  1075,  1081,  1086,  1093,  1105,
    1118,  1131,  1143,  1148,  1153,  1158,  1165,  1166,  1171,  1178,
    1179,  1184,  1189,  1194
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'+'", "'-'", "'*'", "'/'", "'^'", "'<'",
  "'>'", "GE", "LE", "NE", "UMINUS", "UPLUS", "NUMBER", "VARIABLE",
  "VECVAR", "FUNC", "STR", "MARKER", "ELEMENT", "DRIFT", "DIPOLE", "SBEND",
  "QUADRUPOLE", "SEXTUPOLE", "OCTUPOLE", "MULTIPOLE", "SOLENOID",
  "COLLIMATOR", "RCOL", "ECOL", "LINE", "SEQUENCE", "SPOILER", "ABSORBER",
  "LASER", "TRANSFORM3D", "PERIOD", "APERTURE", "FILENAME", "GAS", "PIPE",
  "BEAM", "OPTION", "PRINT", "RANGE", "STOP", "USE", "VALUE", "ECHO",
  "PRINTF", "SAMPLE", "CSAMPLE", "IF", "ELSE", "BEGN", "END", "FOR", "CUT",
  "';'", "'('", "')'", "':'", "','", "'='", "'['", "']'", "'{'", "'}'",
  "$accept", "input", "stmt", "if_clause", "atomic_stmt", "decl", "marker",
  "drift", "sbend", "quad", "sextupole", "octupole", "multipole", "ecol",
  "rcol", "laser", "transform3d", "element", "extension", "parameters",
  "line", "sequence", "element_seq", "expr", "aexpr", "assignment",
  "vecexpr", "vect", "numbers", "command", "use_parameters",
  "sample_options", "csample_options", "gas_options", "option_parameters",
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
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,    59,    40,    41,    58,    44,    61,    91,    93,   123,
     125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    71,    72,    72,    73,    73,    73,    73,    74,    75,
      75,    75,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    90,    90,    90,    90,    90,    90,    91,    92,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    94,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    96,    96,
      96,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    98,    99,    99,    99,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   101,   101,
     102,   102,   103,   103,   103,   103,   103,   103,   104,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   105,   106,
     106,   106,   106,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     3,     2,     4,     1,     3,     4,     0,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     0,     5,     5,     3,     3,     5,     3,     5,     1,
       0,     3,     5,     5,     1,     3,     3,     1,     1,     1,
       1,     1,     4,     3,     3,     3,     3,     3,     2,     2,
       3,     5,     3,     3,     3,     3,     3,     4,     3,     3,
       3,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     3,     1,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     9,
       3,     6,     3,     3,     5,     5,     3,     1,     3,     3,
       5,     5,     7,     5,     5,     3,     0,     5,     3,     0,
       5,     3,     5,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     9,     1,     0,     0,     0,    60,    61,    81,     0,
       0,     0,     0,    97,    95,     0,     0,     0,     0,     0,
       2,     0,    92,     0,     9,     6,    12,    10,    57,    59,
      58,    82,    11,    61,    69,    68,    81,     0,     0,     0,
       0,     0,     0,     0,     0,   129,   126,     0,     0,   104,
       0,     0,     0,     9,     0,    94,     0,     3,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    28,    41,
      41,    41,    41,    41,    41,    41,    41,    41,     0,    49,
      41,    41,    13,    14,    15,    16,    17,    18,    21,    20,
      19,    23,    24,    22,    27,    25,    26,    78,    79,     0,
      80,     0,     0,     0,   107,     0,    96,     0,   103,   100,
     101,    98,    99,     0,   102,     0,   105,     0,   117,   106,
       0,     7,    70,     0,    91,     9,    63,    88,    64,    89,
      65,    90,    66,    67,    72,    74,    75,    73,    76,    85,
      83,    84,    86,    87,    63,    64,    65,     0,     0,    40,
      39,    29,    30,    31,    32,    33,    34,    36,    35,     0,
      37,    38,    77,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,    93,     5,    71,
       0,     0,    50,   119,   118,   125,     0,     0,   133,   131,
       0,   128,     0,   108,   110,   113,   112,   116,     0,    47,
      45,    44,     0,     0,    54,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,     0,   123,
     121,   120,   124,   132,   130,   127,     0,     0,   115,   114,
      46,    42,    43,    56,    55,     0,    51,     0,     0,   111,
       0,     0,   122,     0,    53,    52,     0,   109
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,    23,    24,    25,    26,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   159,
     105,   106,   215,    27,    28,    29,    30,    31,    56,    32,
     124,   128,   129,   114,   118,   116
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -57
static const short yypact[] =
{
     -57,    83,   -57,    30,    30,   225,   -57,    13,   -56,   -45,
     -33,   -18,    10,    17,   -57,    20,    70,    37,    42,    47,
     -57,    30,    30,    50,   219,   -57,   -57,   -57,   437,   -57,
     160,   -57,   -57,    46,   -57,   -57,   -57,   437,    19,   379,
     225,   107,   225,    30,   -12,   108,   110,    77,    94,   -57,
      88,   -11,    30,   140,   241,   447,   -44,   -57,    85,   225,
     225,   225,    30,    30,    30,    30,    30,    30,    30,   225,
     225,    30,    30,    30,    30,    30,   225,   123,   -57,   123,
     123,   123,   123,   123,   123,   123,   123,   123,    76,   -57,
     123,   123,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   437,   160,    78,
     160,   302,    81,    84,    86,    87,    89,    93,    95,   -57,
     -57,   -57,   -57,   101,   -57,   102,   -57,   104,    96,   112,
     312,   -57,   -57,    30,   -57,   219,   290,     8,   290,     8,
      43,   -57,    43,   -57,   -57,   -57,   -57,   -57,   -57,   290,
       8,     8,    43,    43,   380,   380,    43,     3,   106,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   111,
     113,   113,   -57,   -57,   274,   133,    -5,   322,   159,    30,
     163,   165,   167,   331,   -11,   174,   -57,   447,   -57,   -57,
      12,   176,    28,   -57,   447,   190,   134,   135,   -57,   447,
     137,   447,   138,   141,   132,   -57,   447,   112,   139,   -57,
     437,   160,   142,   202,   205,    25,   195,   340,   196,   358,
      30,   166,   200,   364,   100,   203,   209,   -57,   105,   -57,
     -57,   447,   212,   -57,   447,   447,   164,   157,   -57,   447,
     -57,   437,   160,   -57,   -57,   226,   227,   222,   223,   -57,
     238,   240,   -57,   250,   -57,   -57,   242,   -57
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -57,   237,   -21,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   348,
     -57,   -57,   -57,   -57,    -3,   -57,    36,   -57,   -57,   -57,
     -57,   216,    75,   -57,   -57,   -57
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short yytable[] =
{
      34,    35,    37,    58,   112,   127,    69,    70,    71,    72,
      42,   196,   189,    71,    72,     3,     4,    43,    54,    55,
       5,   133,    69,    70,    71,    72,   134,     6,    33,    36,
       9,   209,    44,     3,     4,   113,   125,   107,     5,    37,
     111,    38,   197,   213,   214,     6,    33,    45,     9,   130,
      63,    64,    65,    66,    67,    68,   136,   138,   140,   142,
     143,   144,   145,   146,   147,   148,   149,    37,   152,   153,
     154,   155,   156,    37,    21,    46,   108,    39,   110,    40,
      41,    22,    47,     2,    76,    48,     3,     4,   227,    49,
     228,     5,    21,   119,   120,   137,   139,   141,     6,     7,
       8,     9,    50,     3,     4,   150,   151,    51,     5,    52,
     121,    57,   157,    41,   188,     6,    33,    36,     9,   240,
     245,   246,   122,   109,   115,    10,   117,    11,    12,    13,
     187,    14,    15,   123,    16,   125,    17,    18,    19,   158,
      20,   135,   169,     3,     4,    21,   172,   174,     5,   195,
     175,   176,    22,   177,   178,     6,     7,     8,     9,   179,
     180,   184,    21,    69,    70,    71,    72,   181,   182,    22,
     183,   194,   190,   192,   199,   200,   201,   185,   191,   202,
     206,   203,    10,   204,    11,    12,    13,   210,    14,    15,
     208,    16,   212,    17,    18,    19,   216,    20,   131,   222,
     217,   218,    21,   219,   220,   223,   221,   225,   224,    22,
     226,   229,   232,   236,   231,   237,   234,   235,   247,   243,
     239,   241,     3,     4,   244,   249,   211,     5,     3,     4,
     248,   250,   251,     5,     6,     7,     8,     9,   252,   253,
       6,    33,    36,     9,    73,    74,    75,    62,    63,    64,
      65,    66,    67,    68,   254,   255,   256,    53,   257,   207,
     242,    10,     0,    11,    12,    13,   126,    14,    15,     0,
      16,     0,    17,    18,    19,     0,    20,     3,     4,     0,
       0,    21,     5,     0,     0,     0,     0,    21,    22,     6,
      33,     0,     9,   193,    22,    61,    62,    63,    64,    65,
      66,    67,    68,     0,   132,    73,    74,    75,    62,    63,
      64,    65,    66,    67,    68,    73,    74,    75,    62,    63,
      64,    65,    66,    67,    68,     3,     4,     0,     0,     0,
       5,     0,     0,     0,     3,     4,    21,     6,    33,     5,
       9,   198,     0,     3,     4,     0,     6,    33,     5,     9,
     205,     0,     0,     0,     0,     6,    33,     0,     9,   230,
       0,     3,     4,     0,     0,   173,     5,     3,     4,     0,
       0,     0,     5,     6,    33,   186,     9,   233,     0,     6,
      33,     0,     9,   238,    21,    75,    62,    63,    64,    65,
      66,    67,    68,    21,     0,    77,     0,     0,     0,    78,
      79,    80,    21,    81,    82,    83,    84,    85,     0,     0,
      86,    87,    88,    89,     0,     0,    90,    91,     0,     0,
      21,     0,     0,     0,     0,     0,    21,   160,   161,   162,
     163,   164,   165,   166,   167,   168,     0,     0,   170,   171,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      73,    74,    75,    62,    63,    64,    65,    66,    67,    68
};

static const short yycheck[] =
{
       3,     4,     5,    24,    16,    16,     3,     4,     5,     6,
      66,    16,     9,     5,     6,     3,     4,    62,    21,    22,
       8,    65,     3,     4,     5,     6,    70,    15,    16,    17,
      18,    19,    65,     3,     4,    47,    47,    40,     8,    42,
      43,     5,    47,    15,    16,    15,    16,    65,    18,    52,
       7,     8,     9,    10,    11,    12,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    62,    65,    40,    64,    42,    66,
      67,    69,    65,     0,    65,    65,     3,     4,    63,    19,
      65,     8,    62,    16,    17,    59,    60,    61,    15,    16,
      17,    18,    65,     3,     4,    69,    70,    65,     8,    62,
      33,    61,    76,    67,   135,    15,    16,    17,    18,    19,
      15,    16,    45,    16,    16,    42,    16,    44,    45,    46,
     133,    48,    49,    39,    51,    47,    53,    54,    55,    16,
      57,    56,    66,     3,     4,    62,    68,    66,     8,    16,
      66,    65,    69,    66,    65,    15,    16,    17,    18,    66,
      65,    65,    62,     3,     4,     5,     6,    66,    66,    69,
      66,   174,    66,    62,   177,    16,   179,    65,    65,    16,
     183,    16,    42,    16,    44,    45,    46,   190,    48,    49,
      16,    51,    16,    53,    54,    55,     6,    57,    58,    67,
      66,    66,    62,    66,    66,    66,    65,     5,    66,    69,
       5,    16,    16,    47,   217,    15,   219,   220,     6,    16,
     223,   224,     3,     4,    15,    68,   190,     8,     3,     4,
      66,     5,     5,     8,    15,    16,    17,    18,    16,    16,
      15,    16,    17,    18,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    16,    15,     6,    20,    16,   184,
     224,    42,    -1,    44,    45,    46,    50,    48,    49,    -1,
      51,    -1,    53,    54,    55,    -1,    57,     3,     4,    -1,
      -1,    62,     8,    -1,    -1,    -1,    -1,    62,    69,    15,
      16,    -1,    18,    19,    69,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    63,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     3,     4,    -1,    -1,    -1,
       8,    -1,    -1,    -1,     3,     4,    62,    15,    16,     8,
      18,    19,    -1,     3,     4,    -1,    15,    16,     8,    18,
      19,    -1,    -1,    -1,    -1,    15,    16,    -1,    18,    19,
      -1,     3,     4,    -1,    -1,    63,     8,     3,     4,    -1,
      -1,    -1,     8,    15,    16,    63,    18,    19,    -1,    15,
      16,    -1,    18,    19,    62,     5,     6,     7,     8,     9,
      10,    11,    12,    62,    -1,    16,    -1,    -1,    -1,    20,
      21,    22,    62,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    -1,    -1,    37,    38,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    62,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    -1,    -1,    90,    91,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    72,     0,     3,     4,     8,    15,    16,    17,    18,
      42,    44,    45,    46,    48,    49,    51,    53,    54,    55,
      57,    62,    69,    73,    74,    75,    76,    94,    95,    96,
      97,    98,   100,    16,    95,    95,    17,    95,    97,    64,
      66,    67,    66,    62,    65,    65,    65,    65,    65,    19,
      65,    65,    62,    72,    95,    95,    99,    61,    73,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,     3,
       4,     5,     6,     3,     4,     5,    65,    16,    20,    21,
      22,    24,    25,    26,    27,    28,    31,    32,    33,    34,
      37,    38,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    91,    92,    95,    97,    16,
      97,    95,    16,    47,   104,    16,   106,    16,   105,    16,
      17,    33,    45,    39,   101,    47,   102,    16,   102,   103,
      95,    58,    63,    65,    70,    56,    95,    97,    95,    97,
      95,    97,    95,    95,    95,    95,    95,    95,    95,    95,
      97,    97,    95,    95,    95,    95,    95,    97,    16,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    66,
      90,    90,    68,    63,    66,    66,    65,    66,    65,    66,
      65,    66,    66,    66,    65,    65,    63,    95,    73,     9,
      66,    65,    62,    19,    95,    16,    16,    47,    19,    95,
      16,    95,    16,    16,    16,    19,    95,   103,    16,    19,
      95,    97,    16,    15,    16,    93,     6,    66,    66,    66,
      66,    65,    67,    66,    66,     5,     5,    63,    65,    16,
      19,    95,    16,    19,    95,    95,    47,    15,    19,    95,
      19,    95,    97,    16,    15,    15,    16,     6,    66,    68,
       5,     5,    16,    16,    16,    15,     6,    16
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
                  Token, Value);	\
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
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


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


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 62 "parser.y"
    { 
	 if(ECHO_GRAMMAR) printf("input -> input stmt ';' \n");
       ;}
    break;

  case 4:
#line 68 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> IF '(' aexpr ')' stmt\n" ); execute = 1;;}
    break;

  case 5:
#line 70 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> IF '(' bool_expr ')' ELSE stmt \n" ); ;}
    break;

  case 6:
#line 71 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> atomic_stmt \n"); ;}
    break;

  case 7:
#line 72 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> '{' stmt ';' atomic_stmt '}' \n"); ;}
    break;

  case 8:
#line 75 "parser.y"
    {if( (yyvsp[-1].dval > 0) && (execute > 0) ) execute = 1; else execute = 0;;}
    break;

  case 10:
#line 79 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> expr\n"); ;}
    break;

  case 11:
#line 80 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> command\n"); ;}
    break;

  case 12:
#line 81 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> decl\n"); ;}
    break;

  case 13:
#line 87 "parser.y"
    {
	 if(execute)  {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE (%s) : marker\n",yyvsp[-2].symp->name);
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_MARKER);
	   params.flush();
	 }
       ;}
    break;

  case 14:
#line 96 "parser.y"
    {
	 if(execute) {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE (%s) : drift\n",yyvsp[-2].symp->name);
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_DRIFT);
	   params.flush();
	 }
       ;}
    break;

  case 15:
#line 105 "parser.y"
    {  
	 if(execute) {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE (%s) : sbend\n",yyvsp[-2].symp->name);
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_SBEND);
	   params.flush();
	 }
       ;}
    break;

  case 16:
#line 114 "parser.y"
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
#line 124 "parser.y"
    {
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("decl -> VARIABLE : sext %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_SEXTUPOLE);
	     params.flush();
	   }
       ;}
    break;

  case 18:
#line 134 "parser.y"
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
#line 144 "parser.y"
    {
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("VARIABLE : rcol %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_RCOL);
	     params.flush();
	   }
       ;}
    break;

  case 20:
#line 154 "parser.y"
    {
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("VARIABLE : ecol %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_ECOL);
	     params.flush();
	   }
       ;}
    break;

  case 21:
#line 164 "parser.y"
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

  case 22:
#line 174 "parser.y"
    {
	 if(execute)
	   {	 
	     if(ECHO_GRAMMAR) printf("VARIABLE : element %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_ELEMENT);
	     params.flush();	 
	   }
       ;}
    break;

  case 23:
#line 184 "parser.y"
    {
	 if(execute)
	   {	 
	     if(ECHO_GRAMMAR) printf("VARIABLE : laser %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_LASER);
	     params.flush();	 
	   }
       ;}
    break;

  case 24:
#line 194 "parser.y"
    {
	 if(execute)
	   {	 
	     if(ECHO_GRAMMAR) printf("VARIABLE : transform3d %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_TRANSFORM3D);
	     params.flush();	 
	   }
       ;}
    break;

  case 25:
#line 204 "parser.y"
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

  case 26:
#line 214 "parser.y"
    {
	 if(execute)
	   {
	   }
       ;}
    break;

  case 27:
#line 220 "parser.y"
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

  case 34:
#line 251 "parser.y"
    {
  if(DEBUG) print(params);
;}
    break;

  case 40:
#line 272 "parser.y"
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

  case 42:
#line 295 "parser.y"
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
		  if(!strcmp(yyvsp[-2].symp->name,"k3")) { params.k3 = yyvsp[0].dval; params.k3set = 1;}
		    else 
		  if(!strcmp(yyvsp[-2].symp->name,"angle")) { params.angle = yyvsp[0].dval; params.angleset = 1;}
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"aper") ||!strcmp(yyvsp[-2].symp->name,"aperture") ) 
			      { params.aper = yyvsp[0].dval; params.aperset = 1;}
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"xsize") ) { params.xsize = yyvsp[0].dval; params.xsizeset = 1;}
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"ysize") ) { params.ysize = yyvsp[0].dval; params.ysizeset = 1;}
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"tilt")) { params.tilt = yyvsp[0].dval; params.tiltset = 1;}
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"x")) {params.xdir = yyvsp[0].dval; params.xdirset = 1;} // x direction
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"y")) {params.ydir = yyvsp[0].dval; params.ydirset = 1;} // y direction 
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"z")) {params.zdir = yyvsp[0].dval; params.zdirset = 1;} // z direction 
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"phi")) {params.phi = yyvsp[0].dval; params.phiset = 1;}  // polar angle
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"theta"))  {params.theta = yyvsp[0].dval; params.thetaset = 1;} // azimuthal angle
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"psi"))  {params.psi = yyvsp[0].dval; params.psiset = 1;} // 3rd  angle
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"fint")) {;} // fringe field parameters
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"fintx")) {;}  //
                    else
		  if(!strcmp(yyvsp[-2].symp->name,"e1")) {;}  //
                    else
		  if(!strcmp(yyvsp[-2].symp->name,"e2")) {;}  //
                    else
		  if(!strcmp(yyvsp[-2].symp->name,"hgap")) {;}  //
		    else
		  if(VERBOSE) printf("Warning : unknown parameter %s\n",yyvsp[-2].symp->name);
		  
		}
	    ;}
    break;

  case 43:
#line 347 "parser.y"
    {
	       if(execute) 
		 {
		   if(DEBUG) printf("params,VARIABLE (%s) = vecexpr (%d)\n",yyvsp[-2].symp->name,yyvsp[0].array->size);
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

  case 44:
#line 369 "parser.y"
    {
	       if(execute) 
		 {
		   if(DEBUG) printf("VARIABLE (%s) = vecexpr\n",yyvsp[-2].symp->name);
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

  case 45:
#line 391 "parser.y"
    {
	      if(execute)
		{
		  if(DEBUG) printf("VARIABLE (%s) = aexpr(%.10g)\n",yyvsp[-2].symp->name,yyvsp[0].dval);
		}
	    ;}
    break;

  case 46:
#line 398 "parser.y"
    {
	       if(execute) 
		 {
		   if(DEBUG) printf("params,VARIABLE (%s) = str (%s)\n",yyvsp[-2].symp->name,yyvsp[0].str);
		   if(!strcmp(yyvsp[-2].symp->name,"geometry")) 
		     {
		       params.geomset = 1;
		       strcpy(params.geometry, yyvsp[0].str);

		     } 
		   else
		     if(!strcmp(yyvsp[-2].symp->name,"bmap")) 
		       {
			 params.geomset = 1;
			 strcpy(params.bmap, yyvsp[0].str);
		       }
		   else 
		     if(!strcmp(yyvsp[-2].symp->name,"type")) 
		       {
			 //ignore the "type attribute for the moment"
		       }
		   else
		   if(!strcmp(yyvsp[-2].symp->name,"material")) 
		       {
			 params.materialset = 1;
			 strcpy(params.material, yyvsp[0].str);
		       }
		     else 
		     	  
		       if(VERBOSE) printf("unknown parameter %s\n",yyvsp[-2].symp->name);
		 }
	     ;}
    break;

  case 47:
#line 431 "parser.y"
    {
	       if(execute) 
		 {
		   if(DEBUG) printf("VARIABLE (%s) = str\n",yyvsp[-2].symp->name);
		   if(!strcmp(yyvsp[-2].symp->name,"geometry")) 
		     {
		       params.geomset = 1;
		       strcpy(params.geometry, yyvsp[0].str);
		       
		     } 
		   else
		     if(!strcmp(yyvsp[-2].symp->name,"bmap")) 
		       {
			 params.geomset = 1;
			 strcpy(params.bmap, yyvsp[0].str);
		       }
		     else 
		     if(!strcmp(yyvsp[-2].symp->name,"type")) 
		       {
			 //ignore the "type attribute for the moment"
		       }
		   else
		     if(!strcmp(yyvsp[-2].symp->name,"material")) 
		       {	 
			 params.materialset = 1;
			 strcpy(params.material, yyvsp[0].str);
		       }
		     else 
		       if(VERBOSE) printf("unknown parameter %s\n",yyvsp[-2].symp->name);
		 }         
	     ;}
    break;

  case 51:
#line 471 "parser.y"
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

  case 52:
#line 486 "parser.y"
    {
		if(execute)
		  {
		    if(DEBUG) printf("matched sequence element, %s * %d \n",yyvsp[-2].symp->name,(int)yyvsp[0].dval);
		    // add to temporary element sequence
		    {
		      struct Element e;
		      e.name = yyvsp[-2].symp->name;
		      e.type = _LINE;
		      e.lst = NULL;
		      for(int i=0;i<(int)yyvsp[0].dval;i++)
			tmp_list.push_back(e);
		    }
		  }
	      ;}
    break;

  case 53:
#line 502 "parser.y"
    {
		if(execute)
		  {
		    if(DEBUG) printf("matched sequence element, %s * %d \n",yyvsp[0].symp->name,(int)yyvsp[-2].dval);
		    // add to temporary element sequence
		    {
		      struct Element e;
		      e.name = yyvsp[0].symp->name;
		      e.type = _LINE;
		      e.lst = NULL;
		      for(int i=0;i<(int)yyvsp[-2].dval;i++)
			tmp_list.push_back(e);
		    }
		  }
	      ;}
    break;

  case 54:
#line 518 "parser.y"
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

  case 55:
#line 533 "parser.y"
    {
		if(execute)
		  {
		    if(DEBUG) printf("matched last sequence element, %s * %d\n",yyvsp[-2].symp->name,(int)yyvsp[0].dval);
		    // add to temporary element sequence
		    {
		      struct Element e;
		      e.name = yyvsp[-2].symp->name;
		      e.type = _LINE;
		      e.lst = NULL;
		      for(int i=0;i<(int)yyvsp[0].dval;i++)
			tmp_list.push_back(e);
		    }
		  }
	      ;}
    break;

  case 56:
#line 549 "parser.y"
    {
		if(execute)
		  {
		    if(DEBUG) printf("matched last sequence element, %s * %d\n",yyvsp[0].symp->name,(int)yyvsp[-2].dval);
		    // add to temporary element sequence
		    {
		      struct Element e;
		      e.name = yyvsp[0].symp->name;
		      e.type = _LINE;
		      e.lst = NULL;
		      for(int i=0;i<(int)yyvsp[-2].dval;i++)
			tmp_list.push_back(e);
		    }
		  }
	      ;}
    break;

  case 57:
#line 568 "parser.y"
    { // check type ??
	 if(ECHO_GRAMMAR) printf("expr -> aexpr\n");
	 if(execute) 
	   {
	     if(INTERACTIVE) printf ("\t%.10g\n", yyvsp[0].dval); yyval.dval=yyvsp[0].dval;
	   }
       ;}
    break;

  case 58:
#line 576 "parser.y"
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

  case 59:
#line 589 "parser.y"
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

  case 60:
#line 609 "parser.y"
    { yyval.dval = yyvsp[0].dval;                         ;}
    break;

  case 61:
#line 611 "parser.y"
    { 
	   //check type ??
	   yyval.dval = yyvsp[0].symp->value;        
          ;}
    break;

  case 62:
#line 615 "parser.y"
    { yyval.dval = (*(yyvsp[-3].symp->funcptr))(yyvsp[-1].dval);       ;}
    break;

  case 63:
#line 616 "parser.y"
    { yyval.dval = yyvsp[-2].dval + yyvsp[0].dval;                    ;}
    break;

  case 64:
#line 617 "parser.y"
    { yyval.dval = yyvsp[-2].dval - yyvsp[0].dval;                    ;}
    break;

  case 65:
#line 618 "parser.y"
    { yyval.dval = yyvsp[-2].dval * yyvsp[0].dval;                    ;}
    break;

  case 66:
#line 619 "parser.y"
    { yyval.dval = yyvsp[-2].dval / yyvsp[0].dval;                    ;}
    break;

  case 67:
#line 620 "parser.y"
    { yyval.dval = pow(yyvsp[-2].dval,yyvsp[0].dval);                 ;}
    break;

  case 68:
#line 621 "parser.y"
    { yyval.dval = -yyvsp[0].dval; ;}
    break;

  case 69:
#line 622 "parser.y"
    { yyval.dval = yyvsp[0].dval; ;}
    break;

  case 70:
#line 623 "parser.y"
    { yyval.dval = yyvsp[-1].dval;                         ;}
    break;

  case 71:
#line 625 "parser.y"
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

  case 72:
#line 639 "parser.y"
    { yyval.dval = (yyvsp[-2].dval < yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 73:
#line 640 "parser.y"
    { yyval.dval = (yyvsp[-2].dval <= yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 74:
#line 641 "parser.y"
    { yyval.dval = (yyvsp[-2].dval > yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 75:
#line 642 "parser.y"
    { yyval.dval = (yyvsp[-2].dval >= yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 76:
#line 643 "parser.y"
    { yyval.dval = (yyvsp[-2].dval != yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 77:
#line 645 "parser.y"
    { 
	    if(ECHO_GRAMMAR) printf("aexpr-> %s [ %s ]\n ",yyvsp[-3].symp->name, yyvsp[-1].symp->name); 
	    yyval.dval = property_lookup(yyvsp[-3].symp->name,yyvsp[-1].symp->name);
	  ;}
    break;

  case 78:
#line 652 "parser.y"
    {
		if(ECHO_GRAMMAR) printf("%s \n",yyvsp[-2].symp->name);
		if(execute)
		  {
		    if(yyvsp[-2].symp->is_reserved)
		      printf("%s is reserved",yyvsp[-2].symp->name);
		    else
		      {
			yyvsp[-2].symp->value = yyvsp[0].dval; yyval.symp=yyvsp[-2].symp;       
		      }
		  }
	      ;}
    break;

  case 79:
#line 665 "parser.y"
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

  case 80:
#line 678 "parser.y"
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

  case 81:
#line 692 "parser.y"
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

  case 82:
#line 708 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->data = new double[yyvsp[0].array->size];
	      yyval.array->size = yyvsp[0].array->size;
	      //array_list.push_back($$);
	      
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

  case 83:
#line 729 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = (yyvsp[-2].array->size < yyvsp[0].array->size )? yyvsp[-2].array->size : yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      
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

  case 84:
#line 752 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = (yyvsp[-2].array->size < yyvsp[0].array->size )? yyvsp[-2].array->size : yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      
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

  case 85:
#line 775 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[-2].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      
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

  case 86:
#line 796 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[-2].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      
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

  case 87:
#line 816 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[-2].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      
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

  case 88:
#line 836 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      
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

  case 89:
#line 856 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      
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

  case 90:
#line 876 "parser.y"
    {
	  if(execute)
	    {
	      yyval.array = new struct Array;
	      yyval.array->size = yyvsp[0].array->size;
	      yyval.array->data = new double[yyval.array->size];
	      //array_list.push_back($$);
	      
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

  case 91:
#line 899 "parser.y"
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

  case 93:
#line 924 "parser.y"
    {
	    if(execute)
	      _tmparray.push_back(yyvsp[0].dval);
          ;}
    break;

  case 94:
#line 929 "parser.y"
    {
	   if(execute)
	     _tmparray.push_back(yyvsp[0].dval);
        ;}
    break;

  case 95:
#line 935 "parser.y"
    { if(execute) quit(); ;}
    break;

  case 97:
#line 937 "parser.y"
    { if(execute) print( element_list ); ;}
    break;

  case 98:
#line 938 "parser.y"
    { if(execute) print( beamline_list); ;}
    break;

  case 99:
#line 939 "parser.y"
    { if(execute) print(options); ;}
    break;

  case 100:
#line 941 "parser.y"
    {
	    if(execute)
	      {
		printf("\t");
		printf("\t%.10g\n",yyvsp[0].symp->value);
	      }
	  ;}
    break;

  case 101:
#line 949 "parser.y"
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

  case 102:
#line 963 "parser.y"
    { if(execute) expand_line(current_line,current_start, current_end);;}
    break;

  case 104:
#line 965 "parser.y"
    { if(execute) printf("%s\n",yyvsp[0].str); ;}
    break;

  case 105:
#line 967 "parser.y"
    {
	    if(execute)
	      {  
		if(ECHO_GRAMMAR) printf("command -> SAMPLE\n");
		add_sampler("sampler",yyvsp[0].symp->name, element_count);
		element_count = 1;
		params.flush();
	      }
          ;}
    break;

  case 106:
#line 977 "parser.y"
    {
	    if(execute)
	      {  
		if(ECHO_GRAMMAR) printf("command -> CSAMPLE\n");
		add_csampler("sampler",yyvsp[0].symp->name, element_count,params.l, params.r);
		element_count = 1;
		params.flush();
	      }
          ;}
    break;

  case 107:
#line 987 "parser.y"
    {
	    if(execute)
	      {  
		if(ECHO_GRAMMAR) printf("command -> GAS\n");
		add_gas("gas",yyvsp[0].symp->name, element_count, params.material);
		element_count = 1;
		params.flush();
	      }
          ;}
    break;

  case 108:
#line 1001 "parser.y"
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

  case 109:
#line 1011 "parser.y"
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

  case 110:
#line 1025 "parser.y"
    { if(ECHO_GRAMMAR)  printf("sample_opt : RANGE =  %s \n",yyvsp[0].symp->name);
		  {
		    if(execute) yyval.symp = yyvsp[0].symp;
		  }
                ;}
    break;

  case 111:
#line 1031 "parser.y"
    {
                  if(ECHO_GRAMMAR) printf("sample_opt : RANGE =  %s [%.10g] \n",yyvsp[-3].symp->name,yyvsp[-1].dval);
		    {
		      if(execute) { yyval.symp = yyvsp[-3].symp; element_count = (int)yyvsp[-1].dval; }
		    }
                ;}
    break;

  case 112:
#line 1042 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt ->csopt , %s =  %.10g \n",yyvsp[-2].symp->name,yyvsp[0].dval);
		    
		    if(execute)
		      {
			if( !strcmp(yyvsp[-2].symp->name,"r") ) params.r = yyvsp[0].dval;
			else if (!strcmp(yyvsp[-2].symp->name,"l") ) params.l = yyvsp[0].dval;
			else if(VERBOSE) 
			  printf("Warning : CSAMPLER: unknown parameter %s \n",yyvsp[-2].symp->name);
		      }
		  ;}
    break;

  case 113:
#line 1054 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      {
			;//set_value($1->name,string($3));
		      }
		  ;}
    break;

  case 114:
#line 1062 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt ->csopt , %s =  %.10g \n",yyvsp[-2].symp->name,yyvsp[0].dval);
		    
		    if(execute)
		      {
			if( !strcmp(yyvsp[-2].symp->name,"r") ) params.r = yyvsp[0].dval;
			else if (!strcmp(yyvsp[-2].symp->name,"l") ) params.l = yyvsp[0].dval;
			else if (!strcmp(yyvsp[-2].symp->name,"l") ) params.l = yyvsp[0].dval;
			else if(VERBOSE) 
			  printf("Warning : CSAMPLER: unknown parameter %s at line\n",yyvsp[-2].symp->name);
		      }

		  ;}
    break;

  case 115:
#line 1076 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      ;//set_value($1->name,string($3));
		  ;}
    break;

  case 116:
#line 1082 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> sopt, csopt\n");
		    yyval.symp = yyvsp[-2].symp;
		  ;}
    break;

  case 117:
#line 1087 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> sopt\n");
		    yyval.symp = yyvsp[0].symp;
                  ;}
    break;

  case 118:
#line 1094 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> , %s =  %.10g \n",yyvsp[-2].symp->name,yyvsp[0].dval);
		    
		    if(execute)
		      {
			if( !strcmp(yyvsp[-2].symp->name,"r") ) params.r = yyvsp[0].dval;
			else if (!strcmp(yyvsp[-2].symp->name,"l") ) params.l = yyvsp[0].dval;
			else if(VERBOSE) 
			  printf("Warning : GAS: unknown parameter %s \n",yyvsp[-2].symp->name);
		      }
		  ;}
    break;

  case 119:
#line 1106 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      {
			if( !strcmp(yyvsp[-2].symp->name,"material") ) 
			  {
			    strcpy(params.material ,yyvsp[0].str);
			    params.materialset = 1;
			  }
			//set_value($1->name,string($3));
		      }
		  ;}
    break;

  case 120:
#line 1119 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> , %s =  %.10g \n",yyvsp[-2].symp->name,yyvsp[0].dval);
		    
		    if(execute)
		      {
			if( !strcmp(yyvsp[-2].symp->name,"r") ) params.r = yyvsp[0].dval;
			else if (!strcmp(yyvsp[-2].symp->name,"l") ) params.l = yyvsp[0].dval;
			else if(VERBOSE) 
			  printf("Warning : GAS: unknown parameter %s at line\n",yyvsp[-2].symp->name);
		      }

		  ;}
    break;

  case 121:
#line 1132 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      {
			  if( !strcmp(yyvsp[-2].symp->name,"material") ) 
			    {
			      strcpy(params.material ,yyvsp[0].str);
			      params.materialset = 1;
			    }
		      }
		  ;}
    break;

  case 122:
#line 1144 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> range, csopt\n");

		  ;}
    break;

  case 123:
#line 1149 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> range\n");

                  ;}
    break;

  case 124:
#line 1154 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> range\n");
		    yyval.symp = yyvsp[0].symp;
		  ;}
    break;

  case 125:
#line 1159 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> range\n");
		    yyval.symp = yyvsp[0].symp;
                  ;}
    break;

  case 127:
#line 1167 "parser.y"
    {
		      if(execute)
			set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		    ;}
    break;

  case 128:
#line 1172 "parser.y"
    {
		      if(execute)
			set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		    ;}
    break;

  case 130:
#line 1180 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		  ;}
    break;

  case 131:
#line 1185 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		  ;}
    break;

  case 132:
#line 1190 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,string(yyvsp[0].str));
		  ;}
    break;

  case 133:
#line 1195 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,string(yyvsp[0].str));
		  ;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 2780 "parser.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
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

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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


#line 1201 "parser.y"




int yyerror(char *s)
{
  printf(s);
  exit(1);
}

int yywrap()
{
	return 1;
}




