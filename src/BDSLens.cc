#include "BDSGlobalConstants.hh" 
#include "BDSLens.hh"
#include "BDSMaterials.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Tubs.hh"
#include "BDSDebug.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4Orb.hh"

#include "BDSDebug.hh"

//============================================================
BDSLens::BDSLens (G4String name, G4double diameter, G4double rho, G4double centreThickness):
_name(name+"_Lens"), _diameter(diameter), _rho(rho), _centreThickness(centreThickness)
{
  G4cout << __METHOD_NAME__ << G4endl;
  build();
}


void BDSLens::visAtt()
{
  G4cout << __METHOD_NAME__ << G4endl;
  _visAtt=new G4VisAttributes(G4Colour(0.5,0.8,0.5,0.3));
  _visAtt->SetForceSolid(true);
  _log->SetVisAttributes(_visAtt);
}

void BDSLens::build(){
  G4cout << __METHOD_NAME__ << G4endl;
  G4Tubs* tube = new G4Tubs(_name+"_tempTube", _diameter, _rho,_rho,0,CLHEP::twopi*CLHEP::radian);
  G4SubtractionSolid* sideA = new G4SubtractionSolid(_name+"_sideA",new G4Orb(_name+"_tempOrbA",_rho),tube);
  G4SubtractionSolid* sideB = new G4SubtractionSolid(_name+"_sideB",new G4Orb(_name+"_tempOrbB",_rho),tube);

  //  G4SubtractionSolid* sideA = new G4Orb(_name+"_tempOrbA",_rho);
  //  G4SubtractionSolid* sideB = new G4Orb(_name+"_tempOrbB",_rho);

  G4ThreeVector transVec;
  transVec.setZ(2*_rho-_centreThickness);
  G4IntersectionSolid* intersectionA = new G4IntersectionSolid(_name+"_intersectionA", sideA, sideB, (G4RotationMatrix*)nullptr,transVec);
  transVec.setZ(-1*_rho+_centreThickness/2.0);
  //  _solid = new G4IntersectionSolid(_name+"_solid", new G4Box(_name+"tempBox",_diameter/2.0,_diameter/2.0,_centreThickness/2.0), intersectionA,(G4RotationMatrix*)nullptr,transVec);
  _solid = new G4IntersectionSolid(_name+"_solid", new G4Tubs(_name+"tempTube2",0,_diameter/2.0,_centreThickness/2.0,0,CLHEP::twopi*CLHEP::radian), intersectionA,(G4RotationMatrix*)nullptr,transVec);
  _log = new G4LogicalVolume(_solid,BDSMaterials::Instance()->GetMaterial("n-bk7"),(_name+"_log").c_str(),0,0,0);
  visAtt();
}

G4String BDSLens::name(){
  G4cout << __METHOD_NAME__ << G4endl;
  return _name;
}

G4LogicalVolume* BDSLens::log(){
  G4cout << __METHOD_NAME__ << G4endl;
  return _log;
}

BDSLens::~BDSLens(){
}
