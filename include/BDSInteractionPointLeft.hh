/* BDSIM code.    Version 1.0
   Author: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 02.12.2004
   Copyright (c) 2004 by J.C.Carter.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSInteractionPointLeft_h
#define BDSInteractionPointLeft_h 1

#include"globals.hh"
#include "BDSAcceleratorComponent.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"

class BDSInteractionPointLeft :public BDSAcceleratorComponent
{
public:
  BDSInteractionPointLeft(G4String& aName, G4double aLength, G4double bpRad);
  ~BDSInteractionPointLeft();
  void BuildIPLogicalVolume();
  void BuildBeamCal();
  void BuildLumiCal();
  void BuildQuadFront();

protected:
  G4LogicalVolume* itsOuterBeamCalLogicalVolume;
  G4LogicalVolume* itsInnerBeamCalLogicalVolume;
  G4UserLimits* itsOuterBeamCalUserLimits;
  G4UserLimits* itsInnerBeamCalUserLimits;

  G4LogicalVolume* itsOuterLumiCalLogicalVolume;
  G4LogicalVolume* itsInnerLumiCalLogicalVolume;
  G4UserLimits* itsOuterLumiCalUserLimits;
  G4UserLimits* itsInnerLumiCalUserLimits;

  G4LogicalVolume* itsOuterQuadFrontLogicalVolume;
  G4LogicalVolume* itsInnerQuadFrontLogicalVolume;
  G4UserLimits* itsOuterQuadFrontUserLimits;
  G4UserLimits* itsInnerQuadFrontUserLimits;
  
private:
  G4Tubs* itsOuterBeamCalTube;
  G4Tubs* itsInnerBeamCalTube;

  G4Tubs* itsOuterLumiCalTube;
  G4Tubs* itsInnerLumiCalTube;
  
  G4Tubs* itsOuterQuadFrontTube;
  G4Tubs* itsInnerQuadFrontTube;

  G4VisAttributes* SetVisAttributes();  
};

#endif
