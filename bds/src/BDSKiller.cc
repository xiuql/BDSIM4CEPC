/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 19.1.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
// gab:
#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSKiller.hh"
#include "G4Box.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"               
#include "G4UserLimits.hh"


#include "BDSRootObjects.hh"

//#include"MagFieldFunction.hh"
#include <map>

#include "BDSRootObjects.hh"


// #define DECFortran 1
//#include "/cern/pro/include/cfortran/cfortran.h"
//#include "hbook.h"
//#include "/cern/pro/include/cfortran/packlib.h"
//#include "stdlib.h"

//============================================================
//typedef std::map<G4String,MagFieldFunction*> PhysFieldMap;
//extern PhysFieldMap* MagFieldMap;

typedef std::map<G4String,int> LogVolCountMap;
extern LogVolCountMap* LogVolCount;

typedef std::map<G4String,G4LogicalVolume*> LogVolMap;
extern LogVolMap* LogVol;

extern BDSMaterials* theMaterials;
//============================================================

BDSKiller::BDSKiller (G4String& aName,G4double aLength):
  BDSAcceleratorComponent(
			 aName,
			 aLength,0,0,0,
			 SetVisAttributes())
{
  KillerLogicalVolume();
}


void BDSKiller::KillerLogicalVolume()
{
  if(!(*LogVolCount)[itsName])
    {

      G4double SampTransSize;
      if(BDSGlobals->GetAcceleratorType()->GetType()=="atf")
	SampTransSize=2.*BDSGlobals->GetComponentBoxSize();
      else
	SampTransSize=2.*BDSGlobals->GetTunnelRadius();

      itsMarkerLogicalVolume=
	new G4LogicalVolume(
			    new G4Box(itsName,
				      SampTransSize,
				      SampTransSize,
				      itsLength/2),
			    theMaterials->LCVacuum,
			    itsName);

      (*LogVolCount)[itsName]=1;
      (*LogVol)[itsName]=itsMarkerLogicalVolume;


    }
  else
    {
      (*LogVolCount)[itsName]++;
      itsMarkerLogicalVolume=(*LogVol)[itsName];
    }
}

G4VisAttributes* BDSKiller::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(1,1,1));
  return itsVisAttributes;
}

BDSKiller::~BDSKiller()
{
  delete itsVisAttributes;
  delete itsUserLimits;
}
