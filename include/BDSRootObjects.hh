/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 28.10.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSRootObjects_h
#define BDSRootObjects_h 1

#include "BDSGlobalConstants.hh"
#include "BDSSamplerHit.hh"
#include "BDSLWCalorimeterHit.hh"

#include "TROOT.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"

class BDSRootObjects 
{
  public:
  BDSRootObjects();
  ~BDSRootObjects();

  TFile* theRootOutputFile;
  TTree *theSamplerTree, *TrajTree;
  TTree *theLWCalorimeterTree;

  TH1F *h1;

  // tmp for eBrem studies
  TH1F *heBrem;

  void SetupNewFile(G4String filename);

  void BuildSamplerTrees();
  void BuildLWCalorimeterTrees();
  void BuildEnergyLossHisto();

  void SetEnergyLossZMax(G4double zMax);
  void SetSamplerNumber(G4int n);
  void SetLWCalorimeterNumber(G4int n);
  G4int GetLWCalorimeterNumber(){return nLWCalorimeters;}
  G4int GetSamplerNumber(){return nSamplers;}

  void LoadSamplerTree(BDSSamplerHit* hit);
  void LoadLWCalorimeterTree(BDSLWCalorimeterHit* hit);
  G4String StringFromInt(G4int N);

  void BuildTrajectoryTree();
  void LoadTrajectoryTree(G4ThreeVector* point);

protected:

private:
  // Data Members for Class Attributes
  G4double EnergyLossZMax;
  G4int nSamplers;
  G4int nLWCalorimeters;
  G4int nTrajectories;

  Float_t x0,xp0,y0,yp0,E0,z0,x,xp,y,yp,E,z,weight;
  Int_t part,nev;
  //  Float_t TrajPoint[3];
  Float_t Tx,Ty,Tz;

};

inline void BDSRootObjects::SetEnergyLossZMax(G4double zMax)
{EnergyLossZMax=zMax;}

inline void BDSRootObjects::SetSamplerNumber(G4int n)
{nSamplers=n;}

inline void BDSRootObjects::SetLWCalorimeterNumber(G4int n)
{nLWCalorimeters=n;}

extern BDSRootObjects* BDSRoot;
#endif

