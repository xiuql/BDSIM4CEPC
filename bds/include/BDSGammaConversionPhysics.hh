/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSGammaConversionPhysics_h
#define BDSGammaConversionPhysics_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VPhysicsConstructor.hh"
#include "BDSGammaConversionBuilder.hh"

class BDSGammaConversionPhysics : public G4VPhysicsConstructor
{
public: 
  BDSGammaConversionPhysics(const G4String& name ="BDSGammaConversion");
  virtual ~BDSGammaConversionPhysics();
  
public: 
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  
private:
  
  BDSGammaConversionBuilder  theBDSGammaConversionBuilder;
};


#endif





