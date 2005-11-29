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

