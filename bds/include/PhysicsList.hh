#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

#define kNuCut  5*m

class PhysicsList: public G4VModularPhysicsList
{
public:
  PhysicsList();
  virtual ~PhysicsList();
  
public:
  // SetCuts() 
  virtual void SetCuts();

};

// 2002 by J.P. Wellisch
#endif



