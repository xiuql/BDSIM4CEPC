#ifndef BDSAcceleration_h
#define BDSAcceleration_h 1

// BDSIM code.    Version 1.0
//   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
//   Last modified 24.7.2002
//   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
//

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
#include "Randomize.hh"

#include "G4ChordFinder.hh"
#include "G4FieldManager.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4FieldTrack.hh"
#include "BDSMaterials.hh"

extern BDSMaterials* theMaterials;
extern G4double BDSLocalRadiusOfCurvature;
 
class BDSAcceleration : public G4VDiscreteProcess 
{ 
public:
 
  BDSAcceleration(const G4String& processName = "BDSAcceleration");
 
  ~BDSAcceleration();

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

  BDSAcceleration & operator=(const BDSAcceleration &right);
     
  BDSAcceleration(const BDSAcceleration&);

  G4double nExpConst;
  G4double CritEngFac;

private:
};

inline G4bool 
BDSAcceleration::IsApplicable(const G4ParticleDefinition& particle)
{
  return(  (&particle == G4Electron::Electron())
	   ||(&particle == G4Positron::Positron()) );
}

inline G4double 
BDSAcceleration::GetMeanFreePath(const G4Track& track,
					G4double PreviousStepSize,
					G4ForceCondition* ForceCondition)
{  
  *ForceCondition = NotForced ;
  G4double MeanFreePath=10.*m;

  return MeanFreePath;
}
  


#endif
