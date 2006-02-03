
/** BDSIM, v0.1   

Last modified 01.02.2006 by Ilya Agapov

**/


#ifndef BDSPhysicsList_h
#define BDSPhysicsList_h

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

#define kNuCut  5*m

class BDSPhysicsList: public G4VModularPhysicsList
{
public:
  BDSPhysicsList();
  virtual ~BDSPhysicsList();

public:
  
  void ConstructParticle();
  void ConstructProcess();

  void SetCuts();

  


};

#endif



