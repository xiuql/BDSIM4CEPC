/* BDSIM code.    Version 1.0
   Author: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 7.12.2004
   Copyright (c) 2004 by J.C.Carter.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSLowEMPhysics_h
#define BDSLowEMPhysics_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "G4VPhysicsConstructor.hh"

#include "G4LowEnergyPhotoElectric.hh"
#include "G4LowEnergyCompton.hh"
#include "G4LowEnergyGammaConversion.hh"
#include "G4LowEnergyRayleigh.hh"
#include "G4LowEnergyIonisation.hh"
#include "G4LowEnergyBremsstrahlung.hh"

#include "G4MultipleScattering.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4eIonisation.hh"

class BDSLowEMPhysics : public G4VPhysicsConstructor
{
public: 
  BDSLowEMPhysics(const G4String& name ="LowEm");
  virtual ~BDSLowEMPhysics();
  
public: 
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  
protected:
  
  // Low Energy Gamma physics
  
  G4LowEnergyPhotoElectric theLowEnPhoto;
  G4LowEnergyCompton theLowEnCompton;
  G4LowEnergyGammaConversion theLowEnPair;
  G4LowEnergyRayleigh theLowEnRayleigh;
  
  // Low Energy e- physics
  
  G4LowEnergyIonisation theLowEnIon;
  G4LowEnergyBremsstrahlung theLowEnBremss;

  // Std Energy still needed

  //e-

  G4MultipleScattering theeminusMultipleScattering;

  //e+

  G4MultipleScattering theeplusMultipleScattering;
  G4eIonisation theeplusIonisation;
  G4eBremsstrahlung theeplusBremsstrahlung;
  G4eplusAnnihilation theeplusAnnihilation;
  
};


#endif





