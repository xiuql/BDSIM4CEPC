#include "BDSBeamPipeFactoryBase.hh"
#include "BDSBeamPipeFactoryLHCDetailed.hh"
#include "BDSBeamPipe.hh"

#include "BDSColours.hh"
#include "BDSDebug.hh"
#include "BDSExecOptions.hh"
#include "BDSGlobalConstants.hh"
#include "BDSMaterials.hh"

#include "globals.hh"                      // geant4 globals / types
#include "G4Box.hh"
#include "G4CutTubs.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4VSolid.hh"

#include <cmath>
#include <utility>                         // for std::pair


BDSBeamPipeFactoryLHCDetailed* BDSBeamPipeFactoryLHCDetailed::_instance = nullptr;

BDSBeamPipeFactoryLHCDetailed* BDSBeamPipeFactoryLHCDetailed::Instance()
{
  if (_instance == nullptr)
    {_instance = new BDSBeamPipeFactoryLHCDetailed();}
  return _instance;
}

BDSBeamPipeFactoryLHCDetailed::BDSBeamPipeFactoryLHCDetailed():BDSBeamPipeFactoryBase()
{
  coldBoreThickness         = 1.5*CLHEP::mm;
  coolingPipeThickness      = 0.53*CLHEP::mm;
  coolingPipeRadius         = 3.7*CLHEP::mm*0.5; // will be overwritten if needs be to fit inside beampipe
  coolingPipeOffset         = 0.0;  //initialised only
  copperSkinThickness       = 75*CLHEP::um;
  CleanUp();
}

BDSBeamPipeFactoryLHCDetailed::~BDSBeamPipeFactoryLHCDetailed()
{
  _instance = nullptr;
}

void BDSBeamPipeFactoryLHCDetailed::CleanUp()
{
  BDSBeamPipeFactoryBase::CleanUp();
  copperSkinSolid     = nullptr; // the copper skin
  screenSolid         = nullptr; // the beam screen (first bit of aperture)
  coolingPipeSolid    = nullptr; // small cooling pipe above and below beam screen
  copperSkinLV        = nullptr;
  screenLV            = nullptr;
  coolingPipeLV       = nullptr;
  copperSkinPV        = nullptr;
  screenPV            = nullptr;
  coolingPipeTopPV    = nullptr;
  coolingPipeBottomPV = nullptr;
  
  InitialiseGeometricalParameters();
}

void BDSBeamPipeFactoryLHCDetailed::InitialiseGeometricalParameters()
{
  vacRadius = 0, vacBoxX = 0, vacBoxY = 0;
  
  cuInnerRadius = 0, cuInnerBoxX = 0, cuInnerBoxY = 0;
  cuOuterRadius = 0, cuOuterBoxX = 0, cuOuterBoxY = 0;
  
  bsInnerRadius = 0, bsInnerBoxX = 0, bsInnerBoxY = 0;
  bsOuterRadius = 0, bsOuterBoxX = 0, bsOuterBoxY = 0;
  
  cbInnerRadius = 0, cbOuterRadius = 0;
  
  containerRadius = 0;
  
  vacHalfLength = 0;
  halfLength = 0;
  
  coolingPipeOffset = 0;
  verticalOrientation = true; // arbitrary, will be overwritten
  buildCoolingPipe = true;
}


G4double BDSBeamPipeFactoryLHCDetailed::GetFullWidthOfCoolingPipe()
{
  return coolingPipeRadius + coolingPipeThickness + 2*lengthSafety;
}

void BDSBeamPipeFactoryLHCDetailed::CalculateGeometricalParameters(G4double aper1,
								   G4double aper2,
								   G4double aper3,
								   G4double beamPipeThickness,
								   G4double length)
{
  // vacuum volume
  vacRadius     = aper3;
  vacBoxX       = aper1;
  vacBoxY       = aper2;
  
  // copper skin geometrical parameters
  cuInnerRadius = vacRadius + 1*CLHEP::um;
  cuInnerBoxX   = vacBoxX   + 1*CLHEP::um;
  cuInnerBoxY   = vacBoxY   + 1*CLHEP::um;
  cuOuterRadius = cuInnerRadius + copperSkinThickness;
  cuOuterBoxX   = cuInnerBoxX   + copperSkinThickness;
  cuOuterBoxY   = cuInnerBoxY   + copperSkinThickness;

  // beam screen geometrical parameters
  bsInnerRadius = cuOuterRadius + 1*CLHEP::um;
  bsInnerBoxX   = cuOuterBoxX   + 1*CLHEP::um;
  bsInnerBoxY   = cuOuterBoxY   + 1*CLHEP::um;
  bsOuterRadius = bsInnerRadius + beamPipeThickness;
  bsOuterBoxX   = bsInnerBoxX   + beamPipeThickness;
  bsOuterBoxY   = bsInnerBoxY   + beamPipeThickness;
  
  // cold bore geometrical parameters
  cbInnerRadius = bsOuterRadius + 1*CLHEP::um;
  cbOuterRadius = cbInnerRadius + coldBoreThickness;

  // container geometrical parameters
  containerRadius = cbOuterRadius + 1*CLHEP::um;  
  
  // general length variable (to avoid mistakes)
  vacHalfLength   = length*0.5 - lengthSafety;
  halfLength      = length*0.5 - 1*CLHEP::um; 
  
  // cooling pipe geometrical parameters
  G4double fullWidthOfCoolingPipe = coolingPipeRadius + coolingPipeThickness + 1*CLHEP::um;
  if (aper1 > aper2)
    {
      coolingPipeOffset = bsOuterBoxY + fullWidthOfCoolingPipe;
      verticalOrientation = false;
    }
  else
    {
      coolingPipeOffset = bsOuterBoxX + fullWidthOfCoolingPipe;
      verticalOrientation = true;
    }

  G4double valueToCompare;
  if (verticalOrientation)
    {valueToCompare = bsOuterBoxX;}
  else
    {valueToCompare = bsInnerBoxY;}

  G4double gapForCoolingPipe = std::abs(cbInnerRadius - valueToCompare);
  if (gapForCoolingPipe < fullWidthOfCoolingPipe + 1*CLHEP::um)
    {buildCoolingPipe = false;}
}
  

BDSBeamPipe* BDSBeamPipeFactoryLHCDetailed::CreateBeamPipe(G4String    name,              // name
							   G4double    length,            // length [mm]
							   G4double    aper1,             // rect half width
							   G4double    aper2,             // rect half height
							   G4double    aper3,             // radius of circle
							   G4double    /*aper4*/,         // aperture parameter 4
							   G4Material* vacuumMaterial,    // vacuum material
							   G4double    beamPipeThickness, // beampipe thickness [mm]
							   G4Material* beamPipeMaterial)  // beampipe material
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  // clean up after last usage
  CleanUp();

  // calculate geometrical parameters
  CalculateGeometricalParameters(aper1, aper2, aper3, beamPipeThickness, length);

  // build the solids
  //vacuum cylindrical solid (circular cross-section)
  G4VSolid* vacCylSolid = new G4Tubs(name + "_vacuum_cylinder", // name
				     0,                           // inner radius
				     vacRadius,                   // outer radius
				     vacHalfLength,               // half length
				     0,                           // rotation start angle
				     CLHEP::twopi);               // rotation finish angle
  //vacuum box solid (rectangular cross-section)
  G4VSolid* vacRectSolid = new G4Box(name + "_vacuum_box", // name
				     vacBoxX,                // x half width
				     vacBoxY,                // y half width
				     length); // z full width (long for unambiguous intersection)
  allSolids.push_back(vacCylSolid);
  allSolids.push_back(vacRectSolid);
  
  //intersection of both of these gives the desired shape
  vacuumSolid = new G4IntersectionSolid(name + "_vacuum_solid", // name
					vacCylSolid,              // solid 1
					vacRectSolid);            // solid 2


  //copper skin layer to beamscreen
  //copper skin inner edge for subtraction (actually just like vacuum + lengthSafety)
  G4VSolid* cuInnerCylSolid = new G4Tubs(name + "_cu_inner_cylinder", // name
					 0,                             // inner radius
					 cuInnerRadius,                 // outer radius
					 1.5*length,  // length big for unambiguous subtraction (but < outerlength)
					 0,                             // rotation start angle
					 CLHEP::twopi);                 // rotation finish angle
  //screen inner edge box solid (rectangular cross-section)
  G4VSolid* cuInnerRectSolid = new G4Box(name + "_cu_inner_box", // name
					 cuInnerBoxX,              // x half width
					 cuInnerBoxY,              // y half width
					 1.7*length); // z long for unambiguous intersection
  //screen inner intersection - 1.5*length long which is > half length for unambiguous subtraction later
  G4VSolid* cuInnerSolid = new G4IntersectionSolid(name + "_cu_inner_solid", // name
						   cuInnerCylSolid,            // solid 1
						   cuInnerRectSolid);          // solid 2

  //screen outer edge for subtraction (actually just like vacuum + lengthSafety)
  G4VSolid* cuOuterCylSolid = new G4Tubs(name + "_cu_outer_cylinder",    // name
					 0,                                // inner radius (0 for unambiguous subtraction)
					 cuOuterRadius,                    // outer radius
					 halfLength,                       // half length
					 0,                                // rotation start angle
					 CLHEP::twopi);                    // rotation finish angle
  //screen outer edge box solid (rectangular cross-section)
  G4VSolid* cuOuterRectSolid = new G4Box(name + "_cu_outer_box", // name
					 cuOuterBoxX,              // x half width
					 cuOuterBoxY,              // y half width
					 length); // z full width (long for unambiguous intersection)
  G4VSolid* cuOuterSolid = new G4IntersectionSolid(name + "_cu_outer_solid", // name
						   cuOuterCylSolid,            // solid 1
						   cuOuterRectSolid);          // solid 2
  copperSkinSolid = new G4SubtractionSolid(name + "_copper_skin_solid",// name
					   cuOuterSolid,                 // this
					   cuInnerSolid);                // minus this
  allSolids.push_back(cuInnerCylSolid);
  allSolids.push_back(cuInnerRectSolid);
  allSolids.push_back(cuInnerSolid);
  allSolids.push_back(cuOuterCylSolid);
  allSolids.push_back(cuOuterRectSolid);
  allSolids.push_back(cuOuterSolid);
  allSolids.push_back(copperSkinSolid);
  
  //beampipe cylindrical solid (circular cross-section)
  //beampipe inner edge for subtraction (actually just like vacuum + lengthSafety)
  //using large margin of 1um here to avoid misplacement errors with compound booleans in geant4 (empirical solution)
  G4VSolid* screenInnerCylSolid = new G4Tubs(name + "_screen_inner_cylinder", // name
					     0,                                 // inner radius
					     bsInnerRadius,                     // outer radius
					     1.5*length, // length big for unambiguous subtraction (but < outerlength)
					     0,                                 // rotation start angle
					     CLHEP::twopi);                     // rotation finish angle
  //screen inner edge box solid (rectangular cross-section)
  //using large margin of 1um here to avoid misplacement errors with compound booleans in geant4 (empirical solution)
  G4VSolid* screenInnerRectSolid = new G4Box(name + "_screen_inner_box", // name
					     bsInnerBoxX,                  // x half width
					     bsInnerBoxY,                  // y half width
					     1.7*length); // z long for unambiguous intersection
  //screen inner intersection - 1.5*length long which is > half length for unambiguous subtraction later
  G4VSolid* screenInnerSolid = new G4IntersectionSolid(name + "_screen_inner_solid", // name
						       screenInnerCylSolid,            // solid 1
						       screenInnerRectSolid);          // solid 2

  //screen outer edge for subtraction (actually just like vacuum + lengthSafety)x
  G4VSolid* screenOuterCylSolid = new G4Tubs(name + "_screen_outer_cylinder",// name
					     0,                                // inner radius (0 for unambiguous subtraction)
					     bsOuterRadius,                    // outer radius
					     halfLength,                       // half length
					     0,                                // rotation start angle
					     CLHEP::twopi);                    // rotation finish angle
  //screen outer edge box solid (rectangular cross-section)
  G4VSolid* screenOuterRectSolid = new G4Box(name + "_screen_outer_box", // name
					     bsOuterBoxX,                  // x half width
					     bsOuterBoxY,                  // y half width
					     length); // z full width (long for unambiguous intersection)
  G4VSolid* screenOuterSolid = new G4IntersectionSolid(name + "_screen__outersolid", // name
						       screenOuterCylSolid,            // solid 1
						       screenOuterRectSolid);          // solid 2
  screenSolid = new G4SubtractionSolid(name + "_screen_solid",// name
				       screenOuterSolid,        // this
				       screenInnerSolid);       // minus this
  allSolids.push_back(screenInnerCylSolid);
  allSolids.push_back(screenInnerRectSolid);
  allSolids.push_back(screenInnerSolid);
  allSolids.push_back(screenOuterCylSolid);
  allSolids.push_back(screenOuterRectSolid);
  allSolids.push_back(screenOuterSolid);
  allSolids.push_back(screenSolid);

  if (buildCoolingPipe)
    {
      coolingPipeSolid = new G4Tubs(name + "_cooling_pipe_solid",           // name
				    coolingPipeRadius,                        // inner radius
				    coolingPipeRadius + coolingPipeThickness, // outer radius
				    halfLength,                               // half length
				    0,                                        // rotation start angle
				    CLHEP::twopi);                            // rotation finish angle

      allSolids.push_back(coolingPipeSolid);
    }
  
  // beampipe - ("coldbore") circular cross-section and sits outisde screen and cooling pipe
  beamPipeSolid = new G4Tubs(name + "_beampipe_solid",         // name
			     cbInnerRadius,                      // inner radius
			     cbOuterRadius,                      // outer radius
			     halfLength,                         // half length
			     0,                                  // rotation start angle
			     CLHEP::twopi);                      // rotation finish angle
  
  //container cylindrical solid (circular cross-section)
  containerSolid = new G4Tubs(name + "_container_cylinder", // name
			      0,                              // inner radius
			      containerRadius,                // outer radius
			      length*0.5,                     // half length
			      0,                              // rotation start angle
			      CLHEP::twopi);                  // rotation finish angle

  //container cylindrical solid (circular cross-section)
  containerSubtractionSolid = new G4Tubs(name + "_subtraction_cylinder", // name
					 0,                                // inner radius
					 containerRadius + lengthSafety,   // outer radius
					 2*length,                         // long length for unambiguous subtraction
					 0,                                // rotation start angle
					 CLHEP::twopi);                    // rotation finish angle
  
  return CommonFinalConstruction(name, vacuumMaterial, beamPipeMaterial, length, containerRadius);
}

BDSBeamPipe* BDSBeamPipeFactoryLHCDetailed::CreateBeamPipeAngledInOut(G4String    name,              // name
								      G4double    length,            // length [mm]
								      G4double    angleIn,           // the normal angle of the input face
								      G4double    angleOut,          // the normal angle of the input face
								      G4double    aper1,             // aperture parameter 1
								      G4double    aper2,             // aperture parameter 2
								      G4double    aper3,             // aperture parameter 3
								      G4double    /*aper4*/,         // aperture parameter 4
								      G4Material* vacuumMaterial,    // vacuum material
								      G4double    beamPipeThickness, // beampipe thickness [mm]
								      G4Material* beamPipeMaterial   // beampipe material
								      )
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  // clean up after last usage
  CleanUp();

  // calculate geometrical parameters
  CalculateGeometricalParameters(aper1, aper2, aper3, beamPipeThickness, length);
  
  std::pair<G4ThreeVector,G4ThreeVector> faces = CalculateFaces(angleIn, angleOut);
  G4ThreeVector inputface  = faces.first;
  G4ThreeVector outputface = faces.second;
  
  G4double containerRadius = CreateGeneralAngledSolids(name, length, inputface, outputface);
  
  return CommonFinalConstruction(name, vacuumMaterial, beamPipeMaterial, length, containerRadius);
}

BDSBeamPipe* BDSBeamPipeFactoryLHCDetailed::CommonFinalConstruction(G4String    name,
								    G4Material* vacuumMaterial,
								    G4Material* beamPipeMaterial,
								    G4double    length,
								    G4double    containerRadius)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif

  BDSBeamPipeFactoryBase::CommonConstruction(name,
					     vacuumMaterial,
					     beamPipeMaterial,
					     length);
		    
  // record extents
  std::pair<double,double> extX = std::make_pair(-containerRadius,containerRadius);
  std::pair<double,double> extY = std::make_pair(-containerRadius,containerRadius);
  std::pair<double,double> extZ = std::make_pair(-length*0.5,length*0.5);
  
  // build the BDSBeamPipe instance and return it
  BDSBeamPipe* aPipe = BuildBeamPipeAndRegisterVolumes(extX,extY,extZ,containerRadius);
  
  // register sensitive volumes
  aPipe->RegisterSensitiveVolume(screenLV);
  aPipe->RegisterSensitiveVolume(copperSkinLV);
  if (buildCoolingPipe)
    {aPipe->RegisterSensitiveVolume(coolingPipeLV);}
  
  return aPipe;
}

void BDSBeamPipeFactoryLHCDetailed::BuildLogicalVolumes(G4String    name,
							G4Material* vacuumMaterialIn,
							G4Material* beamPipeMaterialIn)
{
  BDSBeamPipeFactoryBase::BuildLogicalVolumes(name,vacuumMaterialIn,beamPipeMaterialIn);

  // get materials
  G4Material* copper = BDSMaterials::Instance()->GetMaterial("Copper");


  copperSkinLV  = new G4LogicalVolume(copperSkinSolid,
				      copper,
				      name + "_copper_lv");
  
  screenLV      = new G4LogicalVolume(screenSolid,
				      beamPipeMaterialIn,
				      name + "_screen_lv");

  if (buildCoolingPipe)
    {
      coolingPipeLV = new G4LogicalVolume(coolingPipeSolid,
					  beamPipeMaterialIn,
					  name + "_cooling_pipe_lv");
      allLogicalVolumes.push_back(coolingPipeLV);
    }
  allLogicalVolumes.push_back(copperSkinLV);
  allLogicalVolumes.push_back(screenLV);
}

void BDSBeamPipeFactoryLHCDetailed::SetVisAttributes()
{
  BDSBeamPipeFactoryBase::SetVisAttributes();

  // copper skin
  G4VisAttributes* cuVisAttr   = new G4VisAttributes(*BDSColours::Instance()->GetColour("LHCcopperskin"));
  cuVisAttr->SetForceLineSegmentsPerCircle(nSegmentsPerCircle);
  cuVisAttr->SetVisibility(true);
  allVisAttributes.push_back(cuVisAttr);
  
  // beampipe
  G4VisAttributes* pipeVisAttr = new G4VisAttributes(*BDSColours::Instance()->GetColour("beampipe"));
  pipeVisAttr->SetVisibility(true);
  pipeVisAttr->SetForceLineSegmentsPerCircle(nSegmentsPerCircle);
  allVisAttributes.push_back(pipeVisAttr);

  copperSkinLV->SetVisAttributes(cuVisAttr);
  screenLV->SetVisAttributes(pipeVisAttr);
  if (buildCoolingPipe)
    {coolingPipeLV->SetVisAttributes(pipeVisAttr);}
}

G4UserLimits* BDSBeamPipeFactoryLHCDetailed::SetUserLimits(G4double length)
{
  G4UserLimits* beamPipeUserLimits = BDSBeamPipeFactoryBase::SetUserLimits(length);
  copperSkinLV->SetUserLimits(beamPipeUserLimits);
  screenLV->SetUserLimits(beamPipeUserLimits);
  if (buildCoolingPipe)
    {coolingPipeLV->SetUserLimits(beamPipeUserLimits);}
  allUserLimits.push_back(beamPipeUserLimits);
  
  return beamPipeUserLimits;
}

void BDSBeamPipeFactoryLHCDetailed::PlaceComponents(G4String name)
{
  BDSBeamPipeFactoryBase::PlaceComponents(name);

  copperSkinPV = new G4PVPlacement((G4RotationMatrix*)nullptr,   // no rotation
				   G4ThreeVector(0,0,0),         // position
				   copperSkinLV,                 // lv to be placed
				   name + "_copper_skin_pv",     // name
				   containerLV,                  // mother lv to be place in
				   false,                        // no boolean operation
				   0,                            // copy number
				   checkOverlaps);               // whether to check overlaps
  
  screenPV = new G4PVPlacement((G4RotationMatrix*)nullptr,   // no rotation
			       (G4ThreeVector)0,             // position
			       screenLV,                     // lv to be placed
			       name + "_screen_pv",          // name
			       containerLV,                  // mother lv to be place in
			       false,                        // no boolean operation
			       0,                            // copy number
			       checkOverlaps);               // whether to check overlaps

  allPhysicalVolumes.push_back(copperSkinPV);
  allPhysicalVolumes.push_back(screenPV);
  
  if (buildCoolingPipe)
    {
      G4ThreeVector coolingPipeTopPosition;
      G4ThreeVector coolingPipeBottomPosition;
      if (!verticalOrientation)
	{ // horizontal shape -> vertical displacement for pipes
	  coolingPipeTopPosition    = G4ThreeVector(0,coolingPipeOffset,0);
	  coolingPipeBottomPosition = G4ThreeVector(0,-coolingPipeOffset,0);
	}
      else
	{ // vertical shape -> horizontal displacement for pipes
	  coolingPipeTopPosition    = G4ThreeVector(coolingPipeOffset,0,0);
	  coolingPipeBottomPosition = G4ThreeVector(-coolingPipeOffset,0,0);
	}
  
      coolingPipeTopPV = new G4PVPlacement((G4RotationMatrix*)nullptr,   // no rotation
					   coolingPipeTopPosition,       // position
					   coolingPipeLV,                // lv to be placed
					   name + "_cooling_pipe_top_pv",// name
					   containerLV,                  // mother lv to be place in
					   false,                        // no boolean operation
					   0,                            // copy number
					   checkOverlaps);               // whether to check overlaps

      coolingPipeBottomPV = new G4PVPlacement((G4RotationMatrix*)nullptr,   // no rotation
					      coolingPipeBottomPosition,    // position
					      coolingPipeLV,                // lv to be placed
					      name + "_cooling_pipe_bottom_pv", // name
					      containerLV,                  // mother lv to be place in
					      false,                        // no boolean operation
					      0,                            // copy number
					      checkOverlaps);               // whether to check overlaps

      allPhysicalVolumes.push_back(coolingPipeTopPV);
      allPhysicalVolumes.push_back(coolingPipeBottomPV);
    }
}
  
/// the angled ones have degeneracy in the geant4 solids they used so we can avoid code duplication
/// by grouping common construction tasks
G4double BDSBeamPipeFactoryLHCDetailed::CreateGeneralAngledSolids(G4String      name,
								  G4double      length,
								  G4ThreeVector inputface,
								  G4ThreeVector outputface)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  
  // build the solids
  //vacuum cylindrical solid (circular cross-section)
  G4VSolid* vacCylSolid = new G4CutTubs(name + "_vacuum_cylinder",   // name
					0,                           // inner radius
					vacRadius,                   // outer radius
					vacHalfLength,               // half length
					0,                           // rotation start angle
					CLHEP::twopi,                // rotation finish angle
					inputface,                   // input face normal
					outputface);                 // output face normal
  //vacuum box solid (rectangular cross-section)
  G4VSolid* vacRectSolid = new G4Box(name + "_vacuum_box", // name
				     vacBoxX,              // x half width
				     vacBoxY,              // y half width
				     length); // z full width (long for unambiguous intersection)
  //intersection of both of these gives the desired shape
  vacuumSolid = new G4IntersectionSolid(name + "_vacuum_solid", // name
					vacCylSolid,            // solid 1
					vacRectSolid);          // solid 2
  allSolids.push_back(vacCylSolid);
  allSolids.push_back(vacRectSolid);

  //copper skin layer to beamscreen
  //copper skin inner edge for subtraction (actually just like vacuum + lengthSafety)
  G4VSolid* cuInnerCylSolid = new G4CutTubs(name + "_cu_inner_cylinder",   // name
					    0,                             // inner radius
					    cuInnerRadius,                 // outer radius
					    1.5*length, // length big for unambiguous subtraction (but < outerlength)
					    0,                             // rotation start angle
					    CLHEP::twopi,                  // rotation finish angle
					    inputface,                     // input face normal
					    outputface);                   // output face normal
  //screen inner edge box solid (rectangular cross-section)
  G4VSolid* cuInnerRectSolid = new G4Box(name + "_cu_inner_box", // name
					 cuInnerBoxX,            // x half width
					 cuInnerBoxY,            // y half width
					 1.7*length);            // z long for unambiguous intersection
  //screen inner intersection - 1.5*length long which is > half length for unambiguous subtraction later
  G4VSolid* cuInnerSolid = new G4IntersectionSolid(name + "_cu_inner_solid", // name
						   cuInnerCylSolid,            // solid 1
						   cuInnerRectSolid);          // solid 2

  //screen outer edge for subtraction (actually just like vacuum + lengthSafety)x
  G4VSolid* cuOuterCylSolid = new G4CutTubs(name + "_cu_outer_cylinder",  // name
					    0,                            // inner radius (0 for unambiguous subtraction)
					    cuOuterRadius,                // outer radius
					    halfLength,                   // half length
					    0,                            // rotation start angle
					    CLHEP::twopi,                 // rotation finish angle
					    inputface,                    // input face normal
					    outputface);                  // output face normal
  //screen outer edge box solid (rectangular cross-section)
  G4VSolid* cuOuterRectSolid = new G4Box(name + "_cu_outer_box", // name
					 cuOuterBoxX,            // x half width
					 cuOuterBoxY,            // y half width
					 length); // z full width (long for unambiguous intersection)
  G4VSolid* cuOuterSolid = new G4IntersectionSolid(name + "_cu_outer_solid", // name
						   cuOuterCylSolid,          // solid 1
						   cuOuterRectSolid);        // solid 2
  copperSkinSolid = new G4SubtractionSolid(name + "_copper_skin_solid",// name
					   cuOuterSolid,               // this
					   cuInnerSolid);              // minus this
  allSolids.push_back(cuInnerCylSolid);
  allSolids.push_back(cuInnerRectSolid);
  allSolids.push_back(cuInnerSolid);
  allSolids.push_back(cuOuterCylSolid);
  allSolids.push_back(cuOuterRectSolid);
  allSolids.push_back(cuOuterSolid);
  allSolids.push_back(copperSkinSolid);
  
  //beampipe cylindrical solid (circular cross-section)
  //beampipe inner edge for subtraction (actually just like vacuum + lengthSafety)
  G4VSolid* screenInnerCylSolid = new G4CutTubs(name + "_screen_inner_cylinder", // name
						0,                               // inner radius
						bsInnerRadius,                   // outer radius
						1.5*length, // length big for unambiguous subtraction (but < outerlength)
						0,                               // rotation start angle
						CLHEP::twopi,                    // rotation finish angle
						inputface,                       // input face normal
						outputface);                     // output face normal
  //screen inner edge box solid (rectangular cross-section)
  G4VSolid* screenInnerRectSolid = new G4Box(name + "_screen_inner_box", // name
					     bsInnerBoxX,                // x half width
					     bsInnerBoxY,                // y half width
					     1.7*length); // z long for unambiguous intersection
  //screen inner intersection - 1.5*length long which is > half length for unambiguous subtraction later
  G4VSolid* screenInnerSolid = new G4IntersectionSolid(name + "_screen_inner_solid", // name
						       screenInnerCylSolid,          // solid 1
						       screenInnerRectSolid);        // solid 2

  //screen outer edge for subtraction (actually just like vacuum + lengthSafety)x
  G4VSolid* screenOuterCylSolid = new G4CutTubs(name + "_screen_outer_cylinder",// name
						0,       // inner radius (0 for unambiguous subtraction)
						bsOuterRadius,                  // outer radius
						halfLength,                     // half length
						0,                              // rotation start angle
						CLHEP::twopi,                   // rotation finish angle
						inputface,                      // input face normal
						outputface);                    // output face normal
  //screen outer edge box solid (rectangular cross-section)
  G4VSolid* screenOuterRectSolid = new G4Box(name + "_screen_outer_box", // name
					     bsOuterBoxX,                // x half width
					     bsOuterBoxY,                // y half width
					     length); // z full width (long for unambiguous intersection)
  G4VSolid* screenOuterSolid = new G4IntersectionSolid(name + "_pipe_outer_solid", // name
						       screenOuterCylSolid,        // solid 1
						       screenOuterRectSolid);      // solid 2
  
  screenSolid = new G4SubtractionSolid(name + "_screen_solid",// name
				       screenOuterSolid,      // this
				       screenInnerSolid);     // minus this

  allSolids.push_back(screenInnerCylSolid);
  allSolids.push_back(screenInnerRectSolid);
  allSolids.push_back(screenInnerSolid);
  allSolids.push_back(screenOuterCylSolid);
  allSolids.push_back(screenOuterRectSolid);
  allSolids.push_back(screenOuterSolid);
  allSolids.push_back(screenSolid);

  if (buildCoolingPipe)
    {
      coolingPipeSolid = new G4CutTubs(name + "_cooling_pipe_solid",             // name
				       coolingPipeRadius,                        // inner radius
				       coolingPipeRadius + coolingPipeThickness, // outer radius
				       halfLength,                               // half length
				       0,                                        // rotation start angle
				       CLHEP::twopi,                             // rotation finish angle
				       inputface,                                // input face normal
				       outputface);                              // output face normal
      
      allSolids.push_back(coolingPipeSolid);
    }
  
  // beampipe - ("coldbore") circular cross-section and sits outisde screen and cooling pipe
  beamPipeSolid = new G4CutTubs(name + "_beampipe_solid", // name
				cbInnerRadius,            // inner radius
				cbOuterRadius,            // outer radius
				halfLength,               // half length
				0,                        // rotation start angle
				CLHEP::twopi,             // rotation finish angle
				inputface,                // input face normal
				outputface);              // output face normal

  //container cylindrical solid (circular cross-section)
  containerSolid = new G4CutTubs(name + "_container_cylinder", // name
				 0,                            // inner radius
				 containerRadius,              // outer radius
				 length*0.5,                   // half length
				 0,                            // rotation start angle
				 CLHEP::twopi,                 // rotation finish angle
				 inputface,                    // input face normal
				 outputface);                  // output face normal

  //container cylindrical solid (circular cross-section)
  containerSubtractionSolid = new G4Tubs(name + "_subtraction_cylinder", // name
					 0,                              // inner radius
					 containerRadius + lengthSafety, // outer radius
					 2*length,                       // long length for unambiguous subtraction
					 0,                              // rotation start angle
					 CLHEP::twopi);                  // rotation finish angle

  // return the container radius as everything is calculated in this function
  return containerRadius;
}
