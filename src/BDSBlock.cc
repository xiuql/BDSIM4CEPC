/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 20.2.2005
   Copyright (c) 2005 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#include "BDSGlobalConstants.hh" // must be first in include list

#include "BDSBlock.hh"
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
//============================================================

BDSBlock::BDSBlock (G4String& aName,G4double aLength):
  BDSMultipole(aName,aLength, 0.,BDSGlobals->GetComponentBoxSize()/2 
	       , SetVisAttributes()){
  if (!(*LogVolCount)[itsName])
    {
      itsBPFieldMgr=NULL;

      itsMarkerLogicalVolume=new G4LogicalVolume
	(new G4Box( itsName+"_marker",             
		    BDSGlobals->GetComponentBoxSize()/2,//x length
		    BDSGlobals->GetComponentBoxSize()/2, // y half length
		    (itsLength+BDSGlobals->GetLengthSafety())/2), //z hlf ln 
	 theMaterials->LCVacuum,
	 //theMaterials->LCAluminium,
	 //theMaterials->LCLead,
	 itsName+"_marker");

      SetSensitiveVolume(itsMarkerLogicalVolume);

 
      (*LogVolCount)[itsName]=1;
      (*LogVol)[itsName]=itsMarkerLogicalVolume;
    }
  else
    {
      (*LogVolCount)[itsName]++;
      itsMarkerLogicalVolume=(*LogVol)[itsName];
    }
  
}


G4VisAttributes* BDSBlock::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0.3,1,0.3));
  return itsVisAttributes;
}


BDSBlock::~BDSBlock()
{
  delete itsVisAttributes;
  delete itsMarkerLogicalVolume;
}
