/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

//==========================================================
//==========================================================
#include "BDSGlobalConstants.hh" // must be first in include list

#include "BDSRunAction.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

#include "BDSAcceleratorComponent.hh"
#include <list>
#include <fstream>
#include <string>

typedef list<BDSAcceleratorComponent*>  myBeamline;
extern myBeamline theBeamline;

//==========================================================

BDSRunAction::BDSRunAction()
{
}

//==========================================================

BDSRunAction::~BDSRunAction()
{}

//==========================================================

void BDSRunAction::BeginOfRunAction(const G4Run* aRun)
{
  //  BDSGlobals->GetTimer()->Start();
 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  if(BDSGlobals->GetUseTimer())
    {
      BDSGlobals->GetTimer()->Start();
    }

  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer(); 
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    } 


}

//==========================================================

void BDSRunAction::EndOfRunAction(const G4Run* aRun)
{

  //  if (G4VVisManager::GetConcreteInstance()) {
  //   G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");

  if(BDSGlobals->GetUseTimer())
    {
      BDSGlobals->GetTimer()->Stop();
      G4cout<<"RUN Elapsed time="<<*BDSGlobals->GetTimer()<<G4endl;
    }


  /*  
  if(BDSGlobals->GetSynchRadOn())
    {
    ofstream synch_output("synch_factors_new.dat");
      myBeamline::const_iterator iBeam;
      for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
	{
	  synch_output<<(*iBeam)->GetSynchEnergyLoss()/ 
	    G4double(aRun->GetNumberOfEvent())/GeV<<G4endl;
	}
    }
  */

}


//==========================================================
