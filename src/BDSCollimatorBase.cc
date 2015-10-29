#include "BDSCollimatorBase.hh"

#include "BDSColours.hh"
#include "BDSDebug.hh"
#include "BDSGlobalConstants.hh" 
#include "BDSMaterials.hh"
#include "BDSUtilities.hh"

#include "G4Box.hh"
#include "G4EllipticalCone.hh"

#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4UserLimits.hh"

#include <map>

BDSCollimatorBase::BDSCollimatorBase(G4String name,
				     G4double length,
				     G4double outerDiameterIn,
				     G4String type,
				     G4double xApertureIn,
				     G4double yApertureIn,
                     G4double xOutApertureIn,
                     G4double yOutApertureIn,
				     G4String collimatorMaterialIn,
				     G4String vacuumMaterialIn):
  BDSAcceleratorComponent(name, length, 0, type),
  outerDiameter(outerDiameterIn),
  xAperture(xApertureIn),
  yAperture(yApertureIn),
  xOutAperture(xOutApertureIn),
  yOutAperture(yOutApertureIn),
  collimatorMaterial(collimatorMaterialIn),
  vacuumMaterial(vacuumMaterialIn)
{
  if(outerDiameter==0)
    {outerDiameter = BDSGlobalConstants::Instance()->GetOuterDiameter();}

  if ( (xAperture > 0.5*outerDiameter) || (yAperture > 0.5*outerDiameter) )
    {
      G4cerr << __METHOD_NAME__ << "half aperture bigger than diameter!" << G4endl;
      G4cerr << "Outer diameter is " << outerDiameter << " mm for component named: \""
	     << name << "\"" << G4endl;
      exit(1);
    }

  if (collimatorMaterialIn == "")
    {
      G4cout << __METHOD_NAME__ << "Warning - no material set for collimator - using copper" << G4endl;
      collimatorMaterial = "Copper";
    }
    
  if(BDS::IsFinite(xOutAperture) && (xAperture <= 0))
    {
      G4cout << __METHOD_NAME__ << "Warning - no entrance aperture set for collimator - exit aperture parameters will be ignored" << G4endl;
    }
  if(BDS::IsFinite(xOutAperture) && BDS::IsFinite(yOutAperture) && BDS::IsFinite(xAperture) && BDS::IsFinite(yAperture))
    {
      if((xOutAperture / yOutAperture) != (xAperture / yAperture))
        {
          G4cout << __METHOD_NAME__ << "Warning - X/Y half axes ratio at entrance and exit apertures are not equal" << G4endl;
        }
    }
  
  collimatorSolid = nullptr;
  innerSolid      = nullptr;
  vacuumSolid     = nullptr;
}

BDSCollimatorBase::~BDSCollimatorBase()
{;}

void BDSCollimatorBase::BuildContainerLogicalVolume()
{
  containerSolid = new G4Box(name + "_container_solid",
			     outerDiameter*0.5,
			     outerDiameter*0.5,
			     chordLength*0.5);
  
  containerLogicalVolume = new G4LogicalVolume(containerSolid,
					       emptyMaterial,
					       name + "_container_lv");
}

void BDSCollimatorBase::Build()
{
  BDSAcceleratorComponent::Build(); // calls BuildContainer and sets limits and vis for container
  
  // now build the collimator
  G4VSolid* outerSolid = new G4Box(name + "_outer_solid",
  			   outerDiameter * 0.5 - lengthSafety,
			   outerDiameter * 0.5 - lengthSafety,
               chordLength * 0.5   - lengthSafety);
  RegisterSolid(outerSolid);
  
  G4bool buildVacuumAndAperture = (BDS::IsFinite(xAperture) && BDS::IsFinite(yAperture));
  G4bool tapered = (BDS::IsFinite(xOutAperture) && BDS::IsFinite(yOutAperture));
  G4bool isOutLarger = ((xOutAperture > xAperture) && (yOutAperture > yAperture));

  // only do subtraction if aperture actually set
  if(buildVacuumAndAperture)
    {
      BuildInnerCollimator();

      collimatorSolid = new G4SubtractionSolid(name + "_collimator_solid", // name
					       outerSolid,                 // solid 1
					       innerSolid);                // minus solid 2
      RegisterSolid(collimatorSolid);
    }
  else
    {collimatorSolid = outerSolid;}

  G4Material* material = BDSMaterials::Instance()->GetMaterial(collimatorMaterial);
  G4LogicalVolume* collimatorLV = new G4LogicalVolume(collimatorSolid,          // solid
						      material,                 // material
						      name + "_collimator_lv"); // name

  G4VisAttributes* collimatorVisAttr = new G4VisAttributes(*BDSColours::Instance()->GetColour("collimator"));
  collimatorLV->SetVisAttributes(collimatorVisAttr);
  RegisterVisAttributes(collimatorVisAttr);

  //Rotation for tapered collimator
  G4RotationMatrix* colRotate;
  RegisterRotationMatrix(colRotate);
  if (tapered && isOutLarger)
    {
      colRotate = new G4RotationMatrix;
      colRotate->rotateX(M_PI);
    }
  else
    {colRotate = nullptr;}


#ifndef NOUSERLIMITS
  G4UserLimits* collimatorUserLimits = new G4UserLimits(*(BDSGlobalConstants::Instance()->GetDefaultUserLimits()));
  collimatorUserLimits->SetMaxAllowedStep(chordLength * 0.5);
  RegisterUserLimits(collimatorUserLimits);
  collimatorLV->SetUserLimits(collimatorUserLimits);
#endif

  // register with base class (BDSGeometryComponent)
  RegisterLogicalVolume(collimatorLV);
  RegisterSensitiveVolume(collimatorLV);

  G4PVPlacement* collPV = new G4PVPlacement(colRotate,   // rotation
					    (G4ThreeVector)0,        // position
					    collimatorLV,            // its logical volume
					    name + "_collimator_pv", // its name
					    containerLogicalVolume,  // its mother  volume
					    false,		             // no boolean operation
					    0,		                 // copy number
					    checkOverlaps);

  RegisterPhysicalVolume(collPV);

  if (buildVacuumAndAperture)
    {
      G4Material* vMaterial = BDSMaterials::Instance()->GetMaterial(vacuumMaterial);
      G4LogicalVolume* vacuumLV = new G4LogicalVolume(vacuumSolid,          // solid
						      vMaterial,            // material
						      name + "_vacuum_lv"); // name

      vacuumLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetInvisibleVisAttr());
#ifndef NOUSERLIMITS
      vacuumLV->SetUserLimits(BDSGlobalConstants::Instance()->GetDefaultUserLimits());
#endif
      SetAcceleratorVacuumLogicalVolume(vacuumLV);
      RegisterLogicalVolume(vacuumLV);

      G4PVPlacement* vacPV = new G4PVPlacement(colRotate,                       // rotation
					       (G4ThreeVector)0,        // position
					       vacuumLV,                // its logical volume
					       name + "_vacuum_pv",     // its name
					       containerLogicalVolume,  // its mother  volume
					       false,		            // no boolean operation
					       0,		                // copy number
					       checkOverlaps);

      RegisterPhysicalVolume(vacPV);
    }
}

