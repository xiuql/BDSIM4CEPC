/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSPlanckScatter_h
#define BDSPlanckScatter_h 1

#include "G4ios.hh" 
#include "globals.hh"
#include "Randomize.hh" 
#include "G4VeEnergyLoss.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4OrderedTable.hh" 
#include "G4PhysicsTable.hh"
#include "G4PhysicsLogVector.hh"
#include "BDSComptonEngine.hh"
#include "BDSPlanckEngine.hh"
 
class BDSPlanckScatter : public G4VeEnergyLoss
 { 
  public:
 
     BDSPlanckScatter();
 
    ~BDSPlanckScatter();

     G4bool IsApplicable(const G4ParticleDefinition&);
     
     G4double GetMeanFreePath(const G4Track& track,
                              G4double previousStepSize,
                              G4ForceCondition* condition );
 
     G4VParticleChange *PostStepDoIt(const G4Track& track,         
                                     const G4Step&  step);                 

     inline void SetTemperature(G4double aTemperature);
     inline G4double GetTemperature();

  protected:

     virtual G4double SecondaryEnergyThreshold(size_t index);

  private:

     BDSPlanckScatter & operator=(const BDSPlanckScatter &right);
     
     BDSPlanckScatter(const BDSPlanckScatter&);

     const std::vector<G4double>* secondaryEnergyCuts;

private:
    G4double itsTemperature;
    BDSComptonEngine* itsComptonEngine;
    BDSPlanckEngine* itsPlanckEngine;
    G4double itsPlanckMeanFreePath;     
};
inline G4bool BDSPlanckScatter::IsApplicable(
                            const G4ParticleDefinition& particle)
{
   return(  (&particle == G4Electron::Electron())
          ||(&particle == G4Positron::Positron()) );
}
inline G4double BDSPlanckScatter::GetMeanFreePath(const G4Track& track,
                                           G4double PreviousStepSize,
                                           G4ForceCondition* ForceCondition)
{  
*ForceCondition= NotForced ;
return itsPlanckMeanFreePath;
}
  

inline void BDSPlanckScatter::SetTemperature(G4double aTemperature)
{itsTemperature=aTemperature;}
inline G4double BDSPlanckScatter::GetTemperature()
{return itsTemperature;}

inline G4double BDSPlanckScatter::SecondaryEnergyThreshold(size_t index)
{
  return (*secondaryEnergyCuts)[index];
}


#endif
