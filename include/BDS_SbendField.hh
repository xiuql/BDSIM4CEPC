#ifndef BDS_SBEND_FIELD_HH
#define BDS_SBEND_FIELD_HH

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4UniformMagField.hh"
#include "G4Mag_EqRhs.hh"

class BDS_SbendField : public G4UniformMagField 
{
public:  // with description
  
  BDS_SbendField(const G4ThreeVector& FieldVector,const G4double aLength,
		    const G4double aAngle);
  // A field with value equal to FieldVector.
		       
  ~BDS_SbendField() ;

  G4double GetLocalRadius();

private:
  G4double itsLocalRadius ;

};

inline G4double BDS_SbendField::GetLocalRadius()
{return itsLocalRadius;}

#endif
