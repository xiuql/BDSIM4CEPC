/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 3.11.2002
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
//
// $Id: BDSConvParticleChange.cc,v 1.2 2007/05/10 16:23:22 malton Exp $
// GEANT4 tag $Name:  $
//
// 
// --------------------------------------------------------------
//	GEANT 4 class implementation file 
//
//	
//	
// ------------------------------------------------------------
//   Implemented for the new scheme                 23 Mar. 1998  H.Kurahige
//   Change default debug flag to false             10 May. 1998  H.Kurahige
//   Add Track weight                               12 Nov. 1998  H.Kurashige
//   Activate CheckIt method for VERBOSE mode       14 Dec. 1998 H.Kurashige
//   Modified CheckIt method for time                9 Feb. 1999 H.Kurashige
// --------------------------------------------------------------

#include "BDSConvParticleChange.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4TrackFastVector.hh"
#include "G4DynamicParticle.hh"


BDSConvParticleChange::BDSConvParticleChange():G4VParticleChange(),theCurrentTrack(NULL)
{
  // gab set flag so that secondaries can have different weights from
  // their parents
  G4VParticleChange::SetSecondaryWeightByProcess(true);

}

BDSConvParticleChange::~BDSConvParticleChange() 
{
#ifdef G4VERBOSE
  if (verboseLevel>2) {
    G4cout << "BDSConvParticleChange::~BDSConvParticleChange() " << G4endl;
  }
#endif
}

// copy constructor
BDSConvParticleChange::BDSConvParticleChange(const BDSConvParticleChange &right): G4VParticleChange(right)
{
   if (verboseLevel>1) {
    G4cout << "BDSConvParticleChange::  copy constructor is called " << G4endl;
   }
   theMomentumDirectionChange = right.theMomentumDirectionChange;
   thePolarizationChange = right.thePolarizationChange;
   thePositionChange = right.thePositionChange;
   theTimeChange = right.theTimeChange;
   theEnergyChange = right.theEnergyChange;
   theMassChange = right.theMassChange;
   theChargeChange = right.theChargeChange;
   theWeightChange = right.theWeightChange;
   theProperTimeChange = right.theProperTimeChange;
   theCurrentTrack = right.theCurrentTrack;
   theMuonWeight = right.theMuonWeight;
}

// assignemnt operator
BDSConvParticleChange & BDSConvParticleChange::operator=(const BDSConvParticleChange &right)
{
   if (verboseLevel>1) {
    G4cout << "BDSConvParticleChange:: assignment operator is called " << G4endl;
   }
   if (this != &right)
   {
      theListOfSecondaries = right.theListOfSecondaries;
      theSizeOftheListOfSecondaries = right.theSizeOftheListOfSecondaries;
      theNumberOfSecondaries = right.theNumberOfSecondaries;
      theStatusChange = right.theStatusChange;

      theMomentumDirectionChange = right.theMomentumDirectionChange;
      thePolarizationChange = right.thePolarizationChange;
      thePositionChange = right.thePositionChange;
      theTimeChange = right.theTimeChange;
      theEnergyChange = right.theEnergyChange;
      theMassChange = right.theMassChange;
      theChargeChange = right.theChargeChange;
      theWeightChange = right.theWeightChange;

      theTrueStepLength = right.theTrueStepLength;
      theLocalEnergyDeposit = right.theLocalEnergyDeposit;
      theSteppingControlFlag = right.theSteppingControlFlag;
   }
   return *this;
}

G4bool BDSConvParticleChange::operator==(const BDSConvParticleChange &right) const
{
   return ((G4VParticleChange *)this == (G4VParticleChange *) &right);
}

G4bool BDSConvParticleChange::operator!=(const BDSConvParticleChange &right) const
{
   return ((G4VParticleChange *)this != (G4VParticleChange *) &right);
}


//----------------------------------------------------------------
// methods for handling secondaries 
//

void BDSConvParticleChange::AddSecondary(G4DynamicParticle* aParticle, 
				    G4bool   IsGoodForTracking    )
{
  //  create track
  G4Track* aTrack = new G4Track(aParticle, theTimeChange, thePositionChange);
  // set weight:
  if(abs(aParticle->GetDefinition()->GetPDGEncoding())==13)
    aTrack->SetWeight(theMuonWeight);

  // set IsGoodGorTrackingFlag
  if (IsGoodForTracking) aTrack->SetGoodForTrackingFlag();

  //   Touchable handle is copied to keep the pointer
  aTrack->SetTouchableHandle(theCurrentTrack->GetTouchableHandle());
 
 //  add a secondary
  G4VParticleChange::AddSecondary(aTrack);
}

void BDSConvParticleChange::AddSecondary(G4DynamicParticle* aParticle, 
				    G4ThreeVector      newPosition,
				    G4bool   IsGoodForTracking    )
{
  //  create track
  G4Track*  aTrack = new G4Track(aParticle, theTimeChange, newPosition);

  // set IsGoodGorTrackingFlag
  if (IsGoodForTracking) aTrack->SetGoodForTrackingFlag();

  //   Touchable is a temporary object, so you cannot keep the pointer
  aTrack->SetTouchableHandle((G4VTouchable*)0);

  //  add a secondary
  G4VParticleChange::AddSecondary(aTrack);
}

void BDSConvParticleChange::AddSecondary(G4DynamicParticle* aParticle, 
				    G4double           newTime,
				    G4bool   IsGoodForTracking    )
{
  //  create track
  G4Track*  aTrack = new G4Track(aParticle, newTime, thePositionChange); 

  // set IsGoodGorTrackingFlag
  if (IsGoodForTracking) aTrack->SetGoodForTrackingFlag();
 
  //   Touchable handle is copied to keep the pointer
  aTrack->SetTouchableHandle(theCurrentTrack->GetTouchableHandle());

  //  add a secondary
  G4VParticleChange::AddSecondary(aTrack);
}

void BDSConvParticleChange::AddSecondary(G4Track* aTrack)
{
  //  add a secondary
  G4VParticleChange::AddSecondary(aTrack);
}

//----------------------------------------------------------------
// functions for Initialization
//

void BDSConvParticleChange::Initialize(const G4Track& track)
{
  // use base class's method at first
  G4VParticleChange::Initialize(track);
  theCurrentTrack= &track;

  // set Energy/Momentum etc. equal to those of the parent particle
  const G4DynamicParticle*  pParticle = track.GetDynamicParticle();
  theEnergyChange          = pParticle->GetKineticEnergy();
  theMomentumDirectionChange        = pParticle->GetMomentumDirection();
  thePolarizationChange    = pParticle->GetPolarization();
  theProperTimeChange      = pParticle->GetProperTime();

  // Set mass/charge of DynamicParticle
  theMassChange = pParticle->GetMass();
  theChargeChange = pParticle->GetCharge();

  // set Position/Time etc. equal to those of the parent track
  thePositionChange      = track.GetPosition();
  theTimeChange          = track.GetGlobalTime();

  theWeightChange        = track.GetWeight();
}

//----------------------------------------------------------------
// methods for updating G4Step 
//

G4Step* BDSConvParticleChange::UpdateStepForAlongStep(G4Step* pStep)
{
  // A physics process always calculates the final state of the
  // particle relative to the initial state at the beginning
  // of the Step, i.e., based on information of G4Track (or
  // equivalently the PreStepPoint). 
  // So, the differences (delta) between these two states have to be
  // calculated and be accumulated in PostStepPoint. 
  
  // Take note that the return type of GetMomentumDirectionChange is a
  // pointer to G4ParticleMometum. Also it is a normalized 
  // momentum vector.

  G4StepPoint* pPreStepPoint  = pStep->GetPreStepPoint(); 
  G4StepPoint* pPostStepPoint = pStep->GetPostStepPoint(); 
#ifdef G4VERBOSE
  G4Track*     aTrack  = pStep->GetTrack();
#endif
  G4double     mass = theMassChange;

  // Set Mass/Charge
  pPostStepPoint->SetMass(theMassChange);
  pPostStepPoint->SetCharge(theChargeChange);  
 
  // calculate new kinetic energy
  G4double energy = pPostStepPoint->GetKineticEnergy() 
                    + (theEnergyChange - pPreStepPoint->GetKineticEnergy()); 

  // update kinetic energy and momentum direction
  if (energy > 0.0) {
    // calculate new momentum
    G4ThreeVector pMomentum =  pPostStepPoint->GetMomentum() 
                + ( CalcMomentum(theEnergyChange, theMomentumDirectionChange, mass)
	            - pPreStepPoint->GetMomentum());
    G4double      tMomentum = pMomentum.mag();
    G4ThreeVector direction(1.0,0.0,0.0); 
    if( tMomentum > 0. ){
      G4double  inv_Momentum= 1.0 / tMomentum; 
      direction= pMomentum * inv_Momentum;
    }
    pPostStepPoint->SetMomentumDirection(direction);
    pPostStepPoint->SetKineticEnergy( energy );
  } else {
    // stop case
    pPostStepPoint->SetMomentumDirection(G4ThreeVector(1., 0., 0.));
    pPostStepPoint->SetKineticEnergy(0.0);
  }

  // update polarization
  pPostStepPoint->AddPolarization( thePolarizationChange
				   - pPreStepPoint->GetPolarization());
      
  // update position and time
  pPostStepPoint->AddPosition( thePositionChange 
			       - pPreStepPoint->GetPosition() );
  pPostStepPoint->AddGlobalTime( theTimeChange
				 - pPreStepPoint->GetGlobalTime());
  pPostStepPoint->AddLocalTime( theTimeChange 
				 - pPreStepPoint->GetGlobalTime()); 
  pPostStepPoint->AddProperTime( theProperTimeChange 
				 - pPreStepPoint->GetProperTime());

  G4double newWeight= theWeightChange/(pPreStepPoint->GetWeight())*(pPostStepPoint->GetWeight());
  pPostStepPoint->SetWeight( newWeight );

#ifdef G4VERBOSE
  if (debugFlag) CheckIt(*aTrack);
#endif

  //  Update the G4Step specific attributes 
  return UpdateStepInfo(pStep);
}

G4Step* BDSConvParticleChange::UpdateStepForPostStep(G4Step* pStep)
{ 
  // A physics process always calculates the final state of the particle

  // Take note that the return type of GetMomentumChange is a
  // pointer to G4ParticleMometum. Also it is a normalized 
  // momentum vector.

  G4StepPoint* pPostStepPoint = pStep->GetPostStepPoint(); 
  G4Track*     aTrack  = pStep->GetTrack();

  // Set Mass/Charge
  pPostStepPoint->SetMass(theMassChange);
  pPostStepPoint->SetCharge(theChargeChange);  
 
  // update kinetic energy and momentum direction
  pPostStepPoint->SetMomentumDirection(theMomentumDirectionChange);
  pPostStepPoint->SetKineticEnergy( theEnergyChange );

   // update polarization
  pPostStepPoint->SetPolarization( thePolarizationChange );
      
  // update position and time
  pPostStepPoint->SetPosition( thePositionChange  );
  pPostStepPoint->SetGlobalTime( theTimeChange  );
  pPostStepPoint->AddLocalTime( theTimeChange 
				 - aTrack->GetGlobalTime());
  pPostStepPoint->SetProperTime( theProperTimeChange  );

  // update weight
  if(abs(aTrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding())==13)
    {
      pPostStepPoint->SetWeight( theMuonWeight );
    }
  else
    pPostStepPoint->SetWeight( theWeightChange );

#ifdef G4VERBOSE
  if (debugFlag) CheckIt(*aTrack);
#endif

  //  Update the G4Step specific attributes 
  return UpdateStepInfo(pStep);
}


G4Step* BDSConvParticleChange::UpdateStepForAtRest(G4Step* pStep)
{ 
  // A physics process always calculates the final state of the particle

  G4StepPoint* pPostStepPoint = pStep->GetPostStepPoint(); 
  G4Track*     aTrack  = pStep->GetTrack();

  // Set Mass/Charge
  pPostStepPoint->SetMass(theMassChange);
  pPostStepPoint->SetCharge(theChargeChange);  
 
  // update kinetic energy and momentum direction
  pPostStepPoint->SetMomentumDirection(theMomentumDirectionChange);
  pPostStepPoint->SetKineticEnergy( theEnergyChange );

  // update polarization
  pPostStepPoint->SetPolarization( thePolarizationChange );
      
  // update position and time
  pPostStepPoint->SetPosition( thePositionChange  );
  pPostStepPoint->SetGlobalTime( theTimeChange  );
  pPostStepPoint->AddLocalTime( theTimeChange 
				 - aTrack->GetGlobalTime());
  pPostStepPoint->SetProperTime( theProperTimeChange  );

  // update weight 
  pPostStepPoint->SetWeight( theWeightChange );

#ifdef G4VERBOSE
  if (debugFlag) CheckIt(*aTrack);
#endif

  //  Update the G4Step specific attributes 
  return UpdateStepInfo(pStep);
}

//----------------------------------------------------------------
// methods for printing messages  
//

void BDSConvParticleChange::DumpInfo() const
{
// use base-class DumpInfo
  G4VParticleChange::DumpInfo();

  int G4precision = G4cout.precision();
  G4cout.precision(3);

  G4cout << "        Mass (GeV)   : " 
       << std::setw(20) << theMassChange/GeV
       << G4endl; 
  G4cout << "        Charge (eplus)   : " 
       << std::setw(20) << theChargeChange/eplus
       << G4endl; 
  G4cout << "        Position - x (mm)   : " 
       << std::setw(20) << thePositionChange.x()/mm
       << G4endl; 
  G4cout << "        Position - y (mm)   : " 
       << std::setw(20) << thePositionChange.y()/mm
       << G4endl; 
  G4cout << "        Position - z (mm)   : " 
       << std::setw(20) << thePositionChange.z()/mm
       << G4endl;
  G4cout << "        Time (ns)           : " 
       << std::setw(20) << theTimeChange/ns
       << G4endl;
  G4cout << "        Proper Time (ns)    : " 
       << std::setw(20) << theProperTimeChange/ns
       << G4endl;
  G4cout << "        Momentum Direct - x : " 
       << std::setw(20) << theMomentumDirectionChange.x()
       << G4endl;
  G4cout << "        Momentum Direct - y : " 
       << std::setw(20) << theMomentumDirectionChange.y()
       << G4endl;
  G4cout << "        Momentum Direct - z : " 
       << std::setw(20) << theMomentumDirectionChange.z()
       << G4endl;
  G4cout << "        Kinetic Energy (MeV): " 
       << std::setw(20) << theEnergyChange/MeV
       << G4endl;
  G4cout << "        Polarization - x    : " 
       << std::setw(20) << thePolarizationChange.x()
       << G4endl;
  G4cout << "        Polarization - y    : " 
       << std::setw(20) << thePolarizationChange.y()
       << G4endl;
  G4cout << "        Polarization - z    : " 
       << std::setw(20) <<  thePolarizationChange.z()
       << G4endl;
  G4cout << "        Track Weight      : " 
         << std::setw(20) <<  theWeightChange
         << G4endl;	
  // set precision back
  G4cout.precision(G4precision);
}

G4bool BDSConvParticleChange::CheckIt(const G4Track& aTrack)
{
  G4bool    exitWithError = false;
  G4double  accuracy;


  // MomentumDirection should be unit vector
  G4bool itsOKforMomentum = true;  
  if ( theEnergyChange >0.) {
    accuracy = fabs(theMomentumDirectionChange.mag2()-1.0);
    if (accuracy > accuracyForWarning) {
      G4cout << "  BDSConvParticleChange::CheckIt  : ";
      G4cout << "the Momentum Change is not unit vector !!" << G4endl;
      G4cout << "  Difference:  " << accuracy << G4endl;
      itsOKforMomentum = false;
      if (accuracy > accuracyForException) exitWithError = true;
    }
  }

  // Both global and proper time should not go back
  G4bool itsOKforGlobalTime = true;  
  accuracy = (aTrack.GetGlobalTime()- theTimeChange)/ns;
  if (accuracy > accuracyForWarning) {
    G4cout << "  BDSConvParticleChange::CheckIt    : ";
    G4cout << "the global time goes back  !!" << G4endl;
    G4cout << "  Difference:  " << accuracy  << "[ns] " <<G4endl;
    itsOKforGlobalTime = false;
    if (accuracy > accuracyForException) exitWithError = true;
  }

  G4bool itsOKforProperTime = true;
  accuracy = (aTrack.GetProperTime() - theProperTimeChange )/ns;
  if (accuracy > accuracyForWarning) {
    G4cout << "  BDSConvParticleChange::CheckIt    : ";
    G4cout << "the proper time goes back  !!" << G4endl;
    G4cout << "  Difference:  " << accuracy  << "[ns] " <<G4endl;
    itsOKforProperTime = false;
    if (accuracy > accuracyForException) exitWithError = true;
  }

  // Kinetic Energy should not be negative
  G4bool itsOKforEnergy = true;
  accuracy = -1.0*theEnergyChange/MeV;
  if (accuracy > accuracyForWarning) {
    G4cout << "  BDSConvParticleChange::CheckIt    : ";
    G4cout << "the kinetic energy is negative  !!" << G4endl;
    G4cout << "  Difference:  " << accuracy  << "[MeV] " <<G4endl;
    itsOKforEnergy = false;
    if (accuracy > accuracyForException) exitWithError = true;
  }

  G4bool itsOK = itsOKforMomentum && itsOKforEnergy && itsOKforProperTime && itsOKforGlobalTime;
  // dump out information of this particle change
  if (!itsOK) { 
    G4cout << " BDSConvParticleChange::CheckIt " <<G4endl;
    DumpInfo();
  }

  // Exit with error
  if (exitWithError) G4Exception("BDSConvParticleChange::CheckIt", "-1", FatalException, "");

  //correction
  if (!itsOKforMomentum) {
    G4double vmag = theMomentumDirectionChange.mag();
    theMomentumDirectionChange = (1./vmag)*theMomentumDirectionChange;
  }
  if (!itsOKforGlobalTime) {
    theTimeChange = aTrack.GetGlobalTime();
  }
  if (!itsOKforProperTime) {
    theProperTimeChange = aTrack.GetProperTime();
  }
  if (!itsOKforEnergy) {
    theEnergyChange = 0.0;
  }

  itsOK = (itsOK) && G4VParticleChange::CheckIt(aTrack);
  return itsOK;
}



