/* * BDSIM code.    Version 1.0
   * Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   * Last modified 24.7.2002
   * Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 


   Author of this code: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 13.04.2005
*/


#ifndef BDSGeometrySQL_h
#define BDSGeometrySQL_h 1

#include "globals.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "BDSMySQLTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4ChordFinder.hh"
#include "G4FieldManager.hh"
#include "BDSSamplerSD.hh"
#include <fstream>
#include <vector>
#include "BDSMagFieldSQL.hh"

using namespace std;

class BDSClassicalRK4;

class BDSGeometrySQL
{
public:
  BDSGeometrySQL(G4String DBfile, G4double markerlength);
  ~BDSGeometrySQL();

  void Construct(G4LogicalVolume *marker);

  // For List of uniform fields for volumes
  vector<G4ThreeVector> UniformField;
  vector<G4String> Fieldvol; 

  // For List of Quad/Sext Fields
  vector<G4double> QuadBgrad;
  vector<G4String> Quadvol; 
  vector<G4double> SextBgrad;
  vector<G4String> Sextvol;
  G4VPhysicalVolume* align_in_volume;
  G4VPhysicalVolume* align_out_volume;
  vector<G4LogicalVolume*> SensitiveComponents;

  vector<G4LogicalVolume*> VOL_LIST;
  G4bool HasFields;

private:

  void BuildSQLObjects(G4String file);
  void BuildCone(BDSMySQLTable* aSQLTable);
  void BuildPolyCone(BDSMySQLTable* aSQLTable);
  void BuildBox(BDSMySQLTable* aSQLTable);
  void BuildTrap(BDSMySQLTable* aSQLTable);
  void BuildTorus(BDSMySQLTable* aSQLTable);
  void BuildSampler(BDSMySQLTable* aSQLTable);
  G4RotationMatrix* RotateComponent(G4double psi,
				    G4double phi,
				    G4double theta);
  void PlaceComponents(BDSMySQLTable* aSQLTable, vector<G4LogicalVolume*> VOL_LIST);

  G4double itsMarkerLength;
  ifstream ifs;
  G4LogicalVolume* itsMarkerVol;
  vector<BDSMySQLTable*> itsSQLTable;
  BDSMagFieldSQL* itsMagField;
  BDSSamplerSD* SensDet;

protected:
};

#endif
