#include "BDSGlobalConstants.hh" 
#include "BDSSamplerPlane.hh"
#include "BDSSDManager.hh"

#include "globals.hh" // geant4 types / globals
#include "G4Box.hh"
#include "G4LogicalVolume.hh"

// geometry tolerance is 1e-8 and dz of the box must be > 1e-8
// was 4e-8*m
const G4double BDSSamplerPlane::chordLength = 100*CLHEP::nm;

BDSSamplerPlane::BDSSamplerPlane(G4String      name,
				 G4double      boxHalfWidth):
  BDSSampler(name)
{
  containerSolid = new G4Box(name + "_solid",
			     boxHalfWidth,
			     boxHalfWidth,
			     chordLength*0.5);

  SetExtentX(-boxHalfWidth, boxHalfWidth);
  SetExtentY(-boxHalfWidth, boxHalfWidth);
  SetExtentZ(-chordLength*0.5, chordLength*0.5);

  CommonConstruction();

  containerLogicalVolume->SetSensitiveDetector(BDSSDManager::Instance()->GetSamplerPlaneSD());
}
