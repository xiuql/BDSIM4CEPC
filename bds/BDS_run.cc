/** BDSIM code.    Version 1.0
   @Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   @Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

//#include "G4RunManager.hh"
#include "BDSGlobalConstants.hh" // must be first in the list
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4HadronInelasticProcess.hh"

#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif

#include "Randomize.hh"

#ifdef G4VIS_USE
#include "BDSVisManager.hh"
#endif

//#define DECFortran 1
//#include "/cern/pro/include/cfortran/cfortran.h"
//#include "/cern/pro/include/cfortran/packlib.h"
//#include "packlib.h"

#include "stdlib.h"      
#include <stdio.h>

// tmp
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"


//=======================================================

//#define PAWC_SIZE 5000000c
//typedef struct { float PAW[PAWC_SIZE]; } PAWC_DEF;
//#define PAWC COMMON_BLOCK(PAWC,pawc)
//COMMON_BLOCK_DEF(PAWC_DEF,PAWC);
//PAWC_DEF PAWC;

// link to G4eBremsstrahlung.cc and G4GammaConversion.cc for muon studies
G4bool UsePrimaryPhoton_gab=false;

//=======================================================
#include "BDSDetectorConstruction.hh"
#include "BDSPhysicsList.hh"
#include "BDSPrimaryGeneratorAction.hh"
#include "BDSRunAction.hh"
#include "BDSEventAction.hh"
#include "BDSSteppingAction.hh"
#include "BDSUserTrackingAction.hh"
#include "BDSSteppingVerbose.hh"
#include "G4UItcsh.hh"
#include "BDSRunManager.hh"

#include "BDSRootObjects.hh"

BDSGlobalConstants* BDSGlobals;
BDSRootObjects* BDSRoot;


int main(int argc,char** argv) {


  // Read in the global constants
  BDSGlobals=new BDSGlobalConstants("BDSInput.cards");
  BDSRoot=new BDSRootObjects();

  gDirectory->mkdir("Histos");
  gDirectory->mkdir("Trees");
  gDirectory->mkdir("Trajectories");


  // paw stuff:
  //HLIMIT(PAWC_SIZE);
  //  G4int record_size=1024;
  //  G4int istat,icycle;
  //  HROPEN(1,"sampler","sampler_output.rz","N",record_size,istat);

  //  HMDIR("//sampler","S");
  //  HCDIR("//sampler"," ");

  // ROOT stuff:
  TROOT RootStartup("BDSROOT", "Beam Delivery System Simulation");

  // set default output formats:
  G4cout.precision(10);

  // choose the Random engine
  HepRandom::setTheEngine(new RanecuEngine);
  HepRandom::setTheSeed(BDSGlobals->GetRandomSeed());

  G4cout<<" seed from bdsglobals="<<BDSGlobals->GetRandomSeed()<<G4endl;
  G4cout<<"Random Number SEED ="<<HepRandom::getTheSeed<<G4endl;

  BDSRunManager * runManager = new BDSRunManager;

  // set mandatory initialization classes
  BDSDetectorConstruction* detector = new BDSDetectorConstruction;

  runManager->SetUserInitialization(detector);

  BDSPhysicsList* PhysList=new BDSPhysicsList;
  runManager->SetUserInitialization(PhysList);



  G4UIsession* session=0;
  
  if(!BDSGlobals->GetUseBatch())
    {  if (argc==1)   // Define UI session for interactive mode.
      {
#ifdef G4UI_USE_TCSH
	session = new G4UIterminal(new G4UItcsh);      
#else
	session = new G4UIterminal();
#endif    
      }
    }


  // gab: remove this in order to make a version that works on cosmos
#ifdef G4VIS_USE
  G4VisManager* visManager;
  // visualization manager
  if(!BDSGlobals->GetUseBatch());
  {
    visManager = new BDSVisManager;
    visManager->Initialize();
  }
#endif
  

  // set user action classes
  runManager->SetUserAction(new BDSPrimaryGeneratorAction(detector));

  runManager->SetUserAction(new BDSRunAction);

  
  //  BDSEventAction* theBDSEventAction = new BDSEventAction();
  runManager->SetUserAction(new BDSEventAction());


  runManager->SetUserAction(new BDSSteppingAction);


  runManager->SetUserAction(new BDSUserTrackingAction);
  


  //Initialize G4 kernel
  runManager->Initialize();
 
  //  PhysList->BDSAddTransportation();

	  // bias inelastic events

	  G4ProcessManager *pManager = 0;
	  G4ProcessVector *procVec = 0;
	  G4String pName;
	  G4HadronInelasticProcess* HadInProc=0;

	  pManager = G4Electron::Electron()->GetProcessManager();
	  procVec=pManager->GetProcessList();
	  G4int nProc,iProc;
	  nProc=pManager->GetProcessListLength();
	  for(iProc=0;iProc<nProc;iProc++)
	    {
	      pName=(*procVec)[iProc]->GetProcessName();
	      if(pName=="ElectroNuclear") 
		{
		  HadInProc=
		    static_cast<G4HadronInelasticProcess*>((*procVec)[iProc]);
		  HadInProc->
		    BiasCrossSectionByFactor(BDSGlobals->
					     GetHadronInelasticScaleFactor());
		}
	    }

	  pManager = G4Positron::Positron()->GetProcessManager();
	  procVec=pManager->GetProcessList();
	  nProc=pManager->GetProcessListLength();
	  for(iProc=0;iProc<nProc;iProc++)
	    {
	      pName=(*procVec)[iProc]->GetProcessName();
	      if(pName=="PositronNuclear")
		{
		  HadInProc=
		    static_cast<G4HadronInelasticProcess*>((*procVec)[iProc]);
		  HadInProc->
		    BiasCrossSectionByFactor(BDSGlobals->
					     GetHadronInelasticScaleFactor());
		}
	    }

	  
	  pManager =G4Gamma::Gamma()->GetProcessManager();
	  procVec=pManager->GetProcessList();
	  nProc=pManager->GetProcessListLength();
	  for(iProc=0;iProc<nProc;iProc++)
	    {
	      pName=(*procVec)[iProc]->GetProcessName();
	      if(pName=="PhotoNuclear")
		{
		  HadInProc=
		    static_cast<G4HadronInelasticProcess*>((*procVec)[iProc]);
		  HadInProc->
		    BiasCrossSectionByFactor(BDSGlobals->
					     GetHadronInelasticScaleFactor());
		}
	    }

	  /*
	  pManager = G4Neutron::Neutron()->GetProcessManager();
	  procVec=pManager->GetProcessList();
	  nProc=pManager->GetProcessListLength();
	  for(iProc=0;iProc<nProc;iProc++)
	    {
	      pName=(*procVec)[iProc]->GetProcessName();
	      G4cout<<"proc neutron="<<pName<<endl;
	      if(pName=="ElectroNuclear" || pName=="PhotonInelastic"
		 || pName=="NeutronInelastic")
		{
		  HadInProc=
		    static_cast<G4HadronInelasticProcess*>((*procVec)[iProc]);
		  HadInProc->
		    BiasCrossSectionByFactor(BDSGlobals->
					     GetHadronInelasticScaleFactor());
		}
	    }
	  */


  if (!BDSGlobals->GetUseBatch())   // Define UI session for interactive mode.
    {
      // get the pointer to the User Interface manager 
      G4UImanager* UI = G4UImanager::GetUIpointer();  
      // G4UIterminal is a (dumb) terminal.
      UI->ApplyCommand("/control/execute BDS_vis.mac");    
#ifdef G4UI_USE_XM
      // Customize the G4UIXm menubar with a macro file :
      UI->ApplyCommand("/control/execute gui.mac");
#endif
      session->SessionStart();
      delete session;

    }
  else           // Batch mode
    { 
      runManager->BeamOn(BDSGlobals->GetNumberToGenerate());
    }
  
  // job termination
  
  // gab: remove this in order to make a version that works on cosmos
#ifdef G4VIS_USE
  if(!BDSGlobals->GetUseBatch())delete visManager;
#endif

  if(BDSRoot->theRootOutputFile)
    {
      G4cout<<" BDS_run Writing event output file"<<G4endl;
      gDirectory->Write();
      BDSRoot->theRootOutputFile->ls();
      BDSRoot->theRootOutputFile->Close();
    }

  //delete theBDSEventAction;
  //delete runManager;

     
  return 0;
}

