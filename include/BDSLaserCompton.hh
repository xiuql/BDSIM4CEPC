#ifndef BDSLASERCOMPTON_H
#define BDSLASERCOMPTON_H

#include "G4ios.hh" 
#include "globals.hh"
#include "G4VDiscreteProcess.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "BDSComptonEngine.hh"
#include "BDSMaterials.hh"

// flag initiated in BDSEventAction
extern G4bool FireLaserCompton;

/**
 * @brief Laser compton scattering process to achieve a laserwire.
 * 
 * This tests whether the current track is in a 'laservacuum' material
 * as defined by BDSMaterials and if so simulates compton scattering of
 * a photon from the incident particle.
 *
 * This is long standing code and hasn't been used for sometime and should
 * be validated.
 *
 * @author Grahame Blair
 */


class BDSLaserCompton: public G4VDiscreteProcess
{ 
public:
   
  BDSLaserCompton(const G4String& processName = "eLaser");
  
  virtual  ~BDSLaserCompton();

  /// Overridden from G4VProcess - whether applicable to a particular particle.
  virtual G4bool IsApplicable(const G4ParticleDefinition&);

  /// Overridden from G4VDiscreteProcess.
  virtual G4double GetMeanFreePath(const G4Track& track,
				   G4double previousStepSize,
				   G4ForceCondition* condition );
  
  virtual G4VParticleChange *PostStepDoIt(const G4Track& track,         
					  const G4Step&  step);                 
  
  inline void SetLaserDirection(G4ThreeVector aDirection);
  inline G4ThreeVector GetLaserDirection() const;
  
  inline void SetLaserWavelength(G4double aWavelength);
  inline G4double GetLaserWavelength() const;
  
protected:
  G4double ComputeMeanFreePath( const G4ParticleDefinition* ParticleType,
				G4double KineticEnergy, 
				const G4Material* aMaterial);
  
private:
  // assignment and copy constructor not implemented nor used
  BDSLaserCompton & operator=(const BDSLaserCompton &right);
  BDSLaserCompton(const BDSLaserCompton&);

  BDSGlobalConstants* globals;
  
  G4double          laserWavelength;
  G4ThreeVector     laserDirection;
  G4double          laserEnergy;
  BDSComptonEngine* comptonEngine;
};

inline G4bool BDSLaserCompton::IsApplicable(const G4ParticleDefinition& particle)
{
  return ( (&particle == G4Electron::Electron()) || (&particle == G4Positron::Positron()) );
}

inline G4double BDSLaserCompton::GetMeanFreePath(const G4Track& track,
						 G4double /*PreviousStepSize*/,
						 G4ForceCondition* ForceCondition)
{
  if ( track.GetMaterial() == BDSMaterials::Instance()->GetMaterial("LaserVac") &&
      FireLaserCompton )
    {*ForceCondition = Forced;}
  return DBL_MAX;
}

inline void BDSLaserCompton::SetLaserDirection(G4ThreeVector laserDirectionIn)
{laserDirection = laserDirectionIn;}

inline G4ThreeVector BDSLaserCompton::GetLaserDirection() const
{return laserDirection;}

inline void BDSLaserCompton::SetLaserWavelength(G4double wavelengthIn)
{laserWavelength = wavelengthIn;}

inline G4double BDSLaserCompton::GetLaserWavelength() const
{return laserWavelength;}

#endif
