/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSeBremBuilder_h
#define BDSeBremBuilder_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "BDSeBremsstrahlung.hh"
#include "G4VProcess.hh"

class BDSeBremBuilder 
{
public: 
  BDSeBremBuilder();
  virtual ~BDSeBremBuilder();
  
public: 
  void Build();

protected:
  BDSeBremsstrahlung theeBremProcess;


};


// 2003 by G.A Blair (after J.P. Wellisch)
#endif





