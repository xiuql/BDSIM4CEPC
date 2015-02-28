#include "BDSGlobalConstants.hh" 
#include "BDSKicker.hh"

#include "BDSDipoleStepper.hh"
#include "BDSSbendMagField.hh"

#include "G4FieldManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"

BDSKicker::BDSKicker(G4String aName, G4double aLength, 
		     G4double bpRad, G4double FeRad,
		     G4double bField, G4double angle, G4double outR,
		     G4double tilt, G4double bGrad, 
		     G4String aTunnelMaterial, G4String aMaterial):
  BDSMultipole(aName, aLength, bpRad, FeRad, aTunnelMaterial, aMaterial,
	       0, 0, /*itsAngle=*/0)
{
  SetOuterRadius(outR);
  itsTilt      = tilt;
  itsBField    = bField;
  itsBGrad     = bGrad;
  //use separate kick angle as kicker doesn't rotate reference trajectory
  //bdsbeamline places things based on itsAngle
  itsKickAngle = angle;
}

BDSKicker::BDSKicker(G4String     name,
		     G4double     length,
		     G4double     bField,
		     G4double     bGrad,
		     G4double     angle,
		     beamPipeInfo beamPipeInfo,
		     G4double     boxSize,
		     G4String     outerMaterial,
		     G4String     tunnelMaterial,
		     G4double     tunnelRadius,
		     G4double     tunnelOffsetX):
  BDSMultipole(name,length,beamPipeInfo,boxSize,outerMaterial,tunnelMaterial,tunnelRadius,tunnelOffsetX),
  itsBField(bField),itsBGrad(bGrad),itsKickAngle(angle)
{;}

void BDSKicker::Build() {
  BDSMultipole::Build();

  if(BDSGlobalConstants::Instance()->GetIncludeIronMagFields())
    {
      G4double polePos[4];
      G4double Bfield[3];
      
      //coordinate in GetFieldValue
      polePos[0]=0.;
      polePos[1]=BDSGlobalConstants::Instance()->GetMagnetPoleRadius();
      polePos[2]=0.;
      polePos[3]=-999.;//flag to use polePos rather than local track
      
      itsMagField->GetFieldValue(polePos,Bfield);
      G4double BFldIron=
	sqrt(Bfield[0]*Bfield[0]+Bfield[1]*Bfield[1])*
	BDSGlobalConstants::Instance()->GetMagnetPoleSize()/
	(BDSGlobalConstants::Instance()->GetComponentBoxSize()/2-
	 BDSGlobalConstants::Instance()->GetMagnetPoleRadius());
      
      // Magnetic flux from a pole is divided in two directions
      BFldIron/=2.;
      
      BuildOuterFieldManager(2, BFldIron,0);
    }
}


void BDSKicker::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0,0,1));
  itsVisAttributes->SetForceSolid(true);
}


void BDSKicker::BuildBPFieldAndStepper()
{
  // set up the magnetic field and stepper
  G4ThreeVector Bfield(0.,-itsBField,0.); // note the - sign...
  itsMagField=new BDSSbendMagField(Bfield,itsLength,itsKickAngle);
  
  itsEqRhs=new G4Mag_UsualEqRhs(itsMagField);  
  
  BDSDipoleStepper* dipoleStepper = new BDSDipoleStepper(itsEqRhs);
  dipoleStepper->SetBField(-itsBField); // note the - sign...
  dipoleStepper->SetBGrad(itsBGrad);
  itsStepper = dipoleStepper;
}
