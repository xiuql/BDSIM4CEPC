/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 4.3.2005
   Copyright (c) 2005 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
// gab:
#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSResetter.hh"
#include "G4Box.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"               
#include "G4UserLimits.hh"

#include "G4SDManager.hh"
#include <map>

//============================================================
typedef std::map<G4String,int> LogVolCountMap;
extern LogVolCountMap* LogVolCount;

typedef std::map<G4String,G4LogicalVolume*> LogVolMap;
extern LogVolMap* LogVol;

extern BDSMaterials* theMaterials;
//============================================================

BDSResetter::BDSResetter (G4String& aName,G4double aLength):
  BDSAcceleratorComponent(
			 aName,
			 aLength,0,0,0,
			 SetVisAttributes())
{
  ResetterLogicalVolume();

}


void BDSResetter::ResetterLogicalVolume()
{
  if(!(*LogVolCount)[itsName])
    {

      G4double ResetTransSize;
      if(BDSGlobals->GetAcceleratorType()->GetType()=="atf")
	ResetTransSize=BDSGlobals->GetComponentBoxSize();
      else
	ResetTransSize=2.*BDSGlobals->GetTunnelRadius();

      itsMarkerLogicalVolume=
	new G4LogicalVolume(
			    new G4Box(itsName+"_solid",
				      ResetTransSize,
				      ResetTransSize,
				      itsLength/2),
			    theMaterials->LCResetter,
			    itsName);

      (*LogVolCount)[itsName]=1;
      (*LogVol)[itsName]=itsMarkerLogicalVolume;

      itsOuterUserLimits =new G4UserLimits();
      itsOuterUserLimits->SetMaxAllowedStep(itsLength);
      itsMarkerLogicalVolume->SetUserLimits(itsOuterUserLimits);

    }
  else
    {
      (*LogVolCount)[itsName]++;
      itsMarkerLogicalVolume=(*LogVol)[itsName];
    }
}

G4VisAttributes* BDSResetter::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0,1,1));
  return itsVisAttributes;
}

BDSResetter::~BDSResetter()
{
  delete itsVisAttributes;
  delete itsUserLimits;
}
