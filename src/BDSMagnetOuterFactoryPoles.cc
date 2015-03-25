#include "BDSMagnetOuterFactoryPoles.hh"

#include "BDSBeamPipe.hh"
#include "BDSDebug.hh"
#include "BDSGeometryComponent.hh"
#include "BDSGlobalConstants.hh"
#include "BDSMagnetColours.hh"
#include "BDSMagnetOuterFactoryCylindrical.hh" // for default geometry
#include "BDSMaterials.hh"
#include "BDSSDManager.hh"
#include "BDSUtilities.hh"                 // for calculateorientation

#include "globals.hh"                      // geant4 globals / types
#include "G4Colour.hh"
#include "G4CutTubs.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4VSolid.hh"

#include <cmath>
#include <utility>                         // for std::pair
#include <algorithm>                       // for std::max


BDSMagnetOuterFactoryPoles* BDSMagnetOuterFactoryPoles::_instance = 0;

BDSMagnetOuterFactoryPoles* BDSMagnetOuterFactoryPoles::Instance()
{
  if (_instance == 0)
    {_instance = new BDSMagnetOuterFactoryPoles();}
  return _instance;
}

BDSMagnetOuterFactoryPoles::BDSMagnetOuterFactoryPoles()
{
  lengthSafety   = BDSGlobalConstants::Instance()->GetLengthSafety();
  outerSolid     = NULL;
  containerSolid = NULL;
}

BDSMagnetOuterFactoryPoles::~BDSMagnetOuterFactoryPoles()
{
  _instance = 0;
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateSectorBend(G4String      name,
								   G4double      length,
								   BDSBeamPipe*  beamPipe,
								   G4double      boxSize,
								   G4double      angle,
								   G4Material*   outerMaterial)
{
  /*
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  // test input parameters - set global options as default if not specified
  TestInputParameters(beamPipe,boxSize,outerMaterial);

  G4int orientation   = BDS::CalculateOrientation(angle);
  G4double zcomponent = cos(fabs(angle*0.5)); // calculate components of normal vectors (in the end mag(normal) = 1)
  G4double xcomponent = sin(fabs(angle*0.5)); // note full angle here as it's the exit angle
  G4ThreeVector inputface  = G4ThreeVector(-orientation*xcomponent, 0.0, -1.0*zcomponent); //-1 as pointing down in z for normal
  G4ThreeVector outputface = G4ThreeVector(-orientation*xcomponent, 0.0, zcomponent);   // no output face angle
  
  if (beamPipe->ContainerIsCircular())
    {
      //circular beampipe so we can simply use its radius
      outerSolid = new G4CutTubs(name + "_outer_solid",       // name
				 beamPipe->GetContainerRadius() + 2*lengthSafety,  // inner radius
				 boxSize*0.5,                 // outer radius
				 length*0.5-2*lengthSafety,   // half length
				 0,                           // rotation start angle
				 CLHEP::twopi,                // rotation finish angle
				 inputface,                   // input face normal
				 outputface);                 // output face normal

      //container is similar but slightly wider and hollow (to allow placement of beampipe)
      containerSolid = new G4CutTubs(name + "_contiainer_solid",  // name
				     beamPipe->GetContainerRadius() + lengthSafety, // inner radius
				     boxSize*0.5 + lengthSafety,  // outer radius
				     length*0.5,                  // half length
				     0,                           // rotation start angle
				     CLHEP::twopi,                // rotation finish angle
				     inputface,                   // input face normal
				     outputface);                 // output face normal
    }
  else
    {
      G4VSolid* outerSolidCylinder = new G4CutTubs(name + "_outer_solid_cylinder",  // name
						   0,  // inner radius - for unambiguous subtraction
						   boxSize*0.5,                 // outer radius
						   length*0.5-2*lengthSafety,   // half length
						   0,                           // rotation start angle
						   CLHEP::twopi,                // rotation finish angle
						   inputface,                   // input face normal
						   outputface);                 // output face normal
      outerSolid = new G4SubtractionSolid(name + "_outer_solid",
					  outerSolidCylinder,
					  beamPipe->GetContainerSubtractionSolid());

      //container is similar but slightly wider
      G4VSolid* containerSolidCylinder = new G4CutTubs(name + "_container_solid_cylinder", // name
						       0,  // inner radius - for unambiguous subtraction
						       boxSize*0.5 + lengthSafety,  // outer radius
						       length*0.5,                  // half length
						       0,                           // rotation start angle
						       CLHEP::twopi,                // rotation finish angle
						       inputface,                   // input face normal
						       outputface);                 // output face normal
      containerSolid = new G4SubtractionSolid(name + "_container_solid",
					      containerSolidCylinder,
					      beamPipe->GetContainerSubtractionSolid());
    }
  return CommonFinalConstructor(name,length,boxSize,outerMaterial,BDSMagnetColours::Instance()->GetMagnetColour("sectorbend"));
  */
  return NULL;
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateRectangularBend(G4String      name,
									G4double      length,
									BDSBeamPipe*  beamPipe,
									G4double      boxSize,
									G4double      /*angle*/,
									G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  /*
  //rectangular bends currently just make a shorter straight volume, so ignore angle for now
  CreateCylindricalSolids(name, length, beamPipe, boxSize);
  return CommonFinalConstructor(name, length, boxSize, outerMaterial, BDSMagnetColours::Instance()->GetMagnetColour("rectangularbend"));
  */
  return NULL;
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateQuadrupole(G4String      name,
								   G4double      length,
								   BDSBeamPipe*  beamPipe,
								   G4double      boxSize,
								   G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  Create2NPoleSolid(name, length, beamPipe, 2, boxSize);
  return CommonFinalConstructor(name, length, boxSize, outerMaterial, BDSMagnetColours::Instance()->GetMagnetColour("quadrupole"));
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateSextupole(G4String      name,
								  G4double      length,
								  BDSBeamPipe*  beamPipe,
								  G4double      boxSize,
								  G4Material*   outerMaterial)
{
  Create2NPoleSolid(name, length, beamPipe, 3, boxSize);
  return CommonFinalConstructor(name, length, boxSize, outerMaterial, BDSMagnetColours::Instance()->GetMagnetColour("sextupole"));
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateOctupole(G4String      name,
								 G4double      length,
								 BDSBeamPipe*  beamPipe,
								 G4double      boxSize,
								 G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  Create2NPoleSolid(name, length, beamPipe, 4, boxSize);
  return CommonFinalConstructor(name, length, boxSize, outerMaterial, BDSMagnetColours::Instance()->GetMagnetColour("octupole"));
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateDecapole(G4String      name,
								 G4double      length,
								 BDSBeamPipe*  beamPipe,
								 G4double      boxSize,
								 G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  Create2NPoleSolid(name, length, beamPipe, 5, boxSize);
  return CommonFinalConstructor(name, length, boxSize, outerMaterial, BDSMagnetColours::Instance()->GetMagnetColour("decapole"));
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateSolenoid(G4String      name,
								 G4double      length,
								 BDSBeamPipe*  beamPipe,
								 G4double      boxSize,
								 G4Material*   outerMaterial)
{
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateSolenoid(name,length,beamPipe,boxSize,outerMaterial);
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateMultipole(G4String      name,
								  G4double      length,
								  BDSBeamPipe*  beamPipe,
								  G4double      boxSize,
								  G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateMultipole(name,length,beamPipe,boxSize,outerMaterial);
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateRfCavity(G4String      name,
								 G4double      length,
								 BDSBeamPipe*  beamPipe,
								 G4double      boxSize,
								 G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateRfCavity(name,length,beamPipe,boxSize,outerMaterial);
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateMuSpoiler(G4String      name,
								  G4double      length,
								  BDSBeamPipe*  beamPipe,
								  G4double      boxSize,
								  G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateMuSpoiler(name,length,beamPipe,boxSize,outerMaterial);
}

BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CreateKicker(G4String      name,
							       G4double      length,
							       BDSBeamPipe*  beamPipe,
							       G4double      boxSize,
							       G4bool        vertical,
							       G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateKicker(name,length,beamPipe,boxSize,
								    vertical,outerMaterial);
}

/// functions below here are private to this particular factory
void BDSMagnetOuterFactoryPoles::Create2NPoleSolid(G4String     name,
						   G4double     length,
						   BDSBeamPipe* beamPipe,
						   G4int        order,
						   G4double     boxSize)
{
  if (beamPipe->ContainerIsCircular())
    {
      //circular beampipe so we can simply use its radius
      outerSolid = new G4Tubs(name + "_outer_solid",       // name
			      beamPipe->GetContainerRadius() + 2*lengthSafety,  // inner radius
			      boxSize*0.5,                 // outer radius
			      length*0.5-2*lengthSafety,   // half length
			      0,                           // rotation start angle
			      CLHEP::twopi);               // rotation finish angle

      //container is similar but slightly wider and hollow (to allow placement of beampipe)
      containerSolid = new G4Tubs(name + "_contiainer_solid",  // name
				  beamPipe->GetContainerRadius() + lengthSafety, // inner radius
				  boxSize*0.5 + lengthSafety,  // outer radius
				  length*0.5,                  // half length
				  0,                           // rotation start angle
				  CLHEP::twopi);               // rotation finish angle
    }
  else
    {
      G4VSolid* outerSolidCylinder = new G4Tubs(name + "_outer_solid_cylinder",  // name
						0,  // inner radius - for unambiguous subtraction
						boxSize*0.5,                 // outer radius
						length*0.5-2*lengthSafety,   // half length
						0,                           // rotation start angle
						CLHEP::twopi);               // rotation finish angle
      outerSolid = new G4SubtractionSolid(name + "_outer_solid",
					  outerSolidCylinder,
					  beamPipe->GetContainerSubtractionSolid());

      //container is similar but slightly wider
      G4VSolid* containerSolidCylinder = new G4Tubs(name + "_container_solid_cylinder", // name
						    0,  // inner radius - for unambiguous subtraction
						    boxSize*0.5 + lengthSafety,  // outer radius
						    length*0.5,                  // half length
						    0,                           // rotation start angle
						    CLHEP::twopi);               // rotation finish angle
      containerSolid = new G4SubtractionSolid(name + "_container_solid",
					      containerSolidCylinder,
					      beamPipe->GetContainerSubtractionSolid());
    }
}

void BDSMagnetOuterFactoryPoles::TestInputParameters(BDSBeamPipe* beamPipe,
						     G4double&    boxSize,
						     G4Material*& outerMaterial)// reference to a pointer
{
  //function arguments by reference to they can be modified in place
  //check outer material is something
  if (!outerMaterial)
    {outerMaterial = BDSMaterials::Instance()->GetMaterial(BDSGlobalConstants::Instance()->GetEmptyMaterial());}

  // ensure box size is bigger than the beampipe
  if (beamPipe->ContainerIsCircular()) {
    // if it's circular, just check radius
    if (boxSize < 2*(beamPipe->GetContainerRadius()) )
      {boxSize = 2*(beamPipe->GetContainerRadius()) + 1*CLHEP::mm;}
  } else {
    // it's not circular - have a look at extents
    // +ve - -ve
    G4double extentX = beamPipe->GetExtentX().second - beamPipe->GetExtentX().first;
    G4double extentY = beamPipe->GetExtentY().second - beamPipe->GetExtentY().first;
    if ( (boxSize < extentX) || (boxSize < extentY) ) {
      // boxSize isn't sufficient for range in x or y
      boxSize = std::max(extentX,extentY) + 1*CLHEP::mm;
    }
  }
}

/// only the solids are unique, once we have those, the logical volumes and placement in the
/// container are the same.  group all this functionality together
BDSGeometryComponent* BDSMagnetOuterFactoryPoles::CommonFinalConstructor(G4String    name,
									       G4double    length,
									       G4double    boxSize,
									       G4Material* outerMaterial,
									       G4Colour*   colour)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  
  // build the logical volumes
  G4LogicalVolume* outerLV   = new G4LogicalVolume(outerSolid,
						   outerMaterial,
						   name + "_outer_lv");

  G4Material* emptyMaterial = BDSMaterials::Instance()->GetMaterial(BDSGlobalConstants::Instance()->GetEmptyMaterial());
  G4LogicalVolume* containerLV = new G4LogicalVolume(containerSolid,
						     emptyMaterial,
						     name + "_container_lv");
  
  // VISUAL ATTRIBUTES
  // set visual attributes
  // outer
  G4VisAttributes* outerVisAttr = new G4VisAttributes(*colour);
  outerVisAttr->SetVisibility(true);
  outerVisAttr->SetForceSolid(true);
  outerLV->SetVisAttributes(outerVisAttr);
  // container
#ifdef BDSDEBUG
  containerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetVisibleDebugVisAttr());
#else
  containerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetInvisibleVisAttr());
#endif

  // SENSITIVITY
  // make the outer sensitive if required (attachd Sensitive Detector Class)
  outerLV->SetSensitiveDetector(BDSSDManager::Instance()->GetEnergyCounterOnAxisSD());

  // USER LIMITS
  // set user limits based on bdsim user specified parameters

#ifndef NOUSERLIMITS
  G4UserLimits* outerUserLimits = new G4UserLimits("outer_cuts");
  G4double maxStepFactor = 0.5; // fraction of length for maximum step size
  outerUserLimits->SetMaxAllowedStep( length * maxStepFactor );
  outerUserLimits->SetUserMinEkine(BDSGlobalConstants::Instance()->GetThresholdCutCharged());
  outerUserLimits->SetUserMaxTime(BDSGlobalConstants::Instance()->GetMaxTime());
  //attach cuts to volumes
  outerLV->SetUserLimits(outerUserLimits);
  containerLV->SetUserLimits(outerUserLimits);
#endif

  // PLACEMENT
  // place the components inside the container
  // note we don't need the pointer for anything - it's registered upon construction with g4
  new G4PVPlacement((G4RotationMatrix*)0,         // no rotation
		    (G4ThreeVector)0,             // position
		    outerLV,                      // lv to be placed
		    name + "_outer_pv",           // name
		    containerLV,                  // mother lv to be place in
		    false,                        // no boolean operation
		    0,                            // copy number
		    BDSGlobalConstants::Instance()->GetCheckOverlaps() // whether to check overlaps
		    );

  // record extents
  // container radius is the same for all methods as all cylindrical
  G4double containerRadius = boxSize + lengthSafety;
  std::pair<double,double> extX = std::make_pair(-containerRadius,containerRadius);
  std::pair<double,double> extY = std::make_pair(-containerRadius,containerRadius);
  std::pair<double,double> extZ = std::make_pair(-length*0.5,length*0.5);
  
  // build the BDSGeometryComponent instance and return it
  BDSGeometryComponent* outer = new BDSGeometryComponent(containerSolid,
							 containerLV,
							 extX, extY, extZ);
  // REGISTER all lvs
  outer->RegisterLogicalVolume(outerLV); //using geometry component base class method
  outer->RegisterLogicalVolume(containerLV);
  
  return outer;
}
