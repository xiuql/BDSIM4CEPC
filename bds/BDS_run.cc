/** BDSIM code.    Version 1.0
*   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
*   Last modified 24.7.2002
*   @Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

//  TODO: place brief BDSIM discription here
//
//
//
//


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


#include "stdlib.h"      
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// tmp
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"


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

G4String CardsFilename= "BDSInput.cards";
G4String OpticsFilename = "optics";
G4bool verbose = false;

int main(int argc,char** argv) {


  // NOTE: Visualization crashes when the argument parsing is added 
  // Parse the command line options 

  
   static struct option LongOptions[] = {
     { "help" , 0, 0, 0 },
     { "verbose", 0, 0, 0 },
     { "file", 1, 0, 0 },
     { "optics", 1, 0, 0 },
     { 0, 0, 0, 0 }
   };
  
  int OptionIndex = 0;
  int c;
  int ThisOptionId;
  
  for(;;)
    {
      
      ThisOptionId = optind ? optind : 1;
      OptionIndex = 0;
      
      c = getopt_long(argc, argv, "Vv",
		      LongOptions, &OptionIndex );
      
      if ( c == -1 ) // end of options list
  	break;
      
      switch (c) {
      case 0:
	
	//G4cout<<"option "<<LongOptions[OptionIndex].name;
	//if(optarg) {
	//  G4cout<<" with arg "<<optarg;}
	//G4cout<<G4endl;
	
	if( !strcmp(LongOptions[OptionIndex].name , "help") )
	  {
	    G4cout<<"Usage: BDS_run [options]"<<G4endl;
	    G4cout<<"Options:"<<G4endl;
	    G4cout<<"--file=<filename> : specify the cards file"<<G4endl
		  <<"--optics=<filename> : specify the optics fie"<<G4endl
		  <<"--help              : display this message"<<G4endl
		  <<"--verbose           : run in verbose mode"<<G4endl;
	    exit(0);
	  }
	
	if( !strcmp(LongOptions[OptionIndex].name , "verbose") )
	  {
	    verbose = true; 
	  }
	  
	if( !strcmp(LongOptions[OptionIndex].name , "file") )
	  {
	    if(optarg) {
	      CardsFilename = optarg;
	    }
	    else {
	      G4cout<<"please specify the cards filename"<<G4endl;
	    }
	  }
	
	if( !strcmp(LongOptions[OptionIndex].name , "optics") )
	  {
	    
	    if(optarg) {
	      OpticsFilename = optarg;
	    }
	    else {
	      G4cout<<"please specify the optics filename"<<G4endl;
	    }
	  }
	
	break;
      case -1:
	break;
      default:
	break;
      }
      
    }
  
  
//   G4cout<<"using cards file "<<CardsFilename<<
//     G4endl<<"using optics file "<<OpticsFilename<<G4endl;
  
  
  
  // Read in the global constants
  // IA: TODO: change to xml input format

  BDSGlobals = new BDSGlobalConstants(CardsFilename);
  BDSRoot = new BDSRootObjects();

  gDirectory->mkdir("Histos");
  gDirectory->mkdir("Trees");
  gDirectory->mkdir("Trajectories");


  // ROOT stuff:
  TROOT RootStartup("BDSROOT", "Beam Delivery System Simulation");

  // set default output formats:
  G4cout.precision(10);

  // choose the Random engine
  HepRandom::setTheEngine(new RanecuEngine);
  HepRandom::setTheSeed(BDSGlobals->GetRandomSeed());

  G4cout<<" seed from bdsglobals="<<BDSGlobals->GetRandomSeed()<<G4endl;
  G4cout<<"Random Number SEED ="<<HepRandom::getTheSeed()<<G4endl;

  BDSRunManager * runManager = new BDSRunManager;

  // set mandatory initialization classes
  BDSDetectorConstruction* detector = new BDSDetectorConstruction;

  runManager->SetUserInitialization(detector);

  BDSPhysicsList* PhysList=new BDSPhysicsList;
  runManager->SetUserInitialization(PhysList);



  G4UIsession* session=0;
  
  if(!BDSGlobals->GetUseBatch())
    {
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);
#else
      session = new G4UIterminal();
#endif    
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
  if(!BDSGlobals->GetUseBatch()) delete visManager;
#endif

  if(BDSRoot->theRootOutputFile)
    {
      G4cout<<" BDS_run Writing event output file"<<G4endl;
      gDirectory->Write();
      BDSRoot->theRootOutputFile->ls();
      BDSRoot->theRootOutputFile->Close();
    
    }


  delete runManager;

  delete BDSRoot; 
  delete BDSGlobals;
     
  return 0;
}
