/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 28.10.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#include "BDSGlobalConstants.hh"
#include "BDSRootObjects.hh"


BDSRootObjects::BDSRootObjects ()
{}

BDSRootObjects::~BDSRootObjects()
{  

  if(theRootOutputFile->IsOpen())
    {
      theRootOutputFile->Write();
      theRootOutputFile->Close();
      delete theRootOutputFile;
    }

  //if(h1)    delete h1;


  G4int i;
  for(i=0;i<nSamplers;i++)
    {
      G4String name="samp"+StringFromInt(i+1);
      TTree* sTree=(TTree*)gDirectory->Get(name);
      if(sTree)delete sTree;
    }


  for(i=0;i<nLWCalorimeters;i++)
    {
      G4String name="lwcal"+StringFromInt(i+1);
      TTree* sTree=(TTree*)gDirectory->Get(name);
      if(sTree)delete sTree;
    }


  for(i=0;i<nTrajectories;i++)
    {
      G4String name="Trajectory"+StringFromInt(i+1);
      TTree* tTree=(TTree*)gDirectory->Get(name);
      if(tTree)delete tTree;
    }


}

void  BDSRootObjects::SetupNewFile(G4String filename)
{
  G4cout<<"Setting up new file:"<<filename<<G4endl;
  BDSRoot->theRootOutputFile=new TFile(filename,"RECREATE", "BDS output file");
  BuildEnergyLossHisto();
  BuildSamplerTrees();
  BuildLWCalorimeterTrees();
}

void BDSRootObjects::BuildSamplerTrees()
{
  for(G4int i=0;i<nSamplers;i++)
    {
      G4String name="samp"+StringFromInt(i+1);
      TTree* SamplerTree = new TTree(name, "Sampler output");
      
      SamplerTree->Branch("x0",&x0,"x0/F");
      SamplerTree->Branch("xp0",&xp0,"xp0/F");
      SamplerTree->Branch("y0",&y0,"y0/F");
      SamplerTree->Branch("yp0",&yp0,"yp0/F");
      SamplerTree->Branch("E0",&E0,"E0/F");
      SamplerTree->Branch("z0",&z0,"z0/F");
      SamplerTree->Branch("x",&x,"x/F");
      SamplerTree->Branch("xp",&xp,"xp/F");
      SamplerTree->Branch("y",&y,"y/F");
      SamplerTree->Branch("yp",&yp,"yp/F");
      SamplerTree->Branch("E",&E,"E/F");
      SamplerTree->Branch("z",&z,"z/F");
      SamplerTree->Branch("weight",&weight,"weight/F");
      SamplerTree->Branch("part",&part,"part/I");
      SamplerTree->Branch("nev",&nev,"z/I");
    }
}

void BDSRootObjects::BuildLWCalorimeterTrees()
{
  for(G4int i=0;i<nLWCalorimeters;i++)
    {
      G4String name="lwcal"+StringFromInt(i+1);
      TTree* LWCalorimeterTree = new TTree(name, "LWCalorimeter output");
      
      LWCalorimeterTree->Branch("E",&E,"E/F");
      LWCalorimeterTree->Branch("nev",&nev,"z/I");
    }
}

void BDSRootObjects::BuildTrajectoryTree()
{
  nTrajectories++;
  G4String name="Trajectory"+StringFromInt(nTrajectories);  
  TrajTree = new TTree(name, "Track Trajectory");
  //  TrajTree->Branch("point", TrajPoint,"TrajPoint[3]/F");
  TrajTree->Branch("x",&Tx,"x/F");
  TrajTree->Branch("y",&Ty,"y/F");
  TrajTree->Branch("z",&Tz,"z/F");
}

void BDSRootObjects::LoadTrajectoryTree(G4ThreeVector* point)
{
  Tx=point->x()/m;
  Ty=point->y()/m;
  Tz=point->z()/m;
  TrajTree->Fill();
}

void BDSRootObjects::LoadSamplerTree(BDSSamplerHit* hit)
{

  G4String name="samp"+StringFromInt(hit->GetNumber());
  TTree* sTree=(TTree*)gDirectory->Get(name);

  x0=hit->GetInitX()/m; 
  xp0=hit->GetInitXPrime(); 
  y0=hit->GetInitY()/m; 
  yp0=hit->GetInitYPrime(); 
  E0=hit->GetInitMom()/GeV; 
  z0=hit->GetInitZ()/m; 
  x=hit->GetX()/m; 
  xp=hit->GetXPrime(); 
  y=hit->GetY()/m; 
  yp=hit->GetYPrime(); 
  E=hit->GetMom()/GeV; 
  z=hit->GetZ()/m; 
  weight=hit->GetWeight();
  part=hit->GetPDGtype(); 
  nev=hit->GetEventNo(); 

  sTree->Fill();
}

void BDSRootObjects::LoadLWCalorimeterTree(BDSLWCalorimeterHit* hit)
{
  G4String name="lwcal"+StringFromInt(hit->GetCopyNumber());
  TTree* sTree=(TTree*)gDirectory->Get(name);
  E=hit->GetEnergy()/GeV;
  nev=hit->GetEventNo(); 
  sTree->Fill();
}

void BDSRootObjects::BuildEnergyLossHisto()
{
  G4double zMax=EnergyLossZMax/m;
  G4int nBins=G4int(zMax);
  h1=new TH1F("h1", "Energy Loss",nBins,0.,zMax);

  // tmp for eBrem studies
  nBins=G4int(zMax/10);
  heBrem=new TH1F("heBrem", "dBrem",nBins,0.,zMax);


}

G4String BDSRootObjects::StringFromInt(G4int N)
{
  //JCC 020704
  //char* CharN;
  char CharN[50];
  sprintf(CharN,"%d",N);
  G4String Cnum(CharN);
  return Cnum;
}

