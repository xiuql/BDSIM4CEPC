/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 18.10.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#include "BDSGlobalConstants.hh" // must be first in include list

#include "BDSSectorBend.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UserLimits.hh"
#include "G4TransportationManager.hh"

#include <map>

// gab tmp:
extern G4LogicalVolume* TempLogVol;

//============================================================

typedef std::map<G4String,int> LogVolCountMap;
extern LogVolCountMap* LogVolCount;

typedef std::map<G4String,G4LogicalVolume*> LogVolMap;
extern LogVolMap* LogVol;

extern BDSMaterials* theMaterials;
extern G4RotationMatrix* RotY90;

//============================================================

BDSSectorBend::BDSSectorBend(G4String& aName,G4double aLength, 
			     G4double bpRad,G4double FeRad,
			     G4double bField, G4double angle,
			     G4int nSegments):
  BDSMultipole(aName,aLength, bpRad, FeRad,SetVisAttributes(),0,0,angle),
  itsBField(bField)
{
  if (!(*LogVolCount)[itsName])
    {

      BuildBPFieldAndStepper();
      BuildBPFieldMgr(itsStepper,itsMagField);

      BuildSBMarkerLogicalVolume();

  G4cout<<"BPFieldMgr="<<GetBPFieldMgr()<<G4endl;

     
      G4double HalfLength =(itsLength/itsAngle)*sin(itsAngle/2)-
	itsBpRadius*tan(abs(itsAngle)/2);

      //      BuildBeampipe(2.*HalfLength,nSegments);
      BuildBeampipe(2.*HalfLength);

      HalfLength =(itsLength/itsAngle)*sin(itsAngle/2)-
	BDSGlobals->GetComponentBoxSize()*tan(abs(itsAngle)/2);

      BuildDefaultOuterLogicalVolume(2.*HalfLength);

      if(BDSGlobals->GetAcceleratorType()->GetType()=="atf")
	{
	  // apply the magnetic field to the entire marker volume,
	  // to avoid end effects for large bends
	  GetMarkerLogicalVolume()->SetFieldManager(GetBPFieldMgr(),false);
	}

      //SetSensitiveVolume(itsBeampipeLogicalVolume);// for synchrotron
      SetSensitiveVolume(itsOuterLogicalVolume);// otherwise

      if(BDSGlobals->GetIncludeIronMagFields())
	{
	  G4double polePos[4];
	  G4double Bfield[3];

	  polePos[0]=0.;
	  polePos[1]=BDSGlobals->GetMagnetPoleRadius();
	  polePos[2]=0.;
	  polePos[0]=-999.;//flag to use polePos rather than local track
	  //coordinate in GetFieldValue	    
	  
      	  itsMagField->GetFieldValue(polePos,Bfield);
	  G4double BFldIron=
	  sqrt(Bfield[0]*Bfield[0]+Bfield[1]*Bfield[1])*
	  BDSGlobals->GetMagnetPoleSize()/
	  (BDSGlobals->GetComponentBoxSize()/2-
	  BDSGlobals->GetMagnetPoleRadius());
	  // Magnetic flux from a pole is divided in two directions
	  BFldIron/=2.;
	  
	  BuildOuterFieldManager(2, BFldIron,0);
	}
      (*LogVolCount)[itsName]=1;
      (*LogVol)[itsName]=itsMarkerLogicalVolume;
    }
  else
    {
      (*LogVolCount)[itsName]++;
      if(BDSGlobals->GetSynchRadOn()&& BDSGlobals->GetSynchRescale())
	{
	  // with synchrotron radiation, the rescaled magnetic field
	  // means elements with the same name must have different
	  //logical volumes, becuase they have different fields
	  itsName+=StringFromInt((*LogVolCount)[itsName]);

	  BuildBPFieldAndStepper();
	  BuildBPFieldMgr(itsStepper,itsMagField);

  G4cout<<"BPFieldMgr="<<GetBPFieldMgr()<<G4endl;

	  BuildSBMarkerLogicalVolume();

	  G4double HalfLength =(itsLength/itsAngle)*sin(itsAngle/2)-
	    itsBpRadius*tan(abs(itsAngle)/2);

	  BuildBeampipe(2.*HalfLength);

	  HalfLength =(itsLength/itsAngle)*sin(itsAngle/2)-
	    BDSGlobals->GetComponentBoxSize()*tan(abs(itsAngle)/2);
	  BuildDefaultOuterLogicalVolume(2.*HalfLength);

	  if(BDSGlobals->GetAcceleratorType()->GetType()=="atf")
	    {
	      // apply the magnetic field to the entire marker volume,
	      // to avoid end effects for large bends
	      GetMarkerLogicalVolume()->SetFieldManager(GetBPFieldMgr(),false);
	    }

	  SetSensitiveVolume(itsBeampipeLogicalVolume);// for synchrotron  
	  // SetSensitiveVolume(itsOuterLogicalVolume);// for laserwire

	  if(BDSGlobals->GetIncludeIronMagFields())
	    {
	      G4double polePos[4];
	      G4double Bfield[3];
	      
	      polePos[0]=0.;
	      polePos[1]=BDSGlobals->GetMagnetPoleRadius();
	      polePos[2]=0.;
	      polePos[0]=-999.;//flag to use polePos rather than local track
	      //coordinate in GetFieldValue	    
	      
	      itsMagField->GetFieldValue(polePos,Bfield);
	      G4double BFldIron=
		sqrt(Bfield[0]*Bfield[0]+Bfield[1]*Bfield[1])*
		BDSGlobals->GetMagnetPoleSize()/
		(BDSGlobals->GetComponentBoxSize()/2-
		 BDSGlobals->GetMagnetPoleRadius());
	      // Magnetic flux from a pole is divided in two directions
	      BFldIron/=2.;
	      
	      BuildOuterFieldManager(2, BFldIron,0);
	    }
	  (*LogVol)[itsName]=itsMarkerLogicalVolume;
	}
      else
	{
	  itsMarkerLogicalVolume=(*LogVol)[itsName];
	}
    }


}


G4VisAttributes* BDSSectorBend::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0,0,1));
  return itsVisAttributes;
}


void BDSSectorBend::BuildBPFieldAndStepper()
{
  // set up the magnetic field and stepper
  G4ThreeVector Bfield(0.,itsBField,0.);
  itsMagField=new BDS_SbendField(Bfield,itsLength,itsAngle);
  itsEqRhs=new G4Mag_UsualEqRhs(itsMagField);  

  itsStepper=new BDSHelixStepper(itsEqRhs);
  itsStepper->SetBField(itsBField);
}


void BDSSectorBend::BuildSBMarkerLogicalVolume()
{
  G4double LCComponentBoxSize=BDSGlobals->GetComponentBoxSize();
  G4double xHalfLengthMinus=(itsLength/itsAngle)*sin(itsAngle/2)
    -LCComponentBoxSize*tan(itsAngle/2)/2
    +BDSGlobals->GetLengthSafety()/2;

  G4double xHalfLengthPlus=(itsLength/itsAngle)*sin(itsAngle/2)
    +LCComponentBoxSize*tan(itsAngle/2)/2
    +BDSGlobals->GetLengthSafety()/2;

  G4String LocalLogicalName=itsName;
  itsMarkerLogicalVolume=    
    new G4LogicalVolume(new G4Trd(itsName+"_marker" ,             
				  xHalfLengthPlus,      // x hlf lgth at +z
				  xHalfLengthMinus,     // x hlf lgth at -z
				  LCComponentBoxSize/2, // y hlf lgth at +z
				  LCComponentBoxSize/2, // y hlf lgth at -z
				  LCComponentBoxSize/2),// z hlf lgth
			theMaterials->LCVacuum,
			LocalLogicalName+"_marker");

  itsMarkerUserLimits = new G4UserLimits(DBL_MAX,DBL_MAX,DBL_MAX);
  itsMarkerUserLimits->SetMaxAllowedStep(itsLength);
  itsMarkerLogicalVolume->SetUserLimits(itsMarkerUserLimits);
}


BDSSectorBend::~BDSSectorBend()
{
  delete itsVisAttributes;
  delete itsMarkerLogicalVolume;
  delete itsOuterLogicalVolume;
  delete itsPhysiComp;
  delete itsMagField;
  delete itsEqRhs;
  delete itsStepper;
}
