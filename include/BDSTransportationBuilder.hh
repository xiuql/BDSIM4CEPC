#ifndef BDSTransportationBuilder_h
#define BDSTransportationBuilder_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "BDSTransportationProcess.hh"

class BDSTransportationBuilder 
{
  public: 
    BDSTransportationBuilder();
    virtual ~BDSTransportationBuilder();

  public: 
    void Build();

  protected:
    BDSTransportationProcess theBDSTransportationProcess;
};
// 2003 by G.A Blair (after J.P. Wellisch)
#endif





