/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: BDSEventAction.hh,v 1.1.1.1 2004/11/18 17:42:38 ilia Exp $
// GEANT4 tag $Name:  $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef BDSEventAction_h
#define BDSEventAction_h 1
#include "BDSGlobalConstants.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"
#include "BDSAcceleratorComponent.hh"
#include "BDSEnergyCounterSD.hh"
#include <list>

#include "TFile.h"

class BDSEventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class BDSEventAction : public G4UserEventAction
{
public:
  BDSEventAction();
  virtual ~BDSEventAction();

public:
  virtual void   BeginOfEventAction(const G4Event*);
  virtual void   EndOfEventAction(const G4Event*);
  
  void SetDrawFlag   (G4String val)  {drawFlag = val;};
  void SetPrintModulo(G4int    val)  {printModulo = val;};
 
  G4String StringFromInt(G4int N);

  TFile* GetRootOutputFile();

  private:
    G4int                       SamplerCollID;                
  //    G4int                       EnergyCounterCollID;                
    G4String                    drawFlag;
    G4int                       printModulo;                         
    BDSEventActionMessenger*  eventMessenger;


  G4int itsOutputFileNumber;
  G4int itsRecordSize;

  list<BDSAcceleratorComponent*>::const_iterator iBeam;
  list<BDSEnergyCounterSD*>::const_iterator iEC;

  BDSAcceleratorComponent* LastComp;
  ofstream* BunchOutputFile;
  TFile* itsRootOutputFile;
  
};

inline TFile* BDSEventAction::GetRootOutputFile()
{return itsRootOutputFile;}


#endif

    
