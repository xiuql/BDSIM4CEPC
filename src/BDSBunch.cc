#include "BDSGlobalConstants.hh"
#include "BDSBunch.hh"
#include <iostream>
#include "globals.hh"

using namespace std;

extern G4bool verbose;      // run options
extern G4bool verboseStep;
extern G4bool verboseEvent;
extern G4int verboseEventNumber;
extern G4bool isBatch;

BDSBunch::BDSBunch()
{
  sigmaX = 0;
  sigmaY = 0;
  sigmaT = 0;

  sigmaXp = 0;
  sigmaYp = 0;
  
  X0 = 0;
  Y0 = 0;
  Xp0 = 0;
  Yp0 = 0;
  
  betaX = 0;
  betaY = 0;
  alphaX = 0;
  alphaY = 0;
  emitX = 0;
  emitY = 0;

  distribType = _GAUSSIAN;
  
  GaussGen=new RandGauss(*HepRandom::getTheEngine());
  FlatGen=new RandFlat(*HepRandom::getTheEngine());
  
};

BDSBunch::~BDSBunch()
{
  delete GaussGen;
  delete FlatGen;
};

// set options from gmad

void BDSBunch::SetOptions(struct Options& opt)
{

  distribType = _GAUSSIAN; // default

  if(opt.distribType == "gauss")
    {
      distribType = _GAUSSIAN; 
      SetSigmaX(opt.sigmaX); 
      SetSigmaY(opt.sigmaY);
      SetSigmaXp(opt.sigmaXp);
      SetSigmaYp(opt.sigmaYp);
      SetSigmaT(opt.sigmaT);
      energySpread = opt.sigmaE;
    }
  if(opt.distribType == "ring")
    {
      distribType = _RING; 
      X0 = opt.X0;
      Y0 = opt.Y0;
      rMin = opt.Rmin;
      rMax = opt.Rmax;
      energySpread = opt.sigmaE;
    }
  if(opt.distribType == "guineapig_bunch")
    {
      distribType = _GUINEAPIG_BUNCH;
      inputfile = opt.distribFile;
      InputBunchFile.open(inputfile);
    }
  if(opt.distribType == "guineapig_slac")
    {
      distribType = _GUINEAPIG_SLAC;
      inputfile = opt.distribFile;
      InputBunchFile.open(inputfile);
    }
  if(opt.distribType == "guineapig_pairs")
    {
      distribType = _GUINEAPIG_PAIRS;
      inputfile = opt.distribFile;
      InputBunchFile.open(inputfile);
    }
}

// get initial bunch distribution parameters in Gaussian case 
G4double BDSBunch::GetSigmaT() 
{
  return sigmaT;
} 

G4double BDSBunch::GetSigmaX()
{

  return sigmaX;
}
 
G4double BDSBunch::GetSigmaY()
{
  return sigmaY;
} 

G4double BDSBunch::GetSigmaXp()
{
  return sigmaXp;
}

G4double BDSBunch::GetSigmaYp()
{
  return sigmaYp;
}

// generate primary coordinates

G4double BDSBunch::GetNextX()
{
  return sigmaX * GaussGen->shoot() * m;
} 

G4double BDSBunch::GetNextY()
{
  return sigmaX * GaussGen->shoot() * m;
}

G4double BDSBunch::GetNextZ()
{
  return 0;
}



G4double BDSBunch::GetNextXp()
{
  return sigmaXp * GaussGen->shoot();
}

G4double BDSBunch::GetNextYp()
{
  return sigmaYp * GaussGen->shoot();
}

G4double BDSBunch::GetNextT()
{
  return - sigmaT* (1.-2.*GaussGen->shoot());
}


void BDSBunch::GetNextParticle(G4double& x0,G4double& y0,G4double& z0,
			       G4double& xp,G4double& yp,G4double& zp,
			       G4double& t, G4double& E)
{

  if(verboseStep) G4cout<<"distribution type: "<<distribType<<G4endl;

  double r, phi;

  if(distribType == _GAUSSIAN)
    {
      x0 = sigmaX * GaussGen->shoot() * m;
      y0 = sigmaX * GaussGen->shoot() * m;
      z0 = 0;
      xp = sigmaXp * GaussGen->shoot();
      yp = sigmaYp * GaussGen->shoot();
      zp=sqrt(1.-xp*xp -yp*yp);  
      t = - sigmaT* (1.-2.*GaussGen->shoot());
      E = BDSGlobals->GetBeamKineticEnergy() * (1 + energySpread * GaussGen->shoot());
    }
  if(distribType == _RING)
    {
      G4cout<<"RING: rMin="<<rMin<<" rMax="<<rMax<<G4endl;
      
      r = ( rMin + (rMax - rMin) *  rand() / RAND_MAX ) * m;
      phi = 2 * pi * rand() / RAND_MAX * m;

      x0 = r * sin(phi);
      y0 = r * cos(phi);
      z0 = 0;
      xp = 0;
      yp = 0;
      zp=sqrt(1.-xp*xp -yp*yp);  
      t = 0;
      E = BDSGlobals->GetBeamKineticEnergy()
	* (1 + energySpread/2. * (1. -2. * FlatGen->shoot()));
    }
  if(distribType == _GUINEAPIG_BUNCH)
    {
      #define  _READ(value) InputBunchFile>>value
      if(_READ(E))
	  {
	   _READ(x0);
	   _READ(y0);
	   _READ(z0);
	   _READ(xp);
	   _READ(yp);
	   
	   E*=GeV;
	   x0*= micrometer;
	   y0*= micrometer;
           z0*= micrometer;
           xp*=1.e-6*radian;
           yp*=1.e-6*radian;
	   zp=sqrt(1.-xp*xp -yp*yp);  
	   t=-z0/c_light;
	   // use the Kinetic energy:
	   E-=BDSGlobals->GetParticleDefinition()->GetPDGMass();
	  }
    }
  if(distribType == _GUINEAPIG_SLAC)
    {
       #define  _READ(value) InputBunchFile>>value
       if(_READ(E))
	 {
	   _READ(xp);
	   _READ(yp);
	   _READ(z0);
	   _READ(x0);
	   _READ(y0);
	   
	   E*=GeV;
	   x0*= nanometer;
	   y0*= nanometer;
	   z0*= micrometer;
	   xp*=radian;
	   yp*=radian;
	   zp=sqrt(1.-xp*xp -yp*yp);  
	   t=-z0/c_light;
	   // use the Kinetic energy:
	   E-=BDSGlobals->GetParticleDefinition()->GetPDGMass();
	 }
    }
  if(distribType == _GUINEAPIG_PAIRS)
    {
      #define  _READ(value) InputBunchFile>>value
 	if(_READ(E))
	  {
	    _READ(xp);
	    _READ(yp);
	    _READ(zp);
	    _READ(x0);
	    _READ(y0);
	    _READ(z0);
	    if(E>0) BDSGlobals->SetParticleDefinition(G4ParticleTable::
						      GetParticleTable()
						      ->FindParticle("e-"));
	    if(E<0) BDSGlobals->SetParticleDefinition(G4ParticleTable::
						      GetParticleTable()
						      ->FindParticle("e+"));
	    E=abs(E)*GeV;
	    x0*= nanometer;
	    y0*= nanometer;
	    z0*= nanometer;
	    xp*=radian;
	    yp*=radian;
	    zp*=radian;
	    // Using the sign of the pair file zp
	    // but calculating zp more accurately
	    if(zp<0) zp = -sqrt(1-(xp*xp+yp*yp));
	    else zp = sqrt(1-(xp*xp+yp*yp));
	    t=-z0/c_light;
	    // use the Kinetic energy:
	    E-=BDSGlobals->GetParticleDefinition()->GetPDGMass();
	  }
    }
}



G4double BDSBunch::GetEmitX()
{
  return emitX;
}

G4double BDSBunch::GetEmitY()
{
  return emitY;
}

G4double BDSBunch::GetAlphaX()
{
  return alphaX;
}

G4double BDSBunch::GetAlphaY()
{
  return alphaY;
}

G4double BDSBunch::GetBetaX()
{
  return betaX;
}

G4double BDSBunch::GetBetaY()
{
  return betaY;
}



// set initial bunch distribution parameters in Gaussian case 
void BDSBunch::SetSigmaT(double val) 
{
  sigmaT= val;
} 

void BDSBunch::SetSigmaX(double val)
{ 
  sigmaX = val;
}
 
void BDSBunch::SetSigmaY(double val)
{
  sigmaY = val;
} 

void BDSBunch::SetSigmaXp(double val)
{
  sigmaXp = val;
}

void BDSBunch::SetSigmaYp(double val)
{
  sigmaYp = val;
}

void BDSBunch::SetX0(double val)
{
  X0 = val;
} 

void BDSBunch::SetY0(double val)
{
  Y0 = val;
}

void BDSBunch::SetXp0(double val)
{
  Xp0 = val;
}

void BDSBunch::SetYp0(double val)
{
  Yp0 = val;
}

void BDSBunch::SetEmitX(double val)
{
  emitX = val;
}

void BDSBunch::SetEmitY(double val)
{
  emitY = val;
}

void BDSBunch::SetAlphaX(double val)
{
  alphaX = val;
}

void BDSBunch::SetAlphaY(double val)
{
  alphaY = val;
}

void BDSBunch::SetBetaX(double val)
{
  betaX = val;
}

void BDSBunch::SetBetaY(double val)
{
  betaY = val;
}
