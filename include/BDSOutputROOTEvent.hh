#ifndef BDSOUTPUTROOTEVENT_H
#define BDSOUTPUTROOTEVENT_H

#include "globals.hh"

#include <map>

#include "BDSOutputBase.hh"
#include "BDSOutputROOTEventSampler.hh"

#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"

/**
 * @brief ROOT Event output class.
 * 
 * @author Stewart Boogert
 */

class BDSOutputROOTEvent: public BDSOutputBase 
{
public:
  BDSOutputROOTEvent();
  virtual ~BDSOutputROOTEvent();

  /// write sampler hit collection
  virtual void WriteHits(BDSSamplerHitsCollection*);
  
  /// write energy deposition hits
  virtual void WriteEnergyLoss(BDSEnergyCounterHitsCollection*);
  
  /// write where primaries stop being primaries
  virtual void WritePrimaryLoss(BDSEnergyCounterHit* ploss);

  /// write where primaries impact
  virtual void WritePrimaryHit(BDSEnergyCounterHit* phits);

  /// write tunnel hits
  virtual void WriteTunnelHits(BDSTunnelHitsCollection* tunnelHits);
  
  /// write a trajectory 
  virtual void WriteTrajectory(std::vector<BDSTrajectory*> &TrajVec);
  
  /// write primary hit
  virtual void WritePrimary(G4double E,
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
			    G4int    TurnsTaken);

  /// write a histgoram
  virtual void WriteHistogram(BDSHistogram1D* histogramIn);

  /// fill event structure
  virtual void FillEvent();
  
  /// write and close and open new file
  virtual void Commit();
  
  /// write and close the file
  virtual void Write();

  /// clear structures 
  void Clear();
  
private:

  void Init();

  // output file
  TFile *theRootOutputFile;
  // output tree
  TTree *theRootOutputTree;

  // primary structure 
  BDSOutputROOTEventSampler *primary;

  // sampler structures 
  std::map<G4String, BDSOutputROOTEventSampler*> samplerMap;

  // energy hit structures 
};

#endif
