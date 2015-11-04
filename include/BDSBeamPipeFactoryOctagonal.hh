#ifndef BDSBEAMPIPEFACTORYOCTAGONAL_H
#define BDSBEAMPIPEFACTORYOCTAGONAL_H

#include "BDSBeamPipeFactoryBase.hh"
#include "BDSBeamPipeFactoryPoints.hh"
#include "BDSBeamPipe.hh"

class G4Material;

/**
 * @brief Factory for octagonal aperture model beampipes.
 * 
 * This is a rectangular aperture with faceted flat corners. In the 
 * positive quadrant (+ve x & y) the user specifies (x,y) of the full
 * width in the horizontal and the full height in the vertical. A
 * second set of (x,y) coordinates specify the x and y points of the 
 * cut points. Therefore, the second x,y are always <  than the first ones.
 * This is reflected in all four quadrants. Practically, a G4ExtrudedSolid
 * is used where simply points are defined and this shape is extruded.
 *
 * aper1,2 are used to represent x1,y1 and aper3,4 are x2,y2 respectively.
 * 
 * Singleton pattern.
 * 
 * @author Laurie Nevay <laurie.nevay@rhul.ac.uk>
 */

class BDSBeamPipeFactoryOctagonal: public BDSBeamPipeFactoryPoints
{
public:
  static BDSBeamPipeFactoryOctagonal* Instance(); ///< singleton accessor
  
  virtual ~BDSBeamPipeFactoryOctagonal();
  
private:
  BDSBeamPipeFactoryOctagonal(); ///< private default constructor - singleton pattern
  static BDSBeamPipeFactoryOctagonal* _instance;

  /// Generate quarters of a circle to represent the edges joined by straight lines.
  /// Overloaded (required) from BDSBeamPipeFactoryPoints
  virtual void GeneratePoints(G4double aper1,
			      G4double aper2,
			      G4double aper3,
			      G4double aper4,
			      G4double beamPipeThickness,
			      G4int    pointsPerTwoPi = 40);

  /// Calculate the radius of the solid used for intersection for angled faces.
  virtual G4double CalculateIntersectionRadius(G4double aper1,
					       G4double aper2,
					       G4double aper3,
					       G4double aper4,
					       G4double beamPipeThickness);

  void GenerateOctagonal(std::vector<G4TwoVector>& vec,
			 G4double x1,
			 G4double y1,
			 G4double x2,
			 G4double y2);
};
  
#endif
