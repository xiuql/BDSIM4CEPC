/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 18.10.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSSectorBend_h
#define BDSSectorBend_h 1

#include"globals.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"
#include "BDSHelixStepper.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4UniformMagField.hh"
#include "G4PVPlacement.hh"               

#include "BDSMultipole.hh"
#include "BDS_SbendField.hh"
#include "G4Mag_EqRhs.hh"

class BDSSectorBend :public BDSMultipole
{
  public:
    BDSSectorBend(G4String& aName, G4double aLength,
		  G4double bpRad,G4double FeRad,
		  G4double bField, G4double angle,G4int nSegments=1);
    ~BDSSectorBend();

  protected:

  private:
  G4double itsBField;

  //  void BuildOuterLogicalVolume();
  void BuildBPFieldAndStepper();
  void BuildSBMarkerLogicalVolume();
  G4VisAttributes* SetVisAttributes();

  // field related objects:
  BDSHelixStepper* itsStepper;
  BDS_SbendField* itsMagField;
  G4Mag_EqRhs* itsEqRhs;

};

#endif
