/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 18.10.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
/*
  This Wedge component is an adaption of the BDSSectorBend with the B-field
  removed.
  J.C.Carter
  02.03.2005
*/

#ifndef BDSWedge_h
#define BDSWedge_h 1

#include "globals.hh"
#include "BDSMaterials.hh"
#include "G4LogicalVolume.hh"

#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"               

#include "BDSMultipole.hh"

class BDSWedge :public BDSMultipole
{
  public:
  BDSWedge(G4String& aName, G4double aLength, G4double bpRad,
		  G4double angle);
    ~BDSWedge();

  private:

  void BuildWedgeMarkerLogicalVolume();
  G4VisAttributes* SetVisAttributes();

};

#endif
