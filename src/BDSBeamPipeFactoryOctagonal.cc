#include "BDSBeamPipeFactoryOctagonal.hh"

#include "BDSDebug.hh"
#include "BDSBeamPipeFactoryPoints.hh"

#include "globals.hh"                 // geant4 globals / types
#include "G4TwoVector.hh"

#include <cmath>


BDSBeamPipeFactoryOctagonal* BDSBeamPipeFactoryOctagonal::_instance = nullptr;

BDSBeamPipeFactoryOctagonal* BDSBeamPipeFactoryOctagonal::Instance()
{
  if (_instance == nullptr)
    {_instance = new BDSBeamPipeFactoryOctagonal();}
  return _instance;
}

BDSBeamPipeFactoryOctagonal::BDSBeamPipeFactoryOctagonal()
{;}

BDSBeamPipeFactoryOctagonal::~BDSBeamPipeFactoryOctagonal()
{
  _instance = nullptr;
}

void BDSBeamPipeFactoryOctagonal::GenerateOctagonal(std::vector<G4TwoVector>& vec,
						    G4double x1,
						    G4double y1,
						    G4double x2,
						    G4double y2)
{
  AppendPoint(vec, x1,  y2 );
  AppendPoint(vec, x1,  -y2);
  AppendPoint(vec, x2,  -y1);
  AppendPoint(vec, -x2, -y1);
  AppendPoint(vec, -x1, -y2);
  AppendPoint(vec, -x1, y2 );
  AppendPoint(vec, -x2, y1 );
  AppendPoint(vec, x2,  y1 );
}						    

void BDSBeamPipeFactoryOctagonal::GeneratePoints(G4double aper1,
						 G4double aper2,
						 G4double aper3,
						 G4double aper4,
						 G4double beamPipeThickness,
						 G4int    /*pointsPerTwoPi*/)
{
  GenerateOctagonal(vacuumEdge, aper1, aper2, aper3, aper4);
  G4double bpInner1 = aper1 + lengthSafety;
  G4double bpInner2 = aper2 + lengthSafety;
  G4double bpInner3 = aper3 + lengthSafety;
  G4double bpInner4 = aper4 + lengthSafety;
  GenerateOctagonal(beamPipeInnerEdge, bpInner1, bpInner2, bpInner3, bpInner4);
  G4double bpOuter1 = aper1 + beamPipeThickness;
  G4double bpOuter2 = aper2 + beamPipeThickness;
  G4double bpOuter3 = aper3 + beamPipeThickness;
  G4double bpOuter4 = aper4 + beamPipeThickness;
  GenerateOctagonal(beamPipeOuterEdge, bpOuter1, bpOuter2, bpOuter3, bpOuter4);
  G4double cont1 = bpOuter1 + lengthSafetyLarge;
  G4double cont2 = bpOuter2 + lengthSafetyLarge;
  G4double cont3 = bpOuter3 + lengthSafetyLarge;
  G4double cont4 = bpOuter4 + lengthSafetyLarge;
  GenerateOctagonal(containerEdge, cont1, cont2, cont3, cont4);
  G4double contSub1 = cont1 + lengthSafetyLarge;
  G4double contSub2 = cont2 + lengthSafetyLarge;
  G4double contSub3 = cont3 + lengthSafetyLarge;
  G4double contSub4 = cont4 + lengthSafetyLarge;
  GenerateOctagonal(containerSubtractionEdge, contSub1, contSub2, contSub3, contSub4);
}

G4double BDSBeamPipeFactoryOctagonal::CalculateIntersectionRadius(G4double aper1,
								  G4double aper2,
								  G4double aper3,
								  G4double aper4,
								  G4double beamPipeThickness)
{
  // depending on the user supplied parameters, choose the largest radius from the origin,
  // and add the beam pipe thickness plus some margin
  G4double r1 = sqrt(pow(aper1,2) + pow(aper2,2));
  G4double r2 = sqrt(pow(aper3,2) + pow(aper4,2));
  G4double result = std::max(r1,r2) + beamPipeThickness;
  result *= 1.4;
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "intersection radius: " << result << G4endl;
#endif
  return result;
}
