/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicatbdse your acceptance of this statement,
// and all its terms.
//
// $Id: BDSDetectorConstruction.cc,v 1.1.1.1 2004/11/18 17:42:38 ilia Exp $
// GEANT4 tag $Name:  $
//
// 

//=================================================================
//=================================================================
#include "BDSGlobalConstants.hh"

#include "BDSDetectorConstruction.hh"
#include "BDSDetectorMessenger.hh"

#include "G4UserLimits.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4PropagatorInField.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "globals.hh"
#include "G4ios.hh"
#include <iostream>
#include <list>
#include <map>
#include "BDSAcceleratorComponent.hh"

#include"G4Navigator.hh"
#include "G4UniformMagField.hh"

#include "G4Material.hh"
#include "BDSEnergyCounterSD.hh"
#include "BDSAcceleratorType.hh"

#include "BDSRootObjects.hh"

// tmp
#include "TDirectory.h"


//#include "BDSMultipoleOuterMagField.hh"
#include "G4MagneticField.hh"

//====================================
// Merlin things:
#include "BDSMADInterface.hh"
//====================================
typedef list<BDSAcceleratorComponent*>  BDSBeamline;
BDSBeamline theBeamline;

typedef list<BDSEnergyCounterSD*>  ECList;
ECList* theECList;

BDSMaterials* theMaterials;

extern BDSGlobalConstants* BDSGlobals;

// gab tmp:
extern G4LogicalVolume* TempLogVol;

//--------------------------
// SYNCHROTRON RAD ***
G4double BDSLocalRadiusOfCurvature=DBL_MAX;// Used in Mean Free Path calc.
//--------------------------

G4Material* SpoilerMaterial;
extern G4double NumSpoilerRadLen;

typedef std::map<G4String,int> LogVolCountMap;
LogVolCountMap* LogVolCount;

typedef std::map<G4String,G4LogicalVolume*> LogVolMap;
LogVolMap* LogVol;

G4RotationMatrix* RotY90=new G4RotationMatrix();
G4RotationMatrix* RotYM90=new G4RotationMatrix();
G4ThreeVector ZeroVec(0,0,0);

G4Navigator* StepperNavigator;
G4Navigator* QuadNavigator;

//=========================================
G4FieldManager* theOuterFieldManager;

//typedef std::map<G4String,G4MagneticField*> OuterFieldMap;
//OuterFieldMap* theOuterFieldMap;

//=================================================================

BDSDetectorConstruction::BDSDetectorConstruction()
{  // create commands for interactive definition of the beamline  
  G4double pi_ov_2 = asin(1.);
  detectorMessenger = new BDSDetectorMessenger(this);
  RotY90->rotateY(pi_ov_2);
  RotYM90->rotateY(-pi_ov_2);


}

//=================================================================

G4VPhysicalVolume* BDSDetectorConstruction::Construct()
{
  theECList=new ECList;

  //  MagFieldMap=new PhysFieldMap();
  LogVolCount=new LogVolCountMap();

  LogVol=new LogVolMap();

  // memory saving attempt:
  //theOuterFieldManager=new G4FieldManager();
  //theOuterFieldManager->CreateChordFinder();

  //  theOuterFieldMap=new OuterFieldMap();

  theMaterials=new BDSMaterials();

  SpoilerMaterial=theMaterials->LCGraphite;

  // neutron Counter ntuple booking:
 //             |----------this is the number of variables
  char chtag_in[3][6]=
  {
    "E",
    "z",
    "pz"
  };

  // gab to Root:  HBOOKN(101,"NeutronCounter",3,"sampler",5000,chtag_in);

  return ConstructBDS();

}

//=================================================================
  
G4VPhysicalVolume* BDSDetectorConstruction::ConstructBDS()
{

  // TheAccelerator=new AcceleratorType("clic","halo");
  //     TheAccelerator=new AcceleratorType("clic","normal");
  
  BDSAcceleratorType* TheAccelerator=BDSGlobals->GetAcceleratorType();

  // Read in the MAD decks:Linux-g++/BDS_run/BDSDetectorConstruction.o] Error 1
  // Construct the BDS beamline model


  BDSMADInterface mad(TheAccelerator->GetType()+"_BDS.optics",
		      TheAccelerator->GetBeamTotalEnergy() );
  
  G4cout<<" Beam total energy="<<TheAccelerator->GetBeamTotalEnergy()/GeV<<
    " GeV"<<G4endl;
  // ofstream madlog("construction.log");
  //mad.SetLogFile(madlog);
  theBeamline=mad.ConstructModel();
  
  list<BDSAcceleratorComponent*>::const_iterator iBeam;
  
  G4double s_tot=0.;
  G4double x_tot=0.;
  G4double z_tot=0.;
  G4double angle_tot=0.;
  
  // gab tmp
  SetMagField(0.); // necessary to set a global field; so chose zero
  
  // print out x vs z for the BDS (for graphics)
  G4double minX=0.*m;
  G4double minZ=0.*m;
  G4double maxX=0.*m;
  G4double maxZ=0.*m;
  
  for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
    {
      (*iBeam)->SetSPos(s_tot+(*iBeam)->GetLength()/2);
      s_tot+= (*iBeam)->GetLength();
      
      G4double ang=(*iBeam)->GetAngle();
      

      if(ang==0)
	{
	  x_tot+=(*iBeam)->GetLength()*sin(angle_tot);
	  z_tot+=(*iBeam)->GetLength()*cos(angle_tot);
	}
      else
	{
	  G4double LinLen=((*iBeam)->GetLength()/ang*2*sin(ang/2));
	  x_tot+=LinLen*sin(angle_tot+ang/2);
	  z_tot+=LinLen*cos(angle_tot+ang/2);
	  angle_tot+=ang;
	}
      if(z_tot>maxZ)maxZ=z_tot;
      if(x_tot>maxX)maxX=x_tot;
      if(z_tot<minZ)minZ=z_tot;
      if(x_tot<minX)minX=x_tot;
    }
  
  G4cout<<"minX="<<minX/m<<"m"<<" maxX="<<maxX/m<<" m"<<G4endl;
  G4cout<<"minZ="<<minZ/m<<"m"<<" maxZ="<<maxZ/m<<" m"<<G4endl;
  
  minX=abs(minX);
  minZ=abs(minZ);
  // for a ring (atf) negative x can have larger magnitude than the postive,
  // depending on when the ring begins
  if(minX>maxX)maxX=minX;
  if(minZ>maxZ)maxZ=minZ;
  
  // Determine the required relative angle of the tunnel:
  G4double tan_tilt=x_tot/z_tot;  
  
  BDSGlobals->SetGlobalBeamlineRotationY(atan(tan_tilt));
  
  BDSGlobals->SetTotalS(s_tot);
  
  // set default output formats:
  G4cout.precision(10);
  
  // -----------------------------------
  
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  // -----------------------------------
  // World dimensions:
  G4double WorldSizeZ=abs(z_tot)/2;
  BDSGlobals->SetWorldSizeZ(WorldSizeZ);
  
  G4double WorldRadius=1.5*BDSGlobals->GetTunnelRadius();
  
  // Set up a histogram to log the energy loss along z:
  G4cout<<"ztot="<<z_tot/m<<" m"<<G4endl;
  
  
  //  Int_t nBins=int(abs(z_tot)/m);
  //  const Double_t zMax=abs(z_tot)/m;
  //  const Double_t zMax=abs(z_tot)/m;
  BDSRoot->SetEnergyLossZMax(abs(z_tot));
  // gab to Root: HBOOK1(100,"Energy Loss",nBins,0.,abs(z_tot)/m,0);
  
  // gab to Root: HBOOK1(101,"brem event",nBins,0.,abs(z_tot)/m,0);
  //BDSRoot->h2=new TH1F("h2", "Brem event",nBins,0.,zMax);
  
  G4String LocalName="World";
  
  
  if(BDSGlobals->GetAcceleratorType()->GetType()!="atf")
    {
      if(WorldRadius<abs(x_tot)+BDSGlobals->GetComponentBoxSize())
	{G4Exception(" BDSDetectorConstruction:Tunnel radius too small");}
      solidWorld = new G4Box("World",WorldRadius,WorldRadius,
			     WorldSizeZ+1*cm);
    }
  else
    solidWorld = new G4Box("World",
			   maxX+2*BDSGlobals->GetComponentBoxSize(),
			   2*BDSGlobals->GetComponentBoxSize(),
			   maxZ+2*BDSGlobals->GetComponentBoxSize());
  
  logicWorld = new G4LogicalVolume(solidWorld,	       //its solid
				   // theMaterials->LCAir, //its material
				   theMaterials->LCVacuum, //its material
				   "World");	       //its name
  
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  
  G4UserLimits* WorldUserLimits =new G4UserLimits();
  WorldUserLimits->SetMaxAllowedStep(1000*m);



  logicWorld->SetUserLimits(WorldUserLimits);


  G4cout<<"Charged Thresholdcut="<<BDSGlobals->GetThresholdCutCharged()/GeV<<" GeV"<<G4endl;
  G4cout<<"Photon Thresholdcut="<<BDSGlobals->GetThresholdCutPhotons()/GeV<<" GeV"<<G4endl;

  physiWorld = new G4PVPlacement(0,			//no rotation
  				 ZeroVec,       	//at (0,0,0)
                                 LocalName,		//its name
                                 logicWorld,		//its logical volume
                                 NULL,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number


  //---------------------------------------
  if(BDSGlobals->GetAcceleratorType()->GetType()!="atf")
    {
      //build tunnel out of concrete:
      G4LogicalVolume* TunnelLogVol = 
	new G4LogicalVolume(new G4Tubs("Tunnel_solid",
				       BDSGlobals->GetTunnelRadius(),
				       1.5*BDSGlobals->GetTunnelRadius(),
				       WorldSizeZ,
				       0,twopi*radian),
			    theMaterials->LCConcrete,
			    "Tunnel");
      //  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
      TunnelLogVol->SetVisAttributes(new G4VisAttributes(G4Colour(0,1,1)));
      G4UserLimits* TunnelUserLimits =new G4UserLimits();
      TunnelUserLimits->SetMaxAllowedStep(1000*m);
      TunnelLogVol->SetUserLimits(TunnelUserLimits);
      
      G4PVPlacement* physiTunnel = 
	new G4PVPlacement(
			  // TunnelRot,	        //rotation
			  0,
			  ZeroVec,             	//at (0,0,0)
			  "Tunnel_phys",	//its name
			  TunnelLogVol,		//its logical volume
			  physiWorld,		//its mother  volume
			  false,		//no boolean operation
			  0);			//copy number
    }

  BDSEnergyCounterSD* ECounter=new BDSEnergyCounterSD("World");
  logicWorld->SetSensitiveDetector(ECounter);
  SDman->AddNewDetector(ECounter);
  theECList->push_back(ECounter);

  // build up the tunnel:
  G4bool use_graphics=true;
  G4double s_local=-s_tot/2.;
  G4double x,y,z;
  G4ThreeVector TargetPos;

  // set default output formats:
   G4cout.precision(15);
   
   G4cout<<" total length="<<s_tot/m<< " s_local="<<s_local/m<<G4endl;

   // reset counters:
   for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
     (*LogVolCount)[(*iBeam)->GetMarkerLogicalVolume()->GetName()]=1;

   G4double z_local;
   if(BDSGlobals->GetAcceleratorType()->GetType()!="atf")
     {
       angle_tot= -BDSGlobals->GetGlobalBeamlineRotationY();
       z_local=-z_tot/2;
     }
   else
     {
       angle_tot=0;
       z_local=0.;
     }
   
   G4double x_local= 0;
   G4double delta_x,delta_z;
   G4double LinLen;

  ofstream BDSOutline("BDSOutline.dat");
   for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
     { 
       (*iBeam)->SetZLower(z_local);

       G4double ang=(*iBeam)->GetAngle();
       if(ang!=0)
	 {
	   LinLen=((*iBeam)->GetLength()/ang)*2*sin(ang/2);
	   /* original
	   delta_x=LinLen*sin(angle_tot+ang/2);
	   */
	   delta_x=LinLen*sin(-angle_tot-ang/2);
	   delta_z=LinLen*cos(angle_tot+ang/2);
	 }
       else
	 {
	   LinLen=(*iBeam)->GetLength();
	   /* original
	   delta_x=LinLen*sin(angle_tot);
	   */
	   delta_x=LinLen*sin(-angle_tot);
	   delta_z=LinLen*cos(angle_tot);
	 }
       

       x=x_local+delta_x/2+BDSGlobals->GetHorizontalBeamlineOffset();
       y=BDSGlobals->GetVerticalBeamlineOffset();

       z=z_local+delta_z/2;
       
       TargetPos.setX(x);
       TargetPos.setY(y);
       TargetPos.setZ(z);

       BDSOutline<<x/m<<" "<<(z+WorldSizeZ)/m<<G4endl;

       G4RotationMatrix* RotateComponent=new G4RotationMatrix();

       if(ang!=0)
       // allow for the fact that trapezoids are defined along z-axis...
	 RotateComponent->rotateY(angle_tot+pi/2+ang/2);
       else
	 RotateComponent->rotateY(angle_tot);
       /* original:
       if(ang!=0)
       // allow for the fact that trapezoids are defined along z-axis...
	 RotateComponent->rotateY(-angle_tot-pi/2-ang/2);
       else
	 RotateComponent->rotateY(-angle_tot);
       */
       angle_tot+=ang;
       x_local+=delta_x;
       z_local+=delta_z;

       (*iBeam)->SetZUpper(z_local);

       G4LogicalVolume* LocalLogVol=(*iBeam)->GetMarkerLogicalVolume();
       G4String LogVolName=LocalLogVol->GetName();
       int nCopy=(*LogVolCount)[LogVolName]-1;
       (*LogVolCount)[LogVolName]++;
	  
       // set up the sensitive volumes for energy counting:
       (*iBeam)->SetCopyNumber(nCopy);
       G4LogicalVolume* SensVol=(*iBeam)->GetSensitiveVolume();
       if(SensVol)
	 {
	   BDSEnergyCounterSD* ECounter=new BDSEnergyCounterSD(LogVolName);
	   (*iBeam)->SetBDSEnergyCounter(ECounter);
	   SensVol->SetSensitiveDetector(ECounter);
	   SDman->AddNewDetector(ECounter);
	   theECList->push_back(ECounter);
	 }

       LocalName=(*iBeam)->GetName()+"_phys";

       //G4cout<<" name="<<LocalName<<" pos="<<TargetPos<<" angle_tot="<<
       //angle_tot<<G4endl;

       G4PVPlacement* PhysiComponentPlace = 
	 new G4PVPlacement(
			   RotateComponent,   //  rotation
			   TargetPos,         // its position
			   LocalName,	      // its name
			   LocalLogVol,	      // its logical volume
			   physiWorld,	      // its mother  volume
			   false,	      // no boolean operation
			   nCopy);	      // copy number

       if(use_graphics)
	 {
	    (*iBeam)->GetVisAttributes()->SetVisibility(true);
	   //(*iBeam)->GetVisAttributes()->SetVisibility(false);
	   //      (*iBeam)->GetVisAttributes()->SetForceSolid(true);
	   (*iBeam)->GetMarkerLogicalVolume()->
	     SetVisAttributes((*iBeam)->GetVisAttributes());
	 }   
     }

   /*
   for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
     {
       G4cout.precision(8); 
       G4cout<< (*iBeam)->GetName()<<" low z="<<
	 (*iBeam)->GetZLower()/m<<" upper z="<<(*iBeam)->GetZUpper()/m
	     <<G4endl;
     }
   */

   return physiWorld;

 
}

//=================================================================

void BDSDetectorConstruction::SetMagField(const G4double fieldValue)
{
  //  if(fieldValue!=0.)
  //  {
      //apply a global uniform magnetic field along Z axis
      G4FieldManager* fieldMgr 
	= G4TransportationManager::GetTransportationManager()->
	GetFieldManager();
      magField = new G4UniformMagField(G4ThreeVector(0.,fieldValue,0.));  
      fieldMgr->SetDetectorField(magField);
      fieldMgr->CreateChordFinder(magField);
      // }

}

//=================================================================
  
void BDSDetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructBDS());
}

//=================================================================
BDSDetectorConstruction::~BDSDetectorConstruction()
{ 
  delete BDSGlobals;
}

//=================================================================
