/* BDSIM code.

*/

#include "globals.hh"
#include "BDSField.hh"

BDSField::BDSField() :
  nX(0), nY(0), nZ(0)
{
}

BDSField::~BDSField()
{
  // release the b-map memory 
}

G4bool   BDSField::DoesFieldChangeEnergy() const
{
  return 0;
}



void BDSField::GetFieldValue(const G4double Point[4],G4double *Bfield ) const
{

  G4double bx=0, by=0, bz=0;
  int i=0,j=0,k=0;
  // if mesh exists - interpolate
 //  if( (bxMeshSize > 0) && (byMeshSize > 0) && (bzMeshSize > 0))
//     {
      
//     }
//   else

  G4ThreeVector local;

  if( (nX <= 0)|| (nY<=0)|| (nZ<=0) )
    {
      G4cout<<"no mesh"<<G4endl;
      bx = by = bz = 0;
    }
  else
    {
      local[0] = Point[0] - translation[0];
      local[1] = Point[1] - translation[1];
      local[2] = Point[2] - translation[2];

      local *= rotation;

      i = nX/2 + nX * local[0] / (2 * xHalf);
      j = nY/2 + nY * local[1] / (2 * yHalf);
      k = nZ/2 + nZ * local[2] / (2 * zHalf);

      bx = Bx[i][j][k];
      by = By[i][j][k];
      bz = Bz[i][j][k];
    }

  Bfield[0] = bx;
  Bfield[1] = by;
  Bfield[2] = bz;

  Bfield[3] = 0;
  Bfield[4] = 0;
  Bfield[5] = 0;

  //G4cout<<" field value requested : "<<Point[0]<<" , "<<Point[1]<<" , "<<Point[2]<<" , "<<Point[3]<<" : "<<
  //  i<<" , "<<j<<" , "<<k<<"    "<<local[0]<<" "<<local[1]<<" "<<local[2]<<" "<<bx<<" "<<by<<" "<<bz<<G4endl;

}

int BDSField::AllocateMesh(int nx, int ny, int nz) 
{
  nX = nx;
  nY = ny;
  nZ = nz;

  Bx = new double**[nX];
  for(int i=0;i<nX;i++)
    {
      Bx[i] = new double*[nY];
      for(int j=0; j<nY;j++)
	Bx[i][j] = new double[nZ];
    }
   
  By = new double**[nX];
  for(int i=0;i<nX;i++)
    {
      By[i] = new double*[nY];
      for(int j=0; j<nY;j++)
	By[i][j] = new double[nZ];
    }

  Bz = new double**[nX];
  for(int i=0;i<nX;i++)
    {
      Bz[i] = new double*[nY];
      for(int j=0; j<nY;j++)
	Bz[i][j] = new double[nZ];
    }
  
  return 0;
}

void BDSField::FillMesh()
{
  
}

void BDSField::SetOriginRotation(G4RotationMatrix rot)
{
  rotation = rot;
}

void BDSField::SetOriginTranslation(G4ThreeVector trans)
{
  translation = trans;
}


void BDSField::SetBx(int i,int j,int k,double val)
{
  Bx[i][j][k] = val;
}


void BDSField::SetBy(int i,int j,int k,double val)
{
  By[i][j][k] = val;
}


void BDSField::SetBz(int i,int j,int k,double val)
{
  Bz[i][j][k] = val;
}

G4double BDSField::GetBx(int i,int j,int k)
{
  return Bx[i][j][k];
}

G4double BDSField::GetBy(int i,int j,int k)
{
  return By[i][j][k];
}

G4double BDSField::GetBz(int i,int j,int k)
{
  return Bz[i][j][k];
}
