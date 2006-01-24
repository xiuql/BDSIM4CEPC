/* BDSIM code.    Version 1.0
   Author: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 02.12.2004
   Copyright (c) 2004 by J.C.Carter.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSElement_h
#define BDSElement_h 

#include "globals.hh"
#include "BDSAcceleratorComponent.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"

#include "BDSField.hh"
#include "BDSXYMagField.hh"

#include "G4EqMagElectricField.hh"
#include "G4ClassicalRK4.hh"


class BDSElement :public BDSAcceleratorComponent
{
public:
  BDSElement(G4String aName, G4String geometry, G4String bmap, G4double aLength, G4double bpRad);
  ~BDSElement();

  void BuildGeometry();
  void PlaceComponents(G4String geometry, G4String bmap);
  void BuildMagField();

  // creates a field mesh in global coordinates in case it is given by map
  void PrepareField(G4VPhysicalVolume *referenceVolume);
   
protected:
  
  G4VisAttributes* SetVisAttributes();  

private:

  BDSField *itsField;

};


#endif
