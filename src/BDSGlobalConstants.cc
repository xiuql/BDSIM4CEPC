/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.12.2004
   Copyright (c) 2004 by G.A.Blair.  ALL RIGHTS RESERVED. 

   Modified 22.03.05 by J.C.Carter, Royal Holloway, Univ. of London.
   Added GABs StringFromInt function
   Added GABs StringFromDigit function
   Added GABs SynchPrimary code
   Added GABs BeamGasPlug code
   Added GABs GetUseLastMaterialPoint method
   Added LWCal Code
*/

const int DEBUG = 1;

#include "BDSGlobalConstants.hh"

#include "G4UniformMagField.hh"

#include <cstdlib>

#include <assert.h>

#include<string>
#include<stack>

using namespace std;

G4double NumSpoilerRadLen=1.;

namespace 
{

BDSGlobalConstants::BDSGlobalConstants(struct Options& opt)
{

  // defaults:
  itsEnergyOffset=0.;
  itsVerboseEventNumber=0;
  itsTrackWeightFactor=1.0;


  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  itsBeamParticleDefinition= particleTable->FindParticle(G4String(opt.particleName));
  
  if(!itsBeamParticleDefinition) 
    {
      G4cerr<<"particle  "<<opt.particleName<<" not found, quitting!"<<G4endl;
      exit(1);
    }

  itsBeamTotalEnergy = opt.beamEnergy * GeV;

  itsBeamMomentum =sqrt(pow(itsBeamTotalEnergy,2)-
                        pow(itsBeamParticleDefinition->GetPDGMass(),2));

  itsBeamKineticEnergy=itsBeamTotalEnergy - itsBeamParticleDefinition->GetPDGMass();
  
  itsBeamGamma = itsBeamTotalEnergy/(itsBeamParticleDefinition->GetPDGMass());
  
  		
  if(DEBUG) G4cout<<"beam : "<<opt.particleName<<"  energy "<<itsBeamTotalEnergy<<
	      " ganna "<<itsBeamGamma<<G4endl;
	      
  itsBackgroundScaleFactor = opt.backgroundScaleFactor;

  itsComponentBoxSize = opt.componentBoxSize *m;

  itsTunnelRadius = opt.tunnelRadius * m;

  itsBeampipeRadius = opt.beampipeRadius * m;
  
  itsBeampipeThickness = opt.beampipeThickness * m;
    
  itsThresholdCutCharged = opt.thresholdCutCharged * GeV;

  itsThresholdCutPhotons = opt.thresholdCutPhotons * GeV;

  itsTrackWeightFactor = opt.trackWeightFactor;



  itsDeltaChord = opt.deltaChord * m;

  itsChordStepMinimum = opt.chordStepMinimum * m;

  itsDeltaIntersection= opt.deltaIntersection * m;



  itsTurnOnInteractions = opt.turnOnInteractions;

  itsUseLowEMPhysics = opt.useLowEMPhysics;

  itsSynchRadOn = opt.synchRadOn;

  itsSynchRescale = opt.synchRescale; // rescale due to synchrotron

  itsSynchTrackPhotons= opt.synchTrackPhotons;

  itsSynchPrimaryGen = 0;

  itsSynchLowX = opt.synchLowX;

  itsSynchLowGamE = opt.synchLowGamE * GeV;  // lowest gamma energy

  itsSynchPhotonMultiplicity = opt.synchPhotonMultiplicity;

  itsSynchMeanFreeFactor = opt.synchMeanFreeFactor;

  itsPlanckOn = opt.planckOn;

  itsBDSeBremOn = opt.eBremOn;

  itsLengthSafety = opt.lengthSafety * m;

  itsNumberOfParticles = opt.numberOfParticles;

  itsNumberToGenerate = opt.numberToGenerate;

  itsNumberOfEventsPerNtuple = opt.numberOfEventsPerNtuple;

  itsRandomSeed = opt.randomSeed;
 
  itsVerboseStep= opt.verboseStep;
  
  itsVerboseEventNumber = opt.verboseEventNumber;

  if(opt.useTimer) {
    itsTimer=new G4Timer();
    itsUseTimer = opt.useTimer;
  }  

  itsUseEMHadronic = opt.useEMHadronic;

  itsUseMuonPairProduction = opt.useMuonPairProduction;

  itsMuonProductionScaleFactor = opt.muonProductionScaleFactor;

  itsHadronInelasticScaleFactor = opt.hadronInelasticScaleFactor;

  itsStoreMuonTrajectories = opt.storeMuonTrajectories;
  itsStoreTrajectory = opt.storeTrajectory;

  G4cout<<"STOREA TRAJ = "<< itsStoreTrajectory<<G4endl;

  itsUseMuonShowers = opt.useMuonShowers;

  itsMuonLowestGeneratedEnergy = opt.muonLowestGeneratedEnergy * GeV;


  // tmp - parameters of the laserwire process - to be given in the element attributes

  itsLaserwireWavelength = 0.4 * micrometer;
  itsLaserwireDir = G4ThreeVector(1,0,0);
  itsLaserwireTrackPhotons = 1;
  itsLaserwireTrackElectrons = 1;


 //  else if(name=="INCLUDE_IRON_MAG_FIELDS")
//     {
//       _READ(itsIncludeIronMagFields);
//     }


//  else if(name  =="OUTPUT_NTUPLE_FILE_NAME")
//     {_READ(itsOutputNtupleFileName);}

//   else if(name=="NUMBER_OF_EVENTS_PER_NTUPLE")
//     {_READ(itsNumberOfEventsPerNtuple);}


//   else if(name=="USE_SYNCH_PRIMARY_GEN")
//     {
//       _READ(itsSynchPrimaryGen);
//     }
//   else if(name=="SYNCH_PRIMARY_GEN_ANGLE")
//     {
//       _READ(itsSynchPrimaryAngle);
//       itsSynchPrimaryAngle*=radian;
//     }
//   else if(name=="SYNCH_PRIMARY_GEN_LENGTH")
//     {
//       _READ(itsSynchPrimaryLength);
//       itsSynchPrimaryLength*=m;
//     }

//   else if(name=="USE_LAST_MATERIAL_POINT")
//     {
//       _READ(itsUseLastMaterialPoint);
//     }

//   else
//     {
//       G4cout<<" Unknown card in BDSInput.cards:"<<name<<G4endl;
//       G4Exception("BDSGlobalConstants: UNRECOGNISED CARD");
//     } 
 

  itsOutputNtupleFileName="sampler_output.rz";
  // end of defaults

  
  // default value (can be renamed later)

  G4UniformMagField* magField = new G4UniformMagField(G4ThreeVector());
  itsZeroFieldManager=new G4FieldManager();
  itsZeroFieldManager->SetDetectorField(magField);
  itsZeroFieldManager->CreateChordFinder(magField);
   
}


// a robust compiler-invariant method to convert from integer to G4String
G4String BDSGlobalConstants::StringFromInt(G4int N) 
{
  if (N==0) return "0";
 
  G4int nLocal=N, nDigit=0, nMax=1;

  do { nDigit++;
      nMax*=10;} while(N > nMax-1);
  
  nMax/=10;
  G4String Cnum;
  do {Cnum+=StringFromDigit(nLocal/nMax);
      nLocal-= nLocal/nMax * nMax;
      nMax/=10;}   while(nMax>1);
  if(nMax!=0)Cnum+=StringFromDigit(nLocal/nMax);

  return Cnum;
}

// a robust compiler-invariant method to convert from digit to G4String
G4String BDSGlobalConstants::StringFromDigit(G4int N) 
{
  if(N<0 || N>9)
    G4Exception("Invalid Digit in BDSGlobalConstants::StringFromDigit");

  G4String Cnum;

  if(N==0)Cnum="0";
  else if(N==1)Cnum="1";
  else if(N==2)Cnum="2";
  else if(N==3)Cnum="3";
  else if(N==4)Cnum="4";
  else if(N==5)Cnum="5";
  else if(N==6)Cnum="6";
  else if(N==7)Cnum="7";
  else if(N==8)Cnum="8";
  else if(N==9)Cnum="9"; 

  return Cnum;
}

BDSGlobalConstants::~BDSGlobalConstants()
{  
  if( (itsTimer!=NULL) && itsUseTimer) delete itsTimer;
}

}
