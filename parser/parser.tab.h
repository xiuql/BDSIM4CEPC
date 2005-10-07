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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 23 "parser.y"
typedef union YYSTYPE {
  double dval;
  int ival;
  struct symtab *symp;
  char *str;
  struct Array *array;
} YYSTYPE;
/* Line 1268 of yacc.c.  */
#line 147 "parser.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



