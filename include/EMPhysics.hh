#ifndef EMPhysics_h
#define EMPhysics_h 

#include "globals.hh"
#include "G4ios.hh"
#include "G4VPhysicsConstructor.hh"
//#include "G4EMBuilder.hh"

#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4MultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

class EMPhysics : public G4VPhysicsConstructor
{
  public: 
    EMPhysics(const G4String& name ="EM");
    virtual ~EMPhysics();

  public: 
    virtual void ConstructParticle();
    virtual void ConstructProcess();

  private:
  //G4EMBuilder theEMPhysics;

  G4PhotoElectricEffect thePhotoEffect;
  G4ComptonScattering theComptonEffect;
  G4GammaConversion thePairProduction;
  
  G4MultipleScattering theElectronMultipleScattering;
  G4eIonisation theElectronIonisation;
  G4eBremsstrahlung theElectronBremsStrahlung;
  
  G4MultipleScattering thePositronMultipleScattering;
  G4eIonisation thePositronIonisation; 
  G4eBremsstrahlung thePositronBremsStrahlung;  
  G4eplusAnnihilation theAnnihilation;
  
};

#endif





