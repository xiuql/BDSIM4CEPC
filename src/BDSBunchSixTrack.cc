#include "BDSBunchSixTrack.hh"
#include "BDSGlobalConstants.hh"
#include "BDSDebug.hh"
#include <iostream>
#include <fstream>

BDSBunchSixTrack::BDSBunchSixTrack()
{ 
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  useCurvilinear = true; // need to always convert from curvilinear
  iPart = 0;
  nPart = 0;
}

BDSBunchSixTrack::~BDSBunchSixTrack()
{
  for(auto i : sixtrackData)
    {delete i;}
}

void BDSBunchSixTrack::LoadSixTrackFile()
{ 
  // SixTrack file is always LPI file
  // header LPI : 1=sixtrackParticleID, 2=turn, 3=s [m], 4=x[mm], 5=xp[mrad], 6=y[mm], 7=yp[mrad], 8=dE/E, 9=type, 10=turns in machine after first hits on collimators

#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif

  // open file and read line by line and extract values
  std::ifstream infile(fileName.c_str());

  if (!infile)
    {
      G4cout << __METHOD_NAME__ << "\"" << fileName << "\" file doesn't exist - exiting as no input" << G4endl;
      exit(1);
    }
  else
    {G4cout << __METHOD_NAME__ << "Reading as SixTrack input " << fileName << "\"" << G4endl;}
  
  // variable for storage
  double sixtrackParticleID = 0.0;
  double turn  = 0.0;
  double s     = 0.0;
  double x     = 0.0; 
  double xp    = 0.0;
  double y     = 0.0;
  double yp    = 0.0;
  double en    = 0.0;
  double type  = 0.0;
  double turns = 0.0;

  // read single line 
  while(infile >> sixtrackParticleID >> turn >> s >> x >> xp >> y >> yp >> en >> type >> turns)
    {
      double *values =  new double[10];
    
      // append values to storage vector
      values[0] = sixtrackParticleID;
      values[1] = turn;
      values[2] = s;
      values[3] = x;
      values[4] = xp;
      values[5] = y;
      values[6] = yp;
      values[7] = en;
      values[8] = type;
      values[9] = turns;
      
      sixtrackData.push_back(values);
    }

  nPart = sixtrackData.size();
  return;
}

void BDSBunchSixTrack::SetOptions(GMAD::Options& opt)
{
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << " " << opt.distribFile << G4endl;
#endif

  BDSBunchInterface::SetOptions(opt);
  SetDistribFile(G4String(opt.distribFile)); 
  LoadSixTrackFile();
}

void BDSBunchSixTrack::GetNextParticle(G4double& x0, G4double& y0, G4double& z0, 
				       G4double& xp, G4double& yp, G4double& zp,
				       G4double& t , G4double&  E, G4double& weight)
{
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif

  z0 = sixtrackData[iPart][2] * CLHEP::m;
  x0 = sixtrackData[iPart][3] * CLHEP::mm; 
  xp = sixtrackData[iPart][4] * CLHEP::mrad;
  y0 = sixtrackData[iPart][5] * CLHEP::mm;
  yp = sixtrackData[iPart][6] * CLHEP::mrad;
  G4double beamenergy = BDSGlobalConstants::Instance()->GetParticleTotalEnergy();
  E  = beamenergy + sixtrackData[iPart][7] * beamenergy;
  weight = 1.;
  t      = 0.;
  zp     = CalculateZp(xp,yp,1.);

  ApplyCurvilinearTransform(x0, y0, z0, xp, yp, zp);

  iPart++;

  // if all particles are read, start at 0 again
  if (iPart == nPart)
    {
      iPart=0;
      G4cout << __METHOD_NAME__ << "End of file reached. Returning to beginning of file." << G4endl;
    }
  return;
}

