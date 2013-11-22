#include "BDSGlobalConstants.hh" 
#include "BDSLensFacet.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"               
#include "G4SubtractionSolid.hh"
#include "G4UserLimits.hh"
#include "G4TransportationManager.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "BDSDebug.hh"

#include "G4SDManager.hh"
#include "G4UserLimits.hh"
#include "G4Version.hh"
#include "parser/gmad.h"
#include "G4Trap.hh"

//============================================================
BDSLensFacet::BDSLensFacet (G4String name, G4TwoVector size, G4double angle, G4double baseHeight, G4String material):
  _name(name+"_LensFacet"),_size(size),_angle(angle), _baseHeight(baseHeight), _material(material) 
{
  computeDimensions();
  build();
}

void BDSLensFacet::computeDimensions(){
  _totalHeight = _baseHeight + _size.x()*tan(_angle);
  //phi, theta, psi rotation such that the base is perp. to the z direction.
  _rotation = new G4RotationMatrix(0, BDSGlobalConstants::Instance()->GetPI()/2.0,0); 
}


void BDSLensFacet::visAtt()
{
  _visAtt=new G4VisAttributes(G4Colour(0.8,0.2,0.0,0.2));
  _visAtt->SetForceSolid(true);
  _log->SetVisAttributes(_visAtt);
}

void BDSLensFacet::build(){
  _solid = new G4Trap((_name+"solid").c_str(), _size.x(), _size.y(), _totalHeight, _baseHeight);
  _log = new G4LogicalVolume(_solid,BDSMaterials::Instance()->GetMaterial(_material),(_name+"_log").c_str(),0,0,0);
  visAtt();
}


BDSLensFacet::~BDSLensFacet(){
}
