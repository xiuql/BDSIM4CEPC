// BDSRK4Stepper modified from geant4.8.01 version
// Includes RadiusOfCurvature needed to produce Synchrotron Radiation
//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4ClassicalRK4.cc,v 1.11 2003/11/05 16:31:48 japost Exp $
// GEANT4 tag $Name: geant4-08-00-patch-01 $
//
// -------------------------------------------------------------------

#include "BDSRK4Stepper.hh"
#include "G4ThreeVector.hh"

//////////////////////////////////////////////////////////////////
//
// Constructor sets the number of variables (default = 6)

extern G4double BDSLocalRadiusOfCurvature;

BDSRK4Stepper::BDSRK4Stepper(G4EquationOfMotion* EqRhs, G4int numberOfVariables)
  : G4MagErrorStepper(EqRhs, numberOfVariables)
    // fNumberOfVariables(numberOfVariables)
{
  itsEqRhs = EqRhs;
   unsigned int noVariables= std::max(numberOfVariables,8); // For Time .. 7+1
 
   dydxm = new G4double[noVariables];
   dydxt = new G4double[noVariables]; 
   yt    = new G4double[noVariables]; 
}

////////////////////////////////////////////////////////////////
//
// Destructor

BDSRK4Stepper::~BDSRK4Stepper()
{
  delete[] dydxm;
  delete[] dydxt;
  delete[] yt;
}

//////////////////////////////////////////////////////////////////////
//
// Given values for the variables y[0,..,n-1] and their derivatives
// dydx[0,...,n-1] known at x, use the classical 4th Runge-Kutta
// method to advance the solution over an interval h and return the
// incremented variables as yout[0,...,n-1], which not be a distinct
// array from y. The user supplies the routine RightHandSide(x,y,dydx),
// which returns derivatives dydx at x. The source is routine rk4 from
// NRC p. 712-713 .

void
BDSRK4Stepper::DumbStepper( const G4double  yIn[],
                             const G4double  dydx[],
                                   G4double  h,
                                   G4double  yOut[])
{
  const G4int nvar = this->GetNumberOfVariables();   //  fNumberOfVariables(); 
  G4int i;
  G4double  hh = h*0.5 , h6 = h/6.0  ;

  // Initialise time to t0, needed when it is not updated by the integration.
  //        [ Note: Only for time dependent fields (usually electric) 
  //                  is it neccessary to integrate the time.] 
  yt[7]   = yIn[7]; 
  yOut[7] = yIn[7];

  // Have to calculate total Energy assuming Mass = zero
  // because have no way to see particle type here (and hence no mass info)
  const G4double *pIn = yIn+3;
  G4double itsEnergy = sqrt(pIn[0]*pIn[0]+pIn[1]*pIn[1]+pIn[2]*pIn[2]);
  
  G4double BField[3];
  G4double Pos[4];
  Pos[0] = yIn[0];
  Pos[1] = yIn[1];
  Pos[2] = yIn[2];
  Pos[3] = 0.;
  itsEqRhs->GetFieldObj()->GetFieldValue(Pos,BField);

  
  G4ThreeVector BVec = G4ThreeVector(BField[0],
				     BField[1],
				     BField[2]);
  G4ThreeVector pVec = G4ThreeVector(pIn[0],
				     pIn[1],
				     pIn[2]);

  G4double Bmag = (BVec.cross(pVec.unit())).mag();
  
  
  BDSLocalRadiusOfCurvature = (itsEnergy/GeV) / (0.3*Bmag/tesla)*m;

  for(i=0;i<nvar;i++)
  {
    yt[i] = yIn[i] + hh*dydx[i] ;             // 1st Step K1=h*dydx
  }
  RightHandSide(yt,dydxt) ;                   // 2nd Step K2=h*dydxt

  for(i=0;i<nvar;i++)
  { 
    yt[i] = yIn[i] + hh*dydxt[i] ;
  }
  RightHandSide(yt,dydxm) ;                   // 3rd Step K3=h*dydxm

  for(i=0;i<nvar;i++)
  {
    yt[i]   = yIn[i] + h*dydxm[i] ;
    dydxm[i] += dydxt[i] ;                    // now dydxm=(K2+K3)/h
  }
  RightHandSide(yt,dydxt) ;                   // 4th Step K4=h*dydxt
 
  for(i=0;i<nvar;i++)    // Final RK4 output
  {
    yOut[i] = yIn[i]+h6*(dydx[i]+dydxt[i]+2.0*dydxm[i]); //+K1/6+K4/6+(K2+K3)/3
  }
  // NormaliseTangentVector( yOut );
  
}  // end of DumbStepper ....................................................


