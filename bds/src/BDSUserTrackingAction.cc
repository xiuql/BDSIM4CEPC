/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//

#include "BDSGlobalConstants.hh"

#include "BDSUserTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"

//#include "BDSNeutronTrackInfo.hh"

void BDSUserTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
    if(BDSGlobals->GetStoreMuonTrajectories())
      {
	if( abs(aTrack->GetDefinition()->GetPDGEncoding())==13)
	  {fpTrackingManager->SetStoreTrajectory(true); }
	else
	  { fpTrackingManager->SetStoreTrajectory(false); }
      }

    /*
  // Create trajectory only for primaries
  if(aTrack->GetParentID()==0)
  { fpTrackingManager->SetStoreTrajectory(true); }
  else
  { fpTrackingManager->SetStoreTrajectory(false); }
    */
 

  /*  
  if(aTrack->GetDefinition()->GetParticleName()=="neutron")
    {
      BDSNeutronTrackInfo* Info= new BDSNeutronTrackInfo();
      Info->SetIsLogged(false);
      fpTrackingManager->SetUserTrackInformation(Info);
    }
  
  */
}

BDSUserTrackingAction::~BDSUserTrackingAction()
{};


