typedef union{
  double dval;
  int ival;
  struct symtab *symp;
  char *str;
  struct Array *array;
} YYSTYPE;
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


extern YYSTYPE yylval;
