/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSMaterials_h
#define BDSMaterials_h 1

#include "globals.hh"
#include "G4Material.hh"


class BDSMaterials
{
public:

 
  BDSMaterials();


  G4Material*  LCTitanium;
  G4Material*  LCTungsten;
  G4Material*  LCGraphite;
  G4Material*  LCAir;
  G4Material*  LCVacuum;
  G4Material*  LCAluminium;
  G4Material*  LCIron;
  G4Material*  LCWeightIron;
  G4Material*  LaserVac;
  G4Material*  LCCopper;
  G4Material*  LCConcrete;
  G4Material*  LCWater;
  G4Material*  LCLeadTungstate;

private:


};


#endif
