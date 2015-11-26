#ifdef USE_ROOT
#include "BDSOutputROOT.hh"
#include "BDSOutputROOTDetailed.hh"

#include "BDSDebug.hh"
#include "BDSExecOptions.hh"
#include "BDSSamplerBase.hh"
#include "BDSTrajectory.hh"
#include "BDSUtilities.hh"
#include "BDSHistogram.hh"

#include <string>

BDSOutputROOTDetailed::BDSOutputROOTDetailed()
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "output format ROOT detailed"<<G4endl;
#endif
}

BDSOutputROOTDetailed::~BDSOutputROOTDetailed()
{;}

TTree* BDSOutputROOTDetailed::BuildSamplerTree(G4String name)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  
  TTree* SamplerTree = BDSOutputROOT::BuildSamplerTree(name);
  
  SamplerTree->Branch("E0",  &E0,  "E0/F" ); // (GeV)
  SamplerTree->Branch("x0",  &x0,  "x0/F" ); // (m)
  SamplerTree->Branch("y0",  &y0,  "y0/F" ); // (m)
  SamplerTree->Branch("z0",  &z0,  "z0/F" ); // (m)
  SamplerTree->Branch("xp0", &xp0, "xp0/F"); // (rad)
  SamplerTree->Branch("yp0", &yp0, "yp0/F"); // (rad)
  SamplerTree->Branch("zp0", &zp0, "zp0/F"); // (rad)
  SamplerTree->Branch("t0",  &t0,  "t0/F" ); // (ns)

  SamplerTree->Branch("E_prod",  &E_prod,  "E_prod/F" ); // (GeV)
  SamplerTree->Branch("x_prod",  &x_prod,  "x_prod/F" ); // (m)
  SamplerTree->Branch("y_prod",  &y_prod,  "y_prod/F" ); // (m)
  SamplerTree->Branch("z_prod",  &z_prod,  "z_prod/F" ); // (m)
  SamplerTree->Branch("xp_prod", &xp_prod, "xp_prod/F"); // (rad)
  SamplerTree->Branch("yp_prod", &yp_prod, "yp_prod/F"); // (rad)
  SamplerTree->Branch("zp_prod", &zp_prod, "zp_prod/F"); // (rad)
  SamplerTree->Branch("t_prod",  &t_prod,  "t_prod/F" ); // (ns)

  SamplerTree->Branch("E_lastScat",  &E_lastScat,  "E_lastScat/F");  // (GeV)
  SamplerTree->Branch("x_lastScat",  &x_lastScat,  "x_lastScat/F");  // (m)
  SamplerTree->Branch("y_lastScat",  &y_lastScat,  "y_lastScat/F");  // (m)
  SamplerTree->Branch("z_lastScat",  &z_lastScat,  "z_lastScat/F");  // (m)
  SamplerTree->Branch("xp_lastScat", &xp_lastScat, "xp_lastScat/F"); // (rad)
  SamplerTree->Branch("yp_lastScat", &yp_lastScat, "yp_lastScat/F"); // (rad)
  SamplerTree->Branch("zp_lastScat", &zp_lastScat, "zp_lastScat/F"); // (rad)
  SamplerTree->Branch("t_lastScat",  &t_lastScat,  "t_lastScat/F");  // (ns)
  
  SamplerTree->Branch("X",  &X,  "X/F");  // (m)
  SamplerTree->Branch("Y",  &Y,  "Y/F");  // (m)
  SamplerTree->Branch("Z",  &Z,  "Z/F");  // (m)
  SamplerTree->Branch("Xp", &Xp, "Xp/F"); // (rad)
  SamplerTree->Branch("Yp", &Yp, "Yp/F"); // (rad)
  SamplerTree->Branch("Zp", &Zp, "Zp/F"); // (rad)

  return SamplerTree;
}

void BDSOutputROOTDetailed::WriteRootHitDetailed(TTree*   Tree,
						 G4double InitTotalEnergy,
						 G4double InitX,
						 G4double InitY,
						 G4double InitZ,
						 G4double InitXPrime,
						 G4double InitYPrime,
						 G4double InitZPrime,
						 G4double InitT,
						 G4double ProdTotalEnergy,
						 G4double ProdX,
						 G4double ProdY,
						 G4double ProdZ,
						 G4double ProdXPrime,
						 G4double ProdYPrime,
						 G4double ProdZPrime,
						 G4double ProdT,
						 G4double LastScatTotalEnergy,
						 G4double LastScatX,
						 G4double LastScatY,
						 G4double LastScatZ,
						 G4double LastScatXPrime,
						 G4double LastScatYPrime,
						 G4double LastScatZPrime,
						 G4double LastScatT,
						 G4double TotalEnergy,
						 G4double LocalX,
						 G4double LocalY,
						 G4double LocalZ,
						 G4double LocalXPrime,
						 G4double LocalYPrime,
						 G4double LocalZPrime,
						 G4double GlobalT,
						 G4double GlobalX,
						 G4double GlobalY,
						 G4double GlobalZ,
						 G4double GlobalXPrime,
						 G4double GlobalYPrime,
						 G4double GlobalZPrime,
						 G4double GlobalS,
						 G4double Weight,
						 G4int    PDGtype,
						 G4int    EventNo,
						 G4int    ParentID,
						 G4int    TrackID,
						 G4int    TurnsTaken,
						 G4String Process)
{
  BDSOutputROOT::WriteRootHit(Tree,
			      TotalEnergy,
			      LocalX, LocalY, LocalZ,
			      LocalXPrime, LocalYPrime, LocalZPrime,
			      GlobalT, GlobalS,
			      Weight, PDGtype,
			      EventNo, ParentID, TrackID, TurnsTaken, Process,
			      false); // don't fill tree yet
  
  E0          = InitTotalEnergy/ CLHEP::GeV;
  x0          = InitX          / CLHEP::m;
  y0          = InitY          / CLHEP::m;
  z0          = InitZ          / CLHEP::m;
  xp0         = InitXPrime     / CLHEP::radian;
  yp0         = InitYPrime     / CLHEP::radian;
  zp0         = InitZPrime     / CLHEP::radian;
  t0          = InitT          / CLHEP::ns;
  E_prod      = ProdTotalEnergy/ CLHEP::GeV;
  x_prod      = ProdX          / CLHEP::m;
  y_prod      = ProdY          / CLHEP::m;
  z_prod      = ProdZ          / CLHEP::m;
  xp_prod     = ProdXPrime     / CLHEP::radian;
  yp_prod     = ProdYPrime     / CLHEP::radian;
  zp_prod     = ProdZPrime     / CLHEP::radian;
  t_prod      = ProdT          / CLHEP::ns;
  E_lastScat  = LastScatTotalEnergy/ CLHEP::GeV;
  x_lastScat  = LastScatX      / CLHEP::m;
  y_lastScat  = LastScatY      / CLHEP::m;
  z_lastScat  = LastScatZ      / CLHEP::m;
  xp_lastScat = LastScatXPrime / CLHEP::radian;
  yp_lastScat = LastScatYPrime / CLHEP::radian;
  zp_lastScat = LastScatZPrime / CLHEP::radian;
  t_lastScat  = LastScatT      / CLHEP::ns;

  X           = GlobalX        / CLHEP::m;
  Y           = GlobalY        / CLHEP::m;
  Z           = GlobalZ        / CLHEP::m;
  Xp          = GlobalXPrime   / CLHEP::radian;
  Yp          = GlobalYPrime   / CLHEP::radian;
  Zp          = GlobalZPrime   / CLHEP::radian;
  
}


void BDSOutputROOTDetailed::WriteRootHit(TTree*         tree,
					 BDSSamplerHit* hit,
					 G4bool         fillTree)
{
  BDSOutputROOT::WriteRootHit(tree, hit, false); // don't fill the tree yet
  
  E0          = hit->GetInitTotalEnergy();
  x0          = hit->GetInitX();
  y0          = hit->GetInitY();
  y0          = hit->GetInitZ();
  xp0         = hit->GetInitXPrime();
  yp0         = hit->GetInitYPrime();
  zp0         = hit->GetInitZPrime();
  t0          = hit->GetInitT();
  E_prod      = hit->GetProdTotalEnergy();
  x_prod      = hit->GetProdX();
  y_prod      = hit->GetProdY();
  z_prod      = hit->GetProdZ();
  xp_prod     = hit->GetProdXPrime();
  yp_prod     = hit->GetProdYPrime();
  zp_prod     = hit->GetProdZPrime();
  t_prod      = hit->GetProdT();
  E_lastScat  = hit->GetLastScatTotalEnergy();
  x_lastScat  = hit->GetLastScatX();
  y_lastScat  = hit->GetLastScatY();
  z_lastScat  = hit->GetLastScatZ();
  xp_lastScat = hit->GetLastScatXPrime();
  yp_lastScat = hit->GetLastScatYPrime();
  zp_lastScat = hit->GetLastScatZPrime();
  t_lastScat  = hit->GetLastScatT();
  X           = hit->GetGlobalX();
  Y           = hit->GetGlobalY();
  Z           = hit->GetGlobalZ();
  Xp          = hit->GetGlobalXPrime();
  Yp          = hit->GetGlobalYPrime();
  Zp          = hit->GetGlobalZPrime();

  if (fillTree)
    {tree->Fill();}
}


void BDSOutputROOTDetailed::WritePrimary(G4double totalEnergy,
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
					 G4int    turnsTaken)
{
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  WriteRootHitDetailed(samplerTrees[0], // Primaries is the first Sampler
		       totalEnergy, 
		       x0, y0, z0, 
		       xp, yp, zp, 
		       t, 
		       totalEnergy, 
		       x0, y0, z0, 
		       xp, yp, zp, 
		       t, 
		       totalEnergy, 
		       x0, y0, z0, 
		       xp, yp, zp, 
		       t, 
		       totalEnergy, 
		       x0, y0, z0, 
		       xp, yp, zp, 
		       t, 
		       0,0,0,0,0,0,0,
		       weight, 
		       PDGType, 
		       nEvent, 
		       0, 
		       1, 
		       turnsTaken,
		       "");
}

#endif
