/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSDrift_h
#define BDSDrift_h 1

#include"globals.hh"

#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"
#include "BDSDriftStepper.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4UniformMagField.hh"
#include "G4PVPlacement.hh"               

#include "G4UniformElectricField.hh"
//#include "G4ClassicalRK4.hh"
#include "G4MagErrorStepper.hh"
#include "G4EqMagElectricField.hh"
#include "G4TransportationManager.hh"

#include "BDSMultipole.hh"

class BDSDrift :public BDSMultipole
{
  public:
    BDSDrift(G4String aName, G4double aLength,G4double bpRad);
    ~BDSDrift();

  protected:

  private:

  //  void BuildOuterLogicalVolume();
  void BuildMarkerFieldAndStepper();
  //void BuildMarkerLogicalVolume();

  G4VisAttributes* SetVisAttributes();


};

#endif
