/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// BDSExtractBunch.hh
// Bunch format interfacing to PLACET output file
// G.A.Blair (RHUL) 10.12.01
// adapted from code supplied by D.Schulte (CERN)

#ifndef BDSExtractBunch_h
#define BDSExtractBunch_h 1

#include "globals.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "BDSParticle.hh"
#include "BDSRMatrix.hh"

#include <vector>

/*
typedef struct{
  double energy,wgt,y,yp;
  double x,xp;
} PARTICLE;

typedef struct{
  double r11,r12,r21,r22;
} R_MATRIX;
*/

using std::vector;

typedef vector<BDSParticle*> vPART;
typedef vector<BDSRMatrix*> vRMAT;
typedef vector<G4double> vZpos;

class BDSExtractBunch
{

public:

  BDSExtractBunch (char* ExtractBunchInputFilename);
  
  ~BDSExtractBunch();

  void bunch_make(int n_bunch,int n_slice,int n_macro,int n_field);
  
  void read_beam_file(char *name,int ibunch0);

protected:
  //  void BuildSectorBendMaterial();


public:
  int GetNumSlices();
  int GetNumBunches();
  int GetNumSlicesPerBunch();
  int GetNumMacroparticles();
  vZpos* GetZPos();

  /*
  PARTICLE* GetParticle();
  R_MATRIX* GetSigma();
  R_MATRIX* GetSigmaXX();
  R_MATRIX* GetSigmaXY();
  */

  vPART* GetParticleVector();
  vRMAT* GetSigmaVector();
  vRMAT* GetSigmaXXVector();
  vRMAT* GetSigmaXYVector();

private:

  int slices_per_bunch,macroparticles,bunches;
  int slices,n_field,which_field;
  double factor,transv_factor;
  //  PARTICLE *particle;
  //  R_MATRIX *sigma,*sigma_xx,*sigma_xy;
  vPART *partVec;
  vRMAT *sigmaVec,*sigma_xxVec,*sigma_xyVec;
  vZpos *z_position;
};

inline int BDSExtractBunch::GetNumSlices()
{return slices;};

inline  int BDSExtractBunch::GetNumBunches()
{return bunches;};

inline  int BDSExtractBunch::GetNumSlicesPerBunch()
{return slices_per_bunch;};

inline  int BDSExtractBunch::GetNumMacroparticles()
{return macroparticles;};

inline  vZpos* BDSExtractBunch::GetZPos()
{return z_position;};

/*
inline  PARTICLE* BDSExtractBunch::GetParticle()
{return particle;};

inline  R_MATRIX* BDSExtractBunch::GetSigma()
{return sigma;};

inline R_MATRIX* BDSExtractBunch::GetSigmaXX()
{return sigma_xx;};

inline  R_MATRIX* BDSExtractBunch::GetSigmaXY()
{return sigma_xy;};
*/

inline  vPART* BDSExtractBunch::GetParticleVector()
{return partVec;};

inline  vRMAT* BDSExtractBunch::GetSigmaVector()
{return sigmaVec;};

inline vRMAT* BDSExtractBunch::GetSigmaXXVector()
{return sigma_xxVec;};

inline vRMAT* BDSExtractBunch::GetSigmaXYVector()
{return sigma_xyVec;};

#endif
