#include "BDSGlobalConstants.hh"

#include "BDSTransportation.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "iomanip"   
#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"


BDSTransportation::
BDSTransportation(const G4String& name) : G4VPhysicsConstructor(name) {}

BDSTransportation::
~BDSTransportation() {}

void BDSTransportation::
ConstructParticle()
{
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
}

void BDSTransportation::
ConstructProcess()
{
  theBDSTransportation.Build();
}



// 2002 by J.P. Wellisch
