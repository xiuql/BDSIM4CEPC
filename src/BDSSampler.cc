/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 

   Modified 22.03.05 by J.C.Carter, Royal Holloway, Univ. of London.
   Changed Samplers to account for plane and cylinder types (GABs code)
*/
// gab:
#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSSampler.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"               
#include "G4UserLimits.hh"

#include "BDSSamplerSD.hh"
#include "G4SDManager.hh"

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

BDSSampler::BDSSampler (G4String& aName,G4double aLength):
  BDSAcceleratorComponent(
			 aName,
			 aLength,0,0,0,
			 SetVisAttributes())
{
  SamplerLogicalVolume();

  G4int nSamplers=(*LogVolCount)[itsName];

  BDSRoot->SetSamplerNumber(nSamplers);

  /*
  // G4int nVar=8;
  G4int nVar=14;
  //            |----------this is the number of variables
  char chtag_in[14][6]={
    "x0",
    "xp0",
    "y0",
    "yp0",
    "E0",
    "z0",
    "x",
    "xp",
    "y",
    "yp",
    "E",
    "z",
    "part",
    "nev"};
  */

  //gab to Root:  HBOOKN(nSamplers,"Sampler Ntuple",nVar,"sampler",5000,chtag_in);

}


void BDSSampler::SamplerLogicalVolume()
{
  if(!(*LogVolCount)[itsName])
    {

      G4double SampTransSize;
      if(BDSGlobals->GetAcceleratorType()->GetType()=="atf")
	SampTransSize=BDSGlobals->GetComponentBoxSize();
      else
	SampTransSize=2.*BDSGlobals->GetTunnelRadius();

      itsMarkerLogicalVolume=
	new G4LogicalVolume(
			    new G4Box(itsName+"_solid",
				      SampTransSize,
				      SampTransSize,
				      itsLength/2),
			    theMaterials->LCVacuum,
			    itsName);

      (*LogVolCount)[itsName]=1;
      (*LogVol)[itsName]=itsMarkerLogicalVolume;

      itsOuterUserLimits =new G4UserLimits();
      itsOuterUserLimits->SetMaxAllowedStep(itsLength);
      itsMarkerLogicalVolume->SetUserLimits(itsOuterUserLimits);

     // Sensitive Detector:
      G4SDManager* SDMan = G4SDManager::GetSDMpointer();
      BDSSamplerSD* SensDet=new BDSSamplerSD(itsName,"plane");
      SDMan->AddNewDetector(SensDet);
      itsMarkerLogicalVolume->SetSensitiveDetector(SensDet);
    }
  else
    {
      (*LogVolCount)[itsName]++;
      itsMarkerLogicalVolume=(*LogVol)[itsName];
    }
}

G4VisAttributes* BDSSampler::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(1,1,1));
  return itsVisAttributes;
}

BDSSampler::~BDSSampler()
{
  if(itsVisAttributes) delete itsVisAttributes;
  if(itsUserLimits) delete itsUserLimits;
}
