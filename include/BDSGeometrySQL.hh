/* * BDSIM code.    Version 1.0
   * Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   * Last modified 24.7.2002
   * Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 


   Author of this code: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 13.04.2005
*/


#ifndef BDSInteractionPointSQL_h
#define BDSInteractionPointSQL_h 1

#include "globals.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "BDSMySQLTable.hh"

#include "G4MagIntegratorStepper.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4ChordFinder.hh"
#include "G4FieldManager.hh"
#include "BDSSamplerSD.hh"
#include <fstream>
#include <vector>

using namespace std;

class BDSClassicalRK4;

class BDSGeometrySQL
{
public:
  BDSGeometrySQL(G4String DBfile);
  ~BDSGeometrySQL();

  void Construct(G4LogicalVolume *marker);

private:

  ifstream ifs;
  void BuildSQLObjects(G4String file);
  G4LogicalVolume* itsMarkerVol;
  void BuildCone(BDSMySQLTable* aSQLTable);
  void BuildBox(BDSMySQLTable* aSQLTable);
  G4VisAttributes* SetVisAttributes();
  vector<BDSMySQLTable*> itsSQLTable;

protected:
};
#endif
