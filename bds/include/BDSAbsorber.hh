/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSAbsorber_h
#define BDSAbsorber_h 1

#include"globals.hh"
#include"BDSAcceleratorComponent.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"

#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Box.hh"
#include "BDSEnergyCounterSD.hh"

class BDSAbsorber :public BDSAcceleratorComponent
{
public:
  BDSAbsorber(G4String& aName, G4double aLength,G4double bpRad, 
	     G4double xAper, G4double yAper,G4Material* AbsorberMaterial);
  ~BDSAbsorber();

protected:

private:
  void BuildInnerAbsorber();
  G4VisAttributes* SetVisAttributes();

  // Geometrical objects:

  G4VPhysicalVolume* itsPhysiComp;
  G4VPhysicalVolume* itsPhysiComp2;
  G4LogicalVolume* itsSolidLogVol;
  G4LogicalVolume* itsInnerLogVol;
                    
  G4UserLimits* itsUserLimits;
  G4VisAttributes* itsVisAttributes;
  G4Mag_UsualEqRhs* itsEqRhs;

private:
  G4Material* itsAbsorberMaterial;
  BDSEnergyCounterSD* itsBDSEnergyCounterSD;
};

#endif
