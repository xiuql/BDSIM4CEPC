/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#include "BDSAcceleratorComponent.hh"

//
// Class BDSAcceleratorComponent 

void BDSAcceleratorComponent::PrepareField(G4VPhysicalVolume *referenceVolume)
{//do nothing by default
  return;
}

void BDSAcceleratorComponent::SynchRescale(G4double factor)
{
  return;
}

void BDSAcceleratorComponent::AlignComponent(G4ThreeVector& TargetPos,
					     G4RotationMatrix *TargetRot, 
					     G4RotationMatrix& globalRotation,
					     G4ThreeVector& rtot,
					     G4ThreeVector& rlast,
					     G4ThreeVector& localX,
					     G4ThreeVector& localY,
					     G4ThreeVector& localZ)
{//do nothing by default, except set rotation and position for BDSOutline
  itsRotation=TargetRot;
  itsPosition=TargetPos;
  return;
}

BDSAcceleratorComponent::~BDSAcceleratorComponent ()
{
  if(itsOuterLogicalVolume)delete itsOuterLogicalVolume;
  //  if(itsBeamPipe)delete itsBeamPipe;
  if(itsBDSEnergyCounter)delete itsBDSEnergyCounter;
  if(itsOuterUserLimits)delete itsOuterUserLimits;
  if(itsOuterLogicalVolume)delete itsOuterLogicalVolume;
  if(itsMarkerLogicalVolume)delete itsMarkerLogicalVolume;
  if(itsInnerBeampipeUserLimits)delete itsInnerBeampipeUserLimits;

}

