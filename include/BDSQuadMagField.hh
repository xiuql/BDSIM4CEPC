/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
#ifndef BDSQUADMAGFIELD
#define BDSQUADMAGFIELD

#include "G4Types.hh"
#include "G4MagneticField.hh"

class BDSQuadMagField : public G4MagneticField
{
public:  // with description

  BDSQuadMagField(G4double aBGrad);
  virtual ~BDSQuadMagField();
  // Constructor and destructor. No actions.


  virtual void  GetFieldValue( const G4double Point[4],
			       G4double *Bfield ) const;

private:
  G4double itsBGrad;

};


#endif /* BDSQUADMAGFIELD */
