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

#include "BDSAcceleratorType.hh"
#include "BDSTransportation.hh"

#include "BDSLaserWirePhysics.hh"
#include "BDSPlanckScatterPhysics.hh"
#include "BDSSynchRadPhysics.hh"
#include "BDSeBremPhysics.hh"
#include "BDSGammaConversionPhysics.hh"

#include "G4Electron.hh"

BDSPhysicsList::BDSPhysicsList():  G4VModularPhysicsList()
{
  // default cut value  (1.0mm) 
  // defaultCutValue = 1.0*mm;
  defaultCutValue = 0.7*mm;  

  SetVerboseLevel(1);

  // General Physics
  RegisterPhysics( new GeneralPhysics("general") );

  // BDS Transportation
  RegisterPhysics( new BDSTransportation("BDS Transportation") );
 
  G4cout << BDSGlobals->GetUseHaloRadius() << "test"<<G4endl;
  G4cout << BDSGlobals->GetTurnOnInteractions()<<"ssdfasfasfsdff"<<G4endl;  
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
	RegisterPhysics( new EMPhysics("standard EM"));

      if(BDSGlobals->GetAcceleratorType()->GetType()!="PETRA")
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

    }

}
BDSPhysicsList::~BDSPhysicsList()
{
}

void BDSPhysicsList::SetCuts()
{
  if (verboseLevel >1){
    G4cout << "BDSPhysicsList::SetCuts:";
  }  
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types 

  G4cout<<" setting cuts" <<G4endl;

  SetCutsWithDefault();   

  /*

  // gab new:
  SetCutValue(defaultCutValue, "gamma");
  SetCutValue(defaultCutValue, "e-");
  SetCutValue(defaultCutValue, "e+");
  // end of gab new

  
  SetCutValue(kNuCut,"nu_e");
  SetCutValue(kNuCut,"nu_tau");
  SetCutValue(kNuCut,"nu_mu");
  SetCutValue(kNuCut,"anti_nu_e");
  SetCutValue(kNuCut,"anti_nu_tau");
  SetCutValue(kNuCut,"anti_nu_mu");

  //gab new:
  SetParticleCuts(defaultCutValue,G4Gamma::Gamma());
  SetParticleCuts(defaultCutValue,G4Electron::Electron());
  SetParticleCuts(defaultCutValue,G4Positron::Positron());

  */

  DumpCutValuesTable(); 
  
}
// 2002 by J.P. Wellisch
