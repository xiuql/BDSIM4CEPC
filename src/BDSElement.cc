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

  // 

  G4int pos = geometry.find(":");

  G4String gFormat="", bFormat="";
  G4String gFile="", bFile="";

  if(pos<0) { G4cerr<<"ERROR: invalid geometry reference format : "<<geometry<<endl; gFormat="none";}
  else
    {
      gFormat = geometry.substr(0,pos);
      gFile = geometry.substr(pos+1,geometry.length() - pos); 
    }

  pos = bmap.find(":");
  if(pos<0) { G4cerr<<"ERROR: invalid B map reference format : "<<bmap<<endl; bFormat="none";}
  else
    {
      bFormat = bmap.substr(0,pos);
      bFile = bmap.substr(pos+1,bmap.length() - pos); 
    }

  G4cout<<"placing components\n: geometry format - "<<gFormat<<G4endl<<
    "file - "<<gFile<<G4endl;

  G4cout<<"bmap format - "<<bFormat<<G4endl<<
    "file - "<<bFile<<G4endl;


  // get the geometry for the driver

  if(gFormat=="gmad") {

    GGmadDriver *ggmad = new GGmadDriver(gFile);
    ggmad->Construct(itsMarkerLogicalVolume);
    

  }
  else if(gFormat=="mokka") {

    BDSGeometrySQL *Mokka = new BDSGeometrySQL(gFile);
    Mokka->Construct(itsMarkerLogicalVolume);
    

  } else {
    G4cerr<<"geometry format "<<gFormat<<" not supported"<<G4endl;
  }


  // now attach field map if needed

  if(bFormat=="gmad") {

    if(DEBUG) G4cout<<"opening field map file "<<bFile<<G4endl;

    ifstream bmapif(bFile);

    G4double x,y,z,Bx,By,Bz;

    while(bmapif.good())
      {
	bmapif>>x>>y>>z>>Bx>>By>>Bz; 

	if(!bmapif.good()) break;

	//if(DEBUG) G4cout<<"read: "<<x<<" "<<y<<" "<<z<<" "<<Bx<<" "<<By<<" "<<Bz<<" "<<G4endl;
	AddFieldValue(x,y,z,Bx,By,Bz);
      }

    bmapif.close();

    BuildMagField();  // build magnetic field


    // test - dump field values
    G4cout<<"dumping field values..."<<G4endl;
    G4double Point[4];
    G4double BField[6];
    ofstream testf("fields.dat");

    for(G4double x=-1*m;x<1*m;x+=1*cm)
       for(G4double y=-1*m;y<1*m;y+=1*cm)
	 for(G4double z=-1*m;z<1*m;z+=1*cm)
      {
	Point[0] = x;
	Point[1] = y;
	Point[2] = z;
	Point[3] = 0;
	itsField->GetFieldValue(Point,BField);
	testf<<Point[0]<<" "<<Point[1]<<" "<<Point[2]<<" "<<
	  BField[0]<<" "<<BField[1]<<" "<<BField[2]<<G4endl;
      }

    testf.close();
    G4cout<<"done"<<G4endl;


  } else {
    G4cerr<<"field map format "<<bFormat<<"not supported"<<G4endl;
  }

}



G4VisAttributes* BDSElement::SetVisAttributes()
{
  itsVisAttributes=new G4VisAttributes(G4Colour(0.5,0.5,1));
  return itsVisAttributes;
}


void BDSElement::BuildMagField()
{
  itsField = new BDSField();

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

// add a b-field value at (x,y,z) 
void BDSElement::AddFieldValue(G4double x, G4double y, G4double z,G4double Bx, G4double By, G4double Bz )
{
  struct FieldRecord rc;
  rc.x = x;
  rc.y = y;
  rc.z = z;
  rc.Bx = Bx;
  rc.By = By;
  rc.Bz = Bz;
  rc.Ex = 0;
  rc.Ey = 0;
  rc.Ez = 0;

  itsFieldValues.push_back(rc);
}

// creates a field mesh in the reference frame of a physical volume
// from  b-field map value list
void BDSElement::CreateFieldMesh(G4VPhysicalVolume *referenceVolume)
{
  G4cout<<"BDSElement:: create field mesh"<<G4endl;
  
  const G4RotationMatrix* Rot=referenceVolume->GetFrameRotation();
  const G4ThreeVector Trans=referenceVolume->GetFrameTranslation();
  
  G4ThreeVector B;

  if(!itsField) return; // bo field attached to element - nothing to do

  // create a mesh interpolated from the values in the list


  // mesh physical dimensions


  vector<struct FieldRecord>::iterator it, itt;


  double xmax=0, ymax=0, zmax=0;

  for(it=itsFieldValues.begin();it!=itsFieldValues.end();it++)
    {
      if( fabs((*it).x ) > xmax ) xmax = fabs((*it).x);
      if( fabs((*it).y ) > ymax) ymax = fabs((*it).y);
      if( fabs((*it).z ) > zmax) zmax = fabs((*it).z);
    }

  itsField->xHalf = xmax;
  itsField->yHalf = ymax;
  itsField->zHalf = (zmax > 0) ? zmax : itsLength/2;

  G4double elementSizeX = itsField->xHalf;
  G4double elementSizeY = itsField->yHalf;

  //determine mesh step - minimum distance between measurement points
  
  double hx=elementSizeX*2, hxold=elementSizeX*2, hxmax=0;
  double hy=elementSizeY*2, hyold=elementSizeY*2, hymax=0;
  double hz=itsLength, hzold=itsLength, hzmax=0;


  for(it=++itsFieldValues.begin();it!=itsFieldValues.end();it++)
    {

      for(itt=itsFieldValues.begin();itt!=itsFieldValues.end();itt++)
	{
      
	  //G4cout<<(*it).x<<" "<<(*it).y<<" "<<(*it).z<<" "<<(*it).Bx<<G4endl;
            hxold = fabs((*it).x - (*itt).x);
            if( (hxold > 1.0e-1)&&(hxold<hx) ) hx = hxold;
      
            hyold = fabs((*it).y - (*itt).y);
            if( (hyold > 1.0e-1)&&(hyold<hy) ) hy = hyold;
      
            hzold = fabs((*it).z - (*itt).z);
            if( (hzold > 1.0e-1)&&(hzold<hz) ) hz = hzold;
	}
    }

  hxmax = hx;
  hymax = hy;
  hzmax = hz;

  G4cout<<"h ="<<hx<<":"<<hy<<":"<<hz<<G4endl;
  G4cout<<"xmax ="<<xmax<<":"<<ymax<<":"<<zmax<<G4endl;


  // allocate mesh


  G4int nX = static_cast<int> ( 2*elementSizeX / hx ) + 1;
  G4int nY = static_cast<int> ( 2*elementSizeY / hy ) + 1;
  G4int nZ = static_cast<int> ( itsLength / hz ) + 1;

  

  G4cout<<"N ="<<nX<<":"<<nY<<":"<<nZ<<G4endl;
  
  
  itsField->SetOriginRotation(*Rot);
  itsField->SetOriginTranslation(Trans);
  
  itsField->AllocateMesh(nX,nY,nZ);


  G4double rmax = 0.6 * sqrt(hxmax*hxmax + hymax*hymax + hzmax*hzmax);

   // transverse maps
  if (nZ ==2) rmax = sqrt(hxmax*hxmax + hymax*hymax);

  G4cout<<"rmax ="<<rmax<<G4endl;

  G4double x, y, z;
  vector<struct FieldRecord> vals;
  vector<double> rs;

  for(int i=0; i<nX;i++)
     for(int j=0;j<nY;j++)
       for(int k=0; k<nZ;k++)
	 {
	   x =  i * hx - elementSizeX;
	   y =  j * hy - elementSizeY;
	   z =  k * hz - itsLength/2;
	   
	   //G4cout<<" x="<<x<<" y="<<y<<" z="<<z<<G4endl;
	   //G4cout<<" i="<<i<<" j="<<j<<" k="<<k<<G4endl;

	   for(it=itsFieldValues.begin();it!=itsFieldValues.end();it++)
	     {
	       G4double r = sqrt( ((*it).x-x)*((*it).x-x) +
				  ((*it).y-y)*((*it).y-y) + 
				  ((*it).z-z)*((*it).z-z) );

	       // transverse maps
	       if (nZ ==2) r = sqrt( ((*it).x-x)*((*it).x-x) +
				     ((*it).y-y)*((*it).y-y));

	       if(r < 1.e-3) r = 1.e-3;

	       //G4cout<<"trying "<<(*it).x<<" "<<(*it).y<<" "<<(*it).z<<G4endl;
	       //G4cout<<"r="<<r<<G4endl;
	       
	       if( r < rmax  )
		 {
		   //G4cout<<"yes"<<G4endl;

		   vals.push_back((*it));
		   rs.push_back(r);
		 }
	     }

	   //compute weighted means

	   G4int N = rs.size();

	   G4double bxmean=0, bymean=0,bzmean=0,rmean=0;

	   //G4cout<<"computing mean...N="<<N<<G4endl;

	   for(int npt=0;npt<N;npt++)
	     {
	       //G4cout<<"npt="<<npt<<G4endl;

	       bxmean += vals[npt].Bx / ( rs[npt] * rs[npt]* rs[npt] );
	       bymean += vals[npt].By / ( rs[npt] * rs[npt]* rs[npt] );
	       bzmean += vals[npt].Bz / ( rs[npt] * rs[npt]* rs[npt] );

	       rmean += 1/( rs[npt] * rs[npt]* rs[npt] );
	     }

	   if( N >0 )
	     {
	       bxmean /= (rmean);
	       bymean /= (rmean);
	       bzmean /= (rmean);
	     }
	   else
	     {
	       bxmean = 0;
	       bymean = 0;
	       bzmean = 0;
	     }
	   //G4cout<<"writing values..."<<i<<" "<<j<<" "<<k<<G4endl;
	   //G4cout<<"x"<<G4endl;
	   
	   itsField->SetBx(i,j,k,bxmean * tesla);
	   
	   itsField->SetBy(i,j,k,bymean * tesla);
	   
	   itsField->SetBz(i,j,k,bzmean * tesla);

	   

	   vals.clear();
	   rs.clear();
	 }


  // dump the field mes for test

  G4cout<<"writing test file"<<G4endl;

  ofstream testf("btest.dat");

   for(int i=0; i<nX;i++)
     for(int j=0;j<nY;j++)
       for(int k=0; k<nZ;k++)
	 {
	   testf<<i<<" "<<j<<" "<<k<<" "<<
	     itsField->GetBx(i,j,k)<<" "<<
	     itsField->GetBy(i,j,k)<<" "<<
	     itsField->GetBz(i,j,k)<<endl;
	 }

   testf.close();

}

BDSElement::~BDSElement()
{

  delete itsVisAttributes;
 
}
