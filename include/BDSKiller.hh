/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 19.1.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSKiller_h
#define BDSKiller_h 1

#include "globals.hh"
#include "BDSAcceleratorComponent.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"

class BDSKiller :public BDSAcceleratorComponent
{
public:
  BDSKiller(G4String& aName,G4double aLength);
  ~BDSKiller();

protected:

private:
  void KillerLogicalVolume();
  G4VisAttributes* SetVisAttributes();

  // field related objects:
  G4UserLimits* itsUserLimits;
  G4VisAttributes* itsVisAttributes;
};

#endif
