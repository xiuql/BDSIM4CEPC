/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSPhysicsList_h
#define BDSPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

#define kNuCut  5*m

class BDSPhysicsList: public G4VModularPhysicsList
{
public:
  BDSPhysicsList();
  virtual ~BDSPhysicsList();

public:
  // SetCuts() 
  virtual void SetCuts();

};

// 2003 modified by G A Blair
// 2002 by J.P. Wellisch
#endif



