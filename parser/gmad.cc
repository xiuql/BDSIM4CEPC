/*
 * GMAD interface
 *
 */

#include "gmad.h"

extern struct Parameters params;

extern int yyparse();

extern FILE *yyin;

extern int add_func(char *name, double (*func)(double));

int gmad_parser(FILE *f)
{
  // embedded arithmetical functions
  add_func("sqrt",sqrt);
  add_func("cos",cos);
  add_func("sin",sin);
  add_func("exp",exp);
  add_func("log",log); 
  add_func("tan",tan);
  
  params.flush();
  
  yyin=f; 
  while(!feof(yyin))
    {
      yyparse();
    }
  
  
  return 0;
};

int gmad_parser(string name)
{
  FILE *f = fopen(name.c_str(),"r");

  // embedded arithmetical functions
  add_func("sqrt",sqrt);
  add_func("cos",cos);
  add_func("sin",sin);
  add_func("exp",exp);
  add_func("log",log); 
  add_func("tan",tan);
  
  params.flush();
  
  yyin=f; 
  while(!feof(yyin))
    {
      yyparse();
    }
  
  
  return 0;
};

