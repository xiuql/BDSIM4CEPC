/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// BDSExtract
// Generates individual particles from PLACET output file
// G.A.Blair (RHUL) 10.12.01
// adapted from code supplied by D.Schulte (CERN)

#ifndef BDSExtract_h
#define BDSExtract_h 

#include "globals.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "BDSExtractBunch.hh"
#include "BDSMspline.hh"

#include "BDSSpline_tab_entry.hh"
#include "BDSSpline.hh"

typedef vector<BDSSpline*> vSpline;
typedef vector<G4double> vDbl;

class BDSExtract
{
public:
  BDSExtract (char* ExtractInputFilename);

  ~BDSExtract();

  void spline_init(double x[],int xscal,double y[],int yscal,int n,
		   BDSSpline *spline);

  double spline_int(BDSSpline *spline,double x);

  void mspline_init(double x[],int xscal,double y[],int yscal,int n,int nval,
		    BDSMspline *spline);
  void mspline_int(BDSMspline *spline,double x,double y[]);

  void spline_delete(vSpline *splineVec);

  void mspline_delete(BDSMspline *spline);

  void rndmst5(int na1,int na2,int na3, int nb1);

  float rndm5();

  float gasdev();

  void GenerateParticle(G4double& x_rndm, 
				    G4double& xp_rndm,
				    G4double& y_rndm,
				    G4double& yp_rndm,
				    G4double& z_pos,
				    G4double& e_rndm);
protected:
 
private:

  BDSExtractBunch* itsBunch;
  
  vSpline *s_e,*s_x,*s_xp,*s_y,*s_yp,*s_x_x,*s_x_xp,*s_xp_xp,*s_y_y,*s_y_yp,
    *s_yp_yp;
  
  BDSMspline *s_transv;
  //  G4double *xvalue,*yvalue,*ytransv;
  vDbl *xvalue,*yvalue,*ytransv;

};

#endif
