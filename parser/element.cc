#include "element.h"
#include "enums.h"

// extern const char* current_line;
// extern const int VERBOSE;

namespace {
void print(std::list<struct Element> l, int ident)
{
  //  if(VERBOSE) if(ident == 0) printf("using line %s\n",current_line);

  for(std::list<struct Element>::iterator it=l.begin();it!=l.end();it++)
    {
      (*it).print(ident);
    }
}
}

void Element::print(int & ident)const{
  for(int i=0;i<ident;i++)
    printf("--");

  printf("->%s : %s",name.c_str(),typestr(type));

  std::list<double>::const_iterator it;
  switch(type) {
  case _DRIFT:
  case _PCLDRIFT:
  case _SBEND:
  case _RBEND:
  case _QUAD:
  case _SEXTUPOLE:
  case _OCTUPOLE:
    printf(", l=%.10g, k0=%.10g, k1=%.10g, k2=%.10g, k3=%.10g, angle=%.10g,tilt=%.10g ",
	   l,k0,k1,k2,k3,angle,tilt);
    break;
    
  case _SOLENOID:
    printf(", l=%.10g, ks=%.10g ", l, ks);
    break;
    
  case _MULT:
    printf(" , knl={");
    for(it=knl.begin();it!=knl.end();++it)
      printf("%.10g, ",(*it));
    printf("},  ksl={");
    for(it=ksl.begin();it!=ksl.end();++it)
      printf("%.10g, ",(*it));
    printf("}");
    break;
    
  case _ELEMENT:
    printf("\ngeometry file : %s\n",geometryFile.c_str());
    printf("B map file : %s\n",bmapFile.c_str());
    //printf("E map driver : %s\n",geometryFile);
    //printf("E map file : %s\n",geometryFile);
    break;
    
  case _SCREEN:
    break;
    
  case _CSAMPLER:
    printf(" length=%.10g, radius=%.10g",l, r);
    break;
    
  case _TRANSFORM3D:
    printf(" xdir=%.10g, ydir=%.10g, zdir=%.10g,  phi=%.10g, theta=%.10g,psi=%.10g",
	   xdir, ydir, zdir, phi, theta, psi);
    break;
  case _MATERIAL:
    printf(" A=%.10g, Z=%.10g, density=%.10g,  temper=%.10g, pressure=%.10g",
	   A, Z, density, temper, pressure);
    break;
  default:
    break;
  }
  
  printf("\n");
  
  if(lst != NULL)
    {
      ::print(*lst,++ident);
      ident--;
    }
}
