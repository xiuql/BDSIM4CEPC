/* BDSIM code.    Version 1.0
   Author: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 02.12.2004
   Copyright (c) 2004 by J.C.Carter.  ALL RIGHTS RESERVED. 
*/

const int DEBUG = 1;

#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSElement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"
#include "G4Trd.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"

#include "BDSAcceleratorComponent.hh"

// geometry drivers
#include "ggmad.hh"
#include "BDSGeometrySQL.hh"


#include <map>

//============================================================

typedef std::map<G4String,int> LogVolCountMap;
extern LogVolCountMap* LogVolCount;

typedef std::map<G4String,G4LogicalVolume*> LogVolMap;
extern LogVolMap* LogVol;

extern BDSMaterials* theMaterials;
extern G4RotationMatrix* RotY90;

//============================================================

BDSElement::BDSElement(G4String aName, G4String geometry, G4String bmap,
		       G4double aLength, G4double bpRad):
  BDSAcceleratorComponent(
			  aName,
			  aLength,bpRad,0,0,
			  SetVisAttributes()),
  itsField(NULL)
{
  if(DEBUG) G4cout<<"BDSElement : starting build logical volume "<<
	      itsMarkerLogicalVolume<<G4endl;

  BuildGeometry(); // build element box

  if(DEBUG) G4cout<<"BDSElement : end build logical volume "<<
	      itsMarkerLogicalVolume<<G4endl;

  PlaceComponents(geometry,bmap); // place components (from file) and build filed maps

}

void BDSElement::BuildGeometry()
{
  // multiple element instances not implemented yet!!!

  // Build the logical volume 

  if(DEBUG) G4cout<<"BDSElement : creating logical volume"<<G4endl;
  
  G4double elementSizeX =BDSGlobals->GetTunnelRadius() / 2;

  G4double elementSizeY =BDSGlobals->GetTunnelRadius() / 2;
  
  itsMarkerLogicalVolume = 
    new G4LogicalVolume(new G4Box(itsName+"generic_element",
				  elementSizeX,
				  elementSizeY,
				  itsLength/2),
			theMaterials->LCVacuum,
			itsName);
  
  (*LogVolCount)[itsName] = 1;
  (*LogVol)[itsName] = itsMarkerLogicalVolume;
  
  itsOuterUserLimits = new G4UserLimits();
  itsOuterUserLimits->SetMaxAllowedStep(itsLength);
  itsMarkerLogicalVolume->SetUserLimits(itsOuterUserLimits);
 
  
}

// place components 
void BDSElement::PlaceComponents(G4String geometry, G4String bmap)
{

  G4String gFormat="", bFormat="";
  G4String gFile="", bFile="";

  // get geometry format and file
  G4int pos = geometry.find(":");

  if(pos<0) { 
    G4cerr<<"WARNING: invalid geometry reference format : "<<geometry<<endl;
    gFormat="none";
  }
  else {
    gFormat = geometry.substr(0,pos);
    gFile = geometry.substr(pos+1,geometry.length() - pos); 
  }

  // get fieldmap format and file
  pos = bmap.find(":");

  if(pos<0) {
    G4cerr<<"WARNING: invalid B map reference format : "<<bmap<<endl; 
    bFormat="none";
  }
  else {
    bFormat = bmap.substr(0,pos);
    bFile = bmap.substr(pos+1,bmap.length() - pos); 
  }

  G4cout<<"placing components\n: geometry format - "<<gFormat<<G4endl<<
    "file - "<<gFile<<G4endl;

  G4cout<<"bmap format - "<<bFormat<<G4endl<<
    "file - "<<bFile<<G4endl;


  // get the geometry for the driver
  // different drivers may interpret the fieldmap differently
  // so a field map without geometry is not allowed

  GGmadDriver *ggmad;
  BDSGeometrySQL *Mokka;

  if(gFormat=="gmad") {

    ggmad = new GGmadDriver(gFile);
    ggmad->Construct(itsMarkerLogicalVolume);

    // attach magnetic field if present

    if(bFormat=="XY")
      itsField = new BDSXYMagField(bFile);

  }
  else if(gFormat=="mokka") {

    Mokka = new BDSGeometrySQL(gFile);
    Mokka->Construct(itsMarkerLogicalVolume);
    
    // attach magnetic field if present

    // Mokka->BuildField()
    // itsField = Mokka->GetField();

  } 
  else if(gFormat=="gdml") {
    
    G4cout<<"GDML.... sorry, not implemented yet..."<<G4endl;

  }
  else {
    G4cerr<<"geometry format "<<gFormat<<" not supported"<<G4endl;
  }


  // build the magnetic field manager and transportation
  BuildMagField();


  //   // test - dump field values
//     G4cout<<"dumping field values..."<<G4endl;
//     G4double Point[4];
//     G4double BField[6];
//     ofstream testf("fields.dat");

//     for(G4double x=-1*m;x<1*m;x+=1*cm)
//        for(G4double y=-1*m;y<1*m;y+=1*cm)
// 	 for(G4double z=-1*m;z<1*m;z+=1*cm)
//       {
// 	Point[0] = x;
// 	Point[1] = y;
// 	Point[2] = z;
// 	Point[3] = 0;
// 	itsField->GetFieldValue(Point,BField);
// 	testf<<Point[0]<<" "<<Point[1]<<" "<<Point[2]<<" "<<
// 	  BField[0]<<" "<<BField[1]<<" "<<BField[2]<<G4endl;
//       }

//     testf.close();
//     G4cout<<"done"<<G4endl;


}



G4VisAttributes* BDSElement::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0.5,0.5,1));
  return itsVisAttributes;
}


void BDSElement::BuildMagField()
{
  //itsField = new BDSField();

  // Create an equation of motion for this field
  G4EqMagElectricField* fEquation = new G4EqMagElectricField(itsField);

  G4int nvar = 8;
  G4MagIntegratorStepper* fStepper = new G4ClassicalRK4( fEquation, nvar );

  // create a field manager
  G4FieldManager* fieldManager = new G4FieldManager();
  fieldManager->SetDetectorField(itsField );


  G4double fMinStep  = BDSGlobals->GetChordStepMinimum(); 
  
  G4MagInt_Driver* fIntgrDriver = new G4MagInt_Driver(fMinStep, 
						      fStepper, 
						      fStepper->GetNumberOfVariables() );
  
  G4ChordFinder* fChordFinder = new G4ChordFinder(fIntgrDriver);

  fChordFinder->SetDeltaChord(BDSGlobals->GetDeltaChord());

  fieldManager->SetChordFinder( fChordFinder );
  
  itsMarkerLogicalVolume->SetFieldManager(fieldManager,false);
  
  G4UserLimits* fUserLimits =
    new G4UserLimits("element cuts",DBL_MAX,DBL_MAX,DBL_MAX,
  		     BDSGlobals->GetThresholdCutCharged());
  
  fUserLimits->SetMaxAllowedStep(1e-2 * m);

  itsMarkerLogicalVolume->SetUserLimits(fUserLimits);
  
}


// creates a field mesh in the reference frame of a physical volume
// from  b-field map value list 
// has to be called after the component is placed in the geometry
void BDSElement::PrepareField(G4VPhysicalVolume *referenceVolume)
{
  if(!itsField) return;
  itsField->Prepare(referenceVolume);
}

BDSElement::~BDSElement()
{

  delete itsVisAttributes;
 
}
