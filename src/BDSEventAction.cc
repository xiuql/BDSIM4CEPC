/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//


//======================================================
//======================================================
#include "BDSGlobalConstants.hh" // must be first in include list

// link to G4eBremsstrahlung.cc and G4GammaConversion.cc for muon studies
extern G4bool BDSeBremsFiredThisEvent;
extern G4double BDSeBremFireDist;

#include "BDSEventAction.hh"

//#include "BDSCalorHit.hh"
#include "BDSEventActionMessenger.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

#include "G4FieldManager.hh"
#include "G4ChordFinder.hh"

#include "BDSSampler.hh"
#include "BDSSamplerHit.hh"
#include "BDSEnergyCounterHit.hh"

#include "BDSLWCalorimeter.hh"
#include "BDSLWCalorimeterHit.hh"
#include "BDSRootObjects.hh"
#include "BDSSynchrotronRadiation.hh"

#include "BDSAcceleratorComponent.hh"
typedef list<BDSAcceleratorComponent*>  BDSBeamline;
extern BDSBeamline theBeamline;

#include "BDSRootObjects.hh"

typedef std::vector<G4int> MuonTrackVector;
MuonTrackVector* theMuonTrackVector;

typedef std::map<G4String,int> LogVolCountMap;
extern LogVolCountMap* LogVolCount;

typedef list<BDSEnergyCounterSD*>  ECList;
extern ECList* theECList;

extern G4double BDSeBremFireDist;
extern G4double BDSeBremZMin,BDSeBremZMax;


// gab tmp:
//extern G4String LastVolName;
//extern G4ThreeVector LastPos;
//extern G4ThreeVector LastMom;

// gab tmp
G4double htot;

G4int event_number;

G4bool FireLaserCompton;


//======================================================

BDSEventAction::BDSEventAction()
:SamplerCollID(-1),drawFlag("all"),
 eventMessenger(NULL),LWCalorimeterCollID(-1)
{  eventMessenger = new BDSEventActionMessenger(this);
 if(BDSGlobals->GetWriteBunchFile())
   {BunchOutputFile=new ofstream("Bunch.output");}
 else BunchOutputFile=NULL;

 if(BDSGlobals->GetUseBatch())printModulo=1000;
 else printModulo=1;

 itsOutputFileNumber=0;

 itsRecordSize=1024;


 LastComp=NULL;
}

//======================================================

BDSEventAction::~BDSEventAction()
{
  delete eventMessenger;  
}

//======================================================

void BDSEventAction::BeginOfEventAction(const G4Event* evt)
{
  
 event_number = evt->GetEventID();
 htot=0.;

 if(BDSGlobals->GetStoreMuonTrajectories())
   theMuonTrackVector=new MuonTrackVector();


 if(BDSGlobals->GetBDSeBremOn())
   {
     // first reset all the step lengths
     for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
       (*iBeam)->GetInnerBPUserLimits()->
	 SetMaxAllowedStep((*iBeam)->GetLength());

     //   if(LastComp)
     //     {
     //     if(LastComp->GetInnerBPUserLimits())
     //       {
     // LastComp->GetInnerBPUserLimits()->
     //   SetMaxAllowedStep(LastComp->GetLength());
     

     
     BDSeBremFireDist=BDSGlobals->GetTotalS()*(0.5-G4UniformRand());
     BDSeBremsFiredThisEvent=false;
     
     // determine which Log volume the event occurs
     
     for(iBeam=theBeamline.begin();iBeam!=theBeamline.end();iBeam++)
       {
	 if( ((*iBeam)->GetZLower()<BDSeBremFireDist)&&
	     ((*iBeam)->GetZUpper()>BDSeBremFireDist)  )
	   {
	     BDSeBremZMin=(*iBeam)->GetZLower();
	     BDSeBremZMax=(*iBeam)->GetZUpper();	 

	     G4double MaxStep=BDSeBremFireDist-(*iBeam)->GetZLower()-1*cm;
	     if(MaxStep<1*mm)MaxStep=1*mm;
	     (*iBeam)->GetInnerBPUserLimits()->
	       SetMaxAllowedStep(MaxStep);
	   }
       }
   }

 if (event_number == 0)
   {

     G4String filename=BDSGlobals->GetOutputNtupleFileName()+"_"+
       StringFromInt(itsOutputFileNumber++)+".root";
     BDSRoot->SetupNewFile(filename);

     // old paw stuff
     //G4String filename=BDSGlobals->GetOutputNtupleFileName()+"_"+
     //  StringFromInt(itsOutputFileNumber++)+".rz";
     //BDSPaw->SetupNewFile(filename);
     // old paw stuff
     //  G4int istat;
     //  StringFromInt(itsOutputFileNumber++)+".rz";
     //  char* cfile=filename.data();
     //  G4String pawD="sampler"+StringFromInt(itsOutputFileNumber);
     //  char* pawDir=pawD.data();
     //  char* pawDir="sampler";
     //  HROPEN(itsOutputFileNumber,pawDir,cfile,"N",itsRecordSize,istat);

   }

 if ((event_number+1)%printModulo == 0)
   { 
         G4cout << "\n---> Begin of event: " << event_number ;
	 if(BDSGlobals->GetUseTimer())
	   { 
	     BDSGlobals->GetTimer()->Stop();
	     G4cout<<" Time: "<<*BDSGlobals->GetTimer();
	     BDSGlobals->GetTimer()->Start();
	   }
	 G4cout<<G4endl;
   }
 
 G4SDManager * SDman = G4SDManager::GetSDMpointer();

 if(BDSRoot->GetSamplerNumber()>0){   
   if (SamplerCollID==-1) 
     SamplerCollID = SDman->GetCollectionID("SamplerCollection");
 }
 if(BDSRoot->GetLWCalorimeterNumber()>0){
   if (LWCalorimeterCollID==-1) 
     LWCalorimeterCollID = SDman->GetCollectionID("LWCalorimeterCollection");
 }
 FireLaserCompton=true;
}

//======================================================

void BDSEventAction::EndOfEventAction(const G4Event* evt)
{


  G4SDManager * SDman = G4SDManager::GetSDMpointer();

  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  
  BDSSamplerHitsCollection*  SampHC=NULL;
  BDSLWCalorimeterHitsCollection* LWCalHC=NULL;
  BDSEnergyCounterHitsCollection* BDSEnergyCounter_HC=NULL;

  if(SamplerCollID>=0)
    SampHC=(BDSSamplerHitsCollection*)(HCE->GetHC(SamplerCollID));
  
  if(LWCalorimeterCollID>=0) 
    LWCalHC=(BDSLWCalorimeterHitsCollection*)(HCE->GetHC(LWCalorimeterCollID));
  
  for(iEC=theECList->begin();iEC!=theECList->end();iEC++)
    {
      G4String name=(*iEC)->GetCollectionName(0);
      
      G4int BDSEnergyCounter_ID= SDman->GetCollectionID(name);
      
      if(BDSEnergyCounter_ID>=0)
	{
	  BDSEnergyCounter_HC=
	    (BDSEnergyCounterHitsCollection*)(HCE->GetHC(BDSEnergyCounter_ID));
	  if(BDSEnergyCounter_HC) 
	    {
	      G4int n_hit = BDSEnergyCounter_HC->entries();
	      //G4float r[2];
	      for (G4int i=0;i<n_hit;i++)
		{
		  G4double Energy=(*BDSEnergyCounter_HC)[i]->GetEnergy();
		  G4double EWeightZ=(*BDSEnergyCounter_HC)[i]->
		    GetEnergyWeightedPosition()/Energy;
		  //r[0]=Energy/GeV;
		  //r[1]=(EWeightZ+BDSGlobals->GetWorldSizeZ())/m;
		  //		  HF1(100,r[1],r[0]);
	       
		  BDSRoot->h1->
		    Fill((EWeightZ+BDSGlobals->GetWorldSizeZ())/m,
			  Energy/GeV);
		}
	    }
	}
    }
  
  if (SampHC)
    {
      G4int n_hit = SampHC->entries();
      // G4int nSampler;
      //      G4float r[14];
      for (G4int i=0;i<n_hit;i++)
	{
	  BDSRoot->LoadSamplerTree((*SampHC)[i]);

	  
	  // tmp
	  //	  if(sqrt(pow(r[6],2)+pow(r[8],2))<0.1)
	  // tmp
	  //if((*SampHC)[i]->GetPDGtype()!=11)
	  //	    HFN(nSampler,r);


	  //	 G4cout<<nSampler<<"r[6]= "<<r[6]<<G4endl;

	  if(BunchOutputFile)
	    {
	      G4cout.precision(6);
	      *BunchOutputFile<<(*SampHC)[i]->GetMom()/GeV
			      <<" "
			      <<(*SampHC)[i]->GetX()/micrometer
			      <<" "
			      <<(*SampHC)[i]->GetY()/micrometer
			      <<" "
			      <<(*SampHC)[i]->GetZ()/micrometer
			      <<" "
			      <<(*SampHC)[i]->GetXPrime()/(1.e-6*radian)
			      <<" "
			      <<(*SampHC)[i]->GetYPrime()/(1.e-6*radian)
			      <<G4endl;
	    }
	}
    }

  if (LWCalHC)
    {
      G4int nLWCal_hit = LWCalHC->entries();
      for (G4int i=0;i<nLWCal_hit;i++){ 
	BDSRoot->LoadLWCalorimeterTree((*LWCalHC)[i]);
      }
    }	

  if ((event_number+1)%BDSGlobals->GetNumberOfEventsPerNtuple() == 0)
    { 
      gDirectory->Write();
      BDSRoot->theRootOutputFile->Close();
      if ((event_number+1)==BDSGlobals->GetNumberToGenerate())
	BDSRoot->theRootOutputFile=NULL;
      else
	{
	  G4String filename=BDSGlobals->GetOutputNtupleFileName()+"_"+
	    StringFromInt(itsOutputFileNumber++)+".root";
	  BDSRoot->SetupNewFile(filename);
	}      
    }

  // Save interesting trajectories:
  G4TrajectoryContainer* TrajCont=evt->GetTrajectoryContainer();
  if(!TrajCont)return;

  
  TrajectoryVector* TrajVec=TrajCont->GetVector();
  if(BDSGlobals->GetStoreMuonTrajectories()&& TrajVec)
    {
      G4int tID;
      G4TrajectoryPoint* TrajPoint;
      G4ThreeVector TrajPos;  
      G4bool storeTraj;
      if(TrajVec)
	{
	  TrajectoryVector::iterator iT;
	  for(iT=TrajVec->begin();iT<TrajVec->end();iT++)
	    {
	      G4Trajectory* Traj=(G4Trajectory*)(*iT);
	      tID=Traj->GetTrackID();	      
	      storeTraj=false;
	      for(G4int i=0;i<theMuonTrackVector->size();i++)
		if((*theMuonTrackVector)[i]==tID)
		  storeTraj=true;

	      if(storeTraj)
		{
		  BDSRoot->BuildTrajectoryTree();
		  
		  for(G4int j=0; j<Traj->GetPointEntries(); j++)
		    {
		      TrajPoint=(G4TrajectoryPoint*)Traj->GetPoint(j);
		      TrajPos=TrajPoint->GetPosition();
		      BDSRoot->LoadTrajectoryTree(&TrajPos);
		      G4cout<<"TrajPos="<<TrajPos<<G4endl;
		    }
		}
	      else
		{// trajectory not a muon - so delete it
		  delete Traj;
		  TrajVec->erase(iT);
		  iT--;
		}
	    }
	}
      delete theMuonTrackVector;
    }

// needed to draw trajectories and hits:
      if(!BDSGlobals->GetUseBatch())evt->Draw();

      // clear out the remaining trajectories
      TrajectoryVector::iterator iT;
      if(TrajVec)
	{
	  for(iT=TrajVec->begin();iT<TrajVec->end();iT++)
	    {
	      G4Trajectory* Traj=(G4Trajectory*)(*iT);
	      delete Traj;
	      TrajVec->erase(iT);
	      iT--;
	    }
	}
}


G4String BDSEventAction::StringFromInt(G4int N)
{
  //JCC 02/07/04
  //char* CharN;
  char CharN[50];
  sprintf(CharN,"%d",N);
  G4String Cnum(CharN);
  return Cnum;
}


//======================================================
