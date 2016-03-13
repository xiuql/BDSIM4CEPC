#ifndef BDSOUTPUTROOTDETAILED_H
#define BDSOUTPUTROOTDETAILED_H

#include "BDSOutputROOT.hh"
#include "BDSTrajectory.hh"

#include "TTree.h"

/**
 * @brief ROOT output class
 * 
 * Write BDSIM output to ROOT files. Originally
 * part of BDSIM code base and recently developed and maintained
 * by Jochem Snuverink, Lawrence Deacon & Laurie Nevay
 * 
 * @author Laurie Nevay
 */

class BDSOutputROOTDetailed: public BDSOutputROOT
{
public:
  BDSOutputROOTDetailed(G4String numberType);
  virtual ~BDSOutputROOTDetailed();
  
  /// write primary hit
  virtual void WritePrimary(G4double totalEnergy,
			    G4double x0,
			    G4double y0,
			    G4double z0,
			    G4double xp,
			    G4double yp,
			    G4double zp,
			    G4double t,
			    G4double weight,
			    G4int    PDGType, 
			    G4int    nEvent, 
			    G4int    turnsTaken);


  virtual TTree* BuildSamplerTree(G4String name);
  
private:
  /// Private default constructor to force use of provided one
  BDSOutputROOTDetailed();
  
  /// @{ Member for writing to TTree
  double Xp=0.0,Yp=0.0,Zp=0.0;
  double x0=0.0,xp0=0.0,y0=0.0,yp0=0.0,z0=0.0,zp0=0.0,E0=0.0,t0=0.0;
  double x_prod=0.0,xp_prod=0.0,y_prod=0.0,yp_prod=0.0,z_prod=0.0,zp_prod=0.0,E_prod=0.0,t_prod=0.0;
  double x_lastScat=0.0,xp_lastScat=0.0,y_lastScat=0.0,yp_lastScat=0.0,z_lastScat=0.0,zp_lastScat=0.0,E_lastScat=0.0,t_lastScat=0.0;
  /// @}
  
  void FillEvent(){};

  /// write hit to TTree
  virtual void WriteRootHit(TTree*         tree,
			    BDSSamplerHit* hit,
			    G4bool         fillTree = true);
  /// write hit to TTree
  void WriteRootHitDetailed(TTree*   Tree,
			    G4double InitTotalenergy,
			    G4double InitX,
			    G4double InitY,
			    G4double InitZ,
			    G4double InitXPrime,
			    G4double InitYPrime,
			    G4double InitZPrime,
			    G4double InitT,
			    G4double ProdTotalenergy,
			    G4double ProdX,
			    G4double ProdY,
			    G4double ProdZ,
			    G4double ProdXPrime,
			    G4double ProdYPrime,
			    G4double ProdZPrime,
			    G4double ProdT,
			    G4double LastScatTotalenergy,
			    G4double LastScatX,
			    G4double LastScatY,
			    G4double LastScatZ,
			    G4double LastScatXPrime,
			    G4double LastScatYPrime,
			    G4double LastScatZPrime,
			    G4double LastScatT,
			    G4double Totalenergy,
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
			    G4int    TurnsTaken,
			    G4String Process);
  
};

extern BDSOutputBase* bdsOutput;

#endif
