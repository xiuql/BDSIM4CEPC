/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
 
/* Modifications to BDSSynchrotronRadiation physics process
   Author of Mods: John Carter, Royal Holloway, Univ. of London
   Date: 16.11.2004
   Description: Modified to improve efficiency of process. It is now possible 
		to use BDSInput.cards to create a given number of photons 
		each time (rather than one) using SYNCH_PHOTON_MULTIPLICITY

		Also modified to break up the meanfree path length into a given
		number of smaller lengths. Use the following BDSInput.card
		flag, SYNCH_MEANFREE_FACTOR
*/



#ifndef BDSSynchrotronRadiation_h
#define BDSSynchrotronRadiation_h 1

#include "BDSGlobalConstants.hh"

#include "G4ios.hh" 
#include "globals.hh"
#include "Randomize.hh" 
#include "G4VDiscreteProcess.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4OrderedTable.hh" 
#include "G4PhysicsTable.hh"
#include "G4PhysicsLogVector.hh"
#include "BDSComptonEngine.hh"
#include "BDSMaterials.hh"
#include "Randomize.hh"

#include "G4ChordFinder.hh"
#include "G4FieldManager.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4FieldTrack.hh"

#include "G4MagIntegratorDriver.hh"



extern BDSMaterials* theMaterials;
extern G4double BDSLocalRadiusOfCurvature;
 
class BDSSynchrotronRadiation : public G4VDiscreteProcess 
{ 
public:
 
  BDSSynchrotronRadiation(const G4String& processName = "BDSSynchRad");
 
  ~BDSSynchrotronRadiation();

  G4bool IsApplicable(const G4ParticleDefinition&);
     
  G4double GetMeanFreePath(const G4Track& track,
			   G4double previousStepSize,
			   G4ForceCondition* condition );
 
  G4VParticleChange *PostStepDoIt(const G4Track& track,         
				  const G4Step&  step);                 

  G4double SynGenC(G4double xmin);
  G4double SynRadC(G4double x);

protected:

private:

  BDSSynchrotronRadiation & operator=(const BDSSynchrotronRadiation &right);
     
  BDSSynchrotronRadiation(const BDSSynchrotronRadiation&);

  G4double nExpConst;
  G4double CritEngFac;
  G4int MeanFreePathCounter;

private:
};

inline G4bool 
BDSSynchrotronRadiation::IsApplicable(const G4ParticleDefinition& particle)
{
  return(  (&particle == G4Electron::Electron())
	   ||(&particle == G4Positron::Positron()) );
}

inline G4double 
BDSSynchrotronRadiation::GetMeanFreePath(const G4Track& track,
					G4double PreviousStepSize,
					G4ForceCondition* ForceCondition)
{  
  *ForceCondition = NotForced ;

  //   static G4FieldManager* lastFieldManager;

  G4double MeanFreePath;
  G4FieldManager* TheFieldManager=
    track.GetVolume()->GetLogicalVolume()->GetFieldManager();

  if(track.GetTotalEnergy()<BDSGlobals->GetThresholdCutCharged())
    return DBL_MAX;
  /*
  G4double SynchOnZPos = (7.184+4.0) * m;
  if(track.GetPosition().z() + BDSGlobals->GetWorldSizeZ() < SynchOnZPos)
    return DBL_MAX;
  */
  if(TheFieldManager)
    {
      const G4Field* pField = TheFieldManager->GetDetectorField() ;
      G4ThreeVector  globPosition = track.GetPosition() ;
      G4double  globPosVec[3], FieldValueVec[3] ;
      globPosVec[0] = globPosition.x() ;
      globPosVec[1] = globPosition.y() ;
      globPosVec[2] = globPosition.z() ;
      
      if(pField)
	pField->GetFieldValue( globPosVec, FieldValueVec ) ; 
	
      G4double Blocal= FieldValueVec[1];
      if ( FieldValueVec[0]!=0.)
	Blocal=sqrt(Blocal*Blocal+FieldValueVec[0]*FieldValueVec[0]);

      
 
      if(track.GetMaterial()==theMaterials->LCVacuum&&Blocal !=0 )
	{
	  /*
	    if(lastFieldManager!=TheFieldManager)
	    {
	     
	    lastFieldManager=TheFieldManager;
	    
	    G4MagInt_Driver* MagDriver=         
	    TheFieldManager->GetChordFinder()-> GetIntegrationDriver();
	    
	    G4FieldTrack fTrack=G4FieldTrack
	    (track.GetPosition(),track.GetMomentumDirection(),
	    1,track.GetKineticEnergy(),0.511*MeV,track.GetVelocity());
	    
	    G4cout<<" before R="<< BDSLocalRadiusOfCurvature<<G4endl;
	    G4double dydx[6];
	    G4double dchord_step;
	     G4double dyerr;
	     
	     MagDriver->QuickAdvance(       
	     fTrack,         // INOUT
	     dydx ,  
	     1.e-10*m,       // In
	     dchord_step,
	     dyerr )  ;
	     
	     G4cout<<" after R="<< BDSLocalRadiusOfCurvature<<G4endl;
	     
	     //	   MeanFreePath=1.e-10*m;
	     //  BDSLocalRadiusOfCurvature=DBL_MAX;
	     MeanFreePath=
	     abs(BDSLocalRadiusOfCurvature)/(track.GetTotalEnergy()*nExpConst);
	     }
	     else
	     {
	  */
	  G4ThreeVector InitMag=track.GetMomentum();
	  G4double Rlocal=(InitMag.z()/GeV)/(0.299792458 * Blocal/tesla) *m;
	  
	  MeanFreePath=
	    abs(Rlocal)/(track.GetTotalEnergy()*nExpConst);

	  MeanFreePath /= BDSGlobals->GetSynchMeanFreeFactor();

	  if(MeanFreePathCounter==BDSGlobals->GetSynchMeanFreeFactor())
	    MeanFreePathCounter=0;

	  //	  G4cout<<"Rlocal="<<Rlocal/m<<" BDSR="<<BDSLocalRadiusOfCurvature/m
	  //<<G4endl;
	   //       MeanFreePath=
	   //abs(BDSLocalRadiusOfCurvature)/(track.GetTotalEnergy()*nExpConst);
	   // }
	   
	   // tmp 
	   //MeanFreePath=DBL_MAX;

	  //	  G4cout<<"Blocal="<<Blocal/tesla<<"  Rlocal="<<Rlocal/m<<G4endl;
	  //	  G4cout<<track.GetVolume()->GetName()<<" mfp="<<MeanFreePath/m<<G4endl;
	  return MeanFreePath;
	}
      else
	return DBL_MAX;
    }
  else
    return DBL_MAX;
  
}
  


#endif
