/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSPlanckScatterPhysics_h
#define BDSPlanckScatterPhysics_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VPhysicsConstructor.hh"
#include "BDSPlanckScatterBuilder.hh"

class BDSPlanckScatterPhysics : public G4VPhysicsConstructor
{
public: 
  BDSPlanckScatterPhysics(const G4String& name ="BDSPlanckScatter");
  virtual ~BDSPlanckScatterPhysics();
  
public: 
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  
private:
  
  BDSPlanckScatterBuilder  theBDSPlanckScatterBuilder;
};


#endif





