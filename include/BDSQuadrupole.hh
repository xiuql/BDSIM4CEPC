/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSQuadrupole_h
#define BDSQuadrupole_h 1

#include"globals.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"
#include "BDSQuadStepper.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4UniformMagField.hh"
#include "G4PVPlacement.hh"               

#include "BDSMultipole.hh"
#include "BDSQuadMagField.hh"

class BDSQuadrupole :public BDSMultipole
{
  public:
    BDSQuadrupole(G4String& aName, G4double aLength,
		  G4double bpRad,G4double FeRad,
		  G4double bGrad);
    ~BDSQuadrupole();

  protected:

  private:
  G4double itsBGrad;

  //  void BuildOuterLogicalVolume();
  void BuildBPFieldAndStepper();
  //void BuildMarkerLogicalVolume();

  G4VisAttributes* SetVisAttributes();

  // field related objects:
  BDSQuadStepper* itsStepper;
  BDSQuadMagField* itsMagField;
  G4Mag_UsualEqRhs* itsEqRhs;
};

#endif
