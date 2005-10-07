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
     PERIOD = 286,
     APERTURE = 287,
     FILENAME = 288,
     GAS = 289,
     PIPE = 290,
     BEAM = 291,
     OPTION = 292,
     PRINT = 293,
     RANGE = 294,
     STOP = 295,
     USE = 296,
     VALUE = 297,
     ECHO = 298,
     PRINTF = 299,
     SAMPLE = 300,
     CSAMPLE = 301,
     IF = 302,
     ELSE = 303,
     BEGN = 304,
     END = 305,
     FOR = 306
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
#define PERIOD 286
#define APERTURE 287
#define FILENAME 288
#define GAS 289
#define PIPE 290
#define BEAM 291
#define OPTION 292
#define PRINT 293
#define RANGE 294
#define STOP 295
#define USE 296
#define VALUE 297
#define ECHO 298
#define PRINTF 299
#define SAMPLE 300
#define CSAMPLE 301
#define IF 302
#define ELSE 303
#define BEGN 304
#define END 305
#define FOR 306




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
#line 201 "parser.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 213 "parser.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

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
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
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
#define YYLAST   405

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  34
/* YYNRULES -- Number of rules. */
#define YYNRULES  122
/* YYNRULES -- Number of states. */
#define YYNSTATES  233

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      60,    61,     5,     3,    63,     4,     2,     6,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    59,
       8,    64,     9,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    65,     2,    66,     7,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,     2,    68,     2,     2,     2,     2,
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
      52,    53,    54,    55,    56,    57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     8,    11,    16,    18,    22,    27,
      28,    30,    32,    34,    38,    42,    46,    50,    54,    58,
      62,    66,    70,    74,    78,    82,    86,    90,    92,    95,
      98,   101,   104,   107,   110,   113,   116,   119,   122,   125,
     126,   132,   138,   142,   146,   152,   156,   162,   164,   165,
     169,   175,   181,   183,   187,   191,   193,   195,   197,   199,
     201,   206,   210,   214,   218,   222,   226,   229,   232,   236,
     242,   246,   250,   254,   258,   262,   267,   271,   275,   279,
     281,   283,   287,   291,   295,   299,   303,   307,   311,   315,
     319,   320,   324,   326,   328,   332,   334,   338,   342,   346,
     350,   354,   358,   361,   365,   369,   373,   383,   387,   394,
     398,   402,   408,   414,   418,   420,   421,   427,   431,   432,
     438,   442,   448
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      70,     0,    -1,    -1,    70,    71,    59,    -1,    72,    71,
      -1,    72,    71,    55,    71,    -1,    73,    -1,    56,    70,
      57,    -1,    54,    60,    92,    61,    -1,    -1,    91,    -1,
      97,    -1,    74,    -1,    16,    62,    75,    -1,    16,    62,
      76,    -1,    16,    62,    77,    -1,    16,    62,    78,    -1,
      16,    62,    79,    -1,    16,    62,    80,    -1,    16,    62,
      83,    -1,    16,    62,    82,    -1,    16,    62,    81,    -1,
      16,    62,    85,    -1,    16,    62,    84,    -1,    16,    62,
      88,    -1,    16,    62,    89,    -1,    16,    62,    86,    -1,
      20,    -1,    22,    87,    -1,    24,    87,    -1,    25,    87,
      -1,    26,    87,    -1,    27,    87,    -1,    28,    87,    -1,
      32,    87,    -1,    31,    87,    -1,    37,    87,    -1,    21,
      87,    -1,    16,    87,    -1,    -1,    87,    63,    16,    64,
      92,    -1,    87,    63,    16,    64,    94,    -1,    16,    64,
      94,    -1,    16,    64,    92,    -1,    87,    63,    16,    64,
      19,    -1,    16,    64,    19,    -1,    33,    64,    60,    90,
      61,    -1,    34,    -1,    -1,    90,    63,    16,    -1,    90,
      63,    16,     5,    15,    -1,    90,    63,    15,     5,    16,
      -1,    16,    -1,    16,     5,    15,    -1,    15,     5,    16,
      -1,    92,    -1,    94,    -1,    93,    -1,    15,    -1,    16,
      -1,    18,    60,    92,    61,    -1,    92,     3,    92,    -1,
      92,     4,    92,    -1,    92,     5,    92,    -1,    92,     6,
      92,    -1,    92,     7,    92,    -1,     4,    92,    -1,     3,
      92,    -1,    60,    92,    61,    -1,     8,    94,    63,    94,
       9,    -1,    92,     8,    92,    -1,    92,    11,    92,    -1,
      92,     9,    92,    -1,    92,    10,    92,    -1,    92,    12,
      92,    -1,    16,    65,    16,    66,    -1,    16,    64,    92,
      -1,    16,    64,    94,    -1,    17,    64,    94,    -1,    17,
      -1,    95,    -1,    94,     3,    94,    -1,    94,     4,    94,
      -1,    94,     3,    92,    -1,    94,     5,    92,    -1,    94,
       6,    92,    -1,    92,     3,    94,    -1,    92,     4,    94,
      -1,    92,     5,    94,    -1,    67,    96,    68,    -1,    -1,
      96,    63,    92,    -1,    92,    -1,    47,    -1,    43,    63,
     102,    -1,    45,    -1,    45,    63,    33,    -1,    45,    63,
      44,    -1,    45,    63,    16,    -1,    45,    63,    17,    -1,
      48,    63,    98,    -1,    44,    63,   101,    -1,    50,    19,
      -1,    52,    63,    99,    -1,    53,    63,   100,    -1,    38,
      64,    16,    -1,    38,    64,    16,    63,    46,    64,    16,
       6,    16,    -1,    46,    64,    16,    -1,    46,    64,    16,
      65,    15,    66,    -1,    16,    64,    92,    -1,    16,    64,
      19,    -1,   100,    63,    16,    64,    92,    -1,   100,    63,
      16,    64,    19,    -1,    99,    63,   100,    -1,    99,    -1,
      -1,   101,    63,    16,    64,    92,    -1,    16,    64,    92,
      -1,    -1,   102,    63,    16,    64,    92,    -1,    16,    64,
      92,    -1,   102,    63,    16,    64,    19,    -1,    16,    64,
      19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    58,    58,    59,    66,    67,    69,    70,    73,    76,
      77,    78,    79,    84,    93,   102,   111,   121,   131,   141,
     151,   161,   171,   181,   191,   201,   207,   221,   223,   226,
     229,   232,   235,   238,   244,   247,   250,   253,   256,   278,
     279,   319,   341,   363,   370,   403,   436,   439,   442,   443,
     458,   474,   490,   505,   521,   540,   548,   561,   582,   583,
     588,   589,   590,   591,   592,   593,   594,   595,   596,   597,
     612,   613,   614,   615,   616,   617,   624,   637,   650,   664,
     680,   701,   724,   747,   768,   788,   808,   828,   848,   871,
     895,   896,   901,   908,   909,   910,   911,   912,   913,   921,
     936,   937,   938,   939,   949,   963,   973,   987,   993,  1004,
    1016,  1022,  1035,  1041,  1046,  1054,  1055,  1060,  1067,  1068,
    1073,  1078,  1083
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
  "LASER", "PERIOD", "APERTURE", "FILENAME", "GAS", "PIPE", "BEAM",
  "OPTION", "PRINT", "RANGE", "STOP", "USE", "VALUE", "ECHO", "PRINTF",
  "SAMPLE", "CSAMPLE", "IF", "ELSE", "BEGN", "END", "FOR", "';'", "'('",
  "')'", "':'", "','", "'='", "'['", "']'", "'{'", "'}'", "$accept",
  "input", "stmt", "if_clause", "atomic_stmt", "decl", "marker", "drift",
  "sbend", "quad", "sextupole", "octupole", "multipole", "ecol", "rcol",
  "laser", "element", "extension", "parameters", "line", "sequence",
  "element_seq", "expr", "aexpr", "assignment", "vecexpr", "vect",
  "numbers", "command", "use_parameters", "sample_options",
  "csample_options", "option_parameters", "beam_parameters", 0
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
     298,   299,   300,   301,   302,   303,   304,   305,   306,    59,
      40,    41,    58,    44,    61,    91,    93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    72,    73,
      73,    73,    73,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      87,    87,    87,    87,    87,    87,    88,    89,    90,    90,
      90,    90,    90,    90,    90,    91,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    93,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    95,
      96,    96,    96,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    98,    98,    99,    99,   100,
     100,   100,   100,   100,   100,   101,   101,   101,   102,   102,
     102,   102,   102
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     3,     2,     4,     1,     3,     4,     0,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     0,
       5,     5,     3,     3,     5,     3,     5,     1,     0,     3,
       5,     5,     1,     3,     3,     1,     1,     1,     1,     1,
       4,     3,     3,     3,     3,     3,     2,     2,     3,     5,
       3,     3,     3,     3,     3,     4,     3,     3,     3,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     3,     1,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     9,     3,     6,     3,
       3,     5,     5,     3,     1,     0,     5,     3,     0,     5,
       3,     5,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     9,     1,     0,     0,     0,    58,    59,    79,     0,
       0,     0,    95,    93,     0,     0,     0,     0,     0,     2,
       0,    90,     0,     9,     6,    12,    10,    55,    57,    56,
      80,    11,    59,    67,    66,    79,     0,     0,     0,     0,
       0,     0,     0,   118,   115,     0,     0,   102,     0,     0,
       0,     9,     0,    92,     0,     3,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,    27,    39,    39,    39,
      39,    39,    39,    39,    39,    39,     0,    47,    39,    13,
      14,    15,    16,    17,    18,    21,    20,    19,    23,    22,
      26,    24,    25,    76,    77,     0,    78,     0,     0,    94,
       0,   101,    98,    99,    96,    97,     0,   100,     0,   103,
       0,   114,   104,     0,     7,    68,     0,    89,     9,    61,
      86,    62,    87,    63,    88,    64,    65,    70,    72,    73,
      71,    74,    83,    81,    82,    84,    85,    61,    62,    63,
       0,     0,    38,    37,    28,    29,    30,    31,    32,    33,
      35,    34,     0,    36,    75,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,    91,     5,    69,     0,
       0,    48,   122,   120,     0,   117,     0,   105,   107,   110,
     109,   113,     0,    45,    43,    42,     0,     0,    52,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,     0,
     121,   119,   116,     0,     0,   112,   111,    44,    40,    41,
      54,    53,     0,    49,     0,   108,     0,     0,     0,    51,
      50,     0,   106
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,    22,    23,    24,    25,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   152,   101,
     102,   199,    26,    27,    28,    29,    30,    54,    31,   117,
     121,   122,   111,   109
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -50
static const short yypact[] =
{
     -50,    81,   -50,   309,   309,   207,   -50,    13,   -43,    20,
     -31,    10,    25,   -50,    27,    64,    28,    32,    44,   -50,
     309,   309,    47,   191,   -50,   -50,   -50,   367,   -50,    45,
     -50,   -50,    42,   -50,   -50,   -50,   367,    19,   314,   207,
      94,   207,   309,    95,   101,    -7,    80,   -50,    73,   -12,
     309,   136,   272,   377,   -49,   -50,    65,   207,   207,   207,
     309,   309,   309,   309,   309,   309,   309,   207,   207,   309,
     309,   309,   309,   309,   207,   105,   -50,   105,   105,   105,
     105,   105,   105,   105,   105,   105,    58,   -50,   105,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,   -50,   367,    45,    61,    45,   282,    66,    69,
      72,    75,   -50,   -50,   -50,   -50,    78,   -50,    79,   -50,
      82,    84,    86,   292,   -50,   -50,   309,   -50,   191,   385,
       7,   385,     7,    34,   -50,    34,   -50,   -50,   -50,   -50,
     -50,   -50,   385,     7,     7,    34,    34,   393,   393,    34,
       2,    98,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    85,    87,   -50,   -50,   152,   142,   309,   143,
     145,   150,   213,   -12,   156,   -50,   377,   -50,   -50,    12,
     157,    37,   -50,   377,   110,   377,   111,   114,   113,   -50,
     377,    86,   118,   -50,   367,    45,   121,   182,   186,   -28,
     245,   309,   154,   189,   303,    97,   197,   190,   -50,    71,
     -50,   377,   377,   155,   160,   -50,   377,   -50,   367,    45,
     -50,   -50,   215,   222,   202,   -50,   214,   218,   231,   -50,
     -50,   226,   -50
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -50,   227,   -20,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   277,   -50,
     -50,   -50,   -50,    -3,   -50,    35,   -50,   -50,   -50,   -50,
     204,    77,   -50,   -50
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      33,    34,    36,    56,   120,    67,    68,    69,    70,   112,
     113,   178,    69,    70,   126,     3,     4,    52,    53,   127,
       5,    41,    67,    68,    69,    70,   114,     6,    32,    35,
       9,   193,    43,   208,   118,   209,   103,   115,    36,   107,
      37,    61,    62,    63,    64,    65,    66,   123,    67,    68,
      69,    70,   197,   198,   129,   131,   133,   135,   136,   137,
     138,   139,   140,   141,   142,    36,   145,   146,   147,   148,
     149,    36,    20,    44,   104,    38,   106,    39,    40,    21,
      42,     2,    74,    47,     3,     4,   222,   223,    45,     5,
      46,    48,   130,   132,   134,    49,     6,     7,     8,     9,
       3,     4,   143,   144,    50,     5,    55,    40,   177,   150,
     105,   108,     6,    32,    35,     9,   217,   110,   116,   118,
     128,   151,   162,   176,    10,    11,    12,   164,    13,    14,
     166,    15,   167,    16,    17,    18,   168,    19,   169,     3,
       4,    20,   170,   171,     5,   181,   172,   173,    21,   174,
     180,     6,     7,     8,     9,     3,     4,    20,   184,   186,
       5,   187,   179,   183,    21,   185,   188,     6,    32,   190,
       9,   182,   192,   196,   200,   201,   194,   202,   203,    10,
      11,    12,   204,    13,    14,   205,    15,   206,    16,    17,
      18,   207,    19,   124,     3,     4,    20,   211,   212,     5,
     213,   216,   218,    21,   214,   221,     6,     7,     8,     9,
       3,     4,    20,   220,   195,     5,     3,     4,   228,   224,
     226,     5,     6,    32,    35,     9,   225,   227,     6,    32,
     229,     9,   189,   230,    10,    11,    12,   231,    13,    14,
     219,    15,   232,    16,    17,    18,    51,    19,     3,     4,
     191,    20,   119,     5,     0,     0,     0,     0,    21,     0,
       6,    32,     0,     9,   210,     0,     0,    20,     0,     0,
       0,     0,     0,    20,    21,    71,    72,    73,    60,    61,
      62,    63,    64,    65,    66,    71,    72,    73,    60,    61,
      62,    63,    64,    65,    66,    71,    72,    73,    60,    61,
      62,    63,    64,    65,    66,    20,     3,     4,     0,     0,
       0,     5,     3,     4,     0,     0,     0,     5,     6,    32,
       0,     9,   215,     0,     6,    32,     0,     9,     0,     0,
      75,     0,     0,   125,    76,    77,    78,     0,    79,    80,
      81,    82,    83,   165,     0,    84,    85,    86,    87,     0,
       0,    88,     0,   175,   153,   154,   155,   156,   157,   158,
     159,   160,   161,    20,     0,   163,     0,     0,     0,    20,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      71,    72,    73,    60,    61,    62,    63,    64,    65,    66,
      59,    60,    61,    62,    63,    64,    65,    66,    73,    60,
      61,    62,    63,    64,    65,    66
};

static const short yycheck[] =
{
       3,     4,     5,    23,    16,     3,     4,     5,     6,    16,
      17,     9,     5,     6,    63,     3,     4,    20,    21,    68,
       8,    64,     3,     4,     5,     6,    33,    15,    16,    17,
      18,    19,    63,    61,    46,    63,    39,    44,    41,    42,
       5,     7,     8,     9,    10,    11,    12,    50,     3,     4,
       5,     6,    15,    16,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    60,    63,    39,    62,    41,    64,    65,    67,
      60,     0,    63,    19,     3,     4,    15,    16,    63,     8,
      63,    63,    57,    58,    59,    63,    15,    16,    17,    18,
       3,     4,    67,    68,    60,     8,    59,    65,   128,    74,
      16,    16,    15,    16,    17,    18,    19,    16,    38,    46,
      55,    16,    64,   126,    43,    44,    45,    66,    47,    48,
      64,    50,    63,    52,    53,    54,    64,    56,    63,     3,
       4,    60,    64,    64,     8,    60,    64,    63,    67,    63,
      63,    15,    16,    17,    18,     3,     4,    60,    16,    16,
       8,    16,    64,   166,    67,   168,    16,    15,    16,   172,
      18,    19,    16,    16,    64,    64,   179,    63,    65,    43,
      44,    45,    64,    47,    48,    64,    50,     5,    52,    53,
      54,     5,    56,    57,     3,     4,    60,   200,   201,     8,
      46,   204,   205,    67,    15,    15,    15,    16,    17,    18,
       3,     4,    60,    16,   179,     8,     3,     4,    16,    64,
       5,     8,    15,    16,    17,    18,    66,     5,    15,    16,
      16,    18,    19,    15,    43,    44,    45,     6,    47,    48,
     205,    50,    16,    52,    53,    54,    19,    56,     3,     4,
     173,    60,    48,     8,    -1,    -1,    -1,    -1,    67,    -1,
      15,    16,    -1,    18,    19,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    60,    67,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    60,     3,     4,    -1,    -1,
      -1,     8,     3,     4,    -1,    -1,    -1,     8,    15,    16,
      -1,    18,    19,    -1,    15,    16,    -1,    18,    -1,    -1,
      16,    -1,    -1,    61,    20,    21,    22,    -1,    24,    25,
      26,    27,    28,    61,    -1,    31,    32,    33,    34,    -1,
      -1,    37,    -1,    61,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    60,    -1,    88,    -1,    -1,    -1,    60,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       5,     6,     7,     8,     9,    10,    11,    12,     5,     6,
       7,     8,     9,    10,    11,    12
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    70,     0,     3,     4,     8,    15,    16,    17,    18,
      43,    44,    45,    47,    48,    50,    52,    53,    54,    56,
      60,    67,    71,    72,    73,    74,    91,    92,    93,    94,
      95,    97,    16,    92,    92,    17,    92,    94,    62,    64,
      65,    64,    60,    63,    63,    63,    63,    19,    63,    63,
      60,    70,    92,    92,    96,    59,    71,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,     3,     4,     5,
       6,     3,     4,     5,    63,    16,    20,    21,    22,    24,
      25,    26,    27,    28,    31,    32,    33,    34,    37,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    88,    89,    92,    94,    16,    94,    92,    16,   102,
      16,   101,    16,    17,    33,    44,    38,    98,    46,    99,
      16,    99,   100,    92,    57,    61,    63,    68,    55,    92,
      94,    92,    94,    92,    94,    92,    92,    92,    92,    92,
      92,    92,    92,    94,    94,    92,    92,    92,    92,    92,
      94,    16,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    64,    87,    66,    61,    64,    63,    64,    63,
      64,    64,    64,    63,    63,    61,    92,    71,     9,    64,
      63,    60,    19,    92,    16,    92,    16,    16,    16,    19,
      92,   100,    16,    19,    92,    94,    16,    15,    16,    90,
      64,    64,    63,    65,    64,    64,     5,     5,    61,    63,
      19,    92,    92,    46,    15,    19,    92,    19,    92,    94,
      16,    15,    15,    16,    64,    66,     5,     5,    16,    16,
      15,     6,    16
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
#line 60 "parser.y"
    { 
	 if(ECHO_GRAMMAR) printf("input -> input stmt ';' \n");
       ;}
    break;

  case 4:
#line 66 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> IF '(' aexpr ')' stmt\n" ); execute = 1;;}
    break;

  case 5:
#line 68 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> IF '(' bool_expr ')' ELSE stmt \n" ); ;}
    break;

  case 6:
#line 69 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> atomic_stmt \n"); ;}
    break;

  case 7:
#line 70 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> '{' stmt ';' atomic_stmt '}' \n"); ;}
    break;

  case 8:
#line 73 "parser.y"
    {if( (yyvsp[-1].dval > 0) && (execute > 0) ) execute = 1; else execute = 0;;}
    break;

  case 10:
#line 77 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> expr\n"); ;}
    break;

  case 11:
#line 78 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> command\n"); ;}
    break;

  case 12:
#line 79 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> decl\n"); ;}
    break;

  case 13:
#line 85 "parser.y"
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
#line 94 "parser.y"
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
#line 103 "parser.y"
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
#line 112 "parser.y"
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
#line 122 "parser.y"
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
#line 132 "parser.y"
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
#line 142 "parser.y"
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
#line 152 "parser.y"
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
#line 162 "parser.y"
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
#line 172 "parser.y"
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
#line 182 "parser.y"
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
#line 192 "parser.y"
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

  case 25:
#line 202 "parser.y"
    {
	 if(execute)
	   {
	   }
       ;}
    break;

  case 26:
#line 208 "parser.y"
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

  case 33:
#line 239 "parser.y"
    {
  if(DEBUG) print(params);
;}
    break;

  case 38:
#line 257 "parser.y"
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

  case 40:
#line 280 "parser.y"
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

  case 41:
#line 320 "parser.y"
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

  case 42:
#line 342 "parser.y"
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

  case 43:
#line 364 "parser.y"
    {
	      if(execute)
		{
		  if(DEBUG) printf("VARIABLE (%s) = aexpr(%.10g)\n",yyvsp[-2].symp->name,yyvsp[0].dval);
		}
	    ;}
    break;

  case 44:
#line 371 "parser.y"
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

  case 45:
#line 404 "parser.y"
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

  case 49:
#line 444 "parser.y"
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

  case 50:
#line 459 "parser.y"
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

  case 51:
#line 475 "parser.y"
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

  case 52:
#line 491 "parser.y"
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

  case 53:
#line 506 "parser.y"
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

  case 54:
#line 522 "parser.y"
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

  case 55:
#line 541 "parser.y"
    { // check type ??
	 if(ECHO_GRAMMAR) printf("expr -> aexpr\n");
	 if(execute) 
	   {
	     if(INTERACTIVE) printf ("\t%.10g\n", yyvsp[0].dval); yyval.dval=yyvsp[0].dval;
	   }
       ;}
    break;

  case 56:
#line 549 "parser.y"
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

  case 57:
#line 562 "parser.y"
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

  case 58:
#line 582 "parser.y"
    { yyval.dval = yyvsp[0].dval;                         ;}
    break;

  case 59:
#line 584 "parser.y"
    { 
	   //check type ??
	   yyval.dval = yyvsp[0].symp->value;        
          ;}
    break;

  case 60:
#line 588 "parser.y"
    { yyval.dval = (*(yyvsp[-3].symp->funcptr))(yyvsp[-1].dval);       ;}
    break;

  case 61:
#line 589 "parser.y"
    { yyval.dval = yyvsp[-2].dval + yyvsp[0].dval;                    ;}
    break;

  case 62:
#line 590 "parser.y"
    { yyval.dval = yyvsp[-2].dval - yyvsp[0].dval;                    ;}
    break;

  case 63:
#line 591 "parser.y"
    { yyval.dval = yyvsp[-2].dval * yyvsp[0].dval;                    ;}
    break;

  case 64:
#line 592 "parser.y"
    { yyval.dval = yyvsp[-2].dval / yyvsp[0].dval;                    ;}
    break;

  case 65:
#line 593 "parser.y"
    { yyval.dval = pow(yyvsp[-2].dval,yyvsp[0].dval);                 ;}
    break;

  case 66:
#line 594 "parser.y"
    { yyval.dval = -yyvsp[0].dval; ;}
    break;

  case 67:
#line 595 "parser.y"
    { yyval.dval = yyvsp[0].dval; ;}
    break;

  case 68:
#line 596 "parser.y"
    { yyval.dval = yyvsp[-1].dval;                         ;}
    break;

  case 69:
#line 598 "parser.y"
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

  case 70:
#line 612 "parser.y"
    { yyval.dval = (yyvsp[-2].dval < yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 71:
#line 613 "parser.y"
    { yyval.dval = (yyvsp[-2].dval <= yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 72:
#line 614 "parser.y"
    { yyval.dval = (yyvsp[-2].dval > yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 73:
#line 615 "parser.y"
    { yyval.dval = (yyvsp[-2].dval >= yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 74:
#line 616 "parser.y"
    { yyval.dval = (yyvsp[-2].dval != yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 75:
#line 618 "parser.y"
    { 
	    if(ECHO_GRAMMAR) printf("aexpr-> %s [ %s ]\n ",yyvsp[-3].symp->name, yyvsp[-1].symp->name); 
	    yyval.dval = property_lookup(yyvsp[-3].symp->name,yyvsp[-1].symp->name);
	  ;}
    break;

  case 76:
#line 625 "parser.y"
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

  case 77:
#line 638 "parser.y"
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

  case 78:
#line 651 "parser.y"
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

  case 79:
#line 665 "parser.y"
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

  case 80:
#line 681 "parser.y"
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

  case 81:
#line 702 "parser.y"
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

  case 82:
#line 725 "parser.y"
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

  case 83:
#line 748 "parser.y"
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

  case 84:
#line 769 "parser.y"
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

  case 85:
#line 789 "parser.y"
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

  case 86:
#line 809 "parser.y"
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

  case 87:
#line 829 "parser.y"
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

  case 88:
#line 849 "parser.y"
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

  case 89:
#line 872 "parser.y"
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

  case 91:
#line 897 "parser.y"
    {
	    if(execute)
	      _tmparray.push_back(yyvsp[0].dval);
          ;}
    break;

  case 92:
#line 902 "parser.y"
    {
	   if(execute)
	     _tmparray.push_back(yyvsp[0].dval);
        ;}
    break;

  case 93:
#line 908 "parser.y"
    { if(execute) quit(); ;}
    break;

  case 95:
#line 910 "parser.y"
    { if(execute) print( element_list ); ;}
    break;

  case 96:
#line 911 "parser.y"
    { if(execute) print( beamline_list); ;}
    break;

  case 97:
#line 912 "parser.y"
    { if(execute) print(options); ;}
    break;

  case 98:
#line 914 "parser.y"
    {
	    if(execute)
	      {
		printf("\t");
		printf("\t%.10g\n",yyvsp[0].symp->value);
	      }
	  ;}
    break;

  case 99:
#line 922 "parser.y"
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

  case 100:
#line 936 "parser.y"
    { if(execute) expand_line(current_line,current_start, current_end);;}
    break;

  case 102:
#line 938 "parser.y"
    { if(execute) printf("%s\n",yyvsp[0].str); ;}
    break;

  case 103:
#line 940 "parser.y"
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

  case 104:
#line 950 "parser.y"
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

  case 105:
#line 964 "parser.y"
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

  case 106:
#line 974 "parser.y"
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

  case 107:
#line 988 "parser.y"
    { if(ECHO_GRAMMAR)  printf("sample_opt : RANGE =  %s \n",yyvsp[0].symp->name);
		  {
		    if(execute) yyval.symp = yyvsp[0].symp;
		  }
                ;}
    break;

  case 108:
#line 994 "parser.y"
    {
                  if(ECHO_GRAMMAR) printf("sample_opt : RANGE =  %s [%.10g] \n",yyvsp[-3].symp->name,yyvsp[-1].dval);
		    {
		      if(execute) { yyval.symp = yyvsp[-3].symp; element_count = (int)yyvsp[-1].dval; }
		    }
                ;}
    break;

  case 109:
#line 1005 "parser.y"
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

  case 110:
#line 1017 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      ;//set_value($1->name,string($3));
		  ;}
    break;

  case 111:
#line 1023 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt ->csopt , %s =  %.10g \n",yyvsp[-2].symp->name,yyvsp[0].dval);
		    
		    if(execute)
		      {
			if( !strcmp(yyvsp[-2].symp->name,"r") ) params.r = yyvsp[0].dval;
			else if (!strcmp(yyvsp[-2].symp->name,"l") ) params.l = yyvsp[0].dval;
			else if(VERBOSE) 
			  printf("Warning : CSAMPLER: unknown parameter %s at line\n",yyvsp[-2].symp->name);
		      }

		  ;}
    break;

  case 112:
#line 1036 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      ;//set_value($1->name,string($3));
		  ;}
    break;

  case 113:
#line 1042 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> sopt, csopt\n");
		    yyval.symp = yyvsp[-2].symp;
		  ;}
    break;

  case 114:
#line 1047 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> sopt\n");
		    yyval.symp = yyvsp[0].symp;
                  ;}
    break;

  case 116:
#line 1056 "parser.y"
    {
		      if(execute)
			set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		    ;}
    break;

  case 117:
#line 1061 "parser.y"
    {
		      if(execute)
			set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		    ;}
    break;

  case 119:
#line 1069 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		  ;}
    break;

  case 120:
#line 1074 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		  ;}
    break;

  case 121:
#line 1079 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,string(yyvsp[0].str));
		  ;}
    break;

  case 122:
#line 1084 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,string(yyvsp[0].str));
		  ;}
    break;


    }

/* Line 993 of yacc.c.  */
#line 2607 "parser.tab.c"

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


#line 1090 "parser.y"




int yyerror(char *s)
{
  printf(s);
  exit(1);
}

int yywrap()
{
	return 1;
}




