#ifndef BDSTransportation_h
#define BDSTransportation_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VPhysicsConstructor.hh"
#include "BDSTransportationBuilder.hh"


class BDSTransportation : public G4VPhysicsConstructor
{
  public: 
    BDSTransportation(const G4String& name ="BDSTrans");
    virtual ~BDSTransportation();

  public: 
    virtual void ConstructParticle();
    virtual void ConstructProcess();

  private:
    BDSTransportationBuilder theBDSTransportation;
};

// 2002 by J.P. Wellisch

#endif





