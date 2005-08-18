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

#include"G4Navigator.hh"
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
		      " k1 ="<<(*it).k1<<" b' ="<<bPrime<<" brho = "<<brho<<G4endl;
	}
	//theBeamline.push_back(new BDSDrift(G4String((*it).name),(*it).l * m,bpRad));
	theBeamline.push_back(new BDSQuadrupole(G4String((*it).name),(*it).l * m,bpRad,FeRad,bPrime));
      }
  
      if((*it).type==_SEXTUPOLE ) {
	bDoublePrime = brho * (*it).k2 / (*it).l * tesla / (m*m) * synch_factor;
	if(DEBUG) { G4cout<<"---->adding Sextupole, "<<G4String( (*it).name )<<
		      " k1 ="<<(*it).k2<<" b'' ="<<bDoublePrime<<" brho = "<<brho<<G4endl;
	}
	theBeamline.push_back(new BDSSextupole(G4String((*it).name),(*it).l * m,bpRad,FeRad,bDoublePrime));
      }

      if((*it).type==_ELEMENT ) {
	
	if(DEBUG) { G4cout<<"---->adding Element, "<<G4String( (*it).name )<<
		      " l ="<<(*it).l<<G4endl;
	}
	
	
	theBeamline.push_back(new BDSElement( G4String((*it).name) , G4String((*it).geometryFile), 
					      G4String((*it).bmapFile), (*it).l * m, bpRad ) );
      }
      
      if((*it).type==_ECOL ) {

	GetMaterial(aMaterial, (*it).material );

	if(DEBUG) { G4cout<<"---->adding Ecol, "<<G4String( (*it).name )<<G4endl<<
		      "xaper="<<(*it).xsize<<"m, yaper="<<(*it).ysize<<
		      "m, material="<<(*it).material<<G4endl;
	}

	
	G4cout<<"retrieved material :"<<aMaterial->GetName()<<G4endl;
	theBeamline.push_back(new BDSCollimator(G4String((*it).name),(*it).l * m,bpRad,
						(*it).xsize * m,(*it).ysize * m,_ECOL,aMaterial) );
      }
      if((*it).type==_RCOL ) {
	
	GetMaterial(aMaterial, (*it).material );

	if(DEBUG) { G4cout<<"---->adding Rcol, "<<G4String( (*it).name )<<G4endl<<
		      "xaper="<<(*it).xsize<<"m, yaper="<<(*it).ysize<<
		      "m, material="<<(*it).material<<G4endl;

	}

	G4cout<<"retrieved material :"<<aMaterial->GetName()<<G4endl;

	theBeamline.push_back(new BDSCollimator(G4String((*it).name),(*it).l * m,bpRad,
						(*it).xsize * m,(*it).ysize * m,_RCOL,aMaterial) );
      }
      if((*it).type==_LASER ) {
	
	if(DEBUG) { G4cout<<"---->adding Laser, "<<G4String( (*it).name )<<G4endl<<
		      "l="<<(*it).l/m<<"m, lambda="<<(*it).waveLength / m<<
		      "m, xSigma="<<(*it).xsize/m<<" ySigma="<<(*it).ysize<<
		      "m, xdir="<<(*it).xdir/m<<" ydir="<<(*it).ydir<<"m, zdir="<<(*it).zdir/m<<
		      G4endl;

	}

	G4ThreeVector direction = G4ThreeVector(1,0,0);
	G4ThreeVector position  = G4ThreeVector(0,0,0);
	
	theBeamline.push_back(new BDSLaserWire(G4String((*it).name),(*it).l * m,(*it).waveLength * m,
					       direction, position) );
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

  if(DEBUG) G4cout<<"now constructing geometry"<<G4endl;

  list<BDSAcceleratorComponent*>::const_iterator iBeam;
  
  G4double s_tot=0.;
  G4double x_tot=0.;
  G4double z_tot=0.;
  G4double angle_tot=0.;
  
  
  // print out x vs z for the BDS (for graphics)
  G4double minX=0.*m;
  G4double minZ=0.*m;
  G4double maxX=0.*m;
  G4double maxZ=0.*m;
  

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
	}

      if(z_tot>maxZ) maxZ=z_tot;
      if(x_tot>maxX) maxX=x_tot;
      if(z_tot<minZ) minZ=z_tot;
      if(x_tot<minX) minX=x_tot;
    }
    
  minX=fabs(minX);
  minZ=fabs(minZ);
  
  // for a ring (atf) negative x can have larger magnitude than the postive,
  // depending on when the ring begins
  if(minX>maxX) maxX = minX;
  if(minZ>maxZ) maxZ = minZ;
  
  // Determine the required relative angle of the tunnel:
  //G4double tan_tilt=x_tot/z_tot;  
  
  //BDSGlobals->SetGlobalBeamlineRotationY(atan(tan_tilt));
  
  BDSGlobals->SetTotalS(s_tot);
  
  // set default output formats:
  G4cout.precision(10);
  
  // -----------------------------------
  
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  
  // determine the world size
  
  G4String LocalName="World";
  
  G4double WorldSizeX = 1 * ( (fabs(minX) + fabs(maxX)) + BDSGlobals->GetComponentBoxSize());
  G4double WorldSizeY = BDSGlobals->GetComponentBoxSize();
  G4double WorldSizeZ = 1 * (fabs(minZ) + fabs(maxZ) + BDSGlobals->GetComponentBoxSize());
  
  //G4cout<<"world radius="<<WorldRadius/m<<" m"<<G4endl;
  G4cout<<"minX="<<minX/m<<"m"<<" maxX="<<maxX/m<<" m"<<G4endl;
  G4cout<<"minZ="<<minZ/m<<"m"<<" maxZ="<<maxZ/m<<" m"<<G4endl;
  G4cout<<"box size="<<BDSGlobals->GetComponentBoxSize()/m<<" m"<<G4endl;
  G4cout<<"s_tot="<<s_tot/m<<" m"<<G4endl;

  {
    solidWorld = new G4Box("World",WorldSizeX,WorldSizeY,
			   WorldSizeZ);
  }
  
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
   for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++){
     // JCC Mar05 - added IF to check that not resetting for Offset Component
     // This is the only component that should have a length of zero and yet
     // still be registered as an AcceleratorComponent
     
     //if(DEBUG) G4cout<<" resetting "<<(*iBeam)->GetName()<<G4endl;

     if((*iBeam)->GetLength()!=0.)
       {
	 G4String logVolName = (*iBeam)->GetMarkerLogicalVolume()->GetName();
	 //if(DEBUG) G4cout<<" alive "<<G4endl;
	 (*LogVolCount)[logVolName]=1;
       }
   }
   G4double z_local;
   //if(BDSGlobals->GetAcceleratorType()->GetType()!="atf")
     {
       angle_tot= 0;
       z_local = 0;
     }
   //   else
   //{
   //  angle_tot=0;
   //  z_local=0.;
   //}
   
   G4double x_local= 0;
   G4double delta_x,delta_z;
   G4double LinLen;

   if(DEBUG) G4cout<<"staring placement procedure "<<G4endl;

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
       //if(DEBUG) G4cout<<" hoi "<<G4endl;

       x=x_local+delta_x/2+BDSGlobals->GetHorizontalBeamlineOffset();
       y=BDSGlobals->GetVerticalBeamlineOffset();

       z=z_local+delta_z/2;
       
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
       x+=BDSGlobals->GetHorizontalComponentOffset();
       y+=BDSGlobals->GetVerticalComponentOffset();

       //if(DEBUG) G4cout<<" hoi "<<G4endl;

       // << JCC Mar05

       TargetPos.setX(x);
       TargetPos.setY(y);
       TargetPos.setZ(z);

       G4RotationMatrix* RotateComponent=new G4RotationMatrix();

       if(ang!=0)
       // allow for the fact that trapezoids are defined along z-axis...
	 RotateComponent->rotateY(angle_tot+pi/2+ang/2);
       else
	 RotateComponent->rotateY(angle_tot);


       // advance the coordinates, but not for cylindrical samplers 
       if( ( (*iBeam)->GetName() != "sampler") || ( (*iBeam)->GetLength() <= samplerLength )  )
	 {
	   angle_tot+=ang;
	   x_local+=delta_x;
	   z_local+=delta_z;
	 }

       (*iBeam)->SetZUpper(z_local);

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
	 
	 //if(DEBUG) G4cout<<" hoi "<<G4endl;

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

	 (*iBeam)->CreateFieldMesh(PhysiComponentPlace);

	 //if(DEBUG) G4cout<<" hoi "<<G4endl;

	 if(use_graphics)
	   {
	     (*iBeam)->GetVisAttributes()->SetVisibility(true);
	     //(*iBeam)->GetVisAttributes()->SetVisibility(false);
	     //      (*iBeam)->GetVisAttributes()->SetForceSolid(true);
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
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructBDS(beamline_list));
}

//=================================================================
BDSDetectorConstruction::~BDSDetectorConstruction()
{ 
  if(BDSGlobals) delete BDSGlobals;
}

//=================================================================
