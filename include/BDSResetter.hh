/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 4.3.2005
   Copyright (c) 2005 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSResetter_h
#define BDSResetter_h 1

#include "globals.hh"
#include "BDSAcceleratorComponent.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"

class BDSResetter :public BDSAcceleratorComponent
{
public:
  BDSResetter(G4String& aName,G4double aLength);
  ~BDSResetter();

protected:

private:
  void ResetterLogicalVolume();
  G4VisAttributes* SetVisAttributes();

  // field related objects:
  G4UserLimits* itsUserLimits;
  G4VisAttributes* itsVisAttributes;
};

#endif
