/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// BDSMSpline
// Generates individual particles from PLACET output file
// G.A.Blair (RHUL) 10.12.01
// adapted from code supplied by D.Schulte (CERN)

#ifndef BDSMspline_h
#define BDSMspline_h 1
 
#include "globals.hh"
#include <vector>
using std::vector;
typedef vector<G4double> vDbl;

class BDSMspline
{
public:

  BDSMspline(G4int nIn,G4int nvalIn);
  ~BDSMspline();

  void initialise(vDbl* xIn, G4int xscalIn, vDbl* yIn, G4int yscalIn);

  void integrate(G4double xIn, vDbl* yOut);

  const G4int n,nval;
  G4int xscal,yscal;

  //  G4double *x,*y,*y2; 
  vDbl x,y,y2; 

private:
  vDbl u;
};

#endif
