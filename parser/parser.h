/* parser.h
 *
 *
 */

#ifndef __PARSER_H
#define __PARSER_H

#include "sym_table.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "gmad.h"


using namespace std;


double pow(double x, double y) {return exp( y * log(x));}

int yyerror(char *);

extern FILE* yyin;
extern int yylex();


const int MAX_EXPAND_ITERATIONS = 50;
const int MAX_MULTIPOLE_ORDER = 5;

const int _undefined = 0;

list<double> _tmparray;  // for reading of arrays

// representation of arrays used in tokens
struct Array {
  double *data;
  int size;
};


const char *typestr(int type) {
  switch(type){
  case _MARKER : 
    return "marker";
  case _DRIFT :
    return "drift";
  case _SBEND : 
    return "sbend";
  case _QUAD :
    return "quadrupole";
  case _SEXT:
    return "sextupole";
  case _MULT :
    return "multipole";
  case _SOLENOID : 
    return "solenoid";
  case _LINE :
    return "line";
  default:
    return "none";
  }
};
struct Parameters params;
struct Options options;
struct Element element;

void print(struct Parameters params)
{
  printf("printing parameters:\n");
  list<double>::iterator it;
  for(it = params.knl.begin();it!=params.knl.end();it++)
    printf(" %f ", (*it));
  printf("\n");
};

void flush(struct Element& e )
{
  e.l = 0;
  e.k0 = 0;
  e.k1 = 0;
  e.k2 = 0;
  e.name = NULL;
  e.type = _NONE;
};

void copy_properties(list<struct Element>::iterator dest, list<struct Element>::iterator src)
{

  if(DEBUG) printf("%s %s \n",typestr((*dest).type),typestr((*src).type));

  (*dest).type = (*src).type;  
 
  (*dest).l = (*src).l;
 
  (*dest).k0 = (*src).k0; 
  (*dest).k1 = (*src).k1;  
  (*dest).k2 = (*src).k2; 
  (*dest).k3 = (*src).k3; 
  (*dest).knl = (*src).knl;
  (*dest).ksl = (*src).ksl;
  return;
}; 

void inherit_properties(struct Element e)
{
  // copy parameters into temporary buffer params from element e
  // parameters already set in params have priority and are not overridden
  
  if(!params.lset) { params.l = e.l; params.lset = 1; }
  if(!params.k0set) { params.k0 = e.k0; params.k0set = 1; }
  if(!params.k1set) { params.k1 = e.k1; params.k1set = 1; }
  if(!params.k2set) { params.k2 = e.k2; params.k2set = 1; }
  if(!params.k3set) { params.k3 = e.k3; params.k3set = 1; }
  if(!params.knlset) { params.knl = e.knl; params.knlset = 1; }
  if(!params.kslset) { params.ksl = e.ksl; params.kslset = 1; }
};

void set_vector(list<double>& dst, struct Array *src)
{
  for(int i=0; i< src->size;i++)
    dst.push_back(src->data[i]);
};

// lis of all encountered elements
list<struct Element> element_list;

// temporary list
list<struct Element> tmp_list;

list<struct Element> beamline_list;


char* current_line = "";
char* current_start = "";
char* current_end = "";

struct symtab symtab[NSYMS];

extern struct symtab * symlook(char *s);

list<struct Element>::iterator element_lookup(char *name);
list<struct Element>::iterator element_lookup(char *name, list<struct Element>& el);
int write_table(struct Parameters params,char* name, int type, list<struct Element> *lst=NULL);
int expand_line(char *name, char *start, char *end);
void print(list<struct Element> l, int ident=0);

// *********************
// functions
// *********************


void help()
{
  printf("helping...\n");
}

void quit()
{
  printf("parsing complete...\n");
  exit(0);
}

int write_table(struct Parameters params,char* name, int type, list<struct Element> *lst)
{
  if(DEBUG) printf("k1=%.10g ,k2=%.10g, type=%d, lset = %d\n",params.k1, params.k2, type,params.lset);
  
  struct Element e;
  flush(e);
  e.name = name;
  e.lst = NULL;
  
  switch(type) {
  case _MARKER :
    e.type= _MARKER;
    break;
  case _DRIFT:
    e.type = _DRIFT;
    e.l = params.l;
    break;

  case _QUAD:

    e.type = _QUAD;
      
    if(params.lset) {
      e.l = params.l;
    }
    if(params.k0set) {
      if(VERBOSE)
	printf("Warning: k2 will not be set for element %s of type QUADRUPOLE\n",name);
    }
    if(params.k1set) {
      e.k1 = params.k1;
    }
    if(params.k2set) {
      if(VERBOSE)
	printf("Warning: k2 will not be set for element %s of type QUADRUPOLE\n",name);
    }
    
    break;
  case _SBEND:
    
    e.type = _SBEND;
    
    if(params.lset) {
      e.l = params.l;
    }
    if(params.k1set) {
      if(VERBOSE)
	printf("Warning: k1 will not be set for element %s of type SBEND\n",name);
    }
    if(params.k0set) {
      e.k0 = params.k0;
    }
    if(params.k2set) {
      if(VERBOSE)
	printf("Warning: k2 will not be set for element %s of type SBEND\n",name);
    }
    
    break;

  case _MULT:
    
    e.type = _MULT;
    
    if(params.knlset)
      e.knl = params.knl;

    if(params.kslset)
      e.ksl = params.ksl;

    if(params.lset) {
      e.l = params.l;
    }
    if(params.k1set) {
      if(VERBOSE)
	printf("Warning: k1 will not be set for element %s of type MULTIPOLE\n",name);
    }
    if(params.k0set) {
      if(VERBOSE)
	printf("Warning: k0 will not be set for element %s of type MULTIPOLE\n",name);
    }
    if(params.k2set) {
      if(VERBOSE)
	printf("Warning: k2 will not be set for element %s of type MULTIPOLE\n",name);
    }
    
    break;

  case _LINE:
   
    e.lst = lst;
    e.type = _LINE;
    break;
    
  default:
    break;  
  }

  element_list.push_back(e);
}

int expand_line(char *name, char *start, char* end)
{
  list<struct Element>::iterator it;
  
  struct Element e;
  
  it = element_lookup(name);
  
  if( (it!=NULL) && ((*it).type == _LINE) ) 
    {
      
      // delete the previous beamline
      
      beamline_list.erase(beamline_list.begin(),beamline_list.end());
      
      // expand the desired beamline
      
      e.type = _LINE;
      e.name = name;
      e.lst = NULL;
      
      beamline_list.push_back(e);
      
      if(VERBOSE) printf("expanding line %s, range = %s/%s\n",name,start,end);
      
      if(!(*it).lst) return 0; //list empty
      
      // first expand the whole range the range
      list<struct Element>::iterator sit = (*it).lst->begin();
      list<struct Element>::iterator eit = (*it).lst->end();
      
      
      
      // copy the list into the resulting list
      beamline_list.insert(beamline_list.end(),(*it).lst->begin(),(*it).lst->end());
      
      bool is_expanded = false;
      
      // parse starting from the second element until the list is expanded
      int iteration = 0;
      while(!is_expanded)
        {
	  is_expanded = true;
	  for(it = ++beamline_list.begin();it!=beamline_list.end();it++ )
	    {
	      printf("%s , %s \n",(*it).name,typestr((*it).type));
	      
	      if((*it).type == _LINE)  // list - expand further	  
		{
		  is_expanded = false;
		  // lookup the line in main list
		  list<struct Element>::iterator tmpit = element_lookup((*it).name);
		  
		  if( (tmpit != NULL) && ( (*tmpit).lst != NULL) ) { // sublist found and not empty
		    
		    if(DEBUG)
		      printf("inserting sequence for %s - %s ...",(*it).name,(*tmpit).name);
		    
		    beamline_list.insert(it,(*tmpit).lst->begin(),(*tmpit).lst->end());
		    
		    if(DEBUG) printf("inserted\n");
		    
		    // delete the list pointer
		    beamline_list.erase(it--);
		    
		  } else if ( tmpit != NULL ) // entry points to a scalar element type -
		    //transfer properties from the main list
		    { 
		      if(DEBUG) printf("keeping element...%s\n",(*it).name);
		      copy_properties(it,tmpit);
		      if(DEBUG) printf("done\n");

		    } else  // element of undefined type - neglecting
		      {
			if(VERBOSE)
			  printf("Warning : Expanding line %s : element %s has not been \
                               defined , skipping \n",name,(*it).name);
			beamline_list.erase(it--);
		      }
		  
		} else  // element - keep as it is 
		  {
		    // do nothing
		  }
	      
	    }
	  iteration++;
	  if( iteration > MAX_EXPAND_ITERATIONS )
	    {
	      printf("Error : Line expansion of '%s' seems to loop, \
                     \n possible recursive line definition,quitting \n",name);
	      exit(0);
	    }
	  
	}// while
      
      
      // leave only the desired range
      //
      // rule - from first occurence of 'start' till first 'end' coming after 'start'


      if( (start!=NULL)) // determine  the start element
	{
	  sit = element_lookup(start,beamline_list);
	  
	  if(sit==NULL)
	    {
	      sit = beamline_list.begin();
	    }
	  
	  if(!strcmp(start,"#s")) sit = beamline_list.begin(); 
	  
	  beamline_list.erase(beamline_list.begin(),sit);

	}

      if( (end!=NULL)) // determine  the end element
	{
	  eit = element_lookup(end,beamline_list);
	  
	  if(eit==NULL)
	    {
	      eit = beamline_list.end();
	    }
	  
	  if(!strcmp(end,"#e")) eit = beamline_list.end();	  


	  beamline_list.erase(++eit,beamline_list.end());
	}


      
      
      return 0;
    }
  
  
  printf("line '%s' not found",name);
  return 1;
  
}

list<struct Element>::iterator element_lookup(char *name)
{
   list<struct Element>::iterator it;

   for(it=element_list.begin();it!=element_list.end();it++)
     {
       if(!strcmp((*it).name,name) )
	 return it;
     }
   return NULL;
}

list<struct Element>::iterator element_lookup(char *name,list<struct Element>& el)
{
   list<struct Element>::iterator it;

   for(it=el.begin();it!=el.end();it++)
     {
       if(!strcmp((*it).name,name) )
	 return it;
     }
   return NULL;
}


void print(list<struct Element> l, int ident)
{

  if(VERBOSE) if(ident == 0) printf("using line %s\n",current_line);

  list<struct Element>::iterator it;

  for(it=l.begin();it!=l.end();it++)
    {
      for(int i=0;i<ident;i++)
	printf("--");

      printf("->%s : %s",(*it).name,typestr((*it).type));

      switch((*it).type) {
      case _SBEND :
      case _QUAD:
	printf(", l=%.10g, k0=%.10g, k1=%.10g, k2=%.10g ",
	       (*it).l,(*it).k0,(*it).k1,(*it).k2);
	break;
      case _MULT:
	list<double>::iterator it2;
	printf(" , knl={");
	for(it2=(*it).knl.begin();it2!=(*it).knl.end();it2++)
	  printf("%.10g, ",(*it2));
	printf("},  ksl={");
	for(it2=(*it).ksl.begin();it2!=(*it).ksl.end();it2++)
	  printf("%.10g, ",(*it2));
	printf("}");
	break;

      defaut:
	break;
      }

      printf("\n");

      if((*it).lst != NULL)
	{
	  print(*(*it).lst,++ident);
	  ident--;
	}
    }
}

void print(struct Options opt)
{
  printf(" Options: \n");
  printf("         echo  :   %d\n",options.echo);
  printf("         particle  :   %s\n",options.particle);
  printf("         echo  :   %d\n",options.nparticles);
}

// ******************************************************
// parser functions
// ******************************************************


int add_func(char *name, double (*func)(double))
{
  struct symtab *sp=symlook(name);
  sp->funcptr=func;
}

int add_var(char *name, double value)
{
  struct symtab *sp=symlook(name);
  sp->value=value;
}

#endif


