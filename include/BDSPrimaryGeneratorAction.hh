/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 

   Modified 22.03.05 by J.C.Carter, Royal Holloway, Univ. of London.
   Added GABs SynchGen code
*/

// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: BDSPrimaryGeneratorAction.hh,v 1.1 2005/01/22 17:05:31 agapov Exp $
// GEANT4 tag $Name:  $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef BDSPrimaryGeneratorAction_h
#define BDSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include <fstream>
#include "BDSExtract.hh"
#include "BDSSynchrotronRadiation.hh"

#include "BDSGen5Shell.hh"

// tmp
//#include "BDSExtractO.hh"

using std::ifstream;
using std::ostream;

class G4ParticleGun;
class G4Event;
class BDSDetectorConstruction;
class BDSPrimaryGeneratorMessenger;
class RandGauss;
class RandFlat;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class BDSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  BDSPrimaryGeneratorAction(BDSDetectorConstruction*);    
  ~BDSPrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);
  void SetRndmFlag(G4String val) { rndmFlag = val;}
  
private:
  G4ParticleGun*                particleGun;	  //pointer a to G4 service class
  BDSDetectorConstruction*    BDSDetector;  //pointer to the geometry
  
  BDSPrimaryGeneratorMessenger* gunMessenger; //messenger of this class
  G4String                      rndmFlag;    //flag for a random impact point       
  // beam data:
  G4double beta_x,sig_z,KineticEnergy,
    gamma,beta_y,sig_dp,emit_x,emit_y,charge;
  G4double sig_x,sig_xp,sig_y,sig_yp,sig_t;
  
  // Gaussian Random number generator:
  RandGauss* GaussGen;
  RandFlat* FlatGen;
  
  ifstream InputBunchFile;
  ifstream ExtractBunchFile;
  BDSExtract* itsBDSExtract;

  BDSGen5Shell* itsBDSGen5Shell;

  G4double logXfactor;
  G4double logYfactor;

  G4double itsSynchCritEng;
  BDSSynchrotronRadiation* itsBDSSynchrotronRadiation;

  // tmp
  //  BDSExtractO* itsBDSExtractO;

};

#endif


