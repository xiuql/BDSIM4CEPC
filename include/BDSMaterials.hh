/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 

   Added Get method to enable access to materials by passing a string
*/
#ifndef BDSMaterials_h
#define BDSMaterials_h 1

#include "globals.hh"
#include "G4Material.hh"


class BDSMaterials
{
public:

 
  BDSMaterials();

  G4Material*  GetMaterial(G4String aMaterial);

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
  G4Material*  LCLead;
  G4Material*  LCBeamGasPlugMat;


private:


};

inline G4Material* BDSMaterials::GetMaterial(G4String aMaterial)
{
  
  if(aMaterial=="Titanium") return LCTitanium;
  else if(aMaterial=="Tungsten") return LCTungsten;
  else if(aMaterial=="Graphite") return LCGraphite;
  else if(aMaterial=="Air") return LCAir;
  else if(aMaterial=="Vacuum") return LCVacuum;
  else if(aMaterial=="Aluminium") return LCAluminium;
  else if(aMaterial=="Iron") return LCIron;
  else if(aMaterial=="WeightIron") return LCWeightIron;
  else if(aMaterial=="LaserVac") return LaserVac;
  else if(aMaterial=="Copper") return LCCopper;
  else if(aMaterial=="Concrete") return LCConcrete;
  else if(aMaterial=="Water") return LCWater;
  else if(aMaterial=="LeadTungstate") return LCLeadTungstate;
  else if(aMaterial=="Lead") return LCLead;
  
  else
    {
      G4cout <<aMaterial<<" not known. Using Vacuum instead!!" <<G4endl;
      return LCVacuum; //default if not recognized
    }

}

#endif
