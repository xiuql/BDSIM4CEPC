#include "BDSGlobalConstants.hh"
#include "BDSBunch.hh"
#include <iostream>
#include "globals.hh"

const int DEBUG = 0;

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
  
}

BDSBunch::~BDSBunch()
{
  delete GaussGen;
  delete FlatGen;
}

// set options from gmad

void BDSBunch::SetOptions(struct Options& opt)
{
  G4double val;
#define _skip(nvalues) for(G4int i=0;i<nvalues;i++) InputBunchFile>>val;


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
  if(opt.distribType == "eshell")
    {
      distribType = _ESHELL;
      shellx = opt.x;
      shelly = opt.y;
      shellxp = opt.xp;
      shellyp = opt.yp;
      energySpread = opt.sigmaE;
    }
  if(opt.distribType == "guineapig_bunch")
    {
      distribType = _GUINEAPIG_BUNCH;
      inputfile = opt.distribFile;
      InputBunchFile.open(inputfile);
      if(!InputBunchFile.good()) { G4cerr<<"Cannot open bunch file "<<inputfile<<G4endl; exit(1); }
      if(DEBUG) G4cout<<"GUINEAPIG_BUNCH: skipping "<<opt.nlinesIgnore<<"  lines"<<G4endl;
      _skip(opt.nlinesIgnore * 6);
    }
  if(opt.distribType == "guineapig_slac")
    {
      distribType = _GUINEAPIG_SLAC;
      inputfile = opt.distribFile;
      InputBunchFile.open(inputfile);
      if(!InputBunchFile.good()) { G4cerr<<"Cannot open bunch file "<<inputfile<<G4endl; exit(1); }
      _skip(opt.nlinesIgnore);
    }
  if(opt.distribType == "guineapig_pairs")
    {
      distribType = _GUINEAPIG_PAIRS;
      inputfile = opt.distribFile;
      InputBunchFile.open(inputfile);
      if(!InputBunchFile.good()) { G4cerr<<"Cannot open bunch file "<<inputfile<<G4endl; exit(1); }
      _skip(opt.nlinesIgnore);
    }
  if(opt.distribType == "cain")
    {
      distribType = _CAIN;
      inputfile = opt.distribFile;
      InputBunchFile.open(inputfile);
      if(!InputBunchFile.good()) { G4cerr<<"Cannot open bunch file "<<inputfile<<G4endl; exit(1); }
      _skip(opt.nlinesIgnore);
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
      y0 = sigmaY * GaussGen->shoot() * m;
      z0 = 0;
      xp = sigmaXp * GaussGen->shoot();
      yp = sigmaYp * GaussGen->shoot();
      zp=sqrt(1.-xp*xp -yp*yp);  
      t = - sigmaT* (1.-2.*GaussGen->shoot());
      E = BDSGlobals->GetBeamKineticEnergy() * (1 + energySpread * GaussGen->shoot());
    }
  if(distribType == _RING)
    {
      if(DEBUG) G4cout<<"RING: rMin="<<rMin<<" rMax="<<rMax<<G4endl;
      
      r = ( rMin + (rMax - rMin) *  rand() / RAND_MAX ) * m;
      phi = 2 * pi * rand() / RAND_MAX;

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
  if(distribType == _ESHELL)
    {
      // generate elliptical shell - first generate on S1 and then transform into ellipse

      if(DEBUG) G4cout<<"SHELL: x="<<shellx<<" xp="<<shellxp<<G4endl;
      
      phi = 2 * pi * rand() / RAND_MAX;

      x0 = sin(phi) * shellx;
      xp = cos(phi) * shellxp;

      phi = 2 * pi * rand() / RAND_MAX;

      y0 = sin(phi) * shelly;
      yp = cos(phi) * shellyp;

      z0 = 0;


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
	    E=fabs(E)*GeV;
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

  if(distribType == _CAIN)
    {
      // Note that for the CAIN input the following variables are read in but NOT used by BDSIM:
      //     generation, weight, spin_x, spin_y, spin_z

      G4int type;
      G4int gen;
      G4int pos;
      G4double weight;
      G4double part_mass;
      G4double px,py,pz;
      G4double sx;
      G4double sy;
      G4double sz;
      G4String dbl_var;
      G4String rep = 'E';      
      #define  _READ(value) InputBunchFile>>value

      if(_READ(type))
	{
	  
	  _READ(gen); // Read in but not currently used
	  
	  _READ(dbl_var);
	  if(dbl_var.contains('D'))
	    {
	      pos = dbl_var.first('D');
	      weight = atof( dbl_var.replace(pos,1,rep.data(),1) );
	    }
	  else weight = atof(dbl_var);
	  // weight read in but not currently used
	  
	  _READ(dbl_var);
	  if(dbl_var.contains('D'))
	    {
	      pos = dbl_var.first('D');
	      t = atof( dbl_var.replace(pos,1,rep.data(),1) );
	    }
	  else t = atof(dbl_var);
	  
	  _READ(dbl_var);
	  if(dbl_var.contains('D'))
	    {
	      pos = dbl_var.first('D');
	      x0 = atof( dbl_var.replace(pos,1,rep.data(),1) );
	    }
	  else x0 = atof(dbl_var);
	  
	  _READ(dbl_var);
	  if(dbl_var.contains('D'))
	    {
	      pos = dbl_var.first('D');
	      y0 = atof( dbl_var.replace(pos,1,rep.data(),1) );
	    }
	  else y0 = atof(dbl_var);
	  
	  _READ(dbl_var);
	  if(dbl_var.contains('D'))
	    {
	      pos = dbl_var.first('D');
	      z0 = atof( dbl_var.replace(pos,1,rep.data(),1) );
	    }
	  else z0 = atof(dbl_var);
	  
	  _READ(dbl_var);
	  if(dbl_var.contains('D'))
	    {
	      pos = dbl_var.first('D');
	      E = atof( dbl_var.replace(pos,1,rep.data(),1) );
	    }
	  else E = atof(dbl_var);
	  
	  _READ(dbl_var);
	  if(dbl_var.contains('D'))
	    {
	      pos = dbl_var.first('D');
	      px = atof( dbl_var.replace(pos,1,rep.data(),1) );
	    }
	  else px = atof(dbl_var);
	  
	  _READ(dbl_var);
	  if(dbl_var.contains('D'))
	    {
	      pos = dbl_var.first('D');
	      py = atof( dbl_var.replace(pos,1,rep.data(),1) );
	    }
	  else py = atof(dbl_var);
	  
	  _READ(dbl_var);
	  if(dbl_var.contains('D'))
	    {
	      pos = dbl_var.first('D');
	      pz = atof( dbl_var.replace(pos,1,rep.data(),1) );
	    }
	  else pz = atof(dbl_var);
	  
	  // Spin Components read in - but not currently used
	  _READ(sx);
	  _READ(sy);
	  _READ(sz);
	  
	  if(type==1) BDSGlobals->SetParticleDefinition(G4ParticleTable::
							GetParticleTable()
							->FindParticle("gamma"));
	  else if(type==2) BDSGlobals->SetParticleDefinition(G4ParticleTable::
							     GetParticleTable()
							     ->FindParticle("e-"));
	  else if(type==3) BDSGlobals->SetParticleDefinition(G4ParticleTable::
							     GetParticleTable()
							     ->FindParticle("e+"));
	  
	  t*= m/c_light;
	  x0*= m;
	  y0*= m;
	  z0*= m;
	  E*=eV;
	  px*=eV/c_light;
	  py*=eV/c_light;
	  pz*=eV/c_light;
	  
	  part_mass = BDSGlobals->GetParticleDefinition()->GetPDGMass();	    
	  
	  // use the Kinetic energy:
	  E-=part_mass;
	  
	  // calculate the momentum direction needed for BDSPrimaryGenerator
	  xp = px*c_light / sqrt(E*E + 2*E*part_mass);
	  yp = py*c_light / sqrt(E*E + 2*E*part_mass);
	  zp = pz*c_light / sqrt(E*E + 2*E*part_mass);
	  /*	  
	  G4cout << "Bunch input was: " << G4endl;
	  G4cout << type << "\t"
		 << gen << "\t"
		 << weight << "\t"
		 << t/m << "\t"
		 << x0/m << "\t"
		 << y0/m << "\t"
		 << z0/m << "\t"
		 << E/eV << "\t"
		 << px/(eV/c_light) << "\t"
		 << py/(eV/c_light) << "\t"
		 << pz/(eV/c_light) << "\t"
		 << sx << "\t"
		 << sy << "\t"
		 << sz << "\t"
		 << xp << "\t"
		 << yp << "\t"
		 << zp << "\t"
		 << G4endl << G4endl;
	  */	  
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
