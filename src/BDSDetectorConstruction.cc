/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 

   Modified 22.03.05 by J.C.Carter, Royal Holloway, Univ. of London.
   Added GAB include for BDSBeamPipe.hh
   Added GAB Gas Plug Code
   Added X Y Offset code
*/


const int DEBUG = 1;

//=================================================================
//=================================================================
#include "BDSGlobalConstants.hh"

#include "BDSDetectorConstruction.hh"

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

#include "G4Navigator.hh"
#include "G4UniformMagField.hh"

#include "G4Material.hh"
#include "BDSEnergyCounterSD.hh"

// elements
#include "BDSBeamPipe.hh"
#include "BDSSectorBend.hh"
#include "BDSQuadrupole.hh"
#include "BDSDrift.hh"
#include "BDSSkewSextupole.hh"
#include "BDSSextupole.hh"
#include "BDSOctupole.hh"
#include "BDSDecapole.hh"
#include "BDSKiller.hh"
#include "BDSSampler.hh"
#include "BDSSpoiler.hh"
#include "BDSAbsorber.hh"

#include "BDSLaserWire.hh"
#include "BDSLWCalorimeter.hh"

#include "BDSMuSpoiler.hh"
#include "BDSBlock.hh"
#include "BDSWedge.hh"
#include "BDSTransform3D.hh"
#include "BDSElement.hh"
#include "BDSSamplerCylinder.hh"
#include "BDSComponentOffset.hh"

#include "mySectorBend.hh"
#include "BDSCollimator.hh"

// output interface
#include "BDSOutput.hh"


//#include "BDSMultipoleOuterMagField.hh"
#include "G4MagneticField.hh"

// GMAD interface
#include "parser/gmad.h"

extern void GetMaterial(G4Material *&theMaterial, G4String material); //from ggmad

//====================================

typedef list<BDSAcceleratorComponent*>  BDSBeamline;
BDSBeamline theBeamline;

typedef list<BDSEnergyCounterSD*>  ECList;
ECList* theECList;

BDSMaterials* theMaterials;

extern BDSGlobalConstants* BDSGlobals;

//--------------------------
// SYNCHROTRON RAD ***
G4double BDSLocalRadiusOfCurvature=DBL_MAX;// Used in Mean Free Path calc.
//--------------------------

G4Material* aMaterial;
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

extern BDSOutput bdsOutput;

//=================================================================



BDSDetectorConstruction::BDSDetectorConstruction()
{  // create commands for interactive definition of the beamline  
  G4double pi_ov_2 = asin(1.);

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

  theMaterials=new BDSMaterials();

  aMaterial=theMaterials->LCGraphite; // default collimator material

  if(DEBUG) G4cout<<"-->starting BDS construction \n"<<G4endl;

  return ConstructBDS(beamline_list);
}


G4VPhysicalVolume* BDSDetectorConstruction::ConstructBDS(list<struct Element>& beamline_list)
{
  
  // set default output formats:
  G4cout.precision(10);
  
  
  // convert the parsed element list to list of BDS elemenst
  
  list<struct Element>::iterator it;
  
  BDSBeamline theBeamline;
  
  // set global magnetic field first
  SetMagField(0.0); // necessary to set a global field; so chose zero
  
  
  // radius of curvature (!!!!! valid for electrons only???!!!!)
  G4double P0 = BDSGlobals->GetBeamTotalEnergy();
  //G4double m_c2 = BDSGlobals->Get
  // magnetic rigidity
  G4double brho=
    sqrt(pow(P0,2)- pow(electron_mass_c2,2))/(0.299792458 * (GeV/(tesla*m)));

  G4double bField;

  // beampipe radius
  G4double bpRad=BDSGlobals->GetBeampipeRadius();
  // ???
  G4double FeRad = bpRad;
  
  // quadrupole field gradient
  G4double bPrime;
  // sectupole field coef.
  G4double bDoublePrime;
  
  // stuff for rescaling due to synchrotron radiation, IGNORING
  G4double synch_factor = 1;
  G4double samplerLength = 1.E-8 * m;

  if(DEBUG) G4cout<<"bpRad , m : "<<bpRad / m <<G4endl;

  for(it = beamline_list.begin();it!=beamline_list.end();it++)
    {
      if(DEBUG) G4cout<<(*it).name<<"    "<<typestr((*it).type)<<"  "<<(*it).l<<G4endl;
           
      if((*it).type==_SAMPLER ) {
	if(DEBUG) G4cout<<"---->adding Sampler "<<G4String( (*it).name )<<G4endl;
	
	theBeamline.push_back(new BDSSampler( G4String( (*it).name ) , samplerLength ) );
	bdsOutput.nSamplers++;
      }

      if((*it).type==_CSAMPLER ) {
	if(DEBUG) G4cout<<"---->adding CSampler "<<G4String( (*it).name )<<G4endl;
	
	if( (*it).l < 1.E-4 * m ) (*it).l = 1.0 * m; // replace short cylinders with 1 meter cylinders

	theBeamline.push_back(new BDSSamplerCylinder( G4String( (*it).name ) , (*it).l * m , (*it).r * m) );
	bdsOutput.nSamplers++;
      }

      if((*it).type==_DRIFT ) {
	if(DEBUG) G4cout<<"---->adding Drift "<<G4String( (*it).name )<<" l="<<(*it).l<<G4endl;
	if((*it).l > 0) // skip zero-length drift-defined elements
	  theBeamline.push_back(new BDSDrift(G4String((*it).name),(*it).l * m,bpRad));
      }
      
      if((*it).type==_SBEND ) {
	bField = brho * (*it).angle / (*it).l * tesla * synch_factor;
	bPrime = brho * (*it).k1 * tesla / m * synch_factor;
	
	if(DEBUG) G4cout<<"---->adding Sbend "<<G4String( (*it).name )<<"  l= "<<(*it).l<<
		    " angle="<<(*it).angle<<G4endl;
	
	if( fabs((*it).angle) < 1.e-7 * rad ) {
	  theBeamline.push_back(new BDSDrift(G4String((*it).name),(*it).l * m,bpRad));
	} 
	else {
	  theBeamline.push_back(new mySectorBend((*it).name,(*it).l * m,bpRad,FeRad,bField,
						 bPrime,(*it).angle));
	  //theBeamline.push_back(new BDSSectorBend((*it).name,(*it).l * m,bpRad,FeRad,bField,(*it).angle));
	}
      }

      if((*it).type==_QUAD ) {
	
	//bPrime = brho * (*it).k1 / (*it).l * tesla  * synch_factor;
	bPrime = brho * (*it).k1 * tesla / m * synch_factor;
	if(DEBUG) { G4cout<<"---->adding Quad, "<<G4String( (*it).name )<<
		      " k1 ="<<(*it).k1<<" b' ="<<bPrime<<" brho = "<<brho<<G4endl; }

	//theBeamline.push_back(new BDSDrift(G4String((*it).name),(*it).l * m,bpRad));
	theBeamline.push_back(new BDSQuadrupole(G4String((*it).name),(*it).l * m,bpRad,FeRad,bPrime));
      }
      
      if((*it).type==_SEXTUPOLE ) {
	bDoublePrime = brho * (*it).k2 / (*it).l * tesla / (m*m) * synch_factor;
	if(DEBUG) { G4cout<<"---->adding Sextupole, "<<G4String( (*it).name )<<
		      " k1 ="<<(*it).k2<<" b'' ="<<bDoublePrime<<" brho = "<<brho<<G4endl;}
	theBeamline.push_back(new BDSSextupole(G4String((*it).name),(*it).l * m,bpRad,FeRad,bDoublePrime));
      }
      
      if((*it).type==_ELEMENT ) {
	
	if(DEBUG) { G4cout<<"---->adding Element, "<<G4String( (*it).name )<<
		      " l ="<<(*it).l<<G4endl;}
	
	
	theBeamline.push_back(new BDSElement( G4String((*it).name) , G4String((*it).geometryFile), 
					      G4String((*it).bmapFile), (*it).l * m, bpRad ) );
      }

      if((*it).type==_SOLENOID ) {
	
	if(DEBUG) { G4cout<<"---->adding Solenoid, "<<G4String( (*it).name )<<
		      " l ="<<(*it).l<<G4endl;}
	
	
	//theBeamline.push_back(new BDSElement( G4String((*it).name) , G4String((*it).geometryFile), 
	//			      G4String((*it).bmapFile), (*it).l * m, bpRad ) );
      }
      
      if((*it).type==_ECOL ) {
	
	GetMaterial(aMaterial, (*it).material );
	
	if(DEBUG) { G4cout<<"---->adding Ecol, "<<G4String( (*it).name )<<G4endl<<
		      "xaper="<<(*it).xsize<<"m, yaper="<<(*it).ysize<<
		      "m, material="<<(*it).material<<G4endl;}

	
	G4cout<<"retrieved material :"<<aMaterial->GetName()<<G4endl;
	theBeamline.push_back(new BDSCollimator(G4String((*it).name),(*it).l * m,bpRad,
						(*it).xsize * m,(*it).ysize * m,_ECOL,aMaterial) );
      }
      if((*it).type==_RCOL ) {
	
	GetMaterial(aMaterial, (*it).material );

	if(DEBUG) { G4cout<<"---->adding Rcol, "<<G4String( (*it).name )<<G4endl<<
		      "xaper="<<(*it).xsize<<"m, yaper="<<(*it).ysize<<
		      "m, material="<<(*it).material<<G4endl;}

	G4cout<<"retrieved material :"<<aMaterial->GetName()<<G4endl;

	theBeamline.push_back(new BDSCollimator(G4String((*it).name),(*it).l * m,bpRad,
						(*it).xsize * m,(*it).ysize * m,_RCOL,aMaterial) );
      }
      if((*it).type==_LASER ) {
	
	if(DEBUG) { G4cout<<"---->adding Laser, "<<G4String( (*it).name )<<G4endl<<
		      "l="<<(*it).l/m<<"m, lambda="<<(*it).waveLength / m<<
		      "m, xSigma="<<(*it).xsize/m<<" ySigma="<<(*it).ysize<<
		      "m, xdir="<<(*it).xdir/m<<" ydir="<<(*it).ydir<<"m, zdir="<<(*it).zdir/m<<
		      G4endl; }
	
	G4ThreeVector direction = G4ThreeVector(1,0,0);
	G4ThreeVector position  = G4ThreeVector(0,0,0);
	
	theBeamline.push_back(new BDSLaserWire(G4String((*it).name),(*it).l * m,(*it).waveLength * m,
					       direction, position) );
	
	
	}
      if((*it).type==_TRANSFORM3D ) {
	
	if(DEBUG) { G4cout<<"---->adding Transform3d, "<<G4String( (*it).name )<<G4endl<<
		      "m, xdir="<<(*it).xdir/m<<" ydir="<<(*it).ydir<<"m, zdir="<<(*it).zdir/m<<
		      "m, phi="<<(*it).phi/rad<<" theta="<<(*it).theta/rad<<" psi="<<(*it).psi/rad<<
		      G4endl; }
	
	theBeamline.push_back(new BDSTransform3D(G4String((*it).name),(*it).xdir *m,(*it).ydir *m,
						 (*it).zdir *m, (*it).phi * rad, (*it).theta*rad,(*it).psi*rad ));
	
      }
      
      
      //   else if(type=="SEXTUPOLE") 
      //     ctor->push_back( new BDSSextupole(name,len,bpRad,FeRad,bDoublePrime));
      //   else if(type=="SKEWSEXT") 
      //     ctor->push_back(new BDSSkewSextupole(name,len,bpRad,FeRad,bDoublePrime));
      //   else if(type=="OCTUPOLE") 
      //     ctor->push_back(new BDSOctupole(name,len,bpRad,FeRad,bTriplePrime));
      //   else if(type=="DECAPOLE") 
      //     ctor->push_back(new BDSDecapole(name,len,bpRad,FeRad,bQuadPrime));
      //   else if(type=="KILLER")
      //     ctor->push_back(new BDSKiller(name,len));
      //   else if(type=="LASERWIRE")
      //     {
      //       BDSLaserWire* TheBDSLaserWire=
      // 	new BDSLaserWire(name,len,BDSGlobals->GetLaserwireWavelength(),
      // 			 BDSGlobals->GetLaserwireDir());
      //       ctor->push_back(TheBDSLaserWire);
      //     }
      //   else if(type=="LWCAL")
      //     ctor->push_back(new BDSLWCalorimeter(name,len,bpRad));
      //   else if(type=="BLOCK")
      //     ctor->push_back(new BDSBlock(name,len));
      //   else if(type=="RESETTER") 
      //     ctor->push_back(new BDSResetter(name,len));
      //   else if(type=="SAMPCYLNDR")
      //     ctor->push_back(new BDSSamplerCylinder(name,len,radius));
      
      
    }
  
  // free the parser list
  
  G4cout<<"size of parser list: "<< beamline_list.size() << G4endl;;
  beamline_list.clear();
  
  
  
  // construct the component list
  
  if(DEBUG) G4cout<<"now constructing geometry"<<G4endl;
  
  list<BDSAcceleratorComponent*>::const_iterator iBeam;
  
  
  G4ThreeVector rtot = G4ThreeVector(0.,0.,0.);  //world dimension
  G4ThreeVector rlast = G4ThreeVector(0.,0.,0.);  // edge of last element coordinates
  G4ThreeVector rmin = G4ThreeVector(0.,0.,0.);
  G4ThreeVector rmax = G4ThreeVector(0.,0.,0.);

  //G4RotationMatrix localRotation; // rotation of local coordinate system, initially unit

  G4ThreeVector localX = G4ThreeVector(1,0,0);  // local coordinate axis
  G4ThreeVector localY = G4ThreeVector(0,1,0);
  G4ThreeVector localZ = G4ThreeVector(0,0,1);

  G4double s_tot = 0; // position along the beamline

  // define geometry scope
  for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
    {

      if(DEBUG) G4cout<<(*iBeam)->GetName()<<"  "<<(*iBeam)->GetLength()<<
		  "  "<<(*iBeam)->GetAngle()<<G4endl;

      (*iBeam)->SetSPos(s_tot+(*iBeam)->GetLength()/2);

      // advance coordinates , but not for cylindrical sampler
      if(( (*iBeam)->GetName() != "sampler") || ( (*iBeam)->GetLength() <= samplerLength ) )
	{
	  s_tot+= (*iBeam)->GetLength();

	  rtot += localZ * (*iBeam)->GetLength()/2;

	  G4double angle=(*iBeam)->GetAngle();
	  G4double theta=(*iBeam)->GetTheta();

	  // define new coordinate system local frame	  
	  localX.rotate(-angle,localY);
	  localY.rotate(-angle,localY);
	  localZ.rotate(-angle,localY);

	  localX.rotate(theta,localX);
	  localY.rotate(theta,localX);
	  localZ.rotate(theta,localX);

	  // advance the coordinate system translation
	  rtot+= localZ *  (*iBeam)->GetLength();

	}

      if(rmax(0)>rtot(0)) rmax(0) = rtot(0);
      if(rmax(1)>rtot(1)) rmax(1) = rtot(1);
      if(rmax(2)>rtot(2)) rmax(2) = rtot(2);

      if(rmax(0)<rtot(0)) rmin(0) = rtot(0);
      if(rmin(1)<rtot(1)) rmin(1) = rtot(1);
      if(rmin(2)<rtot(2)) rmin(2) = rtot(2);
    }
    
  
  BDSGlobals->SetTotalS(s_tot);
  
  // -----------------------------------
  
  // determine the world size
  
  G4String LocalName="World";
  
  G4double WorldSizeX = 1 * ( (fabs(rmin(0)) + fabs(rmax(0)) ) + 2*BDSGlobals->GetComponentBoxSize());
  G4double WorldSizeY = 1 * ( (fabs(rmin(1)) + fabs(rmax(1)) ) + 2*BDSGlobals->GetComponentBoxSize());
  G4double WorldSizeZ = 1 * ( (fabs(rmin(2)) + fabs(rmax(2)) ) + 2*BDSGlobals->GetComponentBoxSize());
  
  //G4cout<<"world radius="<<WorldRadius/m<<" m"<<G4endl;
  G4cout<<"minX="<<rmin(0)/m<<"m"<<" maxX="<<rmax(0)/m<<" m"<<G4endl;
  G4cout<<"minY="<<rmin(1)/m<<"m"<<" maxY="<<rmax(1)/m<<" m"<<G4endl;
  G4cout<<"minZ="<<rmin(2)/m<<"m"<<" maxZ="<<rmax(2)/m<<" m"<<G4endl;

  G4cout<<"box size="<<BDSGlobals->GetComponentBoxSize()/m<<" m"<<G4endl;
  G4cout<<"s_tot="<<s_tot/m<<" m"<<G4endl;

  solidWorld = new G4Box("World",WorldSizeX,WorldSizeY,
			   WorldSizeZ);
    
  logicWorld = new G4LogicalVolume(solidWorld,	       //its solid
				   // theMaterials->LCAir, //its material
				   theMaterials->LCVacuum, //its material
				   "World");	       //its name
  
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  // set world volume visibility for debugging
  if(DEBUG) logicWorld->SetVisAttributes(new G4VisAttributes(true));
  
  G4UserLimits* WorldUserLimits =new G4UserLimits();
  WorldUserLimits->SetMaxAllowedStep(1000*m);



  logicWorld->SetUserLimits(WorldUserLimits);


  G4cout<<"Charged Thresholdcut="<<BDSGlobals->GetThresholdCutCharged()/GeV<<" GeV"<<G4endl;
  G4cout<<"Photon Thresholdcut="<<BDSGlobals->GetThresholdCutPhotons()/GeV<<" GeV"<<G4endl;

  // world

  physiWorld = new G4PVPlacement(0,			//no rotation
  				 ZeroVec,       	//at (0,0,0)
                                 LocalName,		//its name
                                 logicWorld,		//its logical volume
                                 NULL,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number



  // Think of building tunnel later!!!
  //---------------------------------------
 //  //if(BDSGlobals->GetAcceleratorType()->GetType()!="atf")
//     {
//       //build tunnel out of concrete:
//       G4LogicalVolume* TunnelLogVol = 
// 	new G4LogicalVolume(new G4Tubs("Tunnel_solid",
// 				       BDSGlobals->GetTunnelRadius(),
// 				       1.5*BDSGlobals->GetTunnelRadius(),
// 				       WorldSizeZ,
// 				       0,twopi*radian),
// 			    theMaterials->LCConcrete,
// 			    "Tunnel");
//       //  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
//       TunnelLogVol->SetVisAttributes(new G4VisAttributes(G4Colour(0,1,1)));
//       G4UserLimits* TunnelUserLimits =new G4UserLimits();
//       TunnelUserLimits->SetMaxAllowedStep(1000*m);
//       TunnelLogVol->SetUserLimits(TunnelUserLimits);
      
//       G4PVPlacement* physiTunnel = 
// 	new G4PVPlacement(
// 			  // TunnelRot,	        //rotation
// 			  0,
// 			  ZeroVec,             	//at (0,0,0)
// 			  "Tunnel_phys",	//its name
// 			  TunnelLogVol,		//its logical volume
// 			  physiWorld,		//its mother  volume
// 			  false,		//no boolean operation
// 			  0);			//copy number
//     }


  // densitive detectors

  G4SDManager* SDman = G4SDManager::GetSDMpointer();


  BDSEnergyCounterSD* ECounter=new BDSEnergyCounterSD("World");
  logicWorld->SetSensitiveDetector(ECounter);
  SDman->AddNewDetector(ECounter);
  theECList->push_back(ECounter);

  G4bool use_graphics=true;
  G4double s_local=-s_tot/2.;
  G4ThreeVector TargetPos;

  // set default output formats:
  G4cout.precision(15);
  
  G4cout<<" total length="<<s_tot/m<< " s_local="<<s_local/m<<G4endl;
  
  // reset counters:
  for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++){
    // JCC Mar05 - added IF to check that not resetting for Offset Component
    // This is the only component that should have a length of zero and yet
    // still be registered as an AcceleratorComponent

    // IA - Offset changed to Transform3D
    
    if((*iBeam)->GetLength()!=0.)
      {
	G4String logVolName = (*iBeam)->GetMarkerLogicalVolume()->GetName();
	(*LogVolCount)[logVolName]=1;
      }
  }
  
   if(DEBUG) G4cout<<"staring placement procedure "<<G4endl;
  
  rtot = G4ThreeVector(0.,0.,0.);
  localX = G4ThreeVector(1.,0.,0.); 
  localY = G4ThreeVector(0.,1.,0.);
  localZ = G4ThreeVector(0.,0.,1.);

  G4RotationMatrix globalRotation;

  for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
    { 
      //(*iBeam)->SetZLower(rtot.z());
     
      
      G4double angle=(*iBeam)->GetAngle();
      G4double theta=(*iBeam)->GetTheta();
      G4double psi = (*iBeam)->GetPsi();

      // define new coordinate system local frame	  
     
      globalRotation.rotate(angle,localY);

      G4ThreeVector zHalfAngle = localZ; // for sectro bedn - through half angle
      zHalfAngle.rotate(-angle/2, localY);

      G4ThreeVector oldZ = localZ; 

      localX.rotate(-angle,localY);
      localZ.rotate(-angle,localY);
      
      globalRotation.rotate(theta,localX);

      localY.rotate(theta,localX);
      localZ.rotate(theta,localX);

      if( (*iBeam)->GetType() == "transform3d")
	{
	  rtot(0) += (*iBeam)->GetXOffset(); 
	  rtot(1) += (*iBeam)->GetYOffset(); 
	  rtot(2) += (*iBeam)->GetZOffset(); 

	  globalRotation.rotate(psi,localZ);

	  localX.rotate(psi,localZ);
	  localY.rotate(psi,localZ);
	  localZ.rotate(psi,localZ);

	  rlast(0) += (*iBeam)->GetXOffset();
	  rlast(1) += (*iBeam)->GetYOffset(); 
	  rlast(2) += (*iBeam)->GetZOffset(); 
	  //G4cout<<"transform3d:   x = "<<rtot<<G4endl;

	  continue;
	}
      
             
      // JCC Mar05 XY Offset Code>>
      if((*iBeam)->GetLength()==0.)
	{
	  BDSGlobals->AddHorizontalComponentOffset((*iBeam)->GetXOffset());
	  BDSGlobals->AddVerticalComponentOffset((*iBeam)->GetYOffset());
	  G4cout << "Component Offset in X now set to: ";
	  G4cout << BDSGlobals->GetHorizontalComponentOffset() << G4endl;
	  G4cout << "Component Offset in Y now set to: ";
	  G4cout << BDSGlobals->GetVerticalComponentOffset() << G4endl;
	}
            
      
      // placement position
      //if(angle == 0)
      TargetPos = rlast + zHalfAngle *  (*iBeam)->GetLength()/2;
      //else
      //TargetPos = rlast +  localZ / sin(angle/2) * ( (*iBeam)->GetLength()) * angle;
      
      G4RotationMatrix* RotateComponent=new G4RotationMatrix(globalRotation); // for component placement

      if((angle!=0) && ((*iBeam)->GetType() != "transform3d"))
	{
	// allow for the fact that trapezoids are defined along z-axis...
	  RotateComponent->rotate(pi/2-angle/2,localY);

	  // determine where the face goes and translate the origin accordingly

	  //G4Vector difv = TargetPos - rlast;
	  //difv.rotate

	}

      // advance the coordinates, but not for cylindrical samplers 
      if( ( (*iBeam)->GetName() != "sampler") || ( (*iBeam)->GetLength() <= samplerLength )  )
	{
	  //if( theta ==0 && angle == 0) // sector bend
	    {
	      rtot = rlast + zHalfAngle *  (*iBeam)->GetLength()/2;
	      rlast = rtot + zHalfAngle *  (*iBeam)->GetLength()/2;
	      
	    }
	    //else // transform 3d
	    //{
	    //  rtot = rlast +  localZ * sin(angle/2) * ( (*iBeam)->GetLength()) / angle;
	    //  rlast = rtot +  localZ * sin(angle/2) * ( (*iBeam)->GetLength()) / angle;
	    //}
	}
      
      //(*iBeam)->SetZUpper(rtot.z());
      
      // JCC Mar05 - Added IF to check for CMPOFFSET by checking against
      // the Beamline Components Length. CMPOFFSET is only component that
      // should have length =0
      if((*iBeam)->GetLength()!=0.){
	
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
	
	G4PVPlacement* PhysiComponentPlace = 
	  new G4PVPlacement(
			    RotateComponent,   //  rotation
			    TargetPos,         // its position
			    LocalName,	      // its name
			    LocalLogVol,	      // its logical volume
			    physiWorld,	      // its mother  volume
			    false,	      // no boolean operation
			    nCopy);	      // copy number
	
	(*iBeam)->CreateFieldMesh(PhysiComponentPlace);
	
	if(use_graphics)
	  {
	    (*iBeam)->GetVisAttributes()->SetVisibility(true);
	    //(*iBeam)->GetVisAttributes()->SetForceSolid(true);
	    (*iBeam)->GetMarkerLogicalVolume()->
	      SetVisAttributes((*iBeam)->GetVisAttributes());
	  }
	
      }
    }
  
  if(DEBUG) G4cout<<"end placement, size="<<theBeamline.size()<<G4endl;
  
  
  return physiWorld;
  
}

  
  
  //=================================================================

void BDSDetectorConstruction::SetMagField(const G4double fieldValue)
{
 
  G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->
	GetFieldManager();
  magField = new G4UniformMagField(G4ThreeVector(0.,fieldValue,0.));  
  fieldMgr->SetDetectorField(magField);
  fieldMgr->CreateChordFinder(magField);

}

//=================================================================
  
void BDSDetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructBDS(beamline_list));
}

//=================================================================
BDSDetectorConstruction::~BDSDetectorConstruction()
{ 
  if(BDSGlobals) delete BDSGlobals;
}

//=================================================================
