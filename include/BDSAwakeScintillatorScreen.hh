/* BDSIM code.   
A scintillator screen.
Work in progress.  
*/

#ifndef BDSAwakeScintillatorScreen_h
#define BDSAwakeScintillatorScreen_h 

#include "globals.hh"
#include "BDSAcceleratorComponent.hh"
#include "BDSAwakeMultilayerScreen.hh"
#include "BDSCCDCamera.hh"

#include "G4LogicalVolume.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4VSolid.hh"

class BDSAwakeScintillatorScreen :public BDSAcceleratorComponent
{
public:
  BDSAwakeScintillatorScreen(G4String aName,
			     G4String material,
			     G4double thickness,
			     G4double angle,
			     G4double windowThickness,
			     G4String windowMaterial);
  virtual ~BDSAwakeScintillatorScreen();

protected:

private:
  virtual void Build();
  void BuildCamera();
  void PlaceCamera();
  void BuildScreen();
  void PlaceScreen();
  void BuildAwakeScintillatorScreenTunnel();
  void BuildVacuumChamber1();
  void BuildVacuumChamber2();
  virtual void SetVisAttributes();
  void ComputeDimensions();
  virtual void BuildContainerLogicalVolume();
  void BuildCameraScoringPlane();
  void BuildScreenScoringPlane();
  void BuildAwakeScintillatorMaterial();
  void BuildAwakeScintillatorCompound();
  void BuildAwakeScintillatorOpticalProperties();
  void BuildFrontLayer();
  void BuildAwakeScintillatorLayer();
  void BuildBaseLayer();
  void BuildBackLayer();
  void BuildOpticalSurfaces();
  

  // Geometrical objects:
  G4VPhysicalVolume* itsCameraScoringPlanePhys;
  G4VPhysicalVolume* itsScreenScoringPlanePhys;
  G4LogicalVolume* itsCameraScoringPlaneLog;
  G4LogicalVolume* itsCameraScoringPlaneLog2;
  G4LogicalVolume* itsCameraScoringPlaneLog3;
  G4LogicalVolume* itsCameraScoringPlaneLog4;
  G4LogicalVolume* itsCameraScoringPlaneLog5;
  G4LogicalVolume* itsCameraScoringPlaneLog6;
  G4LogicalVolume* itsScreenScoringPlaneLog;
  G4LogicalVolume* itsScreenScoringPlaneLog2;
  G4VSolid* itsCameraScoringPlaneSolid;
  G4VSolid* itsScreenScoringPlaneSolid;
                    
  G4double itsOuterR;
  G4double itsXLength;
  G4double itsYLength;

  G4RotationMatrix* _screenRotationMatrix;
  G4RotationMatrix* _vacRotationMatrix;

  //scoring plane
  G4double _totalThickness;
  G4double _screenThickness;
  G4double _screenHeight;
  G4double _screenWidth;
  G4double _scoringPlaneThickness;

  //Vacuum chamber dimensions
  G4int _vacChambType;
  G4double _vacWindowHeight;
  G4double _vacMylarThickness;
  G4double _vacKevlarThickness;
  G4double _vacThickness;
  G4double _vacInnerHeight;
  G4double _vacInnerWidth;
  G4double _vacHeight;
  G4double _vacLength;

  G4double _vacWidth1;
  G4double _vacDispX1;
  G4double _vacDispY1;
  G4double _vacDispZ1;

  G4double _vacWidth2;
  G4double _vacDispX2;
  G4double _vacDispY2;
  G4double _vacDispZ2;

  G4VisAttributes* _visAttFront;
  G4VisAttributes* _visAttScint;
  G4VisAttributes* _visAttBase;
  G4VisAttributes* _visAttSampler;

  G4String _scoringPlaneName;
  G4String _screenScoringPlaneName;
  G4String _screenSamplerName;
  G4String _screenSamplerName2;
  G4String _samplerName;
  G4String _samplerName2;
  G4String _samplerName3;
  G4String _samplerName4;
  G4String _samplerName5;
  G4String _samplerName6;
  BDSAwakeMultilayerScreen* _mlScreen;
  BDSCCDCamera* _camera;
  G4double _cameraScreenDist;
  G4String _material;
  G4double _thickness;
  G4double _screenAngle;
  G4double _windowThickness;
  G4String _windowMaterial;
};

#endif
