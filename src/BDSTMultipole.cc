#include "BDSGlobalConstants.hh" 

#include "BDSTMultipole.hh"
#include "BDSMultipoleMagField.hh"

#include "G4FieldManager.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4LogicalVolume.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4Tubs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"


BDSTMultipole::BDSTMultipole(G4String aName, G4double aLength, 
			     G4double bpRad, G4double FeRad,
			     G4double tilt, G4double outR,
			     std::list<G4double> akn, std::list<G4double> aks, 
                             std::list<G4double> blmLocZ, std::list<G4double> blmLocTheta,
			     G4String aTunnelMaterial, G4String aMaterial):
  BDSMultipole(aName,aLength, bpRad, FeRad,blmLocZ, blmLocTheta, aTunnelMaterial, aMaterial)
{
  SetOuterRadius(outR);
  itsTilt=tilt;
  CommonConstructor(akn,aks);
}


BDSTMultipole::BDSTMultipole(G4String        name,
			     G4double        length,
			     std::list<G4double> akn, // list of normal multipole strengths
			     // (NOT multiplied by multipole length)
			     std::list<G4double> aks, // list of skew multipole strengths
			     // (NOT multiplied by multipole length)
			     BDSBeamPipeType beamPipeType,
			     G4double        aper1,
			     G4double        aper2,
			     G4double        aper3,
			     G4double        aper4,
			     G4Material*     vacuumMaterial,
			     G4double        beamPipeThickness,
			     G4Material*     beamPipeMaterial,
			     G4double        boxSize,
			     G4String        outerMaterial,
			     G4String        tunnelMaterial,
			     G4double        tunnelRadius,
			     G4double        tunnelOffsetX):
  BDSMultipole(name,length,beamPipeType,aper1,aper2,aper3,aper4,vacuumMaterial,beamPipeThickness,
	       beamPipeMaterial,boxSize,outerMaterial,tunnelMaterial,tunnelRadius,tunnelOffsetX)
{
  CommonConstructor(akn,aks);
}


void BDSTMultipole::CommonConstructor(std::list<G4double> akn, std::list<G4double> aks)
{
#ifdef BDSDEBUG
  if (akn.size()>0){
    G4cout<<"Building multipole of order "<<akn.size()<<G4endl;
  } else {
    G4cout<<"Building multipole of order "<<aks.size()<<G4endl;
  }
#endif

  //If the multipole has both skew and normal coefficients then they must have the same number of coefficients 
  if((akn.size() != aks.size()) && ((akn.size() >0) && (aks.size() > 0))) { G4cerr<<"ERROR : multipole skew and normal coefficients present, but to different order"<<G4endl;}
  if(akn.size() == 0 &&  aks.size() == 0) { G4cerr<<"ERROR : skew or normal multipole order must be greater than 0"<<G4endl; }

  //Check if any components are non-zero
  /*  
  G4bool fieldNonZero=false;
  for(std::list<double>::iterator it = akn.begin(); it != akn.end() && fieldNonZero == false; it++){
    if(*it != 0) fieldNonZero = true;
  }
  for(std::list<double>::iterator it = aks.begin(); it != aks.end() && fieldNonZero == false; it++){
    if(*it != 0) fieldNonZero = true;
  }
  */

  //If list of normal or skew multipole coefficients not present, create a default list containing zeroes.
  if (aks.size()==0){
    for(unsigned int i=0; i<akn.size(); i++){
      aks.push_back(0.0);
    }
  }
  if (akn.size()==0){
    for(unsigned int i=0; i<aks.size(); i++){
      akn.push_back(0.0);
    }
  }

  kn = akn;
  ks = aks;

#ifdef BDSDEBUG 
  int order = 0;
  G4cout<<"M: kn={ ";
  std::list<double>::iterator kit;
  for(kit=kn.begin();kit!=kn.end();kit++)
    {
      G4cout<<(*kit)<<"m^-"<<++order<<" ";
    }
  G4cout<<"}"<<G4endl;
  order = 0;
  G4cout<<"M: ks={ ";
  for(kit=ks.begin();kit!=ks.end();kit++)
    {
      G4cout<<(*kit)<<"m^-"<<++order<<" ";
    }
  G4cout<<"}"<<G4endl;
#endif

  itsOrder = kn.size();
}

void BDSTMultipole::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0.1,0.4,0.2));
  itsVisAttributes->SetForceSolid(true);
}

void BDSTMultipole::BuildBPFieldAndStepper()
{
  // set up the magnetic field and stepper
  itsMagField = new BDSMultipoleMagField(kn,ks);
  itsEqRhs    = new G4Mag_UsualEqRhs(itsMagField);
  itsStepper  = new G4SimpleRunge(itsEqRhs);
}
