/*
 *  Lexical analyzer for gmad bison parser  
 *  Ilya Agapov, 2005
 *  
*/



%x incl

%option yylineno


%{
  
#include <iostream>
#include <string.h>
#include "parser.tab.h"
#include "sym_table.h"
  
using namespace std;
 
int match_var(char *name);
struct symtab * symlook(char *s);
extern struct symtab *symtab;
extern int yyerror(char *s);

#define MAX_INCLUDE_DEPTH 10
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

//#define YY_USER_ACTION yylloc.first_line = yylineno;\
//                       yylloc.last_line = yylineno;

%}

%s ERROR

%%

[\t ]+     //ignore whitespaces

"!".*/\n {yylineno--;}    // ignore comments; there is a feature so that yylineno increases twice

(([0-9]+)|([0-9]*\.[0-9]*))(e[+|-]?[0-9]+)? { yylval.dval=atof(yytext); return NUMBER; }


"<=" { return LE; }
">=" { return GE; }
"!=" { return NE; }

marker { return MARKER; } // reserved elements
drift { return DRIFT; }
dipole { return DIPOLE; }
sbend { return SBEND; } 
quadrupole { return QUADRUPOLE; }
sextupole { return SEXTUPOLE; }
octupole { return OCTUPOLE; }
multipole { return MULTIPOLE; }
solenoid { return SOLENOID; }
spoiler { return SPOILER ; }
rcol { return RCOL;}
ecol { return ECOL; } 
absorber { return ABSORBER; }
element { return ELEMENT; }
collimator { return COLLIMATOR; }
pipe { return PIPE; }
gas { return GAS; }
laser { return LASER; }

line       { return LINE; } 

apertr {return APERTURE; } // reserved keywords
filename { return FILENAME; }
period { return PERIOD; }
range { return RANGE; }

"if" { return IF; }
"for" { return FOR; }
"else" { return ELSE; } 
"begin" { return BEGN; }
"end" { return END; }


include     BEGIN(incl);  //reserved commands

beam { return BEAM; }
option { return OPTION; }
print { return PRINT; }
echo { return ECHO; }
"return" { return STOP; }
stop {return STOP;}
use { return USE; }
sample { return SAMPLE; }
csample { return CSAMPLE; }

\"[^"]*\" {
  //strip quotes
  
  yylval.str=yytext+1;
  yylval.str[strlen(yylval.str)-1]='\0';
  return STR; 
}

":="    { return '=';}  // alternative assignment 

[a-zA-Z#][A-Za-z0-9_#]* {
     struct symtab *sp = symlook(yytext);
     yylval.symp=sp;
     if(sp->funcptr)
       return FUNC;
     else 
     if(sp->type == _ARRAY)
       return VECVAR;
     else
       return VARIABLE; 
}
.    { return yytext[0]; }

<incl>[ \t]*  // eat the whitespace
<incl>[^ \t\n;]+ {
  printf("reading file %s \n",yytext);
  if( include_stack_ptr >= MAX_INCLUDE_DEPTH )
    {
      fprintf(stderr , "Error : Include depth exceeds %d\n",MAX_INCLUDE_DEPTH);
      exit(1);
    }
  else
    {
      yyin = fopen(yytext, "r");
      if(yyin)
	{
	  include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
	  yy_switch_to_buffer(yy_create_buffer( yyin, YY_BUF_SIZE ) );
	}
      else
	{
	  fprintf(stderr, "Error : can't open %s\n", yytext);
	  exit(1);
	}
    }
  BEGIN(INITIAL);
}

<<EOF>> {
  if (--include_stack_ptr < 0)
    {
      yyterminate();
    }
  else
    {
      yy_delete_buffer(YY_CURRENT_BUFFER);
      yy_switch_to_buffer(include_stack[include_stack_ptr]);
    }
}

%%


struct symtab * symlook(char *s)
{
  char *p;
  struct symtab *sp;
  for( sp=symtab;sp<&symtab[NSYMS];sp++) {
    if(sp->name && !strcmp(sp->name,s)) return sp;
    if(!sp->name) {sp->name=strdup(s); return sp;}
  }
  yyerror("too many symbols");
  exit(1);
}

