#include "BDSBeamPipeFactoryPoints.hh"
#include "BDSBeamPipe.hh"

#include "BDSDebug.hh"

#include "globals.hh"                 // geant4 globals / types
#include "G4CutTubs.hh"
#include "G4ExtrudedSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4Material.hh"
#include "G4SubtractionSolid.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VSolid.hh"

#include <cmath>                           // sin, cos, fabs
#include <utility>                         // for std::pair

BDSBeamPipeFactoryPoints::BDSBeamPipeFactoryPoints()
{
  CleanUp();
}

BDSBeamPipeFactoryPoints::~BDSBeamPipeFactoryPoints()
{;}

void BDSBeamPipeFactoryPoints::CleanUp()
{
  intersectionRadius = 0;
  extentX            = 0;
  extentY            = 0;
  
  vacuumEdge.clear();
  beamPipeInnerEdge.clear();
  beamPipeOuterEdge.clear();
  containerEdge.clear();
  containerSubtractionEdge.clear();

  beamPipeInnerSolid = nullptr;
  beamPipeOuterSolid = nullptr;

  BDSBeamPipeFactoryBase::CleanUp();
}

void BDSBeamPipeFactoryPoints::AppendPoint(std::vector<G4TwoVector>& vec,
					   G4double x,
					   G4double y)
{
  vec.push_back(G4TwoVector(x,y));
}

void BDSBeamPipeFactoryPoints::AppendAngle(std::vector<G4TwoVector>& vec,
					   G4double startAngle,
					   G4double finishAngle,
					   G4double radius,
					   G4int    nPoints,
					   G4double xOffset,
					   G4double yOffset)
{
  G4double diff = finishAngle - startAngle;
  G4double delta = diff / (G4double)nPoints;
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "start angle:  " << startAngle  << G4endl;
  G4cout << __METHOD_NAME__ << "finish angle: " << finishAngle << G4endl;
  G4cout << __METHOD_NAME__ << "# of points:  " << nPoints     << G4endl;
  G4cout << __METHOD_NAME__ << "diff angle:   " << diff        << G4endl;
  G4cout << __METHOD_NAME__ << "delta angle:  " << delta       << G4endl;
#endif
  for (G4double ang = startAngle; ang < finishAngle; ang += delta)
    { // l for local
      G4double xl = xOffset + radius*sin(ang);
      G4double yl = yOffset + radius*cos(ang);
      AppendPoint(vec, xl, yl);
    }
}

void BDSBeamPipeFactoryPoints::CreateSolids(G4String name,
					    G4double length,
					    G4bool   buildLongForIntersection)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  /// Make the solids all longer for intersection
  G4double zHalfLength = 0.5*length;
  if (buildLongForIntersection)
    {zHalfLength *= 1.5;}
  
  G4TwoVector zOffsets(0,0); // the transverse offset of each plane from 0,0
  G4double zScale = 1; // the scale at each end of the points = 1
  vacuumSolid = new G4ExtrudedSolid(name + "_vacuum_solid", // name
				    vacuumEdge,             // vector of TwoVector points
				    zHalfLength,            // half length for +- planes
				    zOffsets, zScale,       // dx,dy offset for each face, scaling
				    zOffsets, zScale);      // dx,dy offset for each face, scaling

  beamPipeInnerSolid = new G4ExtrudedSolid(name + "_bp_inner_solid",
					   beamPipeInnerEdge,
					   zHalfLength * 1.5,
					   zOffsets, zScale,
					   zOffsets, zScale);
  
  beamPipeOuterSolid = new G4ExtrudedSolid(name + "_bp_outer_solid",
					   beamPipeOuterEdge,
					   zHalfLength,
					   zOffsets, zScale,
					   zOffsets, zScale);

  allSolids.push_back(beamPipeInnerSolid);
  allSolids.push_back(beamPipeOuterSolid);
  
  beamPipeSolid = new G4SubtractionSolid(name + "_pipe_solid", // name
					 beamPipeOuterSolid,   // this
					 beamPipeInnerSolid);  // minus this

  containerSolid = new G4ExtrudedSolid(name + "_container_solid",
				       containerEdge,
				       zHalfLength,
				       zOffsets, zScale,
				       zOffsets, zScale);

  containerSubtractionSolid = new G4ExtrudedSolid(name + "_container_subtraction_solid",
						  containerSubtractionEdge,
						  zHalfLength*1.5,
						  zOffsets, zScale,
						  zOffsets, zScale);
}

void BDSBeamPipeFactoryPoints::CreateSolidsAngled(G4String      name,
						  G4double      length,
						  G4ThreeVector inputFace,
						  G4ThreeVector outputFace)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  
  // create straight solids that are a bit long
  CreateSolids(name + "_straight", length, true);

  // now intersect them with one G4CutTubs to get the angled faces
  G4double zHalfLength          = length*0.5 - lengthSafety;
  G4double zHalfLengthContainer = length*0.5;
  
  G4VSolid* faceSolid = new G4CutTubs(name + "_face_solid", // name
				      0,                    // inner radius
				      intersectionRadius,   // outer radius
				      zHalfLength,          // z half length
				      0,                    // start angle
				      CLHEP::twopi,         // sweep angle
				      inputFace,            // input face normal
				      outputFace);          // output face normal

  G4VSolid* faceSolidContainer = new G4CutTubs(name + "_cont_face_solid", // name
					       0,                         // inner radius
					       intersectionRadius,        // outer radius
					       zHalfLengthContainer,      // z half length
					       0,                         // start angle
					       CLHEP::twopi,              // sweep angle
					       inputFace,                 // input face normal
					       outputFace);               // output face normal

  allSolids.push_back(faceSolid);
  allSolids.push_back(faceSolidContainer);

  // copy pointers to do intersection with then reassign member pointer
  // to point to new solid
  G4VSolid* vacuumTemp = vacuumSolid;
  vacuumSolid = new G4IntersectionSolid(name + "_vacuum_solid",
					vacuumTemp,
					faceSolid);

  G4VSolid* beamPipeTemp = beamPipeSolid;
  beamPipeSolid = new G4IntersectionSolid(name + "_pipe_solid",
					  beamPipeTemp,
					  faceSolid);

  G4VSolid* containerTemp = containerSolid;
  containerSolid = new G4IntersectionSolid(name + "_container_solid",
					   containerTemp,
					   faceSolidContainer);

  // container subtraction solid can just be long with flat edges as
  // only used transversely
}

BDSBeamPipe* BDSBeamPipeFactoryPoints::CreateBeamPipe(G4String    nameIn,              // name
						      G4double    lengthIn,            // length [mm]
						      G4double    aper1In,             // aperture parameter 1
						      G4double    aper2In,             // aperture parameter 2
						      G4double    aper3In,             // aperture parameter 3
						      G4double    aper4In,             // aperture parameter 4
						      G4Material* vacuumMaterialIn,    // vacuum material
						      G4double    beamPipeThicknessIn, // beampipe thickness [mm]
						      G4Material* beamPipeMaterialIn)  // beampipe material
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  // clean up after last usage
  CleanUp();
  
  // generate extruded solid edges - provided by derived class
  GeneratePoints(aper1In, aper2In, aper3In, aper4In, beamPipeThicknessIn);

  // calculate and set the intersection solid radius
  intersectionRadius = CalculateIntersectionRadius(aper1In, aper2In, aper3In, aper4In, beamPipeThicknessIn);

  // create solids based on the member vectors of points
  CreateSolids(nameIn, lengthIn);
					
  return CommonFinalConstruction(nameIn, vacuumMaterialIn, beamPipeMaterialIn, lengthIn);
}

BDSBeamPipe* BDSBeamPipeFactoryPoints::CreateBeamPipeAngledInOut(G4String    nameIn,              // name
								 G4double    lengthIn,            // length [mm]
								 G4double    angleInIn,           // the normal angle of the input face
								 G4double    angleOutIn,          // the normal angle of the input face
								 G4double    aper1In,             // aperture parameter 1
								 G4double    aper2In,             // aperture parameter 2
								 G4double    aper3In,             // aperture parameter 3
								 G4double    aper4In,             // aperture parameter 4
								 G4Material* vacuumMaterialIn,    // vacuum material
								 G4double    beamPipeThicknessIn, // beampipe thickness [mm]
								 G4Material* beamPipeMaterialIn)  // beampipe material
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  // clean up after last usage
  CleanUp();
  
  // generate extruded solid edges - provided by derived class
  GeneratePoints(aper1In, aper2In, aper3In, aper4In, beamPipeThicknessIn);
  
  std::pair<G4ThreeVector,G4ThreeVector> faces = CalculateFaces(angleInIn, angleOutIn);
  G4ThreeVector inputface  = faces.first;
  G4ThreeVector outputface = faces.second;

  // calculate and set the intersection solid radius
  intersectionRadius = CalculateIntersectionRadius(aper1In, aper2In, aper3In, aper4In, beamPipeThicknessIn);

  // create solids based on the member vectors of points
  CreateSolidsAngled(nameIn, lengthIn, inputface, outputface);
  
  return CommonFinalConstruction(nameIn, vacuumMaterialIn, beamPipeMaterialIn, lengthIn);
}

BDSBeamPipe* BDSBeamPipeFactoryPoints::CommonFinalConstruction(G4String    nameIn,
							       G4Material* vacuumMaterialIn,
							       G4Material* beamPipeMaterialIn,
							       G4double    lengthIn)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif

  BDSBeamPipeFactoryBase::CommonConstruction(nameIn,
					     vacuumMaterialIn,
					     beamPipeMaterialIn,
					     lengthIn);

  // record extents
  std::pair<double,double> extX = std::make_pair(-extentX, extentX);
  std::pair<double,double> extY = std::make_pair(-extentY, extentY);
  std::pair<double,double> extZ = std::make_pair(-lengthIn*0.5, lengthIn*0.5);
  // calculate radius if a tube were to be place around it
  G4double containerRadius = std::max(extentX, extentY);
  
  BDSBeamPipe* aPipe = BuildBeamPipeAndRegisterVolumes(extX,extY,extZ,containerRadius);
  
  return aPipe;
}
