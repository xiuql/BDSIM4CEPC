/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#include "BDSTransportationBuilder.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>   


BDSTransportationBuilder::
BDSTransportationBuilder() {}

BDSTransportationBuilder::
~BDSTransportationBuilder() {}

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4ProcessManager.hh"


// tmp
#include "G4ProcessVector.hh"
#include "G4VProcess.hh"

void BDSTransportationBuilder::Build()
{

  G4ProcessManager * pManager = 0;
  
  pManager = G4Electron::Electron()->GetProcessManager();

  // tmp
  //  G4ProcessVector* pVec= pManager->GetProcessList();
  //  G4VProcess* proc=(*pVec)[0];
  //  G4cout<<proc->GetProcessName()<<G4endl;


  pManager->RemoveProcess(0);
  pManager->AddProcess(&theBDSTransportationProcess);
  pManager ->SetProcessOrderingToFirst(&theBDSTransportationProcess,idxAlongStep);
  pManager ->SetProcessOrderingToFirst(&theBDSTransportationProcess,idxPostStep);

  // tmp
  //  pVec= pManager->GetProcessList();
  //  proc=(*pVec)[0];
  //  G4cout<<proc->GetProcessName()<<G4endl;


  pManager = G4Positron::Positron()->GetProcessManager();
  pManager->RemoveProcess(0);
  pManager->AddProcess(&theBDSTransportationProcess);
  pManager ->SetProcessOrderingToFirst(&theBDSTransportationProcess,idxAlongStep);
  pManager ->SetProcessOrderingToFirst(&theBDSTransportationProcess,idxPostStep);
}
// 2002 by J.P. Wellisch
