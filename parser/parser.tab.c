
/*  A Bison parser, made from parser.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	NE	257
#define	LE	258
#define	GE	259
#define	UMINUS	260
#define	UPLUS	261
#define	NUMBER	262
#define	VARIABLE	263
#define	VECVAR	264
#define	FUNC	265
#define	STR	266
#define	MARKER	267
#define	ELEMENT	268
#define	DRIFT	269
#define	DIPOLE	270
#define	SBEND	271
#define	QUADRUPOLE	272
#define	SEXTUPOLE	273
#define	OCTUPOLE	274
#define	MULTIPOLE	275
#define	SOLENOID	276
#define	COLLIMATOR	277
#define	RCOL	278
#define	ECOL	279
#define	LINE	280
#define	SEQUENCE	281
#define	SPOILER	282
#define	ABSORBER	283
#define	LASER	284
#define	PERIOD	285
#define	APERTURE	286
#define	FILENAME	287
#define	GAS	288
#define	PIPE	289
#define	BEAM	290
#define	OPTION	291
#define	PRINT	292
#define	RANGE	293
#define	STOP	294
#define	USE	295
#define	VALUE	296
#define	ECHO	297
#define	PRINTF	298
#define	SAMPLE	299
#define	CSAMPLE	300
#define	IF	301
#define	ELSE	302
#define	BEGN	303
#define	END	304
#define	FOR	305

#line 7 "parser.y"


  const int DEBUG = 0; // print debug info like parsing output etc.
  const int ECHO_GRAMMAR = 0; // print grammar rule expamsion (for debugging)
  const int VERBOSE = 0; // print warnings and errors
  const int VERBOSE_EXPAND = 0; // print the process of line expansion 
  const int INTERACTIVE = 0; // print output of commands (like in interactive mode)

#include "parser.h"

  int execute = 1;
  int element_count = 1; // for samplers , ranges etc.


#line 23 "parser.y"
typedef union{
  double dval;
  int ival;
  struct symtab *symp;
  char *str;
  struct Array *array;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		233
#define	YYFLAG		-32768
#define	YYNTBASE	69

#define YYTRANSLATE(x) ((unsigned)(x) <= 305 ? yytranslate[x] : 102)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    60,
    61,     5,     3,    63,     4,     2,     6,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    62,    59,     8,
    64,     9,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    65,     2,    66,     7,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    67,     2,    68,     2,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,    10,    11,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
    24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
    34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
    44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
    54,    55,    56,    57,    58
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     5,     8,    13,    15,    19,    24,    25,    27,
    29,    31,    35,    39,    43,    47,    51,    55,    59,    63,
    67,    71,    75,    79,    83,    87,    89,    92,    95,    98,
   101,   104,   107,   110,   113,   116,   119,   122,   123,   129,
   135,   139,   143,   149,   153,   159,   161,   162,   166,   172,
   178,   180,   184,   188,   190,   192,   194,   196,   198,   203,
   207,   211,   215,   219,   223,   226,   229,   233,   239,   243,
   247,   251,   255,   259,   264,   268,   272,   276,   278,   280,
   284,   288,   292,   296,   300,   304,   308,   312,   316,   317,
   321,   323,   325,   329,   331,   335,   339,   343,   347,   351,
   355,   358,   362,   366,   370,   380,   384,   391,   395,   399,
   405,   411,   415,   417,   418,   424,   428,   429,   435,   439,
   445
};

static const short yyrhs[] = {    -1,
    69,    70,    59,     0,    71,    70,     0,    71,    70,    55,
    70,     0,    72,     0,    56,    69,    57,     0,    54,    60,
    91,    61,     0,     0,    90,     0,    96,     0,    73,     0,
    16,    62,    74,     0,    16,    62,    75,     0,    16,    62,
    76,     0,    16,    62,    77,     0,    16,    62,    78,     0,
    16,    62,    79,     0,    16,    62,    82,     0,    16,    62,
    81,     0,    16,    62,    80,     0,    16,    62,    84,     0,
    16,    62,    83,     0,    16,    62,    87,     0,    16,    62,
    88,     0,    16,    62,    85,     0,    20,     0,    22,    86,
     0,    24,    86,     0,    25,    86,     0,    26,    86,     0,
    27,    86,     0,    28,    86,     0,    32,    86,     0,    31,
    86,     0,    37,    86,     0,    21,    86,     0,    16,    86,
     0,     0,    86,    63,    16,    64,    91,     0,    86,    63,
    16,    64,    93,     0,    16,    64,    93,     0,    16,    64,
    91,     0,    86,    63,    16,    64,    19,     0,    16,    64,
    19,     0,    33,    64,    60,    89,    61,     0,    34,     0,
     0,    89,    63,    16,     0,    89,    63,    16,     5,    15,
     0,    89,    63,    15,     5,    16,     0,    16,     0,    16,
     5,    15,     0,    15,     5,    16,     0,    91,     0,    93,
     0,    92,     0,    15,     0,    16,     0,    18,    60,    91,
    61,     0,    91,     3,    91,     0,    91,     4,    91,     0,
    91,     5,    91,     0,    91,     6,    91,     0,    91,     7,
    91,     0,     4,    91,     0,     3,    91,     0,    60,    91,
    61,     0,     8,    93,    63,    93,     9,     0,    91,     8,
    91,     0,    91,    11,    91,     0,    91,     9,    91,     0,
    91,    12,    91,     0,    91,    10,    91,     0,    16,    65,
    16,    66,     0,    16,    64,    91,     0,    16,    64,    93,
     0,    17,    64,    93,     0,    17,     0,    94,     0,    93,
     3,    93,     0,    93,     4,    93,     0,    93,     3,    91,
     0,    93,     5,    91,     0,    93,     6,    91,     0,    91,
     3,    93,     0,    91,     4,    93,     0,    91,     5,    93,
     0,    67,    95,    68,     0,     0,    95,    63,    91,     0,
    91,     0,    47,     0,    43,    63,   101,     0,    45,     0,
    45,    63,    33,     0,    45,    63,    44,     0,    45,    63,
    16,     0,    45,    63,    17,     0,    48,    63,    97,     0,
    44,    63,   100,     0,    50,    19,     0,    52,    63,    98,
     0,    53,    63,    99,     0,    38,    64,    16,     0,    38,
    64,    16,    63,    46,    64,    16,     6,    16,     0,    46,
    64,    16,     0,    46,    64,    16,    65,    15,    66,     0,
    16,    64,    91,     0,    16,    64,    19,     0,    99,    63,
    16,    64,    91,     0,    99,    63,    16,    64,    19,     0,
    98,    63,    99,     0,    98,     0,     0,   100,    63,    16,
    64,    91,     0,    16,    64,    91,     0,     0,   101,    63,
    16,    64,    91,     0,    16,    64,    91,     0,   101,    63,
    16,    64,    19,     0,    16,    64,    19,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    58,    59,    66,    67,    69,    70,    73,    76,    77,    78,
    79,    84,    93,   102,   111,   121,   131,   141,   151,   161,
   171,   181,   191,   201,   207,   221,   223,   226,   229,   232,
   235,   238,   244,   247,   250,   253,   256,   278,   279,   319,
   341,   363,   370,   403,   436,   439,   442,   443,   458,   474,
   490,   505,   521,   540,   548,   561,   582,   583,   588,   589,
   590,   591,   592,   593,   594,   595,   596,   597,   612,   613,
   614,   615,   616,   617,   624,   637,   650,   664,   680,   701,
   724,   747,   768,   788,   808,   828,   848,   871,   895,   896,
   901,   908,   909,   910,   911,   912,   913,   921,   936,   937,
   938,   939,   949,   963,   973,   987,   993,  1004,  1016,  1022,
  1035,  1041,  1046,  1054,  1055,  1060,  1067,  1068,  1073,  1078,
  1083
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","'+'","'-'",
"'*'","'/'","'^'","'<'","'>'","NE","LE","GE","UMINUS","UPLUS","NUMBER","VARIABLE",
"VECVAR","FUNC","STR","MARKER","ELEMENT","DRIFT","DIPOLE","SBEND","QUADRUPOLE",
"SEXTUPOLE","OCTUPOLE","MULTIPOLE","SOLENOID","COLLIMATOR","RCOL","ECOL","LINE",
"SEQUENCE","SPOILER","ABSORBER","LASER","PERIOD","APERTURE","FILENAME","GAS",
"PIPE","BEAM","OPTION","PRINT","RANGE","STOP","USE","VALUE","ECHO","PRINTF",
"SAMPLE","CSAMPLE","IF","ELSE","BEGN","END","FOR","';'","'('","')'","':'","','",
"'='","'['","']'","'{'","'}'","input","stmt","if_clause","atomic_stmt","decl",
"marker","drift","sbend","quad","sextupole","octupole","multipole","ecol","rcol",
"laser","element","extension","parameters","line","sequence","element_seq","expr",
"aexpr","assignment","vecexpr","vect","numbers","command","use_parameters","sample_options",
"csample_options","option_parameters","beam_parameters", NULL
};
#endif

static const short yyr1[] = {     0,
    69,    69,    70,    70,    70,    70,    71,    72,    72,    72,
    72,    73,    73,    73,    73,    73,    73,    73,    73,    73,
    73,    73,    73,    73,    73,    74,    75,    76,    77,    78,
    79,    80,    81,    82,    83,    84,    85,    86,    86,    86,
    86,    86,    86,    86,    87,    88,    89,    89,    89,    89,
    89,    89,    89,    90,    90,    90,    91,    91,    91,    91,
    91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
    91,    91,    91,    91,    92,    92,    92,    93,    93,    93,
    93,    93,    93,    93,    93,    93,    93,    94,    95,    95,
    95,    96,    96,    96,    96,    96,    96,    96,    96,    96,
    96,    96,    96,    97,    97,    98,    98,    99,    99,    99,
    99,    99,    99,   100,   100,   100,   101,   101,   101,   101,
   101
};

static const short yyr2[] = {     0,
     0,     3,     2,     4,     1,     3,     4,     0,     1,     1,
     1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     1,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     0,     5,     5,
     3,     3,     5,     3,     5,     1,     0,     3,     5,     5,
     1,     3,     3,     1,     1,     1,     1,     1,     4,     3,
     3,     3,     3,     3,     2,     2,     3,     5,     3,     3,
     3,     3,     3,     4,     3,     3,     3,     1,     1,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     0,     3,
     1,     1,     3,     1,     3,     3,     3,     3,     3,     3,
     2,     3,     3,     3,     9,     3,     6,     3,     3,     5,
     5,     3,     1,     0,     5,     3,     0,     5,     3,     5,
     3
};

static const short yydefact[] = {     1,
     8,     0,     0,     0,    57,    58,    78,     0,     0,     0,
    94,    92,     0,     0,     0,     0,     0,     1,     0,    89,
     0,     8,     5,    11,     9,    54,    56,    55,    79,    10,
    58,    66,    65,    78,     0,     0,     0,     0,     0,     0,
     0,   117,   114,     0,     0,   101,     0,     0,     0,     8,
     0,    91,     0,     2,     3,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    38,    26,    38,    38,    38,    38,    38,
    38,    38,    38,    38,     0,    46,    38,    12,    13,    14,
    15,    16,    17,    20,    19,    18,    22,    21,    25,    23,
    24,    75,    76,     0,    77,     0,     0,    93,     0,   100,
    97,    98,    95,    96,     0,    99,     0,   102,     0,   113,
   103,     0,     6,    67,     0,    88,     8,    60,    85,    61,
    86,    62,    87,    63,    64,    69,    71,    73,    70,    72,
    82,    80,    81,    83,    84,    60,    61,    62,     0,     0,
    37,    36,    27,    28,    29,    30,    31,    32,    34,    33,
     0,    35,    74,    59,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     7,    90,     4,    68,     0,     0,    47,
   121,   119,     0,   116,     0,   104,   106,   109,   108,   112,
     0,    44,    42,    41,     0,     0,    51,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    45,     0,   120,   118,
   115,     0,     0,   111,   110,    43,    39,    40,    53,    52,
     0,    48,     0,   107,     0,     0,     0,    50,    49,     0,
   105,     0,     0
};

static const short yydefgoto[] = {     1,
    21,    22,    23,    24,    88,    89,    90,    91,    92,    93,
    94,    95,    96,    97,    98,    99,   151,   100,   101,   198,
    25,    26,    27,    28,    29,    53,    30,   116,   120,   121,
   110,   108
};

static const short yypact[] = {-32768,
    81,   309,   309,   207,-32768,    13,   -43,    20,   -31,    10,
    25,-32768,    27,    64,    28,    32,    44,-32768,   309,   309,
    47,   191,-32768,-32768,-32768,   367,-32768,    45,-32768,-32768,
    42,-32768,-32768,-32768,   367,    19,   314,   207,    94,   207,
   309,    95,   101,    -7,    80,-32768,    73,   -12,   309,   136,
   272,   377,   -49,-32768,    65,   207,   207,   207,   309,   309,
   309,   309,   309,   309,   309,   207,   207,   309,   309,   309,
   309,   309,   207,   105,-32768,   105,   105,   105,   105,   105,
   105,   105,   105,   105,    58,-32768,   105,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   367,    45,    61,    45,   282,    66,    69,    72,    75,
-32768,-32768,-32768,-32768,    78,-32768,    79,-32768,    82,    84,
    86,   292,-32768,-32768,   309,-32768,   191,   385,     7,   385,
     7,    34,-32768,    34,-32768,-32768,-32768,-32768,-32768,-32768,
   385,     7,     7,    34,    34,   393,   393,    34,     2,    98,
    87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
    85,    87,-32768,-32768,   152,   142,   309,   143,   145,   150,
   213,   -12,   156,-32768,   377,-32768,-32768,    12,   157,    37,
-32768,   377,   110,   377,   111,   114,   113,-32768,   377,    86,
   118,-32768,   367,    45,   121,   182,   186,   -28,   245,   309,
   154,   189,   303,    97,   197,   190,-32768,    71,-32768,   377,
   377,   155,   160,-32768,   377,-32768,   367,    45,-32768,-32768,
   215,   222,   202,-32768,   214,   218,   231,-32768,-32768,   226,
-32768,   246,-32768
};

static const short yypgoto[] = {   232,
   -19,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   278,-32768,-32768,-32768,
-32768,    -2,-32768,    36,-32768,-32768,-32768,-32768,   205,    83,
-32768,-32768
};


#define	YYLAST		405


static const short yytable[] = {    32,
    33,    35,    55,   119,    66,    67,    68,    69,   111,   112,
   177,    68,    69,   125,     2,     3,    51,    52,   126,     4,
    40,    66,    67,    68,    69,   113,     5,    31,    34,     8,
   192,    42,   207,   117,   208,   102,   114,    35,   106,    36,
    60,    61,    62,    63,    64,    65,   122,    66,    67,    68,
    69,   196,   197,   128,   130,   132,   134,   135,   136,   137,
   138,   139,   140,   141,    35,   144,   145,   146,   147,   148,
    35,    19,    43,   103,    37,   105,    38,    39,    20,    41,
   232,    73,    46,     2,     3,   221,   222,    44,     4,    45,
    47,   129,   131,   133,    48,     5,     6,     7,     8,     2,
     3,   142,   143,    49,     4,    54,    39,   176,   149,   104,
   107,     5,    31,    34,     8,   216,   109,   115,   117,   127,
   150,   161,   175,     9,    10,    11,   163,    12,    13,   165,
    14,   166,    15,    16,    17,   167,    18,   168,     2,     3,
    19,   169,   170,     4,   180,   171,   172,    20,   173,   179,
     5,     6,     7,     8,     2,     3,    19,   183,   185,     4,
   186,   178,   182,    20,   184,   187,     5,    31,   189,     8,
   181,   191,   195,   199,   200,   193,   201,   202,     9,    10,
    11,   203,    12,    13,   204,    14,   205,    15,    16,    17,
   206,    18,   123,     2,     3,    19,   210,   211,     4,   212,
   215,   217,    20,   213,   220,     5,     6,     7,     8,     2,
     3,    19,   219,   194,     4,     2,     3,   227,   223,   225,
     4,     5,    31,    34,     8,   224,   226,     5,    31,   228,
     8,   188,   229,     9,    10,    11,   230,    12,    13,   218,
    14,   231,    15,    16,    17,   233,    18,     2,     3,    50,
    19,   118,     4,     0,   190,     0,     0,    20,     0,     5,
    31,     0,     8,   209,     0,     0,    19,     0,     0,     0,
     0,     0,    19,    20,    70,    71,    72,    59,    60,    61,
    62,    63,    64,    65,    70,    71,    72,    59,    60,    61,
    62,    63,    64,    65,    70,    71,    72,    59,    60,    61,
    62,    63,    64,    65,    19,     2,     3,     0,     0,     0,
     4,     2,     3,     0,     0,     0,     4,     5,    31,     0,
     8,   214,     0,     5,    31,     0,     8,     0,     0,    74,
     0,     0,   124,    75,    76,    77,     0,    78,    79,    80,
    81,    82,   164,     0,    83,    84,    85,    86,     0,     0,
    87,     0,   174,   152,   153,   154,   155,   156,   157,   158,
   159,   160,    19,     0,   162,     0,     0,     0,    19,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    70,
    71,    72,    59,    60,    61,    62,    63,    64,    65,    58,
    59,    60,    61,    62,    63,    64,    65,    72,    59,    60,
    61,    62,    63,    64,    65
};

static const short yycheck[] = {     2,
     3,     4,    22,    16,     3,     4,     5,     6,    16,    17,
     9,     5,     6,    63,     3,     4,    19,    20,    68,     8,
    64,     3,     4,     5,     6,    33,    15,    16,    17,    18,
    19,    63,    61,    46,    63,    38,    44,    40,    41,     4,
     7,     8,     9,    10,    11,    12,    49,     3,     4,     5,
     6,    15,    16,    56,    57,    58,    59,    60,    61,    62,
    63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
    73,    60,    63,    38,    62,    40,    64,    65,    67,    60,
     0,    63,    19,     3,     4,    15,    16,    63,     8,    63,
    63,    56,    57,    58,    63,    15,    16,    17,    18,     3,
     4,    66,    67,    60,     8,    59,    65,   127,    73,    16,
    16,    15,    16,    17,    18,    19,    16,    38,    46,    55,
    16,    64,   125,    43,    44,    45,    66,    47,    48,    64,
    50,    63,    52,    53,    54,    64,    56,    63,     3,     4,
    60,    64,    64,     8,    60,    64,    63,    67,    63,    63,
    15,    16,    17,    18,     3,     4,    60,    16,    16,     8,
    16,    64,   165,    67,   167,    16,    15,    16,   171,    18,
    19,    16,    16,    64,    64,   178,    63,    65,    43,    44,
    45,    64,    47,    48,    64,    50,     5,    52,    53,    54,
     5,    56,    57,     3,     4,    60,   199,   200,     8,    46,
   203,   204,    67,    15,    15,    15,    16,    17,    18,     3,
     4,    60,    16,   178,     8,     3,     4,    16,    64,     5,
     8,    15,    16,    17,    18,    66,     5,    15,    16,    16,
    18,    19,    15,    43,    44,    45,     6,    47,    48,   204,
    50,    16,    52,    53,    54,     0,    56,     3,     4,    18,
    60,    47,     8,    -1,   172,    -1,    -1,    67,    -1,    15,
    16,    -1,    18,    19,    -1,    -1,    60,    -1,    -1,    -1,
    -1,    -1,    60,    67,     3,     4,     5,     6,     7,     8,
     9,    10,    11,    12,     3,     4,     5,     6,     7,     8,
     9,    10,    11,    12,     3,     4,     5,     6,     7,     8,
     9,    10,    11,    12,    60,     3,     4,    -1,    -1,    -1,
     8,     3,     4,    -1,    -1,    -1,     8,    15,    16,    -1,
    18,    19,    -1,    15,    16,    -1,    18,    -1,    -1,    16,
    -1,    -1,    61,    20,    21,    22,    -1,    24,    25,    26,
    27,    28,    61,    -1,    31,    32,    33,    34,    -1,    -1,
    37,    -1,    61,    76,    77,    78,    79,    80,    81,    82,
    83,    84,    60,    -1,    87,    -1,    -1,    -1,    60,     3,
     4,     5,     6,     7,     8,     9,    10,    11,    12,     3,
     4,     5,     6,     7,     8,     9,    10,    11,    12,     5,
     6,     7,     8,     9,    10,    11,    12,     5,     6,     7,
     8,     9,    10,    11,    12
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 2:
#line 60 "parser.y"
{ 
	 if(ECHO_GRAMMAR) printf("input -> input stmt ';' \n");
       ;
    break;}
case 3:
#line 66 "parser.y"
{ if(ECHO_GRAMMAR) printf("stmt -> IF '(' aexpr ')' stmt\n" ); execute = 1;;
    break;}
case 4:
#line 68 "parser.y"
{ if(ECHO_GRAMMAR) printf("stmt -> IF '(' bool_expr ')' ELSE stmt \n" ); ;
    break;}
case 5:
#line 69 "parser.y"
{ if(ECHO_GRAMMAR) printf("stmt -> atomic_stmt \n"); ;
    break;}
case 6:
#line 70 "parser.y"
{ if(ECHO_GRAMMAR) printf("stmt -> '{' stmt ';' atomic_stmt '}' \n"); ;
    break;}
case 7:
#line 73 "parser.y"
{if( (yyvsp[-1].dval > 0) && (execute > 0) ) execute = 1; else execute = 0;;
    break;}
case 9:
#line 77 "parser.y"
{ if(ECHO_GRAMMAR) printf("atomic_stmt -> expr\n"); ;
    break;}
case 10:
#line 78 "parser.y"
{ if(ECHO_GRAMMAR) printf("atomic_stmt -> command\n"); ;
    break;}
case 11:
#line 79 "parser.y"
{ if(ECHO_GRAMMAR) printf("atomic_stmt -> decl\n"); ;
    break;}
case 12:
#line 85 "parser.y"
{
	 if(execute)  {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE (%s) : marker\n",yyvsp[-2].symp->name);
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_MARKER);
	   params.flush();
	 }
       ;
    break;}
case 13:
#line 94 "parser.y"
{
	 if(execute) {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE (%s) : drift\n",yyvsp[-2].symp->name);
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_DRIFT);
	   params.flush();
	 }
       ;
    break;}
case 14:
#line 103 "parser.y"
{  
	 if(execute) {
	   if(ECHO_GRAMMAR) printf("decl -> VARIABLE (%s) : sbend\n",yyvsp[-2].symp->name);
	   // check parameters and write into element table
	   write_table(params,yyvsp[-2].symp->name,_SBEND);
	   params.flush();
	 }
       ;
    break;}
case 15:
#line 112 "parser.y"
{
	 if(execute)       
	   {
	     if(ECHO_GRAMMAR) printf("decl -> VARIABLE : quad %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_QUAD);
	     params.flush();
	   }
       ;
    break;}
case 16:
#line 122 "parser.y"
{
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("decl -> VARIABLE : sext %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_SEXTUPOLE);
	     params.flush();
	   }
       ;
    break;}
case 17:
#line 132 "parser.y"
{
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("VARIABLE : octupole %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_OCTUPOLE);
	     params.flush();
	   }
       ;
    break;}
case 18:
#line 142 "parser.y"
{
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("VARIABLE : rcol %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_RCOL);
	     params.flush();
	   }
       ;
    break;}
case 19:
#line 152 "parser.y"
{
	 if(execute)
	   {
	     if(ECHO_GRAMMAR) printf("VARIABLE : ecol %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_ECOL);
	     params.flush();
	   }
       ;
    break;}
case 20:
#line 162 "parser.y"
{
	 if(execute)
	   {	 
	     if(ECHO_GRAMMAR) printf("VARIABLE : multipole %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_MULT);
	     params.flush();	 
	   }
       ;
    break;}
case 21:
#line 172 "parser.y"
{
	 if(execute)
	   {	 
	     if(ECHO_GRAMMAR) printf("VARIABLE : element %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_ELEMENT);
	     params.flush();	 
	   }
       ;
    break;}
case 22:
#line 182 "parser.y"
{
	 if(execute)
	   {	 
	     if(ECHO_GRAMMAR) printf("VARIABLE : laser %s \n",yyvsp[-2].symp->name);
	     // check parameters and write into element table
	     write_table(params,yyvsp[-2].symp->name,_LASER);
	     params.flush();	 
	   }
       ;
    break;}
case 23:
#line 192 "parser.y"
{
	 if(execute)
	   {
	     // create entry in the main table and add pointer to the parsed sequence
	     if(ECHO_GRAMMAR) printf("VARIABLE : LINE %s\n",yyvsp[-2].symp->name);
	     write_table(params,yyvsp[-2].symp->name,_LINE,new list<struct Element>(tmp_list));
	     tmp_list.erase(tmp_list.begin(), tmp_list.end());
	   }
       ;
    break;}
case 24:
#line 202 "parser.y"
{
	 if(execute)
	   {
	   }
       ;
    break;}
case 25:
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
       ;
    break;}
case 32:
#line 239 "parser.y"
{
  if(DEBUG) print(params);
;
    break;}
case 37:
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
	    ;
    break;}
case 39:
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
	    ;
    break;}
case 40:
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
	     ;
    break;}
case 41:
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
	     ;
    break;}
case 42:
#line 364 "parser.y"
{
	      if(execute)
		{
		  if(DEBUG) printf("VARIABLE (%s) = aexpr(%.10g)\n",yyvsp[-2].symp->name,yyvsp[0].dval);
		}
	    ;
    break;}
case 43:
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
	     ;
    break;}
case 44:
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
	     ;
    break;}
case 48:
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
	      ;
    break;}
case 49:
#line 459 "parser.y"
{
		if(execute)
		  {
		    if(DEBUG) printf("matched sequence element, %s * %d \n",yyvsp[-2].symp->name,yyvsp[0].dval);
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
	      ;
    break;}
case 50:
#line 475 "parser.y"
{
		if(execute)
		  {
		    if(DEBUG) printf("matched sequence element, %s * %d \n",yyvsp[0].symp->name,yyvsp[-2].dval);
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
	      ;
    break;}
case 51:
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
	      ;
    break;}
case 52:
#line 506 "parser.y"
{
		if(execute)
		  {
		    if(DEBUG) printf("matched last sequence element, %s * %d\n",yyvsp[-2].symp->name,yyvsp[0].dval);
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
	      ;
    break;}
case 53:
#line 522 "parser.y"
{
		if(execute)
		  {
		    if(DEBUG) printf("matched last sequence element, %s * %d\n",yyvsp[0].symp->name,yyvsp[-2].dval);
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
	      ;
    break;}
case 54:
#line 541 "parser.y"
{ // check type ??
	 if(ECHO_GRAMMAR) printf("expr -> aexpr\n");
	 if(execute) 
	   {
	     if(INTERACTIVE) printf ("\t%.10g\n", yyvsp[0].dval); yyval.dval=yyvsp[0].dval;
	   }
       ;
    break;}
case 55:
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
       ;
    break;}
case 56:
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
       ;
    break;}
case 57:
#line 582 "parser.y"
{ yyval.dval = yyvsp[0].dval;                         ;
    break;}
case 58:
#line 584 "parser.y"
{ 
	   //check type ??
	   yyval.dval = yyvsp[0].symp->value;        
          ;
    break;}
case 59:
#line 588 "parser.y"
{ yyval.dval = (*(yyvsp[-3].symp->funcptr))(yyvsp[-1].dval);       ;
    break;}
case 60:
#line 589 "parser.y"
{ yyval.dval = yyvsp[-2].dval + yyvsp[0].dval;                    ;
    break;}
case 61:
#line 590 "parser.y"
{ yyval.dval = yyvsp[-2].dval - yyvsp[0].dval;                    ;
    break;}
case 62:
#line 591 "parser.y"
{ yyval.dval = yyvsp[-2].dval * yyvsp[0].dval;                    ;
    break;}
case 63:
#line 592 "parser.y"
{ yyval.dval = yyvsp[-2].dval / yyvsp[0].dval;                    ;
    break;}
case 64:
#line 593 "parser.y"
{ yyval.dval = pow(yyvsp[-2].dval,yyvsp[0].dval);                 ;
    break;}
case 65:
#line 594 "parser.y"
{ yyval.dval = -yyvsp[0].dval; ;
    break;}
case 66:
#line 595 "parser.y"
{ yyval.dval = yyvsp[0].dval; ;
    break;}
case 67:
#line 596 "parser.y"
{ yyval.dval = yyvsp[-1].dval;                         ;
    break;}
case 68:
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
         ;
    break;}
case 69:
#line 612 "parser.y"
{ yyval.dval = (yyvsp[-2].dval < yyvsp[0].dval )? 1 : 0; ;
    break;}
case 70:
#line 613 "parser.y"
{ yyval.dval = (yyvsp[-2].dval <= yyvsp[0].dval )? 1 : 0; ;
    break;}
case 71:
#line 614 "parser.y"
{ yyval.dval = (yyvsp[-2].dval > yyvsp[0].dval )? 1 : 0; ;
    break;}
case 72:
#line 615 "parser.y"
{ yyval.dval = (yyvsp[-2].dval >= yyvsp[0].dval )? 1 : 0; ;
    break;}
case 73:
#line 616 "parser.y"
{ yyval.dval = (yyvsp[-2].dval != yyvsp[0].dval )? 1 : 0; ;
    break;}
case 74:
#line 618 "parser.y"
{ 
	    if(ECHO_GRAMMAR) printf("aexpr-> %s [ %s ]\n ",yyvsp[-3].symp->name, yyvsp[-1].symp->name); 
	    yyval.dval = property_lookup(yyvsp[-3].symp->name,yyvsp[-1].symp->name);
	  ;
    break;}
case 75:
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
	      ;
    break;}
case 76:
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
              ;
    break;}
case 77:
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
              ;
    break;}
case 78:
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
        ;
    break;}
case 79:
#line 681 "parser.y"
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
	;
    break;}
case 80:
#line 702 "parser.y"
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
        ;
    break;}
case 81:
#line 725 "parser.y"
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
	;
    break;}
case 82:
#line 748 "parser.y"
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
	;
    break;}
case 83:
#line 769 "parser.y"
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
	;
    break;}
case 84:
#line 789 "parser.y"
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
	;
    break;}
case 85:
#line 809 "parser.y"
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
	;
    break;}
case 86:
#line 829 "parser.y"
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
	;
    break;}
case 87:
#line 849 "parser.y"
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
	;
    break;}
case 88:
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
;
    break;}
case 90:
#line 897 "parser.y"
{
	    if(execute)
	      _tmparray.push_back(yyvsp[0].dval);
          ;
    break;}
case 91:
#line 902 "parser.y"
{
	   if(execute)
	     _tmparray.push_back(yyvsp[0].dval);
        ;
    break;}
case 92:
#line 908 "parser.y"
{ if(execute) quit(); ;
    break;}
case 94:
#line 910 "parser.y"
{ if(execute) print( element_list ); ;
    break;}
case 95:
#line 911 "parser.y"
{ if(execute) print( beamline_list); ;
    break;}
case 96:
#line 912 "parser.y"
{ if(execute) print(options); ;
    break;}
case 97:
#line 914 "parser.y"
{
	    if(execute)
	      {
		printf("\t");
		printf("\t%.10g\n",yyvsp[0].symp->value);
	      }
	  ;
    break;}
case 98:
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
	  ;
    break;}
case 99:
#line 936 "parser.y"
{ if(execute) expand_line(current_line,current_start, current_end);;
    break;}
case 101:
#line 938 "parser.y"
{ if(execute) printf("%s\n",yyvsp[0].str); ;
    break;}
case 102:
#line 940 "parser.y"
{
	    if(execute)
	      {  
		if(ECHO_GRAMMAR) printf("command -> SAMPLE\n");
		add_sampler("sampler",yyvsp[0].symp->name, element_count);
		element_count = 1;
		params.flush();
	      }
          ;
    break;}
case 103:
#line 950 "parser.y"
{
	    if(execute)
	      {  
		if(ECHO_GRAMMAR) printf("command -> CSAMPLE\n");
		add_csampler("sampler",yyvsp[0].symp->name, element_count,params.l, params.r);
		element_count = 1;
		params.flush();
	      }
          ;
    break;}
case 104:
#line 964 "parser.y"
{
		    if(execute)
		      {
			yyval.str = yyvsp[0].symp->name;
			current_line = yyvsp[0].symp->name;
			current_start = NULL;
			current_end = NULL;
		      }
                  ;
    break;}
case 105:
#line 974 "parser.y"
{
		    if(execute)
		      {
			yyval.str = yyvsp[-6].symp->name;
			current_line = yyvsp[-6].symp->name;
			current_start = yyvsp[-2].symp->name;
			current_end = yyvsp[0].symp->name;
		      }
		  ;
    break;}
case 106:
#line 988 "parser.y"
{ if(ECHO_GRAMMAR)  printf("sample_opt : RANGE =  %s \n",yyvsp[0].symp->name);
		  {
		    if(execute) yyval.symp = yyvsp[0].symp;
		  }
                ;
    break;}
case 107:
#line 994 "parser.y"
{
                  if(ECHO_GRAMMAR) printf("sample_opt : RANGE =  %s [%.10g] \n",yyvsp[-3].symp->name,yyvsp[-1].dval);
		    {
		      if(execute) { yyval.symp = yyvsp[-3].symp; element_count = (int)yyvsp[-1].dval; }
		    }
                ;
    break;}
case 108:
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
		  ;
    break;}
case 109:
#line 1017 "parser.y"
{
		    if(ECHO_GRAMMAR) printf("csample_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      ;//set_value($1->name,string($3));
		  ;
    break;}
case 110:
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

		  ;
    break;}
case 111:
#line 1036 "parser.y"
{
		    if(ECHO_GRAMMAR) printf("csample_opt -> %s =  %s \n",yyvsp[-2].symp->name,yyvsp[0].str);
		    if(execute)
		      ;//set_value($1->name,string($3));
		  ;
    break;}
case 112:
#line 1042 "parser.y"
{
		    if(ECHO_GRAMMAR) printf("csample_opt -> sopt, csopt\n");
		    yyval.symp = yyvsp[-2].symp;
		  ;
    break;}
case 113:
#line 1047 "parser.y"
{
		    if(ECHO_GRAMMAR) printf("csample_opt -> sopt\n");
		    yyval.symp = yyvsp[0].symp;
                  ;
    break;}
case 115:
#line 1056 "parser.y"
{
		      if(execute)
			set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		    ;
    break;}
case 116:
#line 1061 "parser.y"
{
		      if(execute)
			set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		    ;
    break;}
case 118:
#line 1069 "parser.y"
{
		    if(execute)
		      set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		  ;
    break;}
case 119:
#line 1074 "parser.y"
{
		    if(execute)
		      set_value(yyvsp[-2].symp->name,yyvsp[0].dval);
		  ;
    break;}
case 120:
#line 1079 "parser.y"
{
		    if(execute)
		      set_value(yyvsp[-2].symp->name,string(yyvsp[0].str));
		  ;
    break;}
case 121:
#line 1084 "parser.y"
{
		    if(execute)
		      set_value(yyvsp[-2].symp->name,string(yyvsp[0].str));
		  ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
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



