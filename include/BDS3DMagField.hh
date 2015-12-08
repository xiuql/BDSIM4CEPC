//Based on the Geant4 example examples/advanced/purging_magnet/src/PurgMagTabulatedField3D.cc
#include "G4ios.hh"
#include "BDSMagField.hh"

#include <vector>

class BDS3DMagField : public BDSMagField
{
  
  // Storage space for the table
  std::vector< std::vector< std::vector< double > > > xField;
  std::vector< std::vector< std::vector< double > > > yField;
  std::vector< std::vector< std::vector< double > > > zField;
  // The dimensions of the table
  int nx,ny,nz; 
  // The physical limits of the defined region
  double minx, maxx, miny, maxy, minz, maxz;
  // The physical extent of the defined region
  double dx, dy, dz;
  double fZoffset;
  bool invertX, invertY, invertZ;
  double _lenUnit, _fieldUnit;
  void Prepare(G4VPhysicalVolume *referenceVolume);
  
public:
  BDS3DMagField(const char* filename, double zOffset );
  void  GetFieldValue( const  double Point[4],
		       double *Bfield          ) const;
};

