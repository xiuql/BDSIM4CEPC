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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 22 "parser.y"
typedef union YYSTYPE {
  double dval;
  int ival;
  struct symtab *symp;
  char *str;
  struct Array *array;
} YYSTYPE;
/* Line 1275 of yacc.c.  */
#line 125 "parser.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;


