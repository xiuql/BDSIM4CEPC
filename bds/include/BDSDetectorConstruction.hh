/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: BDSDetectorConstruction.hh,v 1.1.1.1 2004/11/18 17:42:40 ilia Exp $
// GEANT4 tag $Name:  $
//
// 

//==============================================================
//==============================================================

#ifndef BDSDetectorConstruction_h
#define BDSDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include"BDSMaterials.hh"


class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class BDSDetectorMessenger;
class BDSCalorimeterSD;
//class BDSMagField;
class G4UserLimits;
class G4VSensitiveDetector;

class G4Navigator;
//==============================================================

class BDSDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  
  BDSDetectorConstruction();
  ~BDSDetectorConstruction();

public:
     
  G4VPhysicalVolume* Construct();
  void SetMagField(const G4double afield);
  void UpdateGeometry();
     
public:

  private:
  G4Box*            solidWorld;    //pointer to the solid World 
  G4LogicalVolume*   logicWorld;    //pointer to the logical World
  G4VPhysicalVolume* physiWorld;    //pointer to the physical World

  void DefineMaterials();

  G4VPhysicalVolume* ConstructBDS();     
  G4UniformMagField* magField;      //pointer to the magnetic field
  G4UserLimits* BDSUserLimits;

  G4VSensitiveDetector *  BDSSensitiveDetector;
  BDSDetectorMessenger* detectorMessenger;

};
#endif

