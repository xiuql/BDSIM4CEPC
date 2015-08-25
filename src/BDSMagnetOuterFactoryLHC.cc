#include "BDSMagnetOuterFactoryLHC.hh"

#include "BDSBeamPipe.hh"
#include "BDSBeamPipeType.hh"
#include "BDSBeamPipeFactory.hh"
#include "BDSDebug.hh"
#include "BDSGeometryComponent.hh"
#include "BDSGlobalConstants.hh"
#include "BDSMagnetOuter.hh"
#include "BDSMagnetOuterFactoryCylindrical.hh" // for default geometry
#include "BDSMaterials.hh"
#include "BDSUtilities.hh"                 // for calculateorientation

#include "globals.hh"                      // geant4 globals / types
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4CutTubs.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4UnionSolid.hh"
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
#include <vector>


BDSMagnetOuterFactoryLHC::BDSMagnetOuterFactoryLHC(G4bool isLeftOffsetIn):
  isLeftOffset(isLeftOffsetIn)
{
  CleanUp();
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateSectorBend(G4String      name,
							   G4double      length,
							   BDSBeamPipe*  beamPipe,
							   G4double      outerDiameter,
							   G4double      containerLength,
							   G4double      angle,
							   G4Material*   outerMaterial)

{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CleanUp();
  
  // note this geometry does not respond to outerDiameter - it's hard coded to the
  // design of a sector bend for the lhc.  TestInputParameters requires it though
  // to be the same check for the other methods

  // test input parameters - set global options as default if not specified
  TestInputParameters(beamPipe,outerDiameter,outerMaterial);

  // nominal lhc beampipe parameters for reference
  // aper1 = 4.404cm / 2
  // aper2 = 3.428cm / 2
  // aper3 = 4.404cm / 2
  // containerRadius -> 24.599mm for lhc beampipe with these parameters

  // geometrical constants
  // [1] LHC design report - Chapter 7, fig 7.3
  // [2] LHC design report - Chapter 7, fig 7.1
  G4double beamPipeAxisSeparation = 194.00*CLHEP::mm;             // at 1.9K
  G4double massShift              = 0.5 * beamPipeAxisSeparation; // central shift to geometry
  //G4double collarBoxHalfHeight    = 60*CLHEP::mm;                 // [1] by visual inspection
  G4double collarBoxHalfWidth     = 22*CLHEP::mm;                 // fits between outer coils

  // radii
  G4double containerInnerRadius   = beamPipe->GetContainerRadius()+lengthSafetyLarge;
  G4double innerCoilInnerRadius   = containerInnerRadius + lengthSafetyLarge;
  G4double innerCoilInnerRadiusF  = 24.601*CLHEP::mm; // the fixed radius for the second pipe - F for fixed
  G4double innerCoilOuterRadius   = 42*CLHEP::mm;                        // [2] by visual inspection
  G4double outerCoilInnerRadius   = innerCoilOuterRadius + lengthSafetyLarge;
  G4double outerCoilInnerRadiusF  = innerCoilOuterRadius + lengthSafetyLarge; // doesn't change
  G4double outerCoilOuterRadius   = 60*CLHEP::mm;                        // [2] by visual inspection
  G4double collarInnerRadius      = outerCoilOuterRadius + lengthSafetyLarge;
  G4double collarInnerRadiusF     = outerCoilOuterRadius + lengthSafetyLarge;
  G4double collarOuterRadius      = 101.18*CLHEP::mm;                    // [1] - at 293K but don't have 1.9K measurement
  G4double yokeOuterRadius        = 570.0*0.5*CLHEP::mm;                 // [2] - at 293K but don't have 1.9K measurement
  G4double magnetContainerRadius  = yokeOuterRadius + lengthSafetyLarge;

  // angular setup of coils
  // these angles were calculated by visually analysing the coil layout graph in [2]
  G4double poleInnerFullAngle = 33./180.*2; //33 degrees half angle in radians
  G4double poleOuterFullAngle = 100./180.*2; //80 degrees half angle in radians
  G4double coilInnerFullAngle = CLHEP::pi - poleInnerFullAngle - 1e-3; // 1e-3 is small margin to avoid overlap
  G4double coilOuterFullAngle = CLHEP::pi - poleOuterFullAngle - 1e-3;

  // whether to build various components around active beam pipe depending on how wide it is
  // these ONLY apply to the components around the active beampipe
  G4bool buildInnerCoil           = true;
  G4bool buildOuterCoil           = true;
  G4bool buildCollar              = true; // collar around the active beam pipe
  if (innerCoilInnerRadius > innerCoilOuterRadius)
    {buildInnerCoil = false;}
  if ((innerCoilInnerRadius > outerCoilInnerRadius) && (innerCoilInnerRadius < outerCoilOuterRadius))
    {outerCoilInnerRadius = containerInnerRadius + lengthSafety;}
  if (innerCoilInnerRadius > outerCoilOuterRadius)
    {buildOuterCoil = false;}
  // this still uses the boxHalfWidth but just as good as the collar annulli overlap slightly in the middle
  // and this will protect against this
  if ((innerCoilInnerRadius > collarInnerRadius) && (innerCoilInnerRadius < (massShift - collarBoxHalfWidth)))
    {collarInnerRadius = containerInnerRadius + lengthSafety;}
  if (innerCoilInnerRadius > (massShift - collarBoxHalfWidth))
    {buildCollar = false;}
  if (innerCoilInnerRadius > collarOuterRadius)
    {
      // pipe is too big to use with this geometry!
      G4cerr << __METHOD_NAME__ << "this beam pipe is too big to use with the LHC dipole geometry" << G4endl;
      G4cerr << "Please consider using a different magnet geometry for this particular magnet" << G4endl;
      G4cerr << "Magnet named: " << name << G4endl;
      exit(1);
    }

  G4ThreeVector dipolePosition; // translation of whole assembly relative to centre of active pipe
  if (isLeftOffset)
    {
      dipolePosition = G4ThreeVector(massShift,0.,0.);
      beamPipeAxisSeparation  *= -1;
#ifdef BDSDEBUG
      G4cout << __METHOD_NAME__ << "dipole to the left" << G4endl;
#endif
    }
  else
    {
      dipolePosition = G4ThreeVector(-massShift,0.,0.);
      //massShift     *= -1;
#ifdef BDSDEBUG
      G4cout << __METHOD_NAME__ << "dipole to the right" << G4endl;
#endif
    }

  // calculate some geometrical parameters
  G4int orientation        = BDS::CalculateOrientation(angle);
  G4double zcomponent      = cos(fabs(angle*0.5)); // calculate components of normal vectors (in the end mag(normal) = 1)
  G4double xcomponent      = sin(fabs(angle*0.5)); // note full angle here as it's the exit angle
  G4ThreeVector inputface  = G4ThreeVector(-orientation*xcomponent, 0.0, -1.0*zcomponent); //-1 as pointing down in z for normal
  G4ThreeVector outputface = G4ThreeVector(-orientation*xcomponent, 0.0, zcomponent);   // no output face angle

  // lengths at different points transversely - dependent on left or right geometry as well as angle +ve or -ve
  G4double centralHalfLength      = length*0.5 - orientation*0.5*beamPipeAxisSeparation*tan(fabs(angle*0.5)); // central axis of outer cylinder
  // note container length is defined along the main beam axis - here our container is offset so the container length is also slightly different
  G4double centralContainerLength = containerLength - orientation*beamPipeAxisSeparation*tan(fabs(angle*0.5)); // central axis of outer cylinder
  //G4double centralContainerLength = 2*(centralHalfLength + lengthSafetyLarge) + 10*CLHEP::mm;
  G4double secondBPHalfLength     = length*0.5 - orientation*beamPipeAxisSeparation*tan(fabs(angle*0.5));     // central axis of second beampipe

#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "all calculated parameters: " << G4endl;
  G4cout << "container inner radius:  " << containerInnerRadius << G4endl;
  G4cout << "inner coil inner radius: " << innerCoilInnerRadius << G4endl;
  G4cout << "inner coil outer radius: " << innerCoilOuterRadius << G4endl;
  G4cout << "outer coil inner radius: " << outerCoilInnerRadius << G4endl;
  G4cout << "outer coil outer radius: " << outerCoilOuterRadius << G4endl;
  G4cout << "collar inner radius:     " << collarInnerRadius    << G4endl;
  G4cout << "collar outer radius:     " << collarOuterRadius    << G4endl;
  G4cout << "yoke outer radius:       " << yokeOuterRadius      << G4endl;
#endif
  
  if (beamPipe->ContainerIsCircular())
    {
      //circular beampipe so we can simply use its radius
      //container is similar but slightly wider and hollow (to allow placement of beampipe)
      //have to do subtraction as cuttubs aperture is central and the beampipe (active one) is not here
      G4VSolid* containerSolidOuter = new G4CutTubs(name + "_contiainer_solid_outer",  // name
						    0,                           // inner radius
						    yokeOuterRadius,             // outer radius
						    centralHalfLength,           // half length
						    0,                           // rotation start angle
						    CLHEP::twopi,                // rotation finish angle
						    inputface,                   // input face normal
						    outputface);                 // output face normal
      G4VSolid* containerSolidInner = new G4Tubs(name + "_contiainer_solid_inner",  // name
						 0,                                 // inner radius
						 containerInnerRadius,              // outer radius
						 length,                            // full length for unambiguous subtraction
						 0,                                 // rotation start angle
						 CLHEP::twopi);
      allSolids.push_back(containerSolidOuter);
      allSolids.push_back(containerSolidInner);
      containerSolid = new G4SubtractionSolid(name + "_outer_container_solid",// name
					      containerSolidOuter,            // outer bit
					      containerSolidInner,            // subtract this from it
					      0,                              // rotation
					      -dipolePosition);               // translation
    }
  else
    {
      //container is similar but slightly wider
      G4VSolid* containerSolidOuter = new G4CutTubs(name + "_contiainer_solid_outer",  // name
						    0,                                 // inner radius
						    yokeOuterRadius,                   // outer radius
						    centralHalfLength,                 // half length
						    0,                                 // rotation start angle
						    CLHEP::twopi,                      // rotation finish angle
						    inputface,                         // input face normal
						    outputface);                       // output face normal
      allSolids.push_back(containerSolidOuter);
      containerSolid = new G4SubtractionSolid(name + "_outer_container_solid",
					      containerSolidOuter,
					      beamPipe->GetContainerSubtractionSolid(),
					      0,                // rotation
					      -dipolePosition); // translation
    }

  // make the whole magnet container solid
  BuildMagnetContainerSolidAngled(name, centralContainerLength, magnetContainerRadius, inputface, outputface);
  // make the logical volume too manually as we don't use the BDSMagnetOuterFactoryBase method for this

  G4Material* emptyMaterial = BDSMaterials::Instance()->GetMaterial(BDSGlobalConstants::Instance()->GetEmptyMaterial());
  magnetContainerLV = new G4LogicalVolume(magnetContainerSolid,
					  emptyMaterial,
					  name + "_container_lv");
  
  containerLV = new G4LogicalVolume(containerSolid,
				    emptyMaterial,
				    name + "_outer_container_lv");
    
  // coil solids
  G4VSolid*        coil1Inner   = nullptr;
  G4VSolid*        coil1Outer   = nullptr;
  G4VSolid*        coil2Inner   = nullptr;
  G4VSolid*        coil2Outer   = nullptr;
  G4VSolid*        coil3Inner   = nullptr;
  G4VSolid*        coil3Outer   = nullptr;
  G4VSolid*        coil4Inner   = nullptr;
  G4VSolid*        coil4Outer   = nullptr;
  G4LogicalVolume* coil1InnerLV = nullptr;
  G4LogicalVolume* coil1OuterLV = nullptr;
  G4LogicalVolume* coil2InnerLV = nullptr;
  G4LogicalVolume* coil2OuterLV = nullptr;
  G4LogicalVolume* coil3InnerLV = nullptr;
  G4LogicalVolume* coil3OuterLV = nullptr;
  G4LogicalVolume* coil4InnerLV = nullptr;
  G4LogicalVolume* coil4OuterLV = nullptr;
  G4PVPlacement*   coil1InnerPV = nullptr;
  G4PVPlacement*   coil1OuterPV = nullptr;
  G4PVPlacement*   coil2InnerPV = nullptr;
  G4PVPlacement*   coil2OuterPV = nullptr;
  G4PVPlacement*   coil3InnerPV = nullptr;
  G4PVPlacement*   coil3OuterPV = nullptr;
  G4PVPlacement*   coil4InnerPV = nullptr;
  G4PVPlacement*   coil4OuterPV = nullptr;
  G4Material*      nbti         = BDSMaterials::Instance()->GetMaterial("NbTi.1");
  G4Material* stainlesssteel    = BDSMaterials::Instance()->GetMaterial("stainlesssteel");
  G4VisAttributes* coilVisAtt   = new G4VisAttributes(G4Colour(0.9, 0.75, 0.)); //gold-ish colour
  coilVisAtt->SetForceLineSegmentsPerCircle(nSegmentsPerCircle);
  allVisAttributes.push_back(coilVisAtt);
  G4VSolid*        collar1PoleTopInnerSolid     = nullptr;
  G4VSolid*        collar1PoleBottomInnerSolid  = nullptr;
  G4VSolid*        collar1PoleTopOuterSolid     = nullptr;
  G4VSolid*        collar1PoleBottomOuterSolid  = nullptr;
  G4LogicalVolume* collar1PoleTopInnerLV        = nullptr;
  G4LogicalVolume* collar1PoleBottomInnerLV     = nullptr;
  G4LogicalVolume* collar1PoleTopOuterLV        = nullptr;
  G4LogicalVolume* collar1PoleBottomOuterLV     = nullptr;
  G4PVPlacement*   collar1PoleTopInnerPV        = nullptr;
  G4PVPlacement*   collar1PoleBottomInnerPV     = nullptr;
  G4PVPlacement*   collar1PoleTopOuterPV        = nullptr;
  G4PVPlacement*   collar1PoleBottomOuterPV     = nullptr;
  G4VSolid*        collar2PoleTopInnerSolid     = nullptr;
  G4VSolid*        collar2PoleBottomInnerSolid  = nullptr;
  G4VSolid*        collar2PoleTopOuterSolid     = nullptr;
  G4VSolid*        collar2PoleBottomOuterSolid  = nullptr;
  G4LogicalVolume* collar2PoleTopInnerLV        = nullptr;
  G4LogicalVolume* collar2PoleBottomInnerLV     = nullptr;
  G4LogicalVolume* collar2PoleTopOuterLV        = nullptr;
  G4LogicalVolume* collar2PoleBottomOuterLV     = nullptr;
  G4PVPlacement*   collar2PoleTopInnerPV        = nullptr;
  G4PVPlacement*   collar2PoleBottomInnerPV     = nullptr;
  G4PVPlacement*   collar2PoleTopOuterPV        = nullptr;
  G4PVPlacement*   collar2PoleBottomOuterPV     = nullptr;
  G4LogicalVolume* collarsLV                    = nullptr;
  G4PVPlacement*   collarsPV                    = nullptr;
  G4LogicalVolume* yokeLV                       = nullptr;
  G4PVPlacement*   yokePV                       = nullptr;
  G4LogicalVolume* secondBPLV                   = nullptr;
  G4PVPlacement*   secondBPPV                   = nullptr;
  G4VisAttributes* collarVisAtt = new G4VisAttributes(G4Colour(0.9, 0.9, 0.9)); // grey
  collarVisAtt->SetForceLineSegmentsPerCircle(nSegmentsPerCircle);
  allVisAttributes.push_back(collarVisAtt);

  //buildInnerCoil = false;
  if (buildInnerCoil)
    {
      coil1Inner = new G4CutTubs(name+"_coil1_inner_solid",            // name
				 innerCoilInnerRadius,                 // inner radius
				 innerCoilOuterRadius,                 // outer radius
				 length*0.5 - lengthSafetyLarge,       // length
				 -coilInnerFullAngle*0.5,              // start angle
				 coilInnerFullAngle,                   // sweep angle
				 inputface,                            // input face normal
				 outputface);                          // output face normal
      coil2Inner = new G4CutTubs(name+"_coil2_inner_solid",            // name
				 innerCoilInnerRadius,                 // inner radius
				 innerCoilOuterRadius,                 // outer radius
				 length*0.5 - lengthSafetyLarge,       // length
				 CLHEP::pi-coilInnerFullAngle*0.5,     // start angle
				 coilInnerFullAngle,                   // sweep angle
				 inputface,                            // input face normal
				 outputface);                          // output face normal
      coil1InnerLV =  new G4LogicalVolume(coil1Inner,
					  nbti,
					  name+"_coil1_Inner_lv");
      coil2InnerLV =  new G4LogicalVolume(coil2Inner,
					  nbti,
					  name+"_coil2_Inner_lv");
      coil1InnerLV->SetVisAttributes(coilVisAtt);
      coil2InnerLV->SetVisAttributes(coilVisAtt);

      coil1InnerPV = new G4PVPlacement(0,                      // rotation
				       -dipolePosition,        // position
				       coil1InnerLV,           // its logical volume
				       name+"_coil1_inner_pv", // its name
				       containerLV,            // its mother  volume
				       false,                  // no boolean operation
				       0, 
				       checkOverlaps);
      coil2InnerPV = new G4PVPlacement(0,                      // rotation
				       -dipolePosition,        // position
				       coil2InnerLV,           // its logical volume
				       name+"_coil2_inner_pv", // its name
				       containerLV,            // its mother  volume
				       false,                  // no boolean operation
				       0, 
				       checkOverlaps);

      allSolids.push_back(coil1Inner);
      allSolids.push_back(coil2Inner);
      allLogicalVolumes.push_back(coil1InnerLV);
      allLogicalVolumes.push_back(coil2InnerLV);
      allPhysicalVolumes.push_back(coil1InnerPV);
      allPhysicalVolumes.push_back(coil2InnerPV);

      collar1PoleTopInnerSolid    = new G4CutTubs(name+"_collar1_pole_inner_top",      // name
						  innerCoilInnerRadius,                // inner radius
						  innerCoilOuterRadius,                // outer radius
						  length*0.5 - lengthSafetyLarge,      // length
						  CLHEP::pi*0.5-poleInnerFullAngle*0.5,// start angle
						  poleInnerFullAngle,                  // sweep angle
						  inputface,                           // input face normal
						  outputface);                         // output face normal
      collar1PoleBottomInnerSolid = new G4CutTubs(name+"_collar1_pole_inner_bottom",   // name
						  innerCoilInnerRadius,                // inner radius
						  innerCoilOuterRadius,                // outer radius
						  length*0.5 - lengthSafetyLarge,      // length
						  CLHEP::pi*1.5-poleInnerFullAngle*0.5,// start angle
						  poleInnerFullAngle,                  // sweep angle
						  inputface,                           // input face normal
						  outputface);                         // output face normal
      collar1PoleTopInnerLV    = new G4LogicalVolume(collar1PoleTopInnerSolid,
						     stainlesssteel,
						     name+"_collar1_pole_top_inner_lv");
      collar1PoleBottomInnerLV = new G4LogicalVolume(collar1PoleBottomInnerSolid,
						     stainlesssteel,
						     name+"_collar1_pole_bottom_inner_lv");
      
      collar1PoleTopInnerLV->SetVisAttributes(collarVisAtt);
      collar1PoleBottomInnerLV->SetVisAttributes(collarVisAtt);

      collar1PoleTopInnerPV = new G4PVPlacement(0,                          // rotation
						-dipolePosition,            // position
						collar1PoleTopInnerLV,      // its logical volume
						name+"_collar1_pole_top_inner_pv",// its name
						containerLV,                // its mother  volume
						false,                      // no boolean operation
						0,
						checkOverlaps);
      collar1PoleBottomInnerPV = new G4PVPlacement(0,                          // rotation
						   -dipolePosition,            // position
						   collar1PoleBottomInnerLV,   // its logical volume
						   name+"_collar1_pole_top_inner_pv",// its name
						   containerLV,                // its mother  volume
						   false,                      // no boolean operation
						   0,
						   checkOverlaps);

      allSolids.push_back(collar1PoleTopInnerSolid);
      allSolids.push_back(collar1PoleBottomInnerSolid);
      allLogicalVolumes.push_back(collar1PoleTopInnerLV);
      allLogicalVolumes.push_back(collar1PoleBottomInnerLV);
      allPhysicalVolumes.push_back(collar1PoleTopInnerPV);
      allPhysicalVolumes.push_back(collar1PoleBottomInnerPV);
    }

  //buildOuterCoil = false;
  if (buildOuterCoil)
    {
      coil1Outer = new G4CutTubs(name+"_coil1_outer_solid",            // name
				 outerCoilInnerRadius,                 // inner radius
				 outerCoilOuterRadius,                 // outer radius
				 length*0.5 - lengthSafetyLarge,       // length
				 -coilOuterFullAngle*0.5,              // start angle
				 coilOuterFullAngle,                   // sweep angle
				 inputface,                            // input face normal
				 outputface);                          // output face normal
      coil2Outer = new G4CutTubs(name+"_coil2_outer_solid",            // name
				 outerCoilInnerRadius,                 // inner radius
				 outerCoilOuterRadius,                 // outer radius
				 length*0.5 - lengthSafetyLarge,       // length
				 CLHEP::pi-coilOuterFullAngle*0.5,     // start angle
				 coilOuterFullAngle,                   // sweep angle
				 inputface,                            // input face normal
				 outputface);                          // output face normal
      coil1OuterLV =  new G4LogicalVolume(coil1Outer,
					  nbti,
					  name+"_coil1_Inner_lv");
      coil2OuterLV =  new G4LogicalVolume(coil2Outer,
					  nbti,
					  name+"_coil2_Inner_lv");
      coil1OuterLV->SetVisAttributes(coilVisAtt);
      coil2OuterLV->SetVisAttributes(coilVisAtt);

      
      coil1OuterPV = new G4PVPlacement(0,                      // rotation
				       -dipolePosition,        // position
				       coil1OuterLV,           // its logical volume
				       name+"_coil1_outer_pv", // its name
				       containerLV,            // its mother  volume
				       false,                  // no boolean operation
				       0, 
				       checkOverlaps);
      coil2OuterPV = new G4PVPlacement(0,                      // rotation
				       -dipolePosition,        // position
				       coil2OuterLV,           // its logical volume
				       name+"_coil2_outer_pv", // its name
				       containerLV,            // its mother  volume
				       false,                  // no boolean operation
				       0, 
				       checkOverlaps);

      allSolids.push_back(coil1Outer);
      allSolids.push_back(coil2Outer);
      allLogicalVolumes.push_back(coil1OuterLV);
      allLogicalVolumes.push_back(coil2OuterLV);
      allPhysicalVolumes.push_back(coil1OuterPV);
      allPhysicalVolumes.push_back(coil2OuterPV);
      
      collar1PoleTopOuterSolid    = new G4CutTubs(name+"_collar1_pole_outer_top",      // name
						  outerCoilInnerRadius,                // inner radius
						  outerCoilOuterRadius,                // outer radius
						  length*0.5 - lengthSafetyLarge,      // length
						  CLHEP::pi*0.5-poleOuterFullAngle*0.5,// start angle
						  poleOuterFullAngle,                  // sweep angle
						  inputface,                           // input face normal
						  outputface);                         // output face normal
      collar1PoleBottomOuterSolid = new G4CutTubs(name+"_collar1_pole_outer_bottom",   // name
						  outerCoilInnerRadius,                // inner radius
						  outerCoilOuterRadius,                // outer radius
						  length*0.5 - lengthSafetyLarge,      // length
						  CLHEP::pi*1.5-poleOuterFullAngle*0.5,// start angle
						  poleOuterFullAngle,                  // sweep angle
						  inputface,                           // input face normal
						  outputface);                         // output face normal

      collar1PoleTopOuterLV    = new G4LogicalVolume(collar1PoleTopOuterSolid,
						     stainlesssteel,
						     name+"_collar1_pole_top_outer_lv");
      collar1PoleBottomOuterLV = new G4LogicalVolume(collar1PoleBottomOuterSolid,
						     stainlesssteel,
						     name+"_collar1_pole_bottom_outer_lv");
      
      collar1PoleTopOuterLV->SetVisAttributes(collarVisAtt);
      collar1PoleBottomOuterLV->SetVisAttributes(collarVisAtt);
      
      collar1PoleTopOuterPV = new G4PVPlacement(0,                                // rotation
						-dipolePosition,                  // position
						collar1PoleTopOuterLV,            // its logical volume
						name+"_collar1_pole_top_inner_pv",// its name
						containerLV,                      // its mother  volume
						false,                            // no boolean operation
						0,
						checkOverlaps);
      collar1PoleBottomOuterPV = new G4PVPlacement(0,                                // rotation
						   -dipolePosition,                  // position
						   collar1PoleBottomOuterLV,         // its logical volume
						   name+"_collar1_pole_top_inner_pv",// its name
						   containerLV,                      // its mother  volume
						   false,                            // no boolean operation
						   0,
						   checkOverlaps);
						   
      allSolids.push_back(collar1PoleTopOuterSolid);
      allSolids.push_back(collar1PoleBottomOuterSolid);
      allLogicalVolumes.push_back(collar1PoleTopOuterLV);
      allLogicalVolumes.push_back(collar1PoleBottomOuterLV);
      allPhysicalVolumes.push_back(collar1PoleTopOuterPV);
      allPhysicalVolumes.push_back(collar1PoleBottomOuterPV);
    }
  
  // coils on inactive beam pipe - always built
  coil3Inner = new G4CutTubs(name+"_coil3_inner_solid",              // name
			     innerCoilInnerRadiusF,                  // inner radius
			     innerCoilOuterRadius,                   // outer radius
			     secondBPHalfLength - lengthSafetyLarge, // length
			     -coilInnerFullAngle*0.5,                // start angle
			     coilInnerFullAngle,                     // sweep angle
			     inputface,                              // input face normal
			     outputface);                            // output face normal
  coil3Outer = new G4CutTubs(name+"_coil3_outer_solid",              // name
			     outerCoilInnerRadiusF,                  // inner radius
			     outerCoilOuterRadius,                   // outer radius
			     secondBPHalfLength - lengthSafetyLarge, // length
			     -coilOuterFullAngle*0.5,                // start angle
			     coilOuterFullAngle,                     // sweep angle
			     inputface,                              // input face normal
			     outputface);                            // output face normal
  coil4Inner = new G4CutTubs(name+"_coil4_inner_solid",              // name
			     innerCoilInnerRadiusF,                  // inner radius
			     innerCoilOuterRadius,                   // outer radius
			     secondBPHalfLength - lengthSafetyLarge, // length
			     CLHEP::pi-coilInnerFullAngle*0.5,       // start angle
			     coilInnerFullAngle,                     // sweep angle
			     inputface,                              // input face normal
			     outputface);                            // output face normal
  coil4Outer = new G4CutTubs(name+"_coil4_outer_solid",              // name
			     outerCoilInnerRadiusF,                  // inner radius
			     outerCoilOuterRadius,                   // outer radius
			     secondBPHalfLength - lengthSafetyLarge, // length
			     CLHEP::pi-coilOuterFullAngle*0.5,       // start angle
			     coilOuterFullAngle,                     // sweep angle
			     inputface,                              // input face normal
			     outputface);                            // output face normal
  
  coil3InnerLV =  new G4LogicalVolume(coil3Inner,
				      nbti,
				      name+"_coil3_Inner_lv");
  coil3OuterLV =  new G4LogicalVolume(coil3Outer,
				      nbti,
				      name+"_coil3_Inner_lv");
  coil4InnerLV =  new G4LogicalVolume(coil4Inner,
				      nbti,
				      name+"_coil4_Inner_lv");
  coil4OuterLV =  new G4LogicalVolume(coil4Outer,
				      nbti,
				      name+"_coil4_Inner_lv");
  
  coil3InnerLV->SetVisAttributes(coilVisAtt);
  coil3OuterLV->SetVisAttributes(coilVisAtt);
  coil4InnerLV->SetVisAttributes(coilVisAtt);
  coil4OuterLV->SetVisAttributes(coilVisAtt);

  allSolids.push_back(coil3Inner);
  allSolids.push_back(coil3Outer);
  allSolids.push_back(coil4Inner);
  allSolids.push_back(coil4Outer);
  allLogicalVolumes.push_back(coil3InnerLV);
  allLogicalVolumes.push_back(coil3OuterLV);
  allLogicalVolumes.push_back(coil4InnerLV);
  allLogicalVolumes.push_back(coil4OuterLV);

  
  // coil placement  
  coil3InnerPV = new G4PVPlacement(0,                      // rotation
				   dipolePosition,         // position
				   coil3InnerLV,           // its logical volume
				   name+"_coil3_inner_pv", // its name
				   containerLV,            // its mother  volume
				   false,                  // no boolean operation
				   0, 
				   checkOverlaps);
  coil3OuterPV = new G4PVPlacement(0,                      // rotation
				   dipolePosition,         // position
				   coil3OuterLV,           // its logical volume
				   name+"_coil3_outer_pv", // its name
				   containerLV,            // its mother  volume
				   false,                  // no boolean operation
				   0, 
				   checkOverlaps);
  coil4InnerPV = new G4PVPlacement(0,                      // rotation
				   dipolePosition,         // position
				   coil4InnerLV,           // its logical volume
				   name+"_coil4_inner_pv", // its name
				   containerLV,            // its mother  volume
				   false,                  // no boolean operation
				   0, 
				   checkOverlaps);
  coil4OuterPV = new G4PVPlacement(0,                      // rotation
				   dipolePosition,         // position
				   coil4OuterLV,           // its logical volume
				   name+"_coil4_outer_pv", // its name
				   containerLV,            // its mother  volume
				   false,                  // no boolean operation
				   0, 
				   checkOverlaps);
  allPhysicalVolumes.push_back(coil3InnerPV);
  allPhysicalVolumes.push_back(coil3OuterPV);
  allPhysicalVolumes.push_back(coil4InnerPV);
  allPhysicalVolumes.push_back(coil4OuterPV);
  
  // non-magnetic collars
  // collar pole solids  
  collar2PoleTopInnerSolid    = new G4CutTubs(name+"_collar2_pole_inner_top",         // name
					      innerCoilInnerRadiusF,                  // inner radius
					      innerCoilOuterRadius,                   // outer radius
					      secondBPHalfLength - lengthSafetyLarge, // length
					      CLHEP::pi*0.5-poleInnerFullAngle*0.5,   // start angle
					      poleInnerFullAngle,                     // sweep angle
					      inputface,                              // input face normal
					      outputface);                            // output face normal
  collar2PoleTopOuterSolid    = new G4CutTubs(name+"_collar2_pole_outer_top",         // name
					      outerCoilInnerRadiusF,                  // inner radius
					      outerCoilOuterRadius,                   // outer radius
					      secondBPHalfLength - lengthSafetyLarge, // length
					      CLHEP::pi*0.5-poleOuterFullAngle*0.5,   // start angle
					      poleOuterFullAngle,                     // sweep angle
					      inputface,                              // input face normal
					      outputface);                            // output face normal
  collar2PoleBottomInnerSolid = new G4CutTubs(name+"_collar2_pole_inner_bottom",      // name
					      innerCoilInnerRadiusF,                  // inner radius
					      innerCoilOuterRadius,                   // outer radius
					      secondBPHalfLength - lengthSafetyLarge, // length
					      CLHEP::pi*1.5-poleInnerFullAngle*0.5,   // start angle
					      poleInnerFullAngle,                     // sweep angle
					      inputface,                              // input face normal
					      outputface);                            // output face normal
  collar2PoleBottomOuterSolid = new G4CutTubs(name+"_collar2_pole_outer_bottom",      // name
					      outerCoilInnerRadiusF,                  // inner radius
					      outerCoilOuterRadius,                   // outer radius
					      secondBPHalfLength - lengthSafetyLarge, // length
					      CLHEP::pi*1.5-poleOuterFullAngle*0.5,   // start angle
					      poleOuterFullAngle,                     // sweep angle
					      inputface,                              // input face normal
					      outputface);                            // output face normal
  
  // collar pole logical volumes
  collar2PoleTopInnerLV    = new G4LogicalVolume(collar2PoleTopInnerSolid,
						 stainlesssteel,
						 name+"_collar2_pole_top_inner_lv");
  collar2PoleTopOuterLV    = new G4LogicalVolume(collar2PoleTopOuterSolid,
						 stainlesssteel,
						 name+"_collar2_pole_top_outer_lv");
  collar2PoleBottomInnerLV = new G4LogicalVolume(collar2PoleBottomInnerSolid,
						 stainlesssteel,
						 name+"_collar2_pole_bottom_inner_lv");
  collar2PoleBottomOuterLV = new G4LogicalVolume(collar2PoleBottomOuterSolid,
						 stainlesssteel,
						 name+"_collar2_pole_bottom_outer_lv");
  
  // collar pole visualisation
  collar2PoleTopInnerLV->SetVisAttributes(collarVisAtt);
  collar2PoleTopOuterLV->SetVisAttributes(collarVisAtt);
  collar2PoleBottomInnerLV->SetVisAttributes(collarVisAtt);
  collar2PoleBottomOuterLV->SetVisAttributes(collarVisAtt);

  allSolids.push_back(collar2PoleTopInnerSolid);
  allSolids.push_back(collar2PoleTopOuterSolid);
  allSolids.push_back(collar2PoleBottomInnerSolid);
  allSolids.push_back(collar2PoleBottomOuterSolid);
  allLogicalVolumes.push_back(collar2PoleTopInnerLV);
  allLogicalVolumes.push_back(collar2PoleTopOuterLV);
  allLogicalVolumes.push_back(collar2PoleBottomInnerLV);
  allLogicalVolumes.push_back(collar2PoleBottomOuterLV);
  
  // collar pole placement
  collar2PoleTopInnerPV = new G4PVPlacement(0,                                // rotation
					    dipolePosition,                   // position
					    collar2PoleTopInnerLV,            // its logical volume
					    name+"_collar2_pole_top_inner_pv",// its name
					    containerLV,                      // its mother  volume
					    false,                            // no boolean operation
					    0,
					    checkOverlaps);
  collar2PoleTopOuterPV = new G4PVPlacement(0,                                // rotation
					    dipolePosition,                   // position
					    collar2PoleTopOuterLV,            // its logical volume
					    name+"_collar2_pole_top_inner_pv",// its name
					    containerLV,                      // its mother  volume
					    false,                            // no boolean operation
					    0,
					    checkOverlaps);
  collar2PoleBottomInnerPV = new G4PVPlacement(0,                                // rotation
					       dipolePosition,                   // position
					       collar2PoleBottomInnerLV,         // its logical volume
					       name+"_collar2_pole_top_inner_pv",// its name
					       containerLV,                      // its mother  volume
					       false,                            // no boolean operation
					       0,
					       checkOverlaps);
  collar2PoleBottomOuterPV = new G4PVPlacement(0,                                // rotation
					       dipolePosition,                   // position
					       collar2PoleBottomOuterLV,         // its logical volume
					       name+"_collar2_pole_top_inner_pv",// its name
					       containerLV,                      // its mother  volume
					       false,                            // no boolean operation
					       0,
					       checkOverlaps);

  allPhysicalVolumes.push_back(collar2PoleTopInnerPV);
  allPhysicalVolumes.push_back(collar2PoleTopOuterPV);
  allPhysicalVolumes.push_back(collar2PoleBottomInnerPV);
  allPhysicalVolumes.push_back(collar2PoleBottomOuterPV);
  
  // outer annulus of collar - two as slightly different lengths
  G4VSolid* collarAnnulus2 = new G4CutTubs(name+"_collar2_annulus_solid",    // name
					   collarInnerRadiusF,               // inner radius
					   collarOuterRadius,                // outer radius
					   secondBPHalfLength-lengthSafety,  // length
					   0,                                // starting angle
					   CLHEP::twopi,                     // angle of sweep
					   inputface,                        // input face normal
					   outputface);                      // output face normal

  allSolids.push_back(collarAnnulus2);
  // make final solid pointer as collar round active beam pipe optional depending on how big active beam pipe is
  G4VSolid* collars = collarAnnulus2;

  //buildCollar = false;
  if (buildCollar)
    {
      // building collar around active pipe
      G4VSolid* collarAnnulus1 = new G4CutTubs(name+"_collar1_annulus_solid",      // name
					       collarInnerRadius,                  // inner radius
					       collarOuterRadius,                  // outer radius
					       length*0.5 - lengthSafetyLarge,     // length
					       0,                                  // starting angle
					       CLHEP::twopi,                       // angle of sweep
					       inputface,                          // input face normal
					       outputface);                        // output face normal

      collars = new G4UnionSolid(name + "_collars_solid", // name
				 collarAnnulus2,          // solid1
				 collarAnnulus1,          // solid2
				 0,                       // rotation
				 -2*dipolePosition);      // translation
      allSolids.push_back(collarAnnulus1);
      allSolids.push_back(collars);
    }

  /*
  // This part seems to not produce any overlapping volumes and no errors but won't render
  // in anything but the raytracer. Requires commented out collarBoxHalfHeight at top of this
  // method to be uncommented, plus new subtraction solid for yoke will need to written
  // ommitted for now
  
  G4VSolid* collarBox      = new G4Box(name + "_collar_box_solid",           // name
				       collarBoxHalfWidth,                   // x half width
				       collarBoxHalfHeight,                  // y half width
				       2*centralHalfLength);                 // z half length
  G4VSolid* collarBoxFaces = new G4CutTubs(name + "_collar_box_faces_solid", // name
					   0,                                // inner radius
					   50*CLHEP::cm,                     // outer radius
					   centralHalfLength - lengthSafety, // length
					   0,                                // starting angle
					   CLHEP::twopi,                     // sweep angle
					   inputface,                        // input face normal
					   outputface);                      // output face normal
  G4VSolid* collarCentralPiece = new G4IntersectionSolid(name + "_collar_central_solid", // name
							 collarBox,                      // solid 1
							 collarBoxFaces);                // solid 2   
  
  G4VSolid* collarTotal = new G4UnionSolid(name + "_collar2_plus_box_solid", // name
					   collars,                          // solid 2
					   collarCentralPiece,               // solid 1
					   0,                                // rotation
					   -dipolePosition);    // translation
  */
  G4VSolid* collarTotal = collars;
  
  collarsLV =  new G4LogicalVolume(collarTotal,
				   stainlesssteel,
				   name+"_collars_lv");
  
  // collar annulus visualisation attributes
  collarsLV->SetVisAttributes(collarVisAtt);

  allLogicalVolumes.push_back(collarsLV); // register locally
  
  collarsPV = new G4PVPlacement(0,                  // rotation
			       dipolePosition,     // position
			       collarsLV,          // its logical volume
			       name+"_collars_pv", // its name
			       containerLV,        // its mother  volume
			       false,              // no boolean operation
			       0,                  // copy number
			       checkOverlaps);
  allPhysicalVolumes.push_back(collarsPV);
  
  // outer iron yoke
  G4VSolid* yokeCylinder = new G4CutTubs(name+"_yoke_cylinder_solid",     // name
					 0.,                              // inner radius
					 yokeOuterRadius - lengthSafety,  // outer radius
					 centralHalfLength-2*lengthSafety,// length
					 0,                               // starting angle
					 CLHEP::twopi,                    // sweep angle
					 inputface,                       // input face normal
					 outputface);                     // output face normal

  // need to cut hole out for everything inside - note subtraction solid has to be solid
  G4VSolid* yokeSubtractionCylinder = new G4Tubs(name + "_yoke_subtraction_cyl_solid", // name
						 0,                                    // inner radius
						 collarOuterRadius + lengthSafety,     // outer radius
						 length,                               // z half length - long for unamibiuous subtraction
						 0,                                    // start angle
						 CLHEP::twopi);                        // sweep angle

  G4VSolid* yokeSubtractionSolid = new G4UnionSolid(name + "_yoke_subtraction_solid",  // name
						    yokeSubtractionCylinder,           // solid 1
						    yokeSubtractionCylinder,           // solid 2
						    0,                                 // rotation
						    2*dipolePosition);                 // translation
  
  yokeSolid = new G4SubtractionSolid(name+"_yoke_solid",   // name
				     yokeCylinder,         // from this
				     yokeSubtractionSolid, // subtract this
				     0,                    // rotation
				     -dipolePosition);     // translation
  allSolids.push_back(yokeSubtractionCylinder);
  allSolids.push_back(yokeSubtractionSolid);
  allSolids.push_back(yokeSolid);
  yokeLV = new G4LogicalVolume(yokeSolid,
			       BDSMaterials::Instance()->GetMaterial("Iron"),
			       name+"_yoke_lv");
  
  // yoke visualisation
  G4VisAttributes* LHCblue = new G4VisAttributes(G4Colour(0.0, 0.5, 1.0));
  LHCblue->SetForceLineSegmentsPerCircle(nSegmentsPerCircle);
  allVisAttributes.push_back(LHCblue);
  yokeLV->SetVisAttributes(LHCblue);
  
  allLogicalVolumes.push_back(yokeLV); // register locally

  // yoke placement
  yokePV = new G4PVPlacement((G4RotationMatrix*)0,         // no rotation
			     G4ThreeVector(0,0,0),         // position
			     yokeLV,                       // lv to be placed
			     name + "_yoke_pv",            // name
			     containerLV,                  // mother lv to be place in
			     false,                        // no boolean operation
			     0,                            // copy number
			     checkOverlaps);
  allPhysicalVolumes.push_back(yokePV);
  
  G4String defaultMaterialName = BDSGlobalConstants::Instance()->GetBeamPipeMaterialName();
  G4Material* beamPipeMaterial = BDSMaterials::Instance()->GetMaterial(defaultMaterialName);
  G4Material* vacuumMaterial   = BDSMaterials::Instance()->GetMaterial(BDSGlobalConstants::Instance()->GetVacuumMaterial());

  //use beampipe factories to create another beampipe (note no magnetic field for now...)  
  BDSBeamPipe* secondBP = BDSBeamPipeFactory::Instance()->CreateBeamPipeAngledInOut(BDSBeamPipeType::lhcdetailed,
										    name,
										    2*secondBPHalfLength-2*lengthSafety,
										    -angle*0.5,        // entrane angle
										    -angle*0.5,        // exit angle
										    2.202*CLHEP::cm,   // aper1
										    1.714*CLHEP::cm,   // aper2
										    2.202*CLHEP::cm,   // aper3
										    0,                 // aper4
										    vacuumMaterial,    // vacuum material
										    1*CLHEP::mm,       // beampipeThickness
										    beamPipeMaterial); // beampipe material
  
  secondBPLV = secondBP->GetContainerLogicalVolume();
  secondBPPV = new G4PVPlacement((G4RotationMatrix*)0,         // no rotation
				 dipolePosition,               // position
				 secondBPLV,                   // lv to be placed
				 name + "_second_beampipe_pv", // name
				 containerLV,                  // mother lv to be place in
				 false,                        // no boolean operation
				 0,                            // copy number
				 checkOverlaps);
  allPhysicalVolumes.push_back(secondBPPV);
  
  // visual attributes for container
  if (visDebug)
    {
      containerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetVisibleDebugVisAttr());
      magnetContainerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetVisibleDebugVisAttr());
    }
  else
    {
      containerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetInvisibleVisAttr());
      magnetContainerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetInvisibleVisAttr());
    }

  // USER LIMITS for all components
#ifndef NOUSERLIMITS
  G4UserLimits* userLimits = new G4UserLimits("outer_cuts");
  userLimits->SetMaxAllowedStep( length * maxStepFactor );
  userLimits->SetUserMaxTime(BDSGlobalConstants::Instance()->GetMaxTime());
  allUserLimits.push_back(userLimits);
  for (auto i : allLogicalVolumes)
    {i->SetUserLimits(userLimits);} // apply to general vector of logical volumes
  containerLV->SetUserLimits(userLimits);
  magnetContainerLV->SetUserLimits(userLimits);
#endif
  
  // record extents
  // container radius is the same for all methods as all cylindrical
  G4double containerRadius = yokeOuterRadius;
  // massShift defined at very beginning of this function
  std::pair<double,double> extX = std::make_pair(-containerRadius+massShift,containerRadius+massShift); 
  std::pair<double,double> extY = std::make_pair(-containerRadius,containerRadius);
  std::pair<double,double> extZ = std::make_pair(-length*0.5,length*0.5);

  magnetContainer = new BDSGeometryComponent(magnetContainerSolid,
					     magnetContainerLV,
					     magContExtentX,
					     magContExtentY,
					     magContExtentZ,
					     dipolePosition);
  
  // build the BDSMagnetOuter instance and return it
  BDSMagnetOuter* outer = new BDSMagnetOuter(containerSolid,
					     containerLV,
					     extX, extY, extZ,
					     magnetContainer);

  // register objects
  outer->InheritObjects(secondBP);
  outer->RegisterLogicalVolume(allLogicalVolumes);
  outer->RegisterSensitiveVolume(allLogicalVolumes);
  outer->RegisterPhysicalVolume(allPhysicalVolumes);
  outer->RegisterVisAttributes(allVisAttributes);
  outer->RegisterUserLimits(allUserLimits);
  // no rotation matrices used in this one
  // allLogicalVolumes is a local variable and goes out of scope so doesn't
  // need to be emptied or reset here
  
  return outer;
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateRectangularBend(G4String      name,
								G4double      length,
								BDSBeamPipe*  beamPipe,
								G4double      outerDiameter,
								G4double      /*containerDiameter*/,
								G4double      containerLength,
								G4double      /*angle*/,
								G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return CreateSectorBend(name,length,beamPipe,outerDiameter,containerLength,0,outerMaterial);
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateQuadrupole(G4String      name,
							   G4double      length,
							   BDSBeamPipe*  beamPipe,
							   G4double      outerDiameter,
							   G4double      containerLength,
							   G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CleanUp();

  // test input parameters - set global options as default if not specified
  TestInputParameters(beamPipe,outerDiameter,outerMaterial);

  // geometrical constants
  // [1] LHC design report - Chapter 7, fig 7.3
  // [2] LHC design report - Chapter 7, fig 7.1
  G4double beamPipeAxisSeparation = 194.00*CLHEP::mm;               // at 1.9K
  G4double massShift              = 0.5 * beamPipeAxisSeparation;   // central shift to geometry
  //G4double collarBoxHalfHeight    = 60*CLHEP::mm;                 // [1] by visual inspection
  G4double collarBoxHalfWidth     = 22*CLHEP::mm;                   // fits between outer coils

  // radii
  G4double containerInnerRadius   = beamPipe->GetContainerRadius()+1*CLHEP::um;
  G4double coilInnerRadius        = containerInnerRadius + lengthSafety;
  G4double coilInnerRadiusF       = 24.601*CLHEP::mm; // the fixed radius for the second pipe - F for fixed
  G4double coilOuterRadius        = 60*CLHEP::mm;                   // [2] by visual inspection
  G4double collarInnerRadius      = coilOuterRadius + lengthSafety;
  G4double collarInnerRadiusF     = coilOuterRadius + lengthSafety;
  G4double collarOuterRadius      = 101.18*CLHEP::mm;               // [1] - at 293K but don't have 1.9K measurement
  G4double yokeOuterRadius        = 570.0*0.5*CLHEP::mm;            // [2] - at 293K but don't have 1.9K measurement
  G4double magnetContainerRadius  = yokeOuterRadius + lengthSafetyLarge;

  // angular setup of coils
  // these angles were calculated by visually analysing the coil layout graph in [2]
  G4double poleFullAngle    = CLHEP::pi/6.; //30 degrees angle in radians
  G4double coilFullAngle    = CLHEP::pi/2. - poleFullAngle - 1e-5; // 1e-5 to prevent overlaps
  G4double coilHalfAngle    = coilFullAngle*0.5;
  G4double coilStartAngle   = -coilHalfAngle;
  G4double poleStartAngle   = coilHalfAngle;
  G4RotationMatrix* coil2rm = new G4RotationMatrix();
  G4RotationMatrix* coil3rm = new G4RotationMatrix();
  G4RotationMatrix* coil4rm = new G4RotationMatrix();
  coil2rm->rotateZ(CLHEP::pi/2.0);
  coil3rm->rotateZ(CLHEP::pi);
  coil4rm->rotateZ(CLHEP::pi*1.5);
  allRotationMatrices.push_back(coil2rm);
  allRotationMatrices.push_back(coil3rm);
  allRotationMatrices.push_back(coil4rm);

  // whether to build various components around active beam pipe depending on how wide it is
  // these ONLY apply to the components around the active beampipe
  G4bool buildCoil         = true;
  G4bool buildCollar       = true; // collar around the active beam pipe
  if (coilInnerRadius > coilOuterRadius)
    {buildCoil = false;}
  // this still uses the boxHalfWidth but just as good as the collar annulli overlap slightly in the middle
  // and this will protect against this
  if ((coilInnerRadius > collarInnerRadius) && (coilInnerRadius < (massShift - collarBoxHalfWidth)))
    {collarInnerRadius = containerInnerRadius + lengthSafety;}
  if (coilInnerRadius > (massShift - collarBoxHalfWidth))
    {buildCollar = false;}
  if (coilInnerRadius > collarOuterRadius)
    {
      // pipe is too big to use with this geometry!
      G4cerr << __METHOD_NAME__ << "this beam pipe is too big to use with the LHC dipole geometry" << G4endl;
      G4cerr << "Please consider using a different magnet geometry for this particular magnet" << G4endl;
      G4cerr << "Magnet named: " << name << G4endl;
      exit(1);
    }

  G4ThreeVector dipolePosition; // translation of whole assembly relative to centre of active pipe
  if (isLeftOffset)
    {
      dipolePosition = G4ThreeVector(massShift,0.,0.);
      beamPipeAxisSeparation  *= -1;
#ifdef BDSDEBUG
      G4cout << __METHOD_NAME__ << "dipole to the left" << G4endl;
#endif
    }
  else
    {
      dipolePosition = G4ThreeVector(-massShift,0.,0.);
      //massShift     *= -1;
#ifdef BDSDEBUG
      G4cout << __METHOD_NAME__ << "dipole to the right" << G4endl;
#endif
    }
  
  if (beamPipe->ContainerIsCircular())
    {
      //circular beampipe so we can simply use its radius
      //container is similar but slightly wider and hollow (to allow placement of beampipe)
      //have to do subtraction as cuttubs aperture is central and the beampipe (active one) is not here
      G4VSolid* containerSolidOuter = new G4Tubs(name + "_contiainer_solid_outer",  // name
						 0,                           // inner radius
						 yokeOuterRadius,             // outer radius
						 length*0.5,                  // half length
						 0,                           // rotation start angle
						 CLHEP::twopi);               // rotation finish angle
						    
      G4VSolid* containerSolidInner = new G4Tubs(name + "_contiainer_solid_inner",  // name
						 0,                                 // inner radius
						 containerInnerRadius,              // outer radius
						 length,                            // full length for unambiguous subtraction
						 0,                                 // rotation start angle
						 CLHEP::twopi);
      allSolids.push_back(containerSolidOuter);
      allSolids.push_back(containerSolidInner);
      containerSolid = new G4SubtractionSolid(name + "_container_solid",   // name
					      containerSolidOuter,         // outer bit
					      containerSolidInner,         // subtract this from it
					      0,                           // rotation
					      -dipolePosition);            // translation
    }
  else
    {
      //container is similar but slightly wider
      G4VSolid* containerSolidOuter = new G4Tubs(name + "_contiainer_solid_outer",  // name
						 0,                                 // inner radius
						 yokeOuterRadius,                   // outer radius
						 length*0.5,                        // half length
						 0,                                 // rotation start angle
						 CLHEP::twopi);                     // rotation finish angle
      allSolids.push_back(containerSolidOuter);
      containerSolid = new G4SubtractionSolid(name + "_container_solid",
					      containerSolidOuter,
					      beamPipe->GetContainerSubtractionSolid(),
					      0,                // rotation
					      -dipolePosition); // translation
    }

  // make the whole magnet container solid
  BuildMagnetContainerSolidStraight(name, containerLength, magnetContainerRadius);
  // make the logical volume too manually as we don't use the BDSMagnetOuterFactoryBase method for this

  G4Material* emptyMaterial = BDSMaterials::Instance()->GetMaterial(BDSGlobalConstants::Instance()->GetEmptyMaterial());

  magnetContainerLV = new G4LogicalVolume(magnetContainerSolid,
					  emptyMaterial,
					  name + "_container_lv");
  containerLV = new G4LogicalVolume(containerSolid,
				    emptyMaterial,
				    name + "_container_lv");
  
  // coil solids
  // only need one pole & coil per beampipe which can be repeatedly placed
  // just inner radius can be different depending on active beam pipe hence two
  G4VSolid*        coil1     = nullptr;
  G4VSolid*        coil2     = nullptr;
  G4LogicalVolume* coil1LV   = nullptr;
  G4LogicalVolume* coil2LV   = nullptr;
  G4VPhysicalVolume* coil1PV = nullptr;
  G4VPhysicalVolume* coil2PV = nullptr;
  G4VPhysicalVolume* coil3PV = nullptr;
  G4VPhysicalVolume* coil4PV = nullptr;
  G4VPhysicalVolume* coil5PV = nullptr;
  G4VPhysicalVolume* coil6PV = nullptr;
  G4VPhysicalVolume* coil7PV = nullptr;
  G4VPhysicalVolume* coil8PV = nullptr;

  // pole solids are the ones immediately after coilN clockwise
  G4VSolid*        pole1     = nullptr;
  G4VSolid*        pole2     = nullptr;
  G4LogicalVolume* pole1LV   = nullptr;
  G4LogicalVolume* pole2LV   = nullptr;
  G4VPhysicalVolume* pole1PV = nullptr;
  G4VPhysicalVolume* pole2PV = nullptr;
  G4VPhysicalVolume* pole3PV = nullptr;
  G4VPhysicalVolume* pole4PV = nullptr;
  G4VPhysicalVolume* pole5PV = nullptr;
  G4VPhysicalVolume* pole6PV = nullptr;
  G4VPhysicalVolume* pole7PV = nullptr;
  G4VPhysicalVolume* pole8PV = nullptr;

  // collar solid - only need one as can union with itself but offset
  G4VSolid*        collar    = nullptr;
  G4VSolid*        collars   = nullptr; // union of two collars
  G4LogicalVolume* collarsLV = nullptr;

  // materials and visual attributes
  G4Material* nbti              = BDSMaterials::Instance()->GetMaterial("NbTi.1");
  G4Material* iron              = BDSMaterials::Instance()->GetMaterial("iron");
  G4Material* stainlesssteel    = BDSMaterials::Instance()->GetMaterial("stainlesssteel");
  G4VisAttributes* coilVisAtt   = new G4VisAttributes(G4Colour(0.9, 0.75, 0.)); //gold-ish colour
  coilVisAtt->SetForceLineSegmentsPerCircle(nSegmentsPerCircle);
  G4VisAttributes* collarVisAtt = new G4VisAttributes(G4Colour(0.9, 0.9, 0.9)); // grey
  collarVisAtt->SetForceLineSegmentsPerCircle(nSegmentsPerCircle);
  allVisAttributes.push_back(coilVisAtt);
  allVisAttributes.push_back(collarVisAtt);
  
  if (buildCoil)
    {
      // coil solid
      coil1 = new G4Tubs(name+"_coil1_solid",          // name
			 coilInnerRadius,              // inner radius
			 coilOuterRadius,              // outer radius
			 length*0.5-2*lengthSafety,    // z half length
			 coilStartAngle,               // start angle
			 coilFullAngle);               // sweep angle
      // coil logical volumes
      coil1LV = new G4LogicalVolume(coil1,             // solid
				    nbti,              // material
				    name+"_coil1_lv"); // name
      coil1LV->SetVisAttributes(coilVisAtt);
      allSolids.push_back(coil1);
      allLogicalVolumes.push_back(coil1LV);

      // pole solid
      pole1 = new G4Tubs(name+"_pole1_solid",          // name
			 coilInnerRadius,              // inner radius
			 coilOuterRadius,              // outer radius
			 length*0.5 - lengthSafety,    // z half length
			 poleStartAngle,               // start angle
			 poleFullAngle);               // sweep angle
      pole1LV = new G4LogicalVolume(pole1,             // solid
				    stainlesssteel,    // material
				    name+"_pole1_lv"); // name
      pole1LV->SetVisAttributes(collarVisAtt);
      allSolids.push_back(pole1);
      allLogicalVolumes.push_back(pole1LV);

      // coil placements
      coil1PV = new G4PVPlacement(0,                  // rotation
				  -dipolePosition,    // position
				  coil1LV,            // logical volume
				  name + "_coil1_pv", // name
				  containerLV,        // mother volume
				  false,              // boolean operation
				  0,                  // copy number
				  checkOverlaps);
      coil2PV = new G4PVPlacement(coil2rm,            // rotation
				  -dipolePosition,    // position
				  coil1LV,            // logical volume
				  name + "_coil2_pv", // name
				  containerLV,        // mother volume
				  false,              // boolean operation
				  0,                  // copy number
				  checkOverlaps);
      coil3PV = new G4PVPlacement(coil3rm,            // rotation
				  -dipolePosition,    // position
				  coil1LV,            // logical volume
				  name + "_coil3_pv", // name
				  containerLV,        // mother volume
				  false,              // boolean operation
				  0,                  // copy number
				  checkOverlaps);
      coil4PV = new G4PVPlacement(coil4rm,            // rotation
				  -dipolePosition,    // position
				  coil1LV,            // logical volume
				  name + "_coil4_pv", // name
				  containerLV,        // mother volume
				  false,              // boolean operation
				  0,                  // copy number
				  checkOverlaps);
      allPhysicalVolumes.push_back(coil1PV);
      allPhysicalVolumes.push_back(coil2PV);
      allPhysicalVolumes.push_back(coil3PV);
      allPhysicalVolumes.push_back(coil4PV);

      // pole placements
      pole1PV = new G4PVPlacement(0,                  // rotation
				  -dipolePosition,    // position
				  pole1LV,            // logical volume
				  name + "_pole1_pv", // name
				  containerLV,        // mother volume
				  false,              // boolean operation
				  0,                  // copy number
				  checkOverlaps);
      pole2PV = new G4PVPlacement(coil2rm,            // rotation
				  -dipolePosition,    // position
				  pole1LV,            // logical volume
				  name + "_pole2_pv", // name
				  containerLV,        // mother volume
				  false,              // boolean operation
				  0,                  // copy number
				  checkOverlaps);
      pole3PV = new G4PVPlacement(coil3rm,            // rotation
				  -dipolePosition,    // position
				  pole1LV,            // logical volume
				  name + "_pole3_pv", // name
				  containerLV,        // mother volume
				  false,              // boolean operation
				  0,                  // copy number
				  checkOverlaps);
      pole4PV = new G4PVPlacement(coil4rm,            // rotation
				  -dipolePosition,    // position
				  pole1LV,            // logical volume
				  name + "_pole4_pv", // name
				  containerLV,        // mother volume
				  false,              // boolean operation
				  0,                  // copy number
				  checkOverlaps);
      allPhysicalVolumes.push_back(pole1PV);
      allPhysicalVolumes.push_back(pole2PV);
      allPhysicalVolumes.push_back(pole3PV);
      allPhysicalVolumes.push_back(pole4PV);
    }
  
  // fixed coil
  coil2   = new G4Tubs(name+"_coil2_solid",          // name
		       coilInnerRadiusF,             // inner radius
		       coilOuterRadius,              // outer radius
		       length*0.5-2*lengthSafety,    // length
		       coilStartAngle,               // start angle
		       coilFullAngle);               // sweep angle
  coil2LV = new G4LogicalVolume(coil2,               // solid
				nbti,                // material
				name+"_coil2_lv");   // name
  coil2LV->SetVisAttributes(coilVisAtt);
  allSolids.push_back(coil2);
  allLogicalVolumes.push_back(coil2LV);
  
  // fixed pole
  pole2   = new G4Tubs(name+"_pole2_solid",          // name
		       coilInnerRadiusF,             // inner radius
		       coilOuterRadius,              // outer radius
		       length*0.5 - lengthSafety,    // z half length
		       poleStartAngle,               // start angle
		       poleFullAngle);               // sweep angle
  pole2LV = new G4LogicalVolume(pole2,               // solid
				stainlesssteel,      // material
				name+"_pole2_lv");   // name
  pole2LV->SetVisAttributes(collarVisAtt);
  allSolids.push_back(pole2);
  allLogicalVolumes.push_back(pole2LV);
  
  // fixed coil placements
  coil5PV = new G4PVPlacement(0,                  // rotation
			      dipolePosition,     // position
			      coil2LV,            // logical volume
			      name + "_coil5_pv", // name
			      containerLV,        // mother volume
			      false,              // boolean operation
			      0,                  // copy number
			      checkOverlaps);
  coil6PV = new G4PVPlacement(coil2rm,            // rotation
			      dipolePosition,     // position
			      coil2LV,            // logical volume
			      name + "_coil6_pv", // name
			      containerLV,        // mother volume
			      false,              // boolean operation
			      0,                  // copy number
			      checkOverlaps);
  coil7PV = new G4PVPlacement(coil3rm,            // rotation
			      dipolePosition,     // position
			      coil2LV,            // logical volume
			      name + "_coil7_pv", // name
			      containerLV,        // mother volume
			      false,              // boolean operation
			      0,                  // copy number
			      checkOverlaps);
  coil8PV = new G4PVPlacement(coil4rm,            // rotation
			      dipolePosition,     // position
			      coil2LV,            // logical volume
			      name + "_coil8_pv", // name
			      containerLV,        // mother volume
			      false,              // boolean operation
			      0,                  // copy number
			      checkOverlaps);
  allPhysicalVolumes.push_back(coil5PV);
  allPhysicalVolumes.push_back(coil6PV);
  allPhysicalVolumes.push_back(coil7PV);
  allPhysicalVolumes.push_back(coil8PV);
  
  // fixed pole placements
  pole5PV = new G4PVPlacement(0,                  // rotation
			      dipolePosition,    // position
			      pole2LV,            // logical volume
			      name + "_pole5_pv", // name
			      containerLV,        // mother volume
			      false,              // boolean operation
			      0,                  // copy number
			      checkOverlaps);
  pole6PV = new G4PVPlacement(coil2rm,            // rotation
			      dipolePosition,    // position
			      pole2LV,            // logical volume
			      name + "_pole6_pv", // name
			      containerLV,        // mother volume
			      false,              // boolean operation
			      0,                  // copy number
			      checkOverlaps);
  pole7PV = new G4PVPlacement(coil3rm,            // rotation
			      dipolePosition,    // position
			      pole2LV,            // logical volume
			      name + "_pole7_pv", // name
			      containerLV,        // mother volume
			      false,              // boolean operation
			      0,                  // copy number
			      checkOverlaps);
  pole8PV = new G4PVPlacement(coil4rm,            // rotation
			      dipolePosition,    // position
			      pole2LV,            // logical volume
			      name + "_pole8_pv", // name
			      containerLV,        // mother volume
			      false,              // boolean operation
			      0,                  // copy number
			      checkOverlaps);

  allPhysicalVolumes.push_back(pole5PV);
  allPhysicalVolumes.push_back(pole6PV);
  allPhysicalVolumes.push_back(pole7PV);
  allPhysicalVolumes.push_back(pole8PV);
  
  // non-magnetic collars
  // collar pole solid
  collar = new G4Tubs(name+"_collar_solid",        // name
		      collarInnerRadiusF,          // inner radius
		      collarOuterRadius,           // outer radius
		      length*0.5 - 2*lengthSafety, // length
		      0,                           // start angle
		      CLHEP::twopi);               // sweep angle
  allSolids.push_back(collar);
  collars = collar;
  if (buildCollar)
    {
      if (collarInnerRadius == collarInnerRadiusF)
	{
	  // can save a solid by doing the union with the existing one if they're the same
	  collars = new G4UnionSolid(name + "_collars_solid",  // name
				     collar,                   // solid 1
				     collar,                   // solid 2
				     0,                        // rotation
				     -2*dipolePosition);       // translation
	}
      else
	{
	  G4VSolid* collar2 = new G4Tubs(name+"_collar2_solid",      // name
					 collarInnerRadius,          // inner radius
					 collarOuterRadius,          // outer radius
					 length*0.5-2*lengthSafety,  // length
					 0,                          // starting angle
					 CLHEP::twopi);              // angle of sweep
	  allSolids.push_back(collar2);
	  collars = new G4UnionSolid(name + "_collars_solid", // name
				     collar,                  // solid 1
				     collar2,                 // solid 2
				     0,                       // rotation
				     -2*dipolePosition);      // translation
	}
      allSolids.push_back(collars);
    }
  
  collarsLV = new G4LogicalVolume(collars,
				  stainlesssteel,
				  name+"_collars_lv");
  collarsLV->SetVisAttributes(collarVisAtt);
  allLogicalVolumes.push_back(collarsLV); 

  G4PVPlacement* collarPV = new G4PVPlacement(0,                  // rotation
					      dipolePosition,     // position
					      collarsLV,          // its logical volume
					      name+"_collars_pv", // its name
					      containerLV,        // its mother  volume
					      false,              // no boolean operation
					      0,                  // copy number
					      checkOverlaps);
  allPhysicalVolumes.push_back(collarPV);

  // prepare a solid to cut a hole in the outer yoke volume (can just use one twice)
  // can't use the existing collar solids as they're not solid - need them to be solid
  G4VSolid* collarSubtractionCylinder = new G4Tubs(name+"_collar_subtraction_solid",  // name
						   0,                                 // inner radius
						   collarOuterRadius + lengthSafety,  // outer radius
						   length,                            // double length for unambiguous subtraction
						   0,                                 // starting angle
						   CLHEP::twopi);                     // sweep angle

  G4VSolid* collarSubtractionCylinders = new G4UnionSolid(name + "_collar_subtraction_cylinders", // name
							  collarSubtractionCylinder,              // solid1
							  collarSubtractionCylinder,              // solid2 (here = solid1)
							  0,                                      // rotation
							  2*dipolePosition);                      // translation
 
  // outer iron yoke
  G4VSolid* yokeCylinder = new G4Tubs(name+"_yoke_cylinder_solid",     // name
				      0.,                              // inner radius
				      yokeOuterRadius,                 // outer radius
				      0.5*length-2*lengthSafety,       // length
				      0,                               // starting angle
				      CLHEP::twopi * CLHEP::rad);      // sweep angle

  yokeSolid = new G4SubtractionSolid(name+"_yoke_solid",             // name
				     yokeCylinder,                   // from this
				     collarSubtractionCylinders,     // subtract this
				     0,
				     -dipolePosition);               
  allSolids.push_back(collarSubtractionCylinder);
  allSolids.push_back(collarSubtractionCylinders);
  allSolids.push_back(yokeCylinder);
  yokeLV = new G4LogicalVolume(yokeSolid,
			       iron,
			       name+"_yoke_lv");
  
  // yoke visualisation
  G4VisAttributes* LHCred = new G4VisAttributes(G4Colour(1.0, 0., 0.));
  LHCred->SetForceLineSegmentsPerCircle(nSegmentsPerCircle);
  allVisAttributes.push_back(LHCred);
  yokeLV->SetVisAttributes(LHCred);
  
  allLogicalVolumes.push_back(yokeLV); // register locally

  // yoke placement
  yokePV = new G4PVPlacement((G4RotationMatrix*)0,         // no rotation
			     G4ThreeVector(0,0,0),         // position
			     yokeLV,                       // lv to be placed
			     name + "_yoke_pv",            // name
			     containerLV,                  // mother lv to be place in
			     false,                        // no boolean operation
			     0,                            // copy number
			     checkOverlaps);
  allPhysicalVolumes.push_back(yokePV);

  G4String defaultMaterialName = BDSGlobalConstants::Instance()->GetBeamPipeMaterialName();
  G4Material* beamPipeMaterial = BDSMaterials::Instance()->GetMaterial(defaultMaterialName);
  G4Material* vacuumMaterial   = BDSMaterials::Instance()->GetMaterial(BDSGlobalConstants::Instance()->GetVacuumMaterial());
  
  //use beampipe factories to create another beampipe (note no magnetic field for now...)
  BDSBeamPipe* secondBP = BDSBeamPipeFactory::Instance()->CreateBeamPipe(BDSBeamPipeType::lhcdetailed,
									 name,
									 length-2*lengthSafety,
									 2.202*CLHEP::cm,   // aper1
									 1.714*CLHEP::cm,   // aper2
									 2.202*CLHEP::cm,   // aper3
									 0,                 // aper4
									 vacuumMaterial,    // vacuum material
									 1*CLHEP::mm,       // beampipeThickness
									 beamPipeMaterial); // beampipe material
  
  G4LogicalVolume* secondBPLV = secondBP->GetContainerLogicalVolume();
  G4PVPlacement* secondBPPV = new G4PVPlacement((G4RotationMatrix*)0,         // no rotation
						dipolePosition,               // position
						secondBPLV,                   // lv to be placed
						name + "_second_beampipe_pv", // name
						containerLV,                  // mother lv to be place in
						false,                        // no boolean operation
						0,                            // copy number
						checkOverlaps);
  allPhysicalVolumes.push_back(secondBPPV);
  
  // visual attributes for container
  if (visDebug)
    {
      containerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetVisibleDebugVisAttr());
      magnetContainerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetVisibleDebugVisAttr());
    }
  else
    {
      containerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetInvisibleVisAttr());
      magnetContainerLV->SetVisAttributes(BDSGlobalConstants::Instance()->GetInvisibleVisAttr());
    }

  // USER LIMITS and SENSITIVITY for all components
#ifndef NOUSERLIMITS
  G4UserLimits* userLimits = new G4UserLimits("outer_cuts");
  userLimits->SetMaxAllowedStep( length * maxStepFactor );
  userLimits->SetUserMaxTime(BDSGlobalConstants::Instance()->GetMaxTime());
  allUserLimits.push_back(userLimits);    
  for (auto i : allLogicalVolumes)
    {i->SetUserLimits(userLimits);}
  containerLV->SetUserLimits(userLimits);
  magnetContainerLV->SetUserLimits(userLimits);
#endif
    
  // record extents
  // container radius is the same for all methods as all cylindrical
  G4double containerRadius = yokeOuterRadius;
  // massShift defined at very beginning of this function
  std::pair<double,double> extX = std::make_pair(-containerRadius+massShift,containerRadius+massShift); 
  std::pair<double,double> extY = std::make_pair(-containerRadius,containerRadius);
  std::pair<double,double> extZ = std::make_pair(-length*0.5,length*0.5);
  
  magnetContainer = new BDSGeometryComponent(magnetContainerSolid,
					     magnetContainerLV,
					     magContExtentX,
					     magContExtentY,
					     magContExtentZ);
  
  // build the BDSMagnetOuter instance and return it
  BDSMagnetOuter* outer = new BDSMagnetOuter(containerSolid,
					     containerLV,
					     extX, extY, extZ,
					     magnetContainer,
					     dipolePosition);
  
  // register objects
  outer->InheritObjects(secondBP);
  outer->RegisterSolid(allSolids);
  outer->RegisterLogicalVolume(allLogicalVolumes);
  outer->RegisterPhysicalVolume(allPhysicalVolumes);
  outer->RegisterVisAttributes(allVisAttributes);
  outer->RegisterUserLimits(allUserLimits);
  outer->RegisterRotationMatrix(allRotationMatrices);
  
  return outer;
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateSextupole(G4String      name,
								G4double      length,
								BDSBeamPipe*  beamPipe,
								G4double      outerDiameter,
								G4double      containerLength,
								G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateSextupole(name,length,beamPipe,outerDiameter,
								       containerLength,outerMaterial);
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateOctupole(G4String      name,
							 G4double      length,
							 BDSBeamPipe*  beamPipe,
							 G4double      outerDiameter,
							 G4double      containerLength,
							 G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateOctupole(name,length,beamPipe,outerDiameter,
								      containerLength,outerMaterial);
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateDecapole(G4String      name,
							 G4double      length,
							 BDSBeamPipe*  beamPipe,
							 G4double      outerDiameter,
							 G4double      containerLength,
							 G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateDecapole(name,length,beamPipe,outerDiameter,
								      containerLength,outerMaterial);
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateSolenoid(G4String      name,
							 G4double      length,
							 BDSBeamPipe*  beamPipe,
							 G4double      outerDiameter,
							 G4double      containerLength,
							 G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateSolenoid(name,length,beamPipe,outerDiameter,
								      containerLength,outerMaterial);
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateMultipole(G4String      name,
							  G4double      length,
							  BDSBeamPipe*  beamPipe,
							  G4double      outerDiameter,
							  G4double      containerLength,
							  G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateMultipole(name,length,beamPipe,outerDiameter,
								       containerLength,outerMaterial);
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateRfCavity(G4String      name,
							 G4double      length,
							 BDSBeamPipe*  beamPipe,
							 G4double      outerDiameter,
							 G4double      containerLength,
							 G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateRfCavity(name,length,beamPipe,outerDiameter,
								      containerLength,outerMaterial);
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateMuSpoiler(G4String      name,
							  G4double      length,
							  BDSBeamPipe*  beamPipe,
							  G4double      outerDiameter,
							  G4double      containerLength,
							  G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateMuSpoiler(name,length,beamPipe,outerDiameter,
								       containerLength,outerMaterial);
}

BDSMagnetOuter* BDSMagnetOuterFactoryLHC::CreateKicker(G4String      name,
						       G4double      length,
						       BDSBeamPipe*  beamPipe,
						       G4double      outerDiameter,
						       G4double      containerLength,
						       G4bool        vertical,
						       G4Material*   outerMaterial)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  return BDSMagnetOuterFactoryCylindrical::Instance()->CreateKicker(name,length,beamPipe,outerDiameter,
								    containerLength,vertical,outerMaterial);
}

/// functions below here are private to this particular factory
void BDSMagnetOuterFactoryLHC::TestInputParameters(BDSBeamPipe* /*beamPipe*/,
						   G4double&    outerDiameter,
						   G4Material*& outerMaterial)// reference to a pointer
{
  //function arguments by reference to they can be modified in place
  //check outer material is something
  if (!outerMaterial)
    {outerMaterial = BDSMaterials::Instance()->GetMaterial("stainlesssteel");}

  // ensure outerDiameter is > outerCollarDiameter - hard coded as specific to the lhc design
  if (outerDiameter < 202*CLHEP::mm )
    {outerDiameter = 202*CLHEP::mm;}
}
