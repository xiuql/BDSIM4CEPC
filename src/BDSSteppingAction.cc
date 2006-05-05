/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 25.12.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
 
   Modified 22.03.05 by J.C.Carter, Royal Holloway, Univ. of London.
   Added code for GABs BeamGasPlug
   Changed Killer to kill just electrons/positrons if called KILLERE

   Modified 10.05.05 IA
   Removed Killer element, added cuts per element check
   Can have killer functionality if cuts set to 0

*/


//====================================================
//  Class description here ...
//
//====================================================

#include "BDSGlobalConstants.hh" // must be first in include list

#include "BDSSteppingAction.hh"

#include <iostream>
#include "G4Track.hh"

#include"G4TransportationManager.hh"
#include"G4FieldManager.hh"

#include"G4Navigator.hh"
#include"G4StepPoint.hh"
#include "G4RotationMatrix.hh"
#include "G4AffineTransform.hh"

#include "BDSMaterials.hh"
#include "G4Material.hh"
#include "G4VSensitiveDetector.hh"
#include "Randomize.hh"

#include "G4UserLimits.hh"

#include "BDSNeutronTrackInfo.hh"

#include "G4VUserTrackInformation.hh"

#include "G4VProcess.hh"

#include "G4MagneticField.hh"
#include "G4EventManager.hh"
#include "G4StackManager.hh"
#include "G4ChordFinder.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4Region.hh"
#include "BDSAcceleratorComponent.hh"

#include "BDSQuadStepper.hh"
#include "BDSSextStepper.hh"
#include "BDSOctStepper.hh"
#include "myQuadStepper.hh"

extern BDSMaterials* theMaterials;

typedef list<BDSAcceleratorComponent*> BDSBeamline;
extern BDSBeamline theBeamline;

extern G4double BDS_Threshold_Energy;
extern G4double BDSLocalRadiusOfCurvature;

extern G4int event_number;

extern G4double initial_x,initial_xp,initial_y,initial_yp,initial_z,initial_E;

extern G4bool verbose;      // run options
extern G4bool verboseStep;
extern G4bool verboseEvent;
extern G4int verboseEventNumber;
extern G4bool isBatch;

extern G4int nptwiss;

//static G4LogicalVolume* LastLogVol;
//====================================================

BDSSteppingAction::BDSSteppingAction()
{ 
  //  itsZposTolerance=1.e-11*m;
  itsZposTolerance=1.e-4*m;
  itsPosKick=1.e-11*m;
  itsNmax=10000;
  postponedEnergy=0;
}

//====================================================

BDSSteppingAction::~BDSSteppingAction()
{ }


//====================================================

extern G4double htot;

void BDSSteppingAction::UserSteppingAction(const G4Step* ThisStep)
{ 
  // G4cout<<"user stepping action called"<<G4endl;

  G4Track* ThisTrack=ThisStep->GetTrack();
  
  G4int TrackID=ThisTrack->GetTrackID();
  
  G4String pName=ThisTrack->GetDefinition()->GetParticleName();

  if(ThisTrack->GetProperTime() > 1e-5*second)
    {
      G4cout << "WARNING: ProperTime > 1 second!" << G4endl;
      G4cout<<" Killing the particle"<<G4endl;
      ThisTrack->SetTrackStatus(fStopAndKill);
    }
  
  // Check for a problem at the boundaries, where an infinite loop can
  // apparently sometimes occur
  

  // leave Geant4 to take care of it 

 //  if(TrackID!=itsLastTrackID)
//     {
//       itsLastTrackID=TrackID;
//       itsNtry=0;
//     }
//   else 
//     { 
//       if(fabs(ThisTrack->GetPosition().z()-itsLastZpos)<itsZposTolerance)
// 	{
// 	  itsNtry++;
// 	  if(itsNtry>itsNmax)
// 	    {
// 	      G4cout<<" Killing the particle"<<G4endl;
// 	      ThisTrack->SetTrackStatus(fStopAndKill);
// 	      /* ThisTrack->
// 		SetPosition(
// 			    ThisTrack->GetPosition()+
// 			    ThisTrack->GetMomentumDirection()*itsPosKick
// 			    ); */
// 	      //	      itsNtry=0;
// 	    }
// 	}
//       else 	
// 	itsNtry=0;
//     }


  itsLastZpos=ThisTrack->GetPosition().z();
  


  // check that there actually is a next volume as it may be the end of the optics line
  if(BDSGlobals->GetSynchRescale() && ThisTrack->GetNextVolume()) 
    {
      G4int curr_delim = ThisTrack->GetVolume()->GetName().find("_");
      G4String curr_gmad_name = ThisTrack->GetVolume()->GetName().substr(0,curr_delim);
      G4int delim = ThisTrack->GetNextVolume()->GetName().find("_");
      G4String gmad_name = ThisTrack->GetNextVolume()->GetName().substr(0,delim);
      if (curr_gmad_name != gmad_name && gmad_name!="World")
      //      if(ThisTrack->GetVolume()->GetName().contains("samp"))
	{ 
	  //G4cout << curr_gmad_name << " " << gmad_name << G4endl;
	  G4ThreeVector pos = ThisTrack->GetPosition();
	  postponedEnergy+=ThisTrack->GetTotalEnergy();
	  	  
	  G4StackManager* SM = G4EventManager::GetEventManager()->GetStackManager();

	  if(SM->GetNPostponedTrack()!= nptwiss-1 ) { 
	    // postpone track and save its coordinates for twiss fit
	    ThisTrack->SetTrackStatus(fPostponeToNextEvent);

	    G4ThreeVector pos=ThisTrack->GetPosition();
	    G4ThreeVector momDir=ThisTrack->GetMomentumDirection();

	    // Get Translation and Rotation of Sampler Volume w.r.t the World Volume
	    G4AffineTransform tf(ThisTrack->GetTouchable()->GetHistory()->GetTopTransform().Inverse());
	    const G4RotationMatrix Rot=tf.NetRotation();
	    const G4ThreeVector Trans=-tf.NetTranslation();
	    
	    G4ThreeVector LocalPosition=pos+Trans; 
	    G4ThreeVector LocalDirection=Rot*momDir; 


	  //   G4cout<<"postponed track: "<<SM->GetNPostponedTrack()<<G4endl;
// 	    G4cout<<"r: "<<LocalPosition<<G4endl;
// 	    G4cout<<"rp: "<<LocalDirection<<G4endl;
	    //x.push_back(
	  }

	  if(SM->GetNPostponedTrack()== nptwiss-1)
	    {
	      SM->TransferStackedTracks(fPostpone, fUrgent);
	      if(verbose) G4cout << "\nMean Energy: " << (postponedEnergy/nptwiss)/GeV << G4endl;

	      list<BDSAcceleratorComponent*>::const_iterator iBeam;
	      G4String type="";	      
	      for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
		{ 
		  if( (*iBeam)->GetName() == gmad_name)
		    {
		      type = (*iBeam)->GetType();
		      if(verbose) G4cout << "Next Element is: " << (*iBeam)->GetName() << G4endl;
		      if(verbose) G4cout << "Element Type: " << type << G4endl;
		      G4double old_P0 = BDSGlobals->GetBeamTotalEnergy();
		      G4double old_brho = 
			sqrt(pow(old_P0,2)- pow(electron_mass_c2,2))/(0.299792458 * (GeV/(tesla*m)));
		      G4double new_P0 = postponedEnergy/nptwiss;
		      G4double new_brho = 
			sqrt(pow(new_P0,2)- pow(electron_mass_c2,2))/(0.299792458 * (GeV/(tesla*m)));
		      
		      if(BDSGlobals->GetSynchRescale()) 
			{
			  (*iBeam)->SynchRescale(new_brho/old_brho);
			  
			  if(verbose) G4cout << "Rescaling by: " << new_brho/old_brho << G4endl;
			  G4cout << "*";
			  G4cout.flush();
			}
		      break;
		    }
		}
	      postponedEnergy=0;
	    }
	  return;
	}
    }

  
  // ------------  output in case of verbose step ---------------------


  if(verboseStep && (!BDSGlobals->GetSynchRescale()) )
    {

	/*
	  
	  htot+=ThisStep->GetStepLength();
	  // set default output formats:
	  G4cout.precision(10);
	  G4double  theta=htot/BDSLocalRadiusOfCurvature;
	  if(abs(BDSLocalRadiusOfCurvature*(1.-cos(theta))-
	   ThisTrack->GetPosition().x())>1.e-7)
	   G4cout<<"htot_step="<<htot<<" implied x="<<
	   BDSLocalRadiusOfCurvature*(1.-cos(theta))/m
	   <<"true x="<<ThisTrack->GetPosition().x()/m<<G4endl;
	   
	   G4cout<<"step length="<< ThisStep->GetStepLength()/m<<" m"<<G4endl;
	*/
	
	//G4cout<<"angle="<<ThisStep->GetPreStepPoint()->GetMomentumDirection().angle
	//  (ThisStep->GetPostStepPoint()->GetMomentumDirection())<<G4endl;
	
	
	
	int ID=ThisTrack->GetTrackID();
	//       	if(ID==1){
	//G4Navigator* StepperNavigator=G4TransportationManager::
	//GetTransportationManager()->GetNavigatorForTracking();
	//	G4ThreeVector LocalPosVec = StepperNavigator->GetCurrentLocalCoordinate();
	
	// if((abs(LocalPosVec.x())>1.*mm)&&(ThisTrack->GetVolume()->
	//				    GetLogicalVolume()->GetName())!="World" )
	//{

	G4cout.precision(10);
	G4cout<<"This volume="<< ThisTrack->GetVolume()->GetName()<<G4endl;
	  //" Loc pos x="<<LocalPosVec[0]/m<<"y= "<<LocalPosVec[1]/m<<
	  //" z="<< LocalPosVec[2]/m <<G4endl;
	
	G4LogicalVolume* LogVol=ThisTrack->GetVolume()->GetLogicalVolume();
	G4cout<<"This log volume="<<LogVol->GetName() <<G4endl;
	
	G4cout<<"ID="<<ID<<" part="<<
	  ThisTrack->GetDefinition()->GetParticleName()<<
	  "Energy="<<ThisTrack->GetTotalEnergy()/GeV<<
	  " mom Px="
	      <<ThisTrack->GetMomentum()[0]/GeV<<
	  " Py="<<ThisTrack->GetMomentum()[1]/GeV<<
	  " Pz="<<ThisTrack->GetMomentum()[2]/GeV<<" vol="<<
	  ThisTrack->GetVolume()->GetName()<<G4endl;
	
	G4cout<<" Global Position="<<ThisTrack->GetPosition()<<G4endl;
	
	
	if(ThisTrack->GetMaterial()->GetName() !="LCVacuum")
	  G4cout<<"material="<<ThisTrack->GetMaterial()->GetName()<<G4endl;
	//	G4Exception(" wrong material");
	

	  G4VProcess* proc=(G4VProcess*)(ThisStep->GetPostStepPoint()->
	    GetProcessDefinedStep() );

       	  if(proc)G4cout<<" post-step process="<<proc->GetProcessName()<<G4endl<<G4endl;


	  proc=(G4VProcess*)(ThisStep->GetPreStepPoint()->
	    GetProcessDefinedStep() );

       	  if(proc)G4cout<<" pre-step process="<<proc->GetProcessName()<<G4endl<<G4endl;

	

      }


  // -------------  kill tracks according to cuts -------------------
  
  /*
  G4VProcess* proc=ThisStep->GetPostStepPoint()->GetProcessDefinedStep();
  G4cout<<pName<<" weight="<<ThisTrack->GetWeight()<<" ID="<<
    ThisTrack->GetTrackID()<<" parentID="<< ThisTrack->GetParentID()<<G4endl;
  if(proc)G4cout<<" process="<<proc->GetProcessName()<<G4endl<<G4endl;
  */

  // this cuts apply to default region

  G4LogicalVolume* LogVol=ThisTrack->GetVolume()->GetLogicalVolume();
  G4Region* reg = LogVol->GetRegion();

  //G4cout<<"I am in "<<reg->GetName()<<G4endl;

  if(reg->GetName() != "precision")
    {
      
      
      if(pName=="gamma")
	{
	  G4double photonCut = BDSGlobals->GetThresholdCutPhotons();
	  
	  if(ThisTrack->GetTotalEnergy()<photonCut)
	    {
	      //ThisTrack->SetKineticEnergy(0.);
	      ThisTrack->SetTrackStatus(fStopAndKill);
	      //ThisTrack->SetBelowThresholdFlag();
	    }
	}
      
      if(pName=="e-"||pName=="e+")
	{
	  if(ThisTrack->GetTotalEnergy()<BDSGlobals->GetThresholdCutCharged())
	    {
	      //	  ThisTrack->SetKineticEnergy(0.);
	      ThisTrack->SetTrackStatus(fStopAndKill);
	      //ThisTrack->SetBelowThresholdFlag();
	    }
	}
      
    }
  
  /*
    if(pName=="mu+"||pName=="mu-")
    {
    G4cout<<"muon: mom="<<ThisTrack->GetMomentum()<<" vol="<<
    ThisTrack->GetVolume()->GetName()
    <<" weight="<<ThisTrack->GetWeight() <<G4endl;	
    }
  */
  
  
  if(pName=="neutron" && ThisTrack->GetMaterial()->GetName() =="LCVacuum")
    {
      
      /*
	G4VUserTrackInformation* Info=ThisTrack->GetUserInformation();

      if(Info)
	{
	  BDSNeutronTrackInfo* InfoBDS= static_cast<BDSNeutronTrackInfo*>
	    (ThisTrack->GetUserInformation());
	  if(!InfoBDS->GetIsLogged())
	    {
	      G4float r[3];
	      r[0]=ThisTrack->GetKineticEnergy()/eV; 
	      r[1]= (ThisTrack->GetPosition().z()+
		     BDSGlobals->GetWorldSizeZ())/m;
	      r[2]=ThisTrack->GetMomentum().z()/MeV; 
	      // gab to root:	      HFN(101,r);
	      
	      InfoBDS->SetIsLogged(true);
	    }
	}
      */
      // at this stage only interested in production
      //ThisTrack->SetKineticEnergy(0.);
      //ThisTrack->SetTrackStatus(fStopAndKill);
      G4String procName=ThisTrack->GetCreatorProcess()->GetProcessName();
      if((procName!="PhotonInelastic")&&(procName!="NeutronInelastic")
	 &&(procName!="ElectroNuclear"))
	G4cout<<procName<<G4endl;
      
    }
  

	  //	  G4cout<<"material="<<ThisTrack->GetMaterial()->GetName()<<G4endl;

	  /*
  // temp code for laserwire studies:
  if(ThisTrack->GetMaterial()->GetName() =="LCIron"   ||
     ThisTrack->GetMaterial()->GetName() =="LCCopper"  )
    {
       ThisTrack->SetTrackStatus(fStopAndKill);
       G4double eTrack=ThisTrack->GetKineticEnergy();
       //ThisStep->AddTotalEnergyDeposit(eTrack);
      //ThisTrack->SetBelowThresholdFlag(true);
    }
	  */
}

//====================================================



