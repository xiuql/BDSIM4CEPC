/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#include "BDSGlobalConstants.hh"

#include "BDSGammaConversionPhysics.hh"
#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>   
#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"


BDSGammaConversionPhysics::
BDSGammaConversionPhysics(const G4String& name) : G4VPhysicsConstructor(name) {}

BDSGammaConversionPhysics::
~BDSGammaConversionPhysics() {}

void BDSGammaConversionPhysics::
ConstructParticle()
{
  G4Electron::ElectronDefinition();
  G4Gamma::GammaDefinition();
  G4Positron::PositronDefinition();

  if(BDSGlobals->GetUseMuonPairProduction()||BDSGlobals->GetBDSeBremOn())
    {
      G4MuonPlus::MuonPlusDefinition();
      G4MuonMinus::MuonMinusDefinition();      
    }
}

void BDSGammaConversionPhysics::ConstructProcess()
{
  if(BDSGlobals->GetLaserwireWavelength())
    {
      theBDSGammaConversionBuilder.Build();
    }
}



// 2002 by G.A.Blair (after J.P. Wellisch)
