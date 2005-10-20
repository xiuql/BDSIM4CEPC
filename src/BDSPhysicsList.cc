/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSPhysicsList.hh"

#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4ios.hh"
#include <iomanip>   

#include "GeneralPhysics.hh"
#include "EM_GNPhysics.hh"
#include "EMPhysics.hh"
#include "MuonPhysics.hh"
#include "HadronPhysicsQGSP_HP.hh"
#include "IonPhysics.hh"
#include "BDSTransportation.hh"

#include "BDSLaserWirePhysics.hh"
#include "BDSPlanckScatterPhysics.hh"
#include "BDSSynchRadPhysics.hh"
#include "BDSeBremPhysics.hh"
#include "BDSGammaConversionPhysics.hh"
#include "BDSLowEMPhysics.hh"

#include "G4Electron.hh"

extern G4bool verbose;

BDSPhysicsList::BDSPhysicsList():  G4VModularPhysicsList()
{
  defaultCutValue = 0.7*mm;  

  SetVerboseLevel(1);

  // General Physics
  RegisterPhysics( new GeneralPhysics("general") );

  // BDS Transportation
  RegisterPhysics( new BDSTransportation("BDS Transportation") );
 
  if(BDSGlobals->GetTurnOnInteractions())
    {

      if(BDSGlobals->GetUseEMHadronic())
	{
	  G4cout<<" constructing EMHadronic"<<G4endl;
	  // EM Physics
	  RegisterPhysics
	    (new EM_GNPhysics("standard EM plus electro nuclear"));
	  
	  // Hadron Physics
	  RegisterPhysics(  new HadronPhysicsQGSP_HP("hadron"));
	  
	  // Ion Physics
	  RegisterPhysics( new IonPhysics("ion"));
	}
      else
	// EM Physics
	if(!BDSGlobals->GetUseLowEMPhysics())
	  RegisterPhysics( new EMPhysics("standard EM"));
      
      // Muon Physics
      RegisterPhysics(  new MuonPhysics("muon"));
      
      
      // Special process
      if(BDSGlobals->GetPlanckOn())
	RegisterPhysics( new BDSPlanckScatterPhysics("BDSPlanckScatter"));
      
      if(BDSGlobals->GetLaserwireWavelength())
	RegisterPhysics( new BDSLaserWirePhysics("BDSLaserWire"));
      
      if(BDSGlobals->GetSynchRadOn())
	RegisterPhysics( new BDSSynchRadPhysics("BDSSynchRad"));
      
      if(BDSGlobals->GetBDSeBremOn())
	RegisterPhysics( new BDSeBremPhysics("BDSeBrem"));
      
      if(BDSGlobals->GetUseMuonPairProduction())
	RegisterPhysics( new BDSGammaConversionPhysics("BDSGamConv"));
      
      if(BDSGlobals->GetUseLowEMPhysics())
	RegisterPhysics( new BDSLowEMPhysics("LowEM"));
    }
  
}
BDSPhysicsList::~BDSPhysicsList()
{
}

void BDSPhysicsList::SetCuts()
{
  if (verbose){
    G4cout << "BDSPhysicsList:: setting cuts";
 
  }

  SetCutsWithDefault();   

  if(verbose)
    DumpCutValuesTable(); 
  
}
// 2002 by J.P. Wellisch
