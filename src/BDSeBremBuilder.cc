/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#include "BDSeBremBuilder.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4ProcessManager.hh"

BDSeBremBuilder::BDSeBremBuilder() 
{}

BDSeBremBuilder::
~BDSeBremBuilder() {}


void BDSeBremBuilder::Build()
{

  G4ProcessManager * pManager = 0;
  

  pManager = G4Electron::Electron()->GetProcessManager();
  pManager->AddProcess(&theeBremProcess);
  pManager->SetProcessOrderingToLast(&theeBremProcess,idxPostStep);

  pManager = G4Positron::Positron()->GetProcessManager();
  pManager->AddProcess(&theeBremProcess);
  pManager->SetProcessOrderingToLast(&theeBremProcess,idxPostStep);

}
// 2002 by G.A.Blair (after J.P. Wellisch)
