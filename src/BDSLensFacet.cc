#include "BDSGlobalConstants.hh" 
#include "BDSLensFacet.hh"
#include "BDSMaterials.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UserLimits.hh"
#include "G4TransportationManager.hh"

#include "G4UserLimits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Trap.hh"

//============================================================
BDSLensFacet::BDSLensFacet (G4String name, G4TwoVector size, G4double angle, G4double baseHeight, G4String material):
  _name(name+"_LensFacet"),_size(size),_angle(angle), _baseHeight(baseHeight), _material(material) 
{
  computeDimensions();
  build();
}

void BDSLensFacet::computeDimensions(){
  G4double aSmallNumber=1e-9;
  if(_baseHeight==0) {_baseHeight=aSmallNumber;}
  _totalHeight = _baseHeight + _size.x()*tan(_angle);
  //phi, theta, psi rotation such that the base is perp. to the z direction.
  _rotation = new G4RotationMatrix(0,pi/2.0,0); 
}


void BDSLensFacet::visAtt()
{
  _visAtt=new G4VisAttributes(G4Colour(0.8,0.2,0.0,0.2));
  _visAtt->SetForceSolid(true);
  _log->SetVisAttributes(_visAtt);
}

void BDSLensFacet::build(){
  G4cout << "Building G4Trap with dimensions: " << _size.x() << " " << _size.y()<< " " <<  _totalHeight << " " <<  _baseHeight << G4endl;
  _solid = new G4Trap((_name+"solid").c_str(), _size.x(), _size.y(), _totalHeight, _baseHeight);
 _log = new G4LogicalVolume(_solid,BDSMaterials::Instance()->GetMaterial(_material),(_name+"_log").c_str(),0,0,0);
  visAtt();
}


BDSLensFacet::~BDSLensFacet(){
}
