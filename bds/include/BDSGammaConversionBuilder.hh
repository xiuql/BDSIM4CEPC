/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.3.2003
   Copyright (c) 2003 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSGammaConversionBuilder_h
#define BDSGammaConversionBuilder_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "BDSGammaConversion.hh"
#include "G4VProcess.hh"

class BDSGammaConversionBuilder 
{
public: 
  BDSGammaConversionBuilder();
  virtual ~BDSGammaConversionBuilder();
  
public: 
  void Build();
  
protected:
  BDSGammaConversion theGammaConversionProcess;
};
// 2003 by G.A Blair (after J.P. Wellisch)
#endif





