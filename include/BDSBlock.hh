/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 20.2.2005
   Copyright (c) 2005 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSBlock_h
#define BDSBlock_h 1

#include"globals.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4UniformMagField.hh"
#include "G4PVPlacement.hh"               

#include "BDSMultipole.hh"

class BDSBlock :public BDSMultipole
{
  public:
    BDSBlock(G4String& aName, G4double aLength);
    ~BDSBlock();

  protected:

  private:

  void BuildMarkerLogicalVolume();

  G4VisAttributes* SetVisAttributes();

};

#endif
