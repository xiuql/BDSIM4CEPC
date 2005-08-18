/* BDSIM code.

*/

#include "G4ElectroMagneticField.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"

#ifndef __BDS_FIELD 
#define __BDS_FIELD

class BDSField : public G4ElectroMagneticField
{
public:

  // mandatory members

  BDSField();
  
  ~BDSField();

  G4bool   DoesFieldChangeEnergy() const;

  void GetFieldValue(const G4double Point[4],G4double *Bfield ) const;

  // aux members

  int AllocateMesh(int nX, int nY, int nZ);
  void FillMesh();

  void SetOriginRotation(G4RotationMatrix rot);
  void SetOriginTranslation(G4ThreeVector trans);

  void SetBx(int i,int j,int k,double val);
  void SetBy(int i,int j,int k,double val);
  void SetBz(int i,int j,int k,double val);

  G4double GetBx(int i,int j,int k);
  G4double GetBy(int i,int j,int k);
  G4double GetBz(int i,int j,int k);

private:
  
  double ***Bx, ***By, ***Bz;

  G4RotationMatrix rotation;
  G4ThreeVector translation;

public:
  G4double xHalf, yHalf, zHalf; // field mesh dimensions

  int nX, nY, nZ; // dimensions
  
};


#endif
