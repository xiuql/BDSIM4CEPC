/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSSynchRadBuilder_h
#define BDSSynchRadBuilder_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "BDSSynchrotronRadiation.hh"
#include "G4VProcess.hh"

class BDSSynchRadBuilder 
{
public: 
  BDSSynchRadBuilder();
  virtual ~BDSSynchRadBuilder();
  
public: 
  void Build();
  
protected:
  BDSSynchrotronRadiation theSynchRadProcess;
};
// 2003 by G.A Blair (after J.P. Wellisch)
#endif





