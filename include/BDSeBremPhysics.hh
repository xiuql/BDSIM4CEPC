/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSeBremPhysics_h
#define BDSeBremPhysics_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VPhysicsConstructor.hh"
#include "BDSeBremBuilder.hh"

class BDSeBremPhysics : public G4VPhysicsConstructor
{
public: 
  BDSeBremPhysics(const G4String& name ="BDSeBrem");
  virtual ~BDSeBremPhysics();
  
public: 
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  
private:
  
  BDSeBremBuilder  theBDSeBremBuilder;
};


#endif





