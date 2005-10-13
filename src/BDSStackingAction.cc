
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
 
  if(BDSGlobals->GetStopTracks()) // if tracks killed after interaction
    {
      
      //G4cout<<"StackingAction: ClassifyNewtrack "<<aTrack->GetTrackID()<<
      //	" "<<aTrack->GetDefinition()->GetParticleName()<<G4endl;
      
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


