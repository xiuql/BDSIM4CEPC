/* BDSIM code.    Version 1.0
   Author: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 7.12.2004
   Copyright (c) 2004 by J.C.Carter.  ALL RIGHTS RESERVED. 
*/

#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSLowEMPhysics.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>   

#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"


BDSLowEMPhysics::BDSLowEMPhysics(const G4String& name)
               :  G4VPhysicsConstructor(name)
{
}

BDSLowEMPhysics::~BDSLowEMPhysics()
{
}

void BDSLowEMPhysics::ConstructParticle()
{
  // gamma
  G4Gamma::GammaDefinition();
 
  // electron
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
}

void BDSLowEMPhysics::ConstructProcess()
{
  G4ProcessManager * pManager = 0;
  
  // Gamma Physics
  pManager = G4Gamma::Gamma()->GetProcessManager();

  pManager->AddDiscreteProcess(&theLowEnPhoto);
  pManager->AddDiscreteProcess(&theLowEnCompton);
  pManager->AddDiscreteProcess(&theLowEnPair);
  pManager->AddDiscreteProcess(&theLowEnRayleigh);
  
  // Electron Physics
  pManager = G4Electron::Electron()->GetProcessManager();

     // Low energy
  pManager->AddProcess(&theLowEnBremss,-1,-1,3);
  pManager->AddProcess(&theLowEnIon,1,2, 2);

     // Std still needed 
  pManager->AddProcess(&theeminusMultipleScattering,-1,1,1);
  
  // Positron Physics

     // Std still needed
  pManager = G4Positron::Positron()->GetProcessManager();

  pManager->AddProcess(&theeplusMultipleScattering,-1,1,1);
  pManager->AddProcess(&theeplusIonisation,-1,2,2);
  pManager->AddProcess(&theeplusBremsstrahlung,-1,-1,3);
  pManager->AddProcess(&theeplusAnnihilation,0,-1,4);
}



