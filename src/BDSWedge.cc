/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 18.10.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
/*
  This Wedge component is an adaption of the BDSSectorBend with the B-field
  removed.
  J.C.Carter
  02.03.2005
*/

#include "BDSGlobalConstants.hh" // must be first in include list

#include "BDSWedge.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UserLimits.hh"
#include "G4TransportationManager.hh"

#include <map>

//============================================================

typedef std::map<G4String,int> LogVolCountMap;
extern LogVolCountMap* LogVolCount;

typedef std::map<G4String,G4LogicalVolume*> LogVolMap;
extern LogVolMap* LogVol;

extern BDSMaterials* theMaterials;
extern G4RotationMatrix* RotY90;

//============================================================

BDSWedge::BDSWedge(G4String& aName,G4double aLength, G4double bpRad,
			     G4double angle):
  BDSMultipole(aName,aLength, bpRad, bpRad,
	       SetVisAttributes(),0.,0.,angle)
{

  if (!(*LogVolCount)[itsName])
    {

      BuildWedgeMarkerLogicalVolume();
     
      G4double HalfLength =(itsLength/itsAngle)*sin(itsAngle/2)-
	BDSGlobals->GetComponentBoxSize()*tan(abs(itsAngle)/2);

      BuildDefaultOuterLogicalVolume(2.*HalfLength,true);

      (*LogVolCount)[itsName]=1;
      (*LogVol)[itsName]=itsMarkerLogicalVolume;
    }
  else
    {
      (*LogVolCount)[itsName]++;
      itsMarkerLogicalVolume=(*LogVol)[itsName];
	
    }
}


G4VisAttributes* BDSWedge::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0,0,1));
  return itsVisAttributes;
}


void BDSWedge::BuildWedgeMarkerLogicalVolume()
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


BDSWedge::~BDSWedge()
{
  if(itsVisAttributes) delete itsVisAttributes;
  if(itsMarkerLogicalVolume) delete itsMarkerLogicalVolume;
  if(itsOuterLogicalVolume) delete itsOuterLogicalVolume;
  if(itsPhysiComp) delete itsPhysiComp;
}
