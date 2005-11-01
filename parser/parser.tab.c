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
     VKICK = 287,
     HKICK = 288,
     KICK = 289,
     PERIOD = 290,
     APERTURE = 291,
     FILENAME = 292,
     GAS = 293,
     PIPE = 294,
     MATERIAL = 295,
     BEAM = 296,
     OPTION = 297,
     PRINT = 298,
     RANGE = 299,
     STOP = 300,
     USE = 301,
     VALUE = 302,
     ECHO = 303,
     PRINTF = 304,
     SAMPLE = 305,
     CSAMPLE = 306,
     IF = 307,
     ELSE = 308,
     BEGN = 309,
     END = 310,
     FOR = 311,
     CUT = 312
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
#define VKICK 287
#define HKICK 288
#define KICK 289
#define PERIOD 290
#define APERTURE 291
#define FILENAME 292
#define GAS 293
#define PIPE 294
#define MATERIAL 295
#define BEAM 296
#define OPTION 297
#define PRINT 298
#define RANGE 299
#define STOP 300
#define USE 301
#define VALUE 302
#define ECHO 303
#define PRINTF 304
#define SAMPLE 305
#define CSAMPLE 306
#define IF 307
#define ELSE 308
#define BEGN 309
#define END 310
#define FOR 311
#define CUT 312




/* Copy the first part of user declarations.  */
#line 9 "parser.y"


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
#line 25 "parser.y"
typedef union YYSTYPE {
  double dval;
  int ival;
  struct symtab *symp;
  char *str;
  struct Array *array;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 213 "parser.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 225 "parser.tab.c"

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
#define YYLAST   470

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  39
/* YYNRULES -- Number of rules. */
#define YYNRULES  139
/* YYNRULES -- Number of states. */
#define YYNSTATES  267

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   312

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      66,    67,     5,     3,    69,     4,     2,     6,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,    65,
       8,    70,     9,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    71,     2,    72,     7,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,     2,    74,     2,     2,     2,     2,
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
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     8,    11,    16,    18,    22,    27,
      28,    30,    32,    34,    38,    42,    46,    50,    54,    58,
      62,    66,    70,    74,    78,    82,    86,    90,    94,    98,
     102,   106,   108,   111,   114,   117,   120,   123,   126,   129,
     132,   135,   138,   141,   144,   147,   150,   153,   154,   160,
     166,   170,   174,   180,   184,   190,   192,   193,   197,   203,
     209,   211,   215,   219,   221,   223,   225,   227,   229,   234,
     238,   242,   246,   250,   254,   257,   260,   264,   270,   274,
     278,   282,   286,   290,   295,   299,   303,   307,   309,   311,
     315,   319,   323,   327,   331,   335,   339,   343,   347,   348,
     352,   354,   356,   360,   362,   366,   370,   374,   378,   382,
     386,   389,   393,   397,   401,   405,   415,   419,   426,   430,
     434,   440,   446,   450,   452,   456,   460,   466,   472,   480,
     486,   492,   496,   497,   503,   507,   508,   514,   518,   524
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      76,     0,    -1,    -1,    76,    77,    65,    -1,    78,    77,
      -1,    78,    77,    60,    77,    -1,    79,    -1,    61,    76,
      62,    -1,    59,    66,   102,    67,    -1,    -1,   101,    -1,
     107,    -1,    80,    -1,    16,    68,    81,    -1,    16,    68,
      82,    -1,    16,    68,    83,    -1,    16,    68,    84,    -1,
      16,    68,    85,    -1,    16,    68,    86,    -1,    16,    68,
      87,    -1,    16,    68,    88,    -1,    16,    68,    91,    -1,
      16,    68,    90,    -1,    16,    68,    89,    -1,    16,    68,
      94,    -1,    16,    68,    92,    -1,    16,    68,    93,    -1,
      16,    68,    98,    -1,    16,    68,    99,    -1,    16,    68,
      96,    -1,    16,    68,    95,    -1,    20,    -1,    22,    97,
      -1,    24,    97,    -1,    39,    97,    -1,    40,    97,    -1,
      25,    97,    -1,    26,    97,    -1,    27,    97,    -1,    28,
      97,    -1,    32,    97,    -1,    31,    97,    -1,    37,    97,
      -1,    38,    97,    -1,    21,    97,    -1,    47,    97,    -1,
      16,    97,    -1,    -1,    97,    69,    16,    70,   102,    -1,
      97,    69,    16,    70,   104,    -1,    16,    70,   104,    -1,
      16,    70,   102,    -1,    97,    69,    16,    70,    19,    -1,
      16,    70,    19,    -1,    33,    70,    66,   100,    67,    -1,
      34,    -1,    -1,   100,    69,    16,    -1,   100,    69,    16,
       5,    15,    -1,   100,    69,    15,     5,    16,    -1,    16,
      -1,    16,     5,    15,    -1,    15,     5,    16,    -1,   102,
      -1,   104,    -1,   103,    -1,    15,    -1,    16,    -1,    18,
      66,   102,    67,    -1,   102,     3,   102,    -1,   102,     4,
     102,    -1,   102,     5,   102,    -1,   102,     6,   102,    -1,
     102,     7,   102,    -1,     4,   102,    -1,     3,   102,    -1,
      66,   102,    67,    -1,     8,   104,    69,   104,     9,    -1,
     102,     8,   102,    -1,   102,    11,   102,    -1,   102,     9,
     102,    -1,   102,    10,   102,    -1,   102,    12,   102,    -1,
      16,    71,    16,    72,    -1,    16,    70,   102,    -1,    16,
      70,   104,    -1,    17,    70,   104,    -1,    17,    -1,   105,
      -1,   104,     3,   104,    -1,   104,     4,   104,    -1,   104,
       3,   102,    -1,   104,     5,   102,    -1,   104,     6,   102,
      -1,   102,     3,   104,    -1,   102,     4,   104,    -1,   102,
       5,   104,    -1,    73,   106,    74,    -1,    -1,   106,    69,
     102,    -1,   102,    -1,    52,    -1,    48,    69,   113,    -1,
      50,    -1,    50,    69,    33,    -1,    50,    69,    49,    -1,
      50,    69,    16,    -1,    50,    69,    17,    -1,    53,    69,
     108,    -1,    49,    69,   112,    -1,    55,    19,    -1,    57,
      69,   109,    -1,    58,    69,   110,    -1,    45,    69,   111,
      -1,    42,    70,    16,    -1,    42,    70,    16,    69,    51,
      70,    16,     6,    16,    -1,    51,    70,    16,    -1,    51,
      70,    16,    71,    15,    72,    -1,    16,    70,   102,    -1,
      16,    70,    19,    -1,   110,    69,    16,    70,   102,    -1,
     110,    69,    16,    70,    19,    -1,   109,    69,   110,    -1,
     109,    -1,    16,    70,   102,    -1,    16,    70,    19,    -1,
     111,    69,    16,    70,   102,    -1,   111,    69,    16,    70,
      19,    -1,   111,    69,    51,    70,    16,     6,    16,    -1,
      51,    70,    16,     6,    16,    -1,   111,    69,    51,    70,
      16,    -1,    51,    70,    16,    -1,    -1,   112,    69,    16,
      70,   102,    -1,    16,    70,   102,    -1,    -1,   113,    69,
      16,    70,   102,    -1,    16,    70,   102,    -1,   113,    69,
      16,    70,    19,    -1,    16,    70,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    63,    63,    64,    71,    72,    74,    75,    78,    81,
      82,    83,    84,    89,    98,   107,   116,   125,   134,   144,
     154,   164,   174,   184,   194,   204,   214,   224,   234,   240,
     252,   263,   265,   268,   271,   274,   277,   280,   283,   286,
     292,   295,   298,   301,   304,   307,   310,   332,   333,   396,
     418,   440,   447,   480,   513,   516,   519,   520,   535,   551,
     567,   582,   598,   617,   625,   638,   659,   660,   665,   666,
     667,   668,   669,   670,   671,   672,   673,   674,   689,   690,
     691,   692,   693,   694,   701,   714,   727,   741,   757,   778,
     801,   824,   845,   865,   885,   905,   925,   948,   972,   973,
     978,   985,   986,   987,   988,   989,   990,   998,  1013,  1014,
    1015,  1016,  1026,  1036,  1050,  1060,  1074,  1080,  1091,  1103,
    1111,  1125,  1131,  1136,  1143,  1155,  1168,  1181,  1193,  1198,
    1203,  1208,  1215,  1216,  1221,  1228,  1229,  1234,  1239,  1244
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
  "LASER", "TRANSFORM3D", "VKICK", "HKICK", "KICK", "PERIOD", "APERTURE",
  "FILENAME", "GAS", "PIPE", "MATERIAL", "BEAM", "OPTION", "PRINT",
  "RANGE", "STOP", "USE", "VALUE", "ECHO", "PRINTF", "SAMPLE", "CSAMPLE",
  "IF", "ELSE", "BEGN", "END", "FOR", "CUT", "';'", "'('", "')'", "':'",
  "','", "'='", "'['", "']'", "'{'", "'}'", "$accept", "input", "stmt",
  "if_clause", "atomic_stmt", "decl", "marker", "drift", "sbend", "vkick",
  "hkick", "quad", "sextupole", "octupole", "multipole", "ecol", "rcol",
  "laser", "transform3d", "element", "material", "extension", "parameters",
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
     308,   309,   310,   311,   312,    59,    40,    41,    58,    44,
      61,    91,    93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    78,    79,
      79,    79,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    97,    97,
      97,    97,    97,    97,    98,    99,   100,   100,   100,   100,
     100,   100,   100,   101,   101,   101,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   103,   103,   103,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   105,   106,   106,
     106,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108,   109,   109,   110,   110,
     110,   110,   110,   110,   111,   111,   111,   111,   111,   111,
     111,   111,   112,   112,   112,   113,   113,   113,   113,   113
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     3,     2,     4,     1,     3,     4,     0,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     0,     5,     5,
       3,     3,     5,     3,     5,     1,     0,     3,     5,     5,
       1,     3,     3,     1,     1,     1,     1,     1,     4,     3,
       3,     3,     3,     3,     2,     2,     3,     5,     3,     3,
       3,     3,     3,     4,     3,     3,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     3,
       1,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       2,     3,     3,     3,     3,     9,     3,     6,     3,     3,
       5,     5,     3,     1,     3,     3,     5,     5,     7,     5,
       5,     3,     0,     5,     3,     0,     5,     3,     5,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     9,     1,     0,     0,     0,    66,    67,    87,     0,
       0,     0,     0,   103,   101,     0,     0,     0,     0,     0,
       2,     0,    98,     0,     9,     6,    12,    10,    63,    65,
      64,    88,    11,    67,    75,    74,    87,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   132,     0,     0,   110,
       0,     0,     0,     9,     0,   100,     0,     3,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,    31,    47,
      47,    47,    47,    47,    47,    47,    47,    47,     0,    55,
      47,    47,    47,    47,    47,    13,    14,    15,    16,    17,
      18,    19,    20,    23,    22,    21,    25,    26,    24,    30,
      29,    27,    28,    84,    85,     0,    86,     0,     0,     0,
     113,     0,   102,     0,   109,   106,   107,   104,   105,     0,
     108,     0,   111,     0,   123,   112,     0,     7,    76,     0,
      97,     9,    69,    94,    70,    95,    71,    96,    72,    73,
      78,    80,    81,    79,    82,    91,    89,    90,    92,    93,
      69,    70,    71,     0,     0,    46,    44,    32,    33,    36,
      37,    38,    39,    41,    40,     0,    42,    43,    34,    35,
      45,    83,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,    99,     5,    77,     0,
       0,    56,   125,   124,   131,     0,     0,   139,   137,     0,
     134,     0,   114,   116,   119,   118,   122,     0,    53,    51,
      50,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    54,     0,   129,   127,
     126,   130,   138,   136,   133,     0,     0,   121,   120,    52,
      48,    49,    62,    61,     0,    57,     0,     0,   117,     0,
       0,   128,     0,    59,    58,     0,   115
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,    23,    24,    25,    26,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   165,   111,   112,   224,    27,    28,    29,    30,
      31,    56,    32,   130,   134,   135,   120,   124,   122
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const short yypact[] =
{
     -67,    85,   -67,   360,   360,   249,   -67,   -18,   -66,   -49,
     -33,     6,    11,    13,   -67,    14,    65,    17,    18,    24,
     -67,   360,   360,    26,   189,   -67,   -67,   -67,   440,   -67,
      29,   -67,   -67,    21,   -67,   -67,   -67,   440,    25,   378,
     249,    82,   249,   360,    -9,    83,    88,   -11,    66,   -67,
      56,    -8,   360,   111,   205,   450,   -59,   -67,    49,   249,
     249,   249,   360,   360,   360,   360,   360,   360,   360,   249,
     249,   360,   360,   360,   360,   360,   249,    94,   -67,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    41,   -67,
      94,    94,    94,    94,    94,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   440,    29,    44,    29,   270,    43,    47,
      52,    48,    53,    54,    62,   -67,   -67,   -67,   -67,    55,
     -67,    69,   -67,    71,    63,    76,   280,   -67,   -67,   360,
     -67,   189,   379,    15,   379,    15,   292,   -67,   292,   -67,
     -67,   -67,   -67,   -67,   -67,   379,    15,    15,   292,   292,
     458,   458,   292,    42,    77,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    57,    79,    79,    79,    79,
      79,   -67,   -67,   290,   133,    -7,   308,   134,   360,   136,
     137,   138,   317,    -8,   139,   -67,   450,   -67,   -67,     8,
     141,    -2,   -67,   450,   156,    95,    97,   -67,   450,   101,
     450,   104,   106,   105,   -67,   450,    76,   108,   -67,   440,
      29,   109,   176,   177,    10,   172,   326,   174,   335,   360,
     143,   180,   354,   183,   187,   203,   -67,    39,   -67,   -67,
     450,   213,   -67,   450,   450,   150,   149,   -67,   450,   -67,
     440,    29,   -67,   -67,   217,   219,   211,   212,   -67,   215,
     218,   -67,   226,   -67,   -67,   220,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
     -67,   223,   -21,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   348,   -67,   -67,   -67,   -67,    -3,   -67,    36,
     -67,   -67,   -67,   -67,   190,    58,   -67,   -67,   -67
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short yytable[] =
{
      34,    35,    37,    58,    42,   125,   126,   118,   133,   205,
     139,     3,     4,   222,   223,   140,     5,    43,    54,    55,
      71,    72,   127,     6,    33,    36,     9,   218,    69,    70,
      71,    72,    69,    70,    71,    72,    44,   113,   128,    37,
     117,    38,   119,   131,   206,    69,    70,    71,    72,   136,
      39,   198,    40,    41,   254,   255,   142,   144,   146,   148,
     149,   150,   151,   152,   153,   154,   155,    37,   158,   159,
     160,   161,   162,    37,    21,    45,   114,   236,   116,   237,
      46,    22,    47,    48,    49,     2,    50,    51,     3,     4,
      52,    57,    41,     5,    76,   143,   145,   147,   115,   121,
       6,     7,     8,     9,   123,   156,   157,   131,   129,   141,
     164,   175,   163,   183,     3,     4,   181,   184,   186,     5,
     197,   185,   187,   201,   188,   190,     6,     7,     8,     9,
      10,   189,   193,    11,    12,    13,   196,    14,    15,   191,
      16,   192,    17,    18,    19,   194,    20,   199,   200,   204,
     209,    21,   211,   212,   213,   217,    10,   221,    22,    11,
      12,    13,   225,    14,    15,   226,    16,   227,    17,    18,
      19,   228,    20,   137,   229,   230,   231,    21,   232,   233,
     203,   234,   235,   208,    22,   210,     3,     4,   238,   215,
     241,     5,     3,     4,   245,   246,   219,     5,     6,    33,
      36,     9,   249,   252,     6,     7,     8,     9,    73,    74,
      75,    62,    63,    64,    65,    66,    67,    68,   253,   256,
     257,   258,   259,   240,   260,   243,   244,   261,   262,   248,
     250,   263,   265,   264,    10,   220,   266,    11,    12,    13,
     132,    14,    15,    53,    16,     0,    17,    18,    19,    21,
      20,   216,     3,     4,     0,    21,    22,     5,     0,     0,
       0,     0,    22,     0,     6,    33,    36,     9,     0,   251,
       0,     0,   138,    73,    74,    75,    62,    63,    64,    65,
      66,    67,    68,    73,    74,    75,    62,    63,    64,    65,
      66,    67,    68,     3,     4,     0,     0,     0,     5,    63,
      64,    65,    66,    67,    68,     6,    33,     0,     9,   202,
       0,     3,     4,     0,     0,    21,     5,     0,     0,     0,
       3,     4,    22,     6,    33,     5,     9,   207,     0,     3,
       4,     0,     6,    33,     5,     9,   214,   182,     3,     4,
       0,     6,    33,     5,     9,   239,     0,   195,     0,     0,
       6,    33,     0,     9,   242,     0,    21,     3,     4,     0,
       0,     0,     5,     3,     4,     0,     0,     0,     5,     6,
      33,     0,     9,   247,    21,     6,    33,     0,     9,     0,
       0,     0,     0,    21,    61,    62,    63,    64,    65,    66,
      67,    68,    21,     0,    77,     0,     0,     0,    78,    79,
      80,    21,    81,    82,    83,    84,    85,     0,     0,    86,
      87,    88,    89,     0,     0,    90,    91,    92,    93,     0,
      21,     0,     0,     0,     0,    94,    21,   166,   167,   168,
     169,   170,   171,   172,   173,   174,     0,     0,   176,   177,
     178,   179,   180,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    73,    74,    75,    62,    63,    64,    65,
      66,    67,    68,    75,    62,    63,    64,    65,    66,    67,
      68
};

static const short yycheck[] =
{
       3,     4,     5,    24,    70,    16,    17,    16,    16,    16,
      69,     3,     4,    15,    16,    74,     8,    66,    21,    22,
       5,     6,    33,    15,    16,    17,    18,    19,     3,     4,
       5,     6,     3,     4,     5,     6,    69,    40,    49,    42,
      43,     5,    51,    51,    51,     3,     4,     5,     6,    52,
      68,     9,    70,    71,    15,    16,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    66,    69,    40,    67,    42,    69,
      69,    73,    69,    69,    19,     0,    69,    69,     3,     4,
      66,    65,    71,     8,    69,    59,    60,    61,    16,    16,
      15,    16,    17,    18,    16,    69,    70,    51,    42,    60,
      16,    70,    76,    70,     3,     4,    72,    70,    70,     8,
     141,    69,    69,    66,    70,    70,    15,    16,    17,    18,
      45,    69,    69,    48,    49,    50,   139,    52,    53,    70,
      55,    70,    57,    58,    59,    69,    61,    70,    69,    16,
      16,    66,    16,    16,    16,    16,    45,    16,    73,    48,
      49,    50,     6,    52,    53,    70,    55,    70,    57,    58,
      59,    70,    61,    62,    70,    69,    71,    66,    70,    70,
     183,     5,     5,   186,    73,   188,     3,     4,    16,   192,
      16,     8,     3,     4,    51,    15,   199,     8,    15,    16,
      17,    18,    19,    16,    15,    16,    17,    18,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    15,     6,
      70,    72,     5,   226,     5,   228,   229,    16,    16,   232,
     233,    16,     6,    15,    45,   199,    16,    48,    49,    50,
      50,    52,    53,    20,    55,    -1,    57,    58,    59,    66,
      61,   193,     3,     4,    -1,    66,    73,     8,    -1,    -1,
      -1,    -1,    73,    -1,    15,    16,    17,    18,    -1,   233,
      -1,    -1,    67,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     3,     4,    -1,    -1,    -1,     8,     7,
       8,     9,    10,    11,    12,    15,    16,    -1,    18,    19,
      -1,     3,     4,    -1,    -1,    66,     8,    -1,    -1,    -1,
       3,     4,    73,    15,    16,     8,    18,    19,    -1,     3,
       4,    -1,    15,    16,     8,    18,    19,    67,     3,     4,
      -1,    15,    16,     8,    18,    19,    -1,    67,    -1,    -1,
      15,    16,    -1,    18,    19,    -1,    66,     3,     4,    -1,
      -1,    -1,     8,     3,     4,    -1,    -1,    -1,     8,    15,
      16,    -1,    18,    19,    66,    15,    16,    -1,    18,    -1,
      -1,    -1,    -1,    66,     5,     6,     7,     8,     9,    10,
      11,    12,    66,    -1,    16,    -1,    -1,    -1,    20,    21,
      22,    66,    24,    25,    26,    27,    28,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    37,    38,    39,    40,    -1,
      66,    -1,    -1,    -1,    -1,    47,    66,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    -1,    -1,    90,    91,
      92,    93,    94,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     5,     6,     7,     8,     9,    10,    11,
      12
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    76,     0,     3,     4,     8,    15,    16,    17,    18,
      45,    48,    49,    50,    52,    53,    55,    57,    58,    59,
      61,    66,    73,    77,    78,    79,    80,   101,   102,   103,
     104,   105,   107,    16,   102,   102,    17,   102,   104,    68,
      70,    71,    70,    66,    69,    69,    69,    69,    69,    19,
      69,    69,    66,    76,   102,   102,   106,    65,    77,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,     3,
       4,     5,     6,     3,     4,     5,    69,    16,    20,    21,
      22,    24,    25,    26,    27,    28,    31,    32,    33,    34,
      37,    38,    39,    40,    47,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    98,    99,   102,   104,    16,   104,   102,    16,    51,
     111,    16,   113,    16,   112,    16,    17,    33,    49,    42,
     108,    51,   109,    16,   109,   110,   102,    62,    67,    69,
      74,    60,   102,   104,   102,   104,   102,   104,   102,   102,
     102,   102,   102,   102,   102,   102,   104,   104,   102,   102,
     102,   102,   102,   104,    16,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    70,    97,    97,    97,    97,
      97,    72,    67,    70,    70,    69,    70,    69,    70,    69,
      70,    70,    70,    69,    69,    67,   102,    77,     9,    70,
      69,    66,    19,   102,    16,    16,    51,    19,   102,    16,
     102,    16,    16,    16,    19,   102,   110,    16,    19,   102,
     104,    16,    15,    16,   100,     6,    70,    70,    70,    70,
      69,    71,    70,    70,     5,     5,    67,    69,    16,    19,
     102,    16,    19,   102,   102,    51,    15,    19,   102,    19,
     102,   104,    16,    15,    15,    16,     6,    70,    72,     5,
       5,    16,    16,    16,    15,     6,    16
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
#line 65 "parser.y"
    { 
	 if(ECHO_GRAMMAR) printf("input -> input stmt ';' \n");
       ;}
    break;

  case 4:
#line 71 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> IF '(' aexpr ')' stmt\n" ); execute = 1;;}
    break;

  case 5:
#line 73 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> IF '(' bool_expr ')' ELSE stmt \n" ); ;}
    break;

  case 6:
#line 74 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> atomic_stmt \n"); ;}
    break;

  case 7:
#line 75 "parser.y"
    { if(ECHO_GRAMMAR) printf("stmt -> '{' stmt ';' atomic_stmt '}' \n"); ;}
    break;

  case 8:
#line 78 "parser.y"
    {if( (yyvsp[-1].dval > 0) && (execute > 0) ) execute = 1; else execute = 0;;}
    break;

  case 10:
#line 82 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> expr\n"); ;}
    break;

  case 11:
#line 83 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> command\n"); ;}
    break;

  case 12:
#line 84 "parser.y"
    { if(ECHO_GRAMMAR) printf("atomic_stmt -> decl\n"); ;}
    break;

  case 13:
#line 90 "parser.y"
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
#line 99 "parser.y"
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
#line 108 "parser.y"
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
#line 117 "parser.y"
    {  
	 if(execute) {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE (%s) : vkick\n",yyvsp[-2].symp->name);
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_VKICK);
	   params.flush();
	 }
       ;}
    break;

  case 17:
#line 126 "parser.y"
    {  
	 if(execute) {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE (%s) : hkick\n",yyvsp[-2].symp->name);
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_HKICK);
	   params.flush();
	 }
       ;}
    break;

  case 18:
#line 135 "parser.y"
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

  case 19:
#line 145 "parser.y"
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

  case 20:
#line 155 "parser.y"
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

  case 21:
#line 165 "parser.y"
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

  case 22:
#line 175 "parser.y"
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

  case 23:
#line 185 "parser.y"
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

  case 24:
#line 195 "parser.y"
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

  case 25:
#line 205 "parser.y"
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

  case 26:
#line 215 "parser.y"
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

  case 27:
#line 225 "parser.y"
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

  case 28:
#line 235 "parser.y"
    {
	 if(execute)
	   {
	   }
       ;}
    break;

  case 29:
#line 241 "parser.y"
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

  case 30:
#line 253 "parser.y"
    {
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("decl -> VARIABLE : Material, %s \n",yyvsp[-2].symp->name);
	     write_table(params,yyvsp[-2].symp->name,_MATERIAL);
	     params.flush();
	   }
       ;}
    break;

  case 39:
#line 287 "parser.y"
    {
  if(DEBUG) print(params);
;}
    break;

  case 46:
#line 311 "parser.y"
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

  case 48:
#line 334 "parser.y"
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
		  if(!strcmp(yyvsp[-2].symp->name,"theta"))  {params.theta = yyvsp[0].dval; params.thetaset = 1;} 
		  // azimuthal angle
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
		  if(!strcmp(yyvsp[-2].symp->name,"density")) {;}  //
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"A")) {params.A = yyvsp[0].dval; params.Aset = 1;}  //
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"Z")) {params.Z = yyvsp[0].dval; params.Zset = 1;}  //
		    else
		  if(!strcmp(yyvsp[-2].symp->name,"density")) {params.density = yyvsp[0].dval; params.densityset = 1;}  //
                    else
		  if(!strcmp(yyvsp[-2].symp->name,"T")) {params.temper = yyvsp[0].dval; params.temperset = 1;}  //
		    else
		  if(VERBOSE) printf("Warning : unknown parameter %s\n",yyvsp[-2].symp->name);
		  
		}
	    ;}
    break;

  case 49:
#line 397 "parser.y"
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

  case 50:
#line 419 "parser.y"
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

  case 51:
#line 441 "parser.y"
    {
	      if(execute)
		{
		  if(DEBUG) printf("VARIABLE (%s) = aexpr(%.10g)\n",yyvsp[-2].symp->name,yyvsp[0].dval);
		}
	    ;}
    break;

  case 52:
#line 448 "parser.y"
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

  case 53:
#line 481 "parser.y"
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

  case 57:
#line 521 "parser.y"
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

  case 58:
#line 536 "parser.y"
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

  case 59:
#line 552 "parser.y"
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

  case 60:
#line 568 "parser.y"
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

  case 61:
#line 583 "parser.y"
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

  case 62:
#line 599 "parser.y"
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

  case 63:
#line 618 "parser.y"
    { // check type ??
	 if(ECHO_GRAMMAR) printf("expr -> aexpr\n");
	 if(execute) 
	   {
	     if(INTERACTIVE) printf ("\t%.10g\n", yyvsp[0].dval); yyval.dval=yyvsp[0].dval;
	   }
       ;}
    break;

  case 64:
#line 626 "parser.y"
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

  case 65:
#line 639 "parser.y"
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

  case 66:
#line 659 "parser.y"
    { yyval.dval = yyvsp[0].dval;                         ;}
    break;

  case 67:
#line 661 "parser.y"
    { 
	   //check type ??
	   yyval.dval = yyvsp[0].symp->value;        
          ;}
    break;

  case 68:
#line 665 "parser.y"
    { yyval.dval = (*(yyvsp[-3].symp->funcptr))(yyvsp[-1].dval);       ;}
    break;

  case 69:
#line 666 "parser.y"
    { yyval.dval = yyvsp[-2].dval + yyvsp[0].dval;                    ;}
    break;

  case 70:
#line 667 "parser.y"
    { yyval.dval = yyvsp[-2].dval - yyvsp[0].dval;                    ;}
    break;

  case 71:
#line 668 "parser.y"
    { yyval.dval = yyvsp[-2].dval * yyvsp[0].dval;                    ;}
    break;

  case 72:
#line 669 "parser.y"
    { yyval.dval = yyvsp[-2].dval / yyvsp[0].dval;                    ;}
    break;

  case 73:
#line 670 "parser.y"
    { yyval.dval = pow(yyvsp[-2].dval,yyvsp[0].dval);                 ;}
    break;

  case 74:
#line 671 "parser.y"
    { yyval.dval = -yyvsp[0].dval; ;}
    break;

  case 75:
#line 672 "parser.y"
    { yyval.dval = yyvsp[0].dval; ;}
    break;

  case 76:
#line 673 "parser.y"
    { yyval.dval = yyvsp[-1].dval;                         ;}
    break;

  case 77:
#line 675 "parser.y"
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

  case 78:
#line 689 "parser.y"
    { yyval.dval = (yyvsp[-2].dval < yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 79:
#line 690 "parser.y"
    { yyval.dval = (yyvsp[-2].dval <= yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 80:
#line 691 "parser.y"
    { yyval.dval = (yyvsp[-2].dval > yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 81:
#line 692 "parser.y"
    { yyval.dval = (yyvsp[-2].dval >= yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 82:
#line 693 "parser.y"
    { yyval.dval = (yyvsp[-2].dval != yyvsp[0].dval )? 1 : 0; ;}
    break;

  case 83:
#line 695 "parser.y"
    { 
	    if(ECHO_GRAMMAR) printf("aexpr-> %s [ %s ]\n ",yyvsp[-3].symp->name, yyvsp[-1].symp->name); 
	    yyval.dval = property_lookup(yyvsp[-3].symp->name,yyvsp[-1].symp->name);
	  ;}
    break;

  case 84:
#line 702 "parser.y"
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

  case 85:
#line 715 "parser.y"
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

  case 86:
#line 728 "parser.y"
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

  case 87:
#line 742 "parser.y"
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

  case 88:
#line 758 "parser.y"
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

  case 89:
#line 779 "parser.y"
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

  case 90:
#line 802 "parser.y"
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

  case 91:
#line 825 "parser.y"
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

  case 92:
#line 846 "parser.y"
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

  case 93:
#line 866 "parser.y"
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

  case 94:
#line 886 "parser.y"
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

  case 95:
#line 906 "parser.y"
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

  case 96:
#line 926 "parser.y"
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

  case 97:
#line 949 "parser.y"
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

  case 99:
#line 974 "parser.y"
    {
	    if(execute)
	      _tmparray.push_back(yyvsp[0].dval);
          ;}
    break;

  case 100:
#line 979 "parser.y"
    {
	   if(execute)
	     _tmparray.push_back(yyvsp[0].dval);
        ;}
    break;

  case 101:
#line 985 "parser.y"
    { if(execute) quit(); ;}
    break;

  case 103:
#line 987 "parser.y"
    { if(execute) print( element_list ); ;}
    break;

  case 104:
#line 988 "parser.y"
    { if(execute) print( beamline_list); ;}
    break;

  case 105:
#line 989 "parser.y"
    { if(execute) print(options); ;}
    break;

  case 106:
#line 991 "parser.y"
    {
	    if(execute)
	      {
		printf("\t");
		printf("\t%.10g\n",yyvsp[0].symp->value);
	      }
	  ;}
    break;

  case 107:
#line 999 "parser.y"
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

  case 108:
#line 1013 "parser.y"
    { if(execute) expand_line(current_line,current_start, current_end);;}
    break;

  case 110:
#line 1015 "parser.y"
    { if(execute) printf("%s\n",yyvsp[0].str); ;}
    break;

  case 111:
#line 1017 "parser.y"
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

  case 112:
#line 1027 "parser.y"
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

  case 113:
#line 1037 "parser.y"
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

  case 114:
#line 1051 "parser.y"
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

  case 115:
#line 1061 "parser.y"
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

  case 116:
#line 1075 "parser.y"
    { if(ECHO_GRAMMAR)  printf("sample_opt : RANGE =  %s \n",yyvsp[0].symp->name);
		  {
		    if(execute) yyval.symp = yyvsp[0].symp;
		  }
                ;}
    break;

  case 117:
#line 1081 "parser.y"
    {
                  if(ECHO_GRAMMAR) printf("sample_opt : RANGE =  %s [%.10g] \n",yyvsp[-3].symp->name,yyvsp[-1].dval);
		    {
		      if(execute) { yyval.symp = yyvsp[-3].symp; element_count = (int)yyvsp[-1].dval; }
		    }
                ;}
    break;

  case 118:
#line 1092 "parser.y"
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

  case 119:
#line 1104 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      {
			;//set_value($1->name,string($3));
		      }
		  ;}
    break;

  case 120:
#line 1112 "parser.y"
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

  case 121:
#line 1126 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      ;//set_value($1->name,string($3));
		  ;}
    break;

  case 122:
#line 1132 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> sopt, csopt\n");
		    yyval.symp = yyvsp[-2].symp;
		  ;}
    break;

  case 123:
#line 1137 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("csample_opt -> sopt\n");
		    yyval.symp = yyvsp[0].symp;
                  ;}
    break;

  case 124:
#line 1144 "parser.y"
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

  case 125:
#line 1156 "parser.y"
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

  case 126:
#line 1169 "parser.y"
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

  case 127:
#line 1182 "parser.y"
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

  case 128:
#line 1194 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> range, csopt\n");

		  ;}
    break;

  case 129:
#line 1199 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> range\n");

                  ;}
    break;

  case 130:
#line 1204 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> range\n");
		    yyval.symp = yyvsp[0].symp;
		  ;}
    break;

  case 131:
#line 1209 "parser.y"
    {
		    if(ECHO_GRAMMAR) printf("gas_opt -> range\n");
		    yyval.symp = yyvsp[0].symp;
                  ;}
    break;

  case 133:
#line 1217 "parser.y"
    {
		      if(execute)
			set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		    ;}
    break;

  case 134:
#line 1222 "parser.y"
    {
		      if(execute)
			set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		    ;}
    break;

  case 136:
#line 1230 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		  ;}
    break;

  case 137:
#line 1235 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		  ;}
    break;

  case 138:
#line 1240 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,string(yyvsp[0].str));
		  ;}
    break;

  case 139:
#line 1245 "parser.y"
    {
		    if(execute)
		      set_value(yyvsp[-2].symp->name,string(yyvsp[0].str));
		  ;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 2846 "parser.tab.c"

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


#line 1251 "parser.y"




int yyerror(char *s)
{
  printf(s);
  exit(1);
}

int yywrap()
{
	return 1;
}




