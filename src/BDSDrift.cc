/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#include "BDSGlobalConstants.hh" // must be first in include list

#include "BDSDrift.hh"
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

BDSDrift::BDSDrift (G4String& aName,G4double aLength, G4double bpRad):
  BDSMultipole(aName,aLength, bpRad, bpRad, SetVisAttributes())
{
  if (!(*LogVolCount)[itsName])
    {
      //BuildMarkerFieldAndStepper();
      //BuildMarkerFieldMgr(itsStepper,itsMagField);

      itsBPFieldMgr=NULL;
      BuildDefaultMarkerLogicalVolume();

      BuildBeampipe(itsLength);

      // drift doesn't have an outer volume - but include it for laserwire
      //      BuildDefaultOuterLogicalVolume(itsLength);
      SetSensitiveVolume(itsBeampipeLogicalVolume);// for laserwire
      //SetSensitiveVolume(itsOuterLogicalVolume);// for laserwire

 
      (*LogVolCount)[itsName]=1;
      (*LogVol)[itsName]=itsMarkerLogicalVolume;
    }
  else
    {
      (*LogVolCount)[itsName]++;
      itsMarkerLogicalVolume=(*LogVol)[itsName];
    }
  
}


G4VisAttributes* BDSDrift::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0,1,0));
  return itsVisAttributes;
}

/*
void BDSDrift::BuildMarkerFieldAndStepper()
{
  // set up the magnetic field and stepper
  G4ThreeVector Bfield(0.,0.,0.);
  itsMagField=new G4UniformMagField(Bfield);
  itsEqRhs=new G4Mag_UsualEqRhs(itsMagField);
  
  itsStepper=new BDSDriftStepper(itsEqRhs);
}
*/

BDSDrift::~BDSDrift()
{
  if(itsVisAttributes) delete itsVisAttributes;
  if(itsMarkerLogicalVolume) delete itsMarkerLogicalVolume;
  if(itsOuterLogicalVolume) delete itsOuterLogicalVolume;
  if(itsPhysiComp) delete itsPhysiComp;
  if(itsMagField) delete itsMagField;
  if(itsEqRhs) delete itsEqRhs;
  if(itsStepper) delete itsStepper;
}
