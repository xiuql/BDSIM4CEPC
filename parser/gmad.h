/*
 * GMAD interface 
 * I. Agapov 2005
*/

#ifndef _GMAD_H
#define _GMAD_H

#include <iostream>
#include <stdio.h>
#include <list>
#include <string>

using namespace std;

// types of elements

const int _NONE = -1;
const int _MARKER = 100;
const int _DRIFT = 0;
const int _SBEND = 1; 
const int _QUAD  = 2;
const int _SEXT  = 3;
const int _OCTUPOLE = 4;
const int _MULT  = 5;
const int _SOLENOID = 6;
const int _LINE = 10;
const int _OPTION = 20;


const char *typestr(int type);

struct Options {
  int echo;
  int sr;
  char particle[32];
  double energy;
  int nparticles;
};

struct Element {
  short type;
  char * name;
  
  double l,k0,k1,k2,k3;
  
  list<double> knl;
  list<double> ksl;
  
  // in case the element is a list itself (line)
  list <struct Element> *lst;
  
};


struct Parameters {
  double l;  int lset;    // length
  double k0; int k0set;   // dipole 
  double k1; int k1set;   // quadrupole
  double k2; int k2set;   // sextupole
  double k3; int k3set;   // octupole
  
  list<double> knl;           // multipole expansion coefficients
  list<double> ksl;           // skew multipole expansion
  
  int knlset; int kslset;
  
  void flush() {
    l=0; lset = 0;
    k0 = 0; k0set = 0;
    k1 = 0; k1set = 0;
    k2 = 0; k2set = 0;
    k3 = 0; k3set = 0;
    
    knlset = 0; kslset=0;
    knl.erase(knl.begin(),knl.end());
    ksl.erase(ksl.begin(),ksl.end());
    
  }
};


extern list<struct Element> beamline_list;
extern struct Options options;

// parse the input file and construct beamline_list and options 
int gmad_parser(FILE *f);

int gmad_parser(string name);


#endif
