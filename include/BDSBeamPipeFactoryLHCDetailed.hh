#ifndef BDSBEAMPIPEFACTORYLHCDETAILED_H
#define BDSBEAMPIPEFACTORYLHCDETAILED_H

#include "BDSBeamPipeFactoryBase.hh"
#include "BDSBeamPipe.hh"

/**
 * @brief Factory for detailed lhc aperture model beam pipes
 * 
 * singleton pattern
 * 
 * @author Laurie Nevay <laurie.nevay@rhul.ac.uk>
 */

class BDSBeamPipeFactoryLHCDetailed: public BDSBeamPipeFactoryBase
{
public:
  static BDSBeamPipeFactoryLHCDetailed* Instance(); ///< singleton accessor
  
  virtual ~BDSBeamPipeFactoryLHCDetailed();

  /// Access cooling pipe information from factory for parameter tests
  G4double GetFullWidthOfCoolingPipe();

  /// Clean up extra pointers particular to this factory before use
  virtual void CleanUp();

  virtual BDSBeamPipe* CreateBeamPipe(G4String    nameIn,                     // name
				      G4double    lengthIn,                   // length [mm]
				      G4double    aper1 = 0,                  // aperture parameter 1
				      G4double    aper2 = 0,                  // aperture parameter 2
				      G4double    aper3 = 0,                  // aperture parameter 3
				      G4double    aper4 = 0,                  // aperture parameter 4
				      G4Material* vacuumMaterialIn = nullptr,    // vacuum material
				      G4double    beamPipeThicknessIn = 0,    // beampipe thickness [mm]
				      G4Material* beamPipeMaterialIn = nullptr   // beampipe material
				      );
  
  virtual BDSBeamPipe* CreateBeamPipeAngledInOut(G4String    nameIn,
						 G4double    lengthIn,
						 G4double    angleInIn,  // the normal angle of the input face
						 G4double    angleOutIn, // the normal angle of the output face
						 G4double    aper1 = 0,
						 G4double    aper2 = 0,
						 G4double    aper3 = 0,
						 G4double    aper4 = 0,
						 G4Material* vacuumMaterialIn = nullptr,
						 G4double    beamPipeThicknessIn = 0,
						 G4Material* beamPipeMaterialIn = nullptr
						 );

private:
  BDSBeamPipeFactoryLHCDetailed(); ///< private default constructor - singleton pattern
  static BDSBeamPipeFactoryLHCDetailed* _instance;

  //abstract common build features to one function
  //use member variables unique to this factory to pass them around

  /// only the solids are unique, once we have those, the logical volumes and placement in the
  /// container are the same.  group all this functionality together
  BDSBeamPipe* CommonFinalConstruction(G4String    name,
				       G4Material* vacuumMaterial,
				       G4Material* beamPipeMaterial,
				       G4double    length,
				       G4double    containerRadius);
  G4double CreateGeneralAngledSolids(G4String      name,
				     G4double      length,
				     G4ThreeVector inputface,
				     G4ThreeVector outputface);

  virtual void          BuildLogicalVolumes(G4String    nameIn,
					    G4Material* vacuumMaterialIn,
					    G4Material* beamPipeMaterialIn);
  virtual void          SetVisAttributes();
  virtual G4UserLimits* SetUserLimits(G4double lengthIn);
  virtual void          PlaceComponents(G4String nameIn);

  /// Utility function to initialise the geometry parameters
  void InitialiseGeometricalParameters();

  /// Calculate the various radii and geometrical parameters for this design
  /// based on the input aperture parameters
  void CalculateGeometricalParameters(G4double aper1,
				      G4double aper2,
				      G4double aper3,
				      G4double beamPipeThickness,
				      G4double length);

  G4VSolid*        copperSkinSolid;
  G4VSolid*        screenSolid;
  G4VSolid*        coolingPipeSolid;
  G4LogicalVolume* copperSkinLV;
  G4LogicalVolume* screenLV;
  G4LogicalVolume* coolingPipeLV;
  G4PVPlacement*   copperSkinPV;
  G4PVPlacement*   screenPV;
  G4PVPlacement*   coolingPipeTopPV;
  G4PVPlacement*   coolingPipeBottomPV;

  /// Parameters that control the design
  G4double coldBoreThickness;
  G4double coolingPipeThickness;
  G4double coolingPipeRadius;
  G4double copperSkinThickness;

  /// Calculated parameters below here
  /// vacuum volume
  G4double vacRadius, vacBoxX, vacBoxY;
  
  /// Copper skin geometrical parameters
  G4double cuInnerRadius, cuInnerBoxX, cuInnerBoxY;
  G4double cuOuterRadius, cuOuterBoxX, cuOuterBoxY;

  /// Beam screen geometrical parameters
  G4double bsInnerRadius, bsInnerBoxX, bsInnerBoxY;
  G4double bsOuterRadius, bsOuterBoxX, bsOuterBoxY;
  
  /// Cold bore geometrical parameters
  G4double cbInnerRadius, cbOuterRadius;

  /// Container geometrical parameters
  G4double containerRadius;
  
  /// General length variable (to avoid mistakes)
  G4double vacHalfLength;
  G4double halfLength;

  /// Cooling pipe geometrical parameters
  G4double coolingPipeOffset;

  /// Whether given the aperture parameters the pipe is square on the sides and round at the top
  /// - the 'vertical'.
  G4bool verticalOrientation;

  /// Whether to build the cooling pipes on either side
  G4bool buildCoolingPipe;
  
};
  
#endif
