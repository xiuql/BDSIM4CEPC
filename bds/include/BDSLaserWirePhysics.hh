/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSLaserWirePhysics_h
#define BDSLaserWirePhysics_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VPhysicsConstructor.hh"
#include "BDSLaserWireBuilder.hh"

class BDSLaserWirePhysics : public G4VPhysicsConstructor
{
public: 
  BDSLaserWirePhysics(const G4String& name ="BDSLaserWire");
  virtual ~BDSLaserWirePhysics();
  
public: 
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  
private:
  
  BDSLaserWireBuilder  theBDSLaserWireBuilder;
};


#endif





