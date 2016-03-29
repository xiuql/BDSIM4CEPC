#include "BDSMagnetOuterInfo.hh"

#include "BDSMagnetGeometryType.hh"
#include "globals.hh"             // geant4 globals / types
#include "G4Material.hh"

BDSMagnetOuterInfo::BDSMagnetOuterInfo()
{
  geometryType  = BDSMagnetGeometryType::cylindrical;
  outerDiameter = 0;
  outerMaterial = nullptr;
  angleIn       = 0;
  angleOut      = 0;
}

BDSMagnetOuterInfo::BDSMagnetOuterInfo(BDSMagnetGeometryType geometryTypeIn,
				       G4double              outerDiameterIn,
				       G4Material*           outerMaterialIn,
				       G4double              angleInIn,
				       G4double              angleOutIn)
{
  geometryType  = geometryTypeIn;
  outerDiameter = outerDiameterIn;
  outerMaterial = outerMaterialIn;
  angleIn       = angleInIn;
  angleOut      = angleOutIn;
}
  
