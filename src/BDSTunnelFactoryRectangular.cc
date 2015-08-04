#include "BDSTunnelFactoryBase.hh"
#include "BDSTunnelFactoryRectangular.hh"

#include "BDSDebug.hh"
#include "BDSTunnelInfo.hh"
#include "BDSGlobalConstants.hh"

#include "globals.hh"                 // geant4 globals / types
#include "G4Box.hh"
#include "G4CutTubs.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4SubtractionSolid.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4VSolid.hh"

#include <cmath>                           // sin, cos, fabs
#include <utility>                         // for std::pair


BDSTunnelFactoryRectangular* BDSTunnelFactoryRectangular::_instance = 0;

BDSTunnelFactoryRectangular* BDSTunnelFactoryRectangular::Instance()
{
  if (_instance == 0)
    {_instance = new BDSTunnelFactoryRectangular();}
  return _instance;
}

BDSTunnelFactoryRectangular::BDSTunnelFactoryRectangular()
{;}

BDSTunnelFactoryRectangular::~BDSTunnelFactoryRectangular()
{
  _instance = 0;
}

BDSTunnelSection* BDSTunnelFactoryRectangular::CreateTunnelSection(G4String      name,
								   G4double      length,
								   G4double      tunnelThickness,
								   G4double      tunnelSoilThickness,
								   G4Material*   tunnelMaterial,
								   G4Material*   tunnelSoilMaterial,
								   G4bool        tunnelFloor,
								   G4double      tunnelFloorOffset,
								   G4double      tunnel1,
								   G4double      tunnel2,
								   G4bool        visible)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  // tidy up things from previous usage if any - base class method
  TidyUp();
  
  // test input parameters - set global options as default if not specified
  TestInputParameters(length, tunnelThickness, tunnelSoilThickness, tunnelMaterial,
		      tunnelSoilMaterial, tunnelFloorOffset, tunnel1, tunnel2);

  // build the solids
  G4VSolid* tunnelOuterSolid = new G4Box(name + "_tunnel_outer_solid", // name
					 tunnel1 + tunnelThickness,    // x radius
					 tunnel2 + tunnelThickness,    // y radius
					 0.5*length - lengthSafety);   // z half length (to fit in container)
  
  G4VSolid* tunnelInnerSolid = new G4Box(name + "_tunnel_outer_solid", // name
					 tunnel1 + lengthSafety,       // x radius
					 tunnel2 + lengthSafety,       // y radius
					 length); // z half length - long for unambiguous subtraction

  // register solids
  solidsToBeRegistered.push_back(tunnelOuterSolid);
  solidsToBeRegistered.push_back(tunnelInnerSolid);

  tunnelSolid = new G4SubtractionSolid(name + "_tunnel_solid", // name
				       tunnelOuterSolid,      // this
				       tunnelInnerSolid);     // minus this


  G4double soilInnerX = tunnel1 + tunnelThickness + lengthSafety;
  G4double soilInnerY = tunnel2 + tunnelThickness + lengthSafety;

  G4double soilOuterX = soilInnerX + tunnelSoilThickness;
  G4double soilOuterY = soilInnerY + tunnelSoilThickness;
  
  G4double containerX = soilOuterX + lengthSafety;
  G4double containerY = soilOuterY + lengthSafety;

  G4VSolid* soilOuterSolid = new G4Box(name + "_soild_outer_solid", // name
				       soilOuterX,                  // x half width
				       soilOuterY,                  // y half width
				       0.5*length);                 // z half width
  
  G4VSolid* soilInnerSolid = new G4Box(name + "_soil_outer_solid",  // name
				       soilInnerX,                  // x radius
				       soilInnerY,                  // y radius
				       length); // z half length - long for unambiguous subtraction

  // register solids
  solidsToBeRegistered.push_back(soilOuterSolid);
  solidsToBeRegistered.push_back(soilInnerSolid);

  soilSolid = new G4SubtractionSolid(name + "_soil_solid", // name
				     soilOuterSolid,       // this
				     soilInnerSolid);      // minus this

  // container solid depends on whether the floor is there or not, but can prepare the outer part for subtraction
  G4VSolid* containerSolidOuter = new G4Box(name + "_container_outer_solid", // name
					    containerX,                      // x half width
					    containerY,                      // y half width
					    length*0.5);                     // z half width
  G4ThreeVector contInsideDisplacement;
  G4VSolid*     containerSolidInner = nullptr;
  
  // build the floor if necessary
  if (tunnelFloor)
    {
      G4double floorThickness = tunnel2 - tunnelFloorOffset - lengthSafety;

      // placement vector for floor - assinging default 0,0,0 in base class
      floorDisplacement = G4ThreeVector(0, -(tunnelFloorOffset + floorThickness*0.5), 0);
      floorSolid = new G4Box(name + "_floor_solid",      // name
			     tunnel1,                    // x half width
			     floorThickness*0.5,         // y half width
			     0.5*length - lengthSafety); // z half width
      
      G4double tunnelContInnerYRadius = tunnel2 - 0.5*floorThickness;
      
      containerSolidInner = new G4Box(name + "_tunnel_cont_solid_inner", // name
				      tunnel1,                           // x radius
				      tunnelContInnerYRadius,            // y radius
				      length*0.5);

      // offset the centre cut out by the difference between the vertical half widths of tunnel2 and tunnel2+floor
      contInsideDisplacement = G4ThreeVector(0, tunnel2-floorThickness, 0); 
    }
  else
    {
      containerSolidInner = new G4Box(name + "_tunnel_cont_solid_inner", // name
				      tunnel1,                           // x radius
				      tunnel2,                           // y radius
				      length); // long z for unambiguous subtraction
      contInsideDisplacement = G4ThreeVector(0,0,0);
    }
  
  containerSolid = new G4SubtractionSolid(name + "_tunnel_cont_solid", // name
					  containerSolidOuter,         // this
					  containerSolidInner,         // minus this
					  0,                           // rotate by this
					  contInsideDisplacement);

  G4double radius = std::max(containerX, containerY);
  BuildReadOutVolumeStraight(name, length, radius);
  
  CommonConstruction(name, tunnelMaterial, tunnelSoilMaterial, length, containerX, containerY, visible);

  return tunnelSection;
}


BDSTunnelSection* BDSTunnelFactoryRectangular::CreateTunnelSectionAngled(G4String      name,
									 G4double      length,
									 G4ThreeVector inputFace,
									 G4ThreeVector outputFace,
									 G4double      tunnelThickness,
									 G4double      tunnelSoilThickness,
									 G4Material*   tunnelMaterial,
									 G4Material*   tunnelSoilMaterial,
									 G4bool        tunnelFloor,
									 G4double      tunnelFloorOffset,
									 G4double      tunnel1,
									 G4double      tunnel2,
									 G4bool        visible)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  // tidy up things from previous usage if any - base class method
  TidyUp();
  
  // test input parameters - set global options as default if not specified
  TestInputParameters(length, tunnelThickness, tunnelSoilThickness, tunnelMaterial,
		      tunnelSoilMaterial, tunnelFloorOffset, tunnel1, tunnel2);
  
  // build the solids
  // create an intersection cut tubs to get the faces - make it bigger than everything else
  // then make elliptical solids longer than they need to be
  G4double intersectionRadius = ( std::max(tunnel1,tunnel2) + tunnelThickness + tunnelSoilThickness ) * 3;
  G4VSolid* faceSolid = new G4CutTubs(name + "_face_intersection_solid", // name
				      0,                                 // inner radius
				      intersectionRadius,                // outer radius
				      length*0.5 - lengthSafety,         // z half length
				      0,                                 // start angle
				      CLHEP::twopi,                      // sweep angle
				      inputFace,                         // input face normal vector
				      outputFace);                       // output face normal vector


  // tunnel
  G4VSolid* tunnelOuterSolid = new G4Box(name + "_tunnel_outer_solid", // name
					 tunnel1 + tunnelThickness,    // x radius
					 tunnel2 + tunnelThickness,    // y radius
					 length);                      // z half length
  
  G4VSolid* tunnelInnerSolid = new G4Box(name + "_tunnel_outer_solid", // name
					 tunnel1 + lengthSafety,       // x radius
					 tunnel2 + lengthSafety,       // y radius
					 length*1.5); // z half length - long for unambiguous subtraction

  G4VSolid* tunnelSolidUnAngled = new G4SubtractionSolid(name + "_tunnel_square_solid", // name
							 tunnelOuterSolid,      // this
							 tunnelInnerSolid);     // minus this

  // register solids
  solidsToBeRegistered.push_back(faceSolid);
  solidsToBeRegistered.push_back(tunnelOuterSolid);
  solidsToBeRegistered.push_back(tunnelInnerSolid);
  solidsToBeRegistered.push_back(tunnelSolidUnAngled);

  // cut off the faces with the angled face solid
  tunnelSolid = new G4IntersectionSolid(name + "_tunnel_solid", // name
					tunnelSolidUnAngled,
					faceSolid);

  // soil solid
  G4double soilInnerX = tunnel1 + tunnelThickness + lengthSafety;
  G4double soilInnerY = tunnel2 + tunnelThickness + lengthSafety;

  G4double soilOuterX = soilInnerX + tunnelSoilThickness;
  G4double soilOuterY = soilInnerY + tunnelSoilThickness;
  
  G4double containerX = soilOuterX + lengthSafety;
  G4double containerY = soilOuterY + lengthSafety;
  
  G4VSolid* soilOuterSolid = new G4Box(name + "_soil_outer_solid", // name
				       soilOuterX,                 // x half width
				       soilOuterY,                 // y half width
				       length);                    // z half length
  
  G4VSolid* soilInnerSolid = new G4Box(name + "_soil_inner_solid", // name
				       soilInnerX,                 // x radius
				       soilInnerY,                 // y radius
				       1.5*length); // z half length - long for unambiguous subtraction

  // cut out inside of big box of soil to get rectangular tube - purposively long for upcoming intersection
  G4VSolid* soilSolidUnAngled = new G4SubtractionSolid(name + "_soil_square_solid", // name
						       soilOuterSolid,              // this
						       soilInnerSolid);             // minus this

  // register solids
  solidsToBeRegistered.push_back(soilOuterSolid);
  solidsToBeRegistered.push_back(soilInnerSolid);
  solidsToBeRegistered.push_back(soilSolidUnAngled);

  // make it angled
  soilSolid = new G4IntersectionSolid(name + "_soil_soild", // name
				      soilSolidUnAngled,
				      faceSolid);


  // container solid depends on whether the floor is there or not, but can prepare the outer part for subtraction
  G4VSolid* containerSolidOuter = new G4Box(name + "_container_outer_solid", // name
					    containerX,                      // x half width
					    containerY,                      // y half width
					    length*0.5);                     // z half width
  G4ThreeVector contInsideDisplacement;
  G4VSolid*     containerSolidInner = nullptr;

  solidsToBeRegistered.push_back(containerSolidOuter);
  
  // build the floor if necessary
  if (tunnelFloor)
    {
      G4double floorThickness = tunnel2 - tunnelFloorOffset - lengthSafety;

      // placement vector for floor - assinging default 0,0,0 in base class
      floorDisplacement = G4ThreeVector(0, -(tunnelFloorOffset + floorThickness*0.5), 0);

      G4VSolid* floorSolidSquare = new G4Box(name + "_floor_box_solid",  // name
					     tunnel1,                    // x half width
					     floorThickness*0.5,         // y half width
					     length);                    // z half width
      
      floorSolid = new G4IntersectionSolid(name + "_floor_solid", // name
					   floorSolidSquare,
					   faceSolid);

      solidsToBeRegistered.push_back(floorSolidSquare);
      
      // need to create a container for the tunnel + floor that only just contains it
      G4double tunnelContInnerYRadius = ( tunnelFloorOffset + tunnel2 ) * 0.5;
      containerSolidInner = new G4Box(name + "_tunnel_cont_solid_inner", // name
				      tunnel1,                           // x radius
				      tunnelContInnerYRadius,            // y radius
				      length);
      
      // offset the centre cut out by the difference between the vertical half widths of tunnel2 and tunnel2+floor
      contInsideDisplacement = G4ThreeVector(0, tunnelContInnerYRadius - tunnel2, 0); 
    }
  else
    {      
      containerSolidInner = new G4Box(name + "_tunnel_cont_solid_inner", // name
				      tunnel1,                           // x radius
				      tunnel2,                           // y radius
				      length); // z half length - long for unambiguous subtraction
      contInsideDisplacement = G4ThreeVector(0,0,0);
    }

  containerSolid = new G4SubtractionSolid(name + "_container_solid", // name
					  containerSolidOuter,       // this
					  containerSolidInner,       // minus this
					  0,                         // rotate by this
					  contInsideDisplacement);

  G4double radius = std::max(containerX, containerY);
  BuildReadOutVolumeAngled(name, length, radius, inputFace, outputFace);
  
  CommonConstruction(name, tunnelMaterial, tunnelSoilMaterial, length, containerX, containerY, visible);

  return tunnelSection;
}

/// functions below here are private to this particular factory
void BDSTunnelFactoryRectangular::TestInputParameters(G4double&    length,
						      G4double&    tunnelThickness,
						      G4double&    tunnelSoilThickness,
						      G4Material*& tunnelMaterial,
						      G4Material*& tunnelSoilMaterial,
						      G4double&    tunnelFloorOffset,
						      G4double&    tunnel1,
						      G4double&    tunnel2)
{
  CommontTestInputParameters(length, tunnelThickness, tunnelSoilThickness, tunnelMaterial, tunnelSoilMaterial);
  
  if (tunnelFloorOffset < 1e-10)
    {tunnelFloorOffset = defaultModel->floorOffset;}
  
  if (tunnel1 < 1e-10)
    {tunnel1 = defaultModel->aper1;}

  if (tunnel2 < 1e-10)
    {tunnel2 = defaultModel->aper2;}
}
