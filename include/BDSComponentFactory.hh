#ifndef __BDSCOMPONENTFACTORY_
#define __BDSCOMPONENTFACTORY_

#include <list>
#include "globals.hh"
#include "parser/element.h"
#include "BDSAcceleratorComponent.hh"
#include "BDSBeamPipe.hh"
#include "BDSBeamPipeInfo.hh"
#include "BDSMagnetOuterInfo.hh"
#include "BDSTunnelInfo.hh"

class ElementList; 

class BDSComponentFactory{
public:
  BDSComponentFactory();
  ~BDSComponentFactory();
  
  BDSAcceleratorComponent* createComponent(std::list<struct Element>::iterator elementIter, ElementList& beamline_list);
  BDSAcceleratorComponent* createComponent(Element& aElement, Element& previousElement, Element& nextElement);
  BDSAcceleratorComponent* createComponent();

  // for each of them - special cases need only for ring logic
  BDSAcceleratorComponent* createTerminator();
  BDSAcceleratorComponent* createTeleporter();
 
private:
  G4bool   verbose;

  G4double lengthSafety;
  
  G4double _charge, _momentum, _brho;
  
  std::list<struct Element>::iterator _elementIter, _previousElementIter, _nextElementIter;
  /// beamline
  std::list<BDSAcceleratorComponent*> itsBeamline;
  /// parser data
  Element _element, _previousElement, _nextElement;
  
  BDSAcceleratorComponent* createSampler();
  BDSAcceleratorComponent* createCSampler();
  BDSAcceleratorComponent* createDump();
  BDSAcceleratorComponent* createDrift();
  BDSAcceleratorComponent* createRF();
  BDSAcceleratorComponent* createSBend();
  BDSAcceleratorComponent* createRBend();
  BDSAcceleratorComponent* createHKick();
  BDSAcceleratorComponent* createVKick();
  BDSAcceleratorComponent* createQuad();  
  BDSAcceleratorComponent* createSextupole();
  BDSAcceleratorComponent* createOctupole();
  BDSAcceleratorComponent* createMultipole();
  BDSAcceleratorComponent* createElement();
  BDSAcceleratorComponent* createSolenoid();
  BDSAcceleratorComponent* createRectangularCollimator();
  BDSAcceleratorComponent* createEllipticalCollimator();
  BDSAcceleratorComponent* createMuSpoiler();
  BDSAcceleratorComponent* createLaser();
  BDSAcceleratorComponent* createScreen();
  BDSAcceleratorComponent* createAwakeScreen();
  BDSAcceleratorComponent* createTransform3D();

  /// Testing function
  G4bool HasSufficientMinimumLength(Element& element);
  
  ///@{ Utility function to prepare beampipe
  G4Material*        PrepareBeamPipeMaterial(Element& element);
  G4Material*        PrepareVacuumMaterial(Element& element);
  BDSMagnetOuterInfo PrepareMagnetOuterInfo(Element& element);
  G4double           PrepareOuterDiameter(Element& element);
  BDSBeamPipeInfo*   PrepareBeamPipeInfo(Element& element);
  ///@}

};
#endif
