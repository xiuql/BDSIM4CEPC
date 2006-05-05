//  
//   BDSIM, (C) 2001-2006 
//    
//   version 0.2 
//   last modified : 28 Mar 2006 by agapov@pp.rhul.ac.uk
//  



//
//    Stacking action - taken when secondaries created
//



#include "BDSGlobalConstants.hh"
#include "BDSStackingAction.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ios.hh"



const int DEBUG = 0;


BDSStackingAction::BDSStackingAction()
{ 
}

BDSStackingAction::~BDSStackingAction()
{
}

G4ClassificationOfNewTrack 
BDSStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  G4ClassificationOfNewTrack classification = fWaiting;
 
  G4String pName=aTrack->GetDefinition()->GetParticleName();


  if(DEBUG)
    G4cout<<"StackingAction: ClassifyNewtrack "<<aTrack->GetTrackID()<<
      " "<<aTrack->GetDefinition()->GetParticleName()<<G4endl;

  if(BDSGlobals->DoTwiss())
    {
            if((aTrack->GetParentID() <= 0) &&
	       (aTrack->GetTrackStatus()==fPostponeToNextEvent) )
	classification = fPostpone;
    }

  if(BDSGlobals->GetStopTracks()) // if tracks killed after interaction
    {
      
      // kill secondary electrons
      
      if( (aTrack->GetParentID() != 0) && 
	  (aTrack->GetDefinition() == G4Electron::ElectronDefinition() ) )
	{
	  
	  
	  classification = fKill;
	  //classification = fUrgent;
	}
      
      // kill secondary photons
      
      if( (aTrack->GetParentID() != 0) && 
	  (aTrack->GetDefinition() == G4Gamma::GammaDefinition() ) )
	{
	  classification = fKill;
	}
      
      // kill secondary positrons
      
      if( (aTrack->GetParentID() != 0) && 
	  (aTrack->GetDefinition() == G4Positron::PositronDefinition() ) )
	{
	  classification = fKill;
	}
      
    }
  
  return classification;
}


void BDSStackingAction::NewStage()
{
  // urgent stack empty, looking into the waiting stack
 
  //G4cout<<"StackingAction: New stage"<<G4endl;


  //  stackManager->ReClassify();
  return;
 
}
    
void BDSStackingAction::PrepareNewEvent()
{ 
}


