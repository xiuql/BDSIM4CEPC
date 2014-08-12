#ifndef BDSOutputROOT_h
#define BDSOutputROOT_h 

#ifdef USE_ROOT

#include "BDSOutputBase.hh"

#include "TROOT.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"

/// ROOT output class

class BDSOutputROOT : public BDSOutputBase {

public: 

  BDSOutputROOT(); // default constructor
  //  BDSOutput(BDSOutputFormat format);
  virtual ~BDSOutputROOT();

  /// write sampler hit collection
  virtual void WriteHits(BDSSamplerHitsCollection*);
  /// make energy loss histo
  virtual void WriteEnergyLoss(BDSEnergyCounterHitsCollection*);
  /// write a trajectory 
  virtual void WriteTrajectory(std::vector<G4VTrajectory*> &TrajVec);
  /// write primary hit
  virtual void WritePrimary(G4String samplerName, 
			    G4double E,
			    G4double x0,
			    G4double y0,
			    G4double z0,
			    G4double xp,
			    G4double yp,
			    G4double zp,
			    G4double t,
			    G4double weight,
			    G4int PDGType, 
			    G4int nEvent, 
			    G4int TurnsTaken);

  virtual void Commit();  /// close the file
  virtual void Write();   /// close and open new file

private:

  void Init(); /// output initialisation

  void BuildSamplerTree(G4String name);
  TFile* theRootOutputFile;
  //  TTree *theLWCalorimeterTree;

  TH1F *EnergyLossHisto;
  //  TH3F *EnergyLossHisto3d;
  TTree *PrecisionRegionEnergyLossTree;
  TTree *EnergyLossTree;
  
  float x0,xp0,y0,yp0,z0,zp0,E0,t0;
  float x_prod,xp_prod,y_prod,yp_prod,z_prod,zp_prod,E_prod,t_prod;
  float x_lastScat,xp_lastScat,y_lastScat,yp_lastScat,z_lastScat,zp_lastScat,E_lastScat,t_lastScat;
  float x,xp,y,yp,z,zp,E,t; //Edep;
  float X,Xp,Y,Yp,Z,Zp,s,weight; //,EWeightZ;
  int part,nev, pID, track_id, turnnumber;
  float s_el,E_el;
  float x_el_p,y_el_p,z_el_p,E_el_p,s_el_p;
  int part_el_p, weight_el_p;
  char volumeName_el_p[100];

  void WriteRootHit(G4String Name, 
		    G4double InitMom, 
		    G4double InitX, 
		    G4double InitY, 
		    G4double InitZ, 
		    G4double InitXPrime, 
		    G4double InitYPrime, 
		    G4double InitZPrime, 
		    G4double InitT, 
		    G4double ProdMom, 
		    G4double ProdX, 
		    G4double ProdY, 
		    G4double ProdZ, 
		    G4double ProdXPrime, 
		    G4double ProdYPrime, 
		    G4double ProdZPrime, 
		    G4double ProdT, 
		    G4double LastScatMom, 
		    G4double LastScatX, 
		    G4double LastScatY, 
		    G4double LastScatZ, 
		    G4double LastScatXPrime, 
		    G4double LastScatYPrime, 
		    G4double LastScatZPrime, 
		    G4double LastScatT, 
		    G4double Mom, 
		    G4double X, 
		    G4double Y, 
		    G4double Z, 
		    G4double XPrime, 
		    G4double YPrime, 
		    G4double ZPrime, 
		    G4double T, 
		    G4double GlobalX, 
		    G4double GlobalY, 
		    G4double GlobalZ, 
		    G4double GlobalXPrime, 
		    G4double GlobalYPrime, 
		    G4double GlobalZPrime, 
		    G4double S, 
		    G4double Weight, 
		    G4int    PDGtype, 
		    G4int    EventNo, 
		    G4int    ParentID,
		    G4int    TrackID, 
		    G4int    TurnsTaken);
  
};

extern BDSOutputBase* bdsOutput;

#endif // USE_ROOT
#endif
