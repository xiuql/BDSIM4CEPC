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

#include "BDSMaterials.hh"
#include "G4Material.hh"
#include "G4VSensitiveDetector.hh"
#include "Randomize.hh"

#include "G4UserLimits.hh"

#include "BDSNeutronTrackInfo.hh"

#include "G4VUserTrackInformation.hh"

#include "G4VProcess.hh"


#include "G4MagneticField.hh"

extern BDSMaterials* theMaterials;


extern G4double BDS_Threshold_Energy;
extern G4double BDSLocalRadiusOfCurvature;

extern G4int event_number;

extern G4double initial_x,initial_xp,initial_y,initial_yp,initial_z,initial_E;

extern G4bool verbose;      // run options
extern G4bool verboseStep;
extern G4bool verboseEvent;
extern G4int verboseEventNumber;
extern G4bool isBatch;




//static G4LogicalVolume* LastLogVol;
//====================================================

BDSSteppingAction::BDSSteppingAction()
{ 
  //  itsZposTolerance=1.e-11*m;
  itsZposTolerance=1.e-4*m;
  itsPosKick=1.e-11*m;
  itsNmax=10000;
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

  // Check for a problem at the boundaries, where an infinite loop can
  // apparently sometimes occur


  if(TrackID!=itsLastTrackID)
    {
      itsLastTrackID=TrackID;
      itsNtry=0;
    }
  else 
    { 
      if(abs(ThisTrack->GetPosition().z()-itsLastZpos)<itsZposTolerance)
	{
	  itsNtry++;
	  if(itsNtry>itsNmax)
	    {
	      G4cout<<" Killing the particle"<<G4endl;
	      ThisTrack->SetTrackStatus(fStopAndKill);
	      /* ThisTrack->
		SetPosition(
			    ThisTrack->GetPosition()+
			    ThisTrack->GetMomentumDirection()*itsPosKick
			    ); */
	      //	      itsNtry=0;
	    }
	}
      else 	
	itsNtry=0;
    }


  itsLastZpos=ThisTrack->GetPosition().z();


  // Killer - obsolete
  //if(ThisTrack->GetVolume()->GetName()=="KILLER_phys")
  //  ThisTrack->SetTrackStatus(fStopAndKill);

  //G4String pName1=ThisTrack->GetDefinition()->GetParticleName();
  //if(ThisTrack->GetVolume()->GetName()=="KILLERE_phys"&&pName1=="e+")
  //  ThisTrack->SetTrackStatus(fStopAndKill);
  //if(ThisTrack->GetVolume()->GetName()=="KILLERE_phys"&&pName1=="e-")
  //  ThisTrack->SetTrackStatus(fStopAndKill);


  // for electrons (and positrons) store the last point where they
  // were not in vacuum - ie, the last point of scatter

  G4String LocMatName=ThisTrack->GetMaterial()->GetName();
  
  if( (BDSGlobals->GetUseLastMaterialPoint()&& LocMatName!="LCVacuum")||
      (LocMatName=="LCReset"))
    {
      const G4RotationMatrix* Rot=
	ThisTrack->GetVolume()->GetFrameRotation();
      const G4ThreeVector Trans=
	ThisTrack->GetVolume()->GetFrameTranslation();
      
      G4ThreeVector momDir=ThisTrack->GetMomentumDirection();
      G4ThreeVector LocalPosition=ThisTrack->GetPosition()+Trans; 
      
      G4ThreeVector LocalDirection;
      if(Rot)
	LocalDirection=(*Rot)*momDir; 
      else
	LocalDirection=momDir; 
      
      initial_x =LocalPosition.x();
      initial_xp=LocalDirection.x() ;
      initial_y =LocalPosition.y();
      initial_yp=LocalDirection.y();
      initial_z = ThisTrack->GetPosition().z();
      initial_E=ThisTrack->GetTotalEnergy() ;
    }
  
  

  /*
  // tmp gab 25.04.04
  G4VProcess* proc=ThisStep->GetPostStepPoint()->GetProcessDefinedStep();
  if(proc)
    {
      G4String procName=proc->GetProcessName();
  
      if(procName!="BDSTransportationProcess")
	{
       	  G4cout<<" post-step process="<<procName<<G4endl<<G4endl;
	  G4cout<<"This volume="<< ThisTrack->GetVolume()->GetName()<<G4endl;
	  //" Loc pos x="<<LocalPosVec[0]/m<<"y= "<<LocalPosVec[1]/m<<
	  //" z="<< LocalPosVec[2]/m <<G4endl;
	  
	  G4LogicalVolume* LogVol=ThisTrack->GetVolume()->GetLogicalVolume();
	  G4cout<<"This log volume="<<LogVol->GetName() <<G4endl;
	  
	  G4cout<<" part="<<
	    ThisTrack->GetDefinition()->GetParticleName()<<
	    "Energy="<<ThisTrack->GetTotalEnergy()/GeV<<
	    " mom Px="
		<<ThisTrack->GetMomentum()[0]/GeV<<
	    " Py="<<ThisTrack->GetMomentum()[1]/GeV<<
	    " Pz="<<ThisTrack->GetMomentum()[2]/GeV<<" vol="<<
	    ThisTrack->GetVolume()->GetName()<<G4endl;
      
	  G4cout<<" Global Position="<<ThisTrack->GetPosition()<<G4endl;
	}
    }
  */

  
  /*
    if(ThisTrack->GetDefinition()->GetParticleName()=="mu+"||
    ThisTrack->GetDefinition()->GetParticleName()=="mu-")
    {G4cout<<" pos="<<ThisTrack->GetPosition()<< " mat="
    <<ThisTrack->GetMaterial()->GetName()<<G4endl;}
  */
  /*
    // tmp code to show what happens to primary only
    if(ThisTrack->GetTrackID()!=1)
    {
    ThisTrack->SetKineticEnergy(0.);
    ThisTrack->SetTrackStatus(fStopAndKill);
    }
  */
  
  
  /*    // tmp
    if(ThisTrack->GetTrackID()==1
    //       &&       ThisTrack->GetTotalEnergy()>2*GeV
       && ThisTrack->GetMaterial()->GetName()!="LCVacuum"
       )
       {
       G4cout<<"This volume="<< ThisTrack->GetVolume()->GetName()<<G4endl;
       
       G4cout<<" material="<<ThisTrack->GetMaterial()->GetName()<<
       " rad len="<<ThisTrack->GetMaterial()->GetRadlen()/m<<" m"<<G4endl;
       
	
       G4LogicalVolume* LogVol=ThisTrack->GetVolume()->GetLogicalVolume();
       
       
       
       G4cout<<"ID="<<ThisTrack->GetTrackID()<<" part="<<
       ThisTrack->GetDefinition()->GetParticleName()<<
       "Energy="<<ThisTrack->GetTotalEnergy()/GeV<<
       " mom Px="
       <<ThisTrack->GetMomentum()[0]/GeV<<
       " Py="<<ThisTrack->GetMomentum()[1]/GeV<<
       " Pz="<<ThisTrack->GetMomentum()[2]/GeV<<" vol="<<
	  ThisTrack->GetVolume()->GetName()<<G4endl;
	  
	  G4cout<<" Global Position="<<ThisTrack->GetPosition()<<G4endl;
	  
	  G4VProcess* proc=ThisStep->GetPreStepPoint()->
	  GetProcessDefinedStep();
	  
	  if(proc)G4cout<<" process="<<proc->GetProcessName()<<G4endl;
	  
	  G4Exception(" particle crashing");
      }
 
  */
  

  
  //  G4cout<<ThisTrack->GetMaterial()->GetName()<<G4endl;
  
  /*
    G4cout<<ThisTrack->GetVolume()->GetLogicalVolume()->GetName()<<
    " fieldMgr="<<ThisTrack->GetVolume()->GetLogicalVolume()->
    GetFieldManager()<<G4endl;
  */
  
  /*
    // gab tmp:
    G4double ElapsedTime;
    if(BDSGlobals->GetUseTimer())
    {
    BDSGlobals->GetTimer()->Stop();
    ElapsedTime=BDSGlobals->GetTimer()->GetRealElapsed();
    //      G4cout<<"RUN Elapsed time="<<*BDSGlobals->GetTimer()<<G4endl;
    if(ElapsedTime>0.001)
    G4cout<<"STEP Elapsed time="<<ElapsedTime <<
    " volume="<< ThisStep->GetTrack()->GetVolume()->GetName()<<G4endl;
    BDSGlobals->GetTimer()->Start();
    }
    
    
    
    
    
    
    if(ThisTrack->GetMaterial()->GetName()=="LCWeightIron")
    {
    if(ThisTrack->GetDefinition()->GetParticleName()!="gamma")
    {      
    G4cout<<" LCWeightIron "<<
    ThisTrack->GetDefinition()->GetParticleName()
    <<" mom="<<ThisTrack->GetMomentum()<<G4endl;
    //  G4cout<<" weight="<<ThisTrack->GetWeight()<<G4endl;
    }
    }
    
  */
  
  // total energy deposit 
  //  if(ThisTrack->GetMaterial()->GetName()!="LCVacuum")
  //   G4cout<<" Edep="<<ThisStep->GetTotalEnergyDeposit()/GeV<<
  //	" Vol="<<ThisTrack->GetVolume()->GetName()<<G4endl;


  
  //  if(part!="e-"&& part!="e+"&& part!="gamma")
  //  G4cout<<part<<"Energy="<<ThisTrack->GetTotalEnergy()/GeV<<" GeV"<<G4endl;



  
  // ------------  output in case of verbose step ---------------------


  if(verboseStep)
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



