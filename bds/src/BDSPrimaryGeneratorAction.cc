/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: BDSPrimaryGeneratorAction.cc,v 1.2 2004/12/16 19:27:28 agapov Exp $
// GEANT4 tag $Name:  $
//
// 

//==================================================================
//==================================================================
#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSPrimaryGeneratorAction.hh"

#include "BDSDetectorConstruction.hh"
#include "BDSPrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

#include "BDSAcceleratorType.hh"
#include "BDSExtract.hh"

#include<iostream>

extern G4int event_number;
//===================================================
// Keep initial point in phase space for diagnostics
G4double initial_x,initial_xp,initial_y,initial_yp,initial_z,initial_E;

BDSPrimaryGeneratorAction::BDSPrimaryGeneratorAction(
                                               BDSDetectorConstruction* BDSDC)
:BDSDetector(BDSDC),rndmFlag("on")
{

  BDSAcceleratorType* TheAccelerator=BDSGlobals->GetAcceleratorType();

  G4int n_particle = 1;

  //create a messenger for this class
  gunMessenger = new BDSPrimaryGeneratorMessenger(this);

  particleGun  = new G4ParticleGun(n_particle);
  particleGun->SetParticleDefinition(TheAccelerator->
                                      GetBeamParticleDefinition());
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

  particleGun->
    SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,
				      -BDSGlobals->GetWorldSizeZ()));

  particleGun->SetParticleEnergy(TheAccelerator->GetBeamKineticEnergy());


  // IA: the engine should be passed by reference, not by pointer,
  // otherwise two subsequent destructor calls will crash

  GaussGen=new RandGauss( *HepRandom::getTheEngine() );
  FlatGen=new RandFlat( *HepRandom::getTheEngine() );

  if (BDSGlobals->GetReadBunchFile() && BDSGlobals->GetExtractBunchFile())
    G4Exception(" Both the Extract Bunch and the Read Bunch flags are set!");
  
  if(BDSGlobals->GetReadBunchFile())InputBunchFile.open("BDSBunch.input");
  else if (BDSGlobals->GetExtractBunchFile())
    { 
      char* filename="BDSExtract.input";
      itsBDSExtract=new BDSExtract(filename);
      itsBDSExtract->rndmst5(12,34,56,78);
      // tmp
      //      itsBDSExtractO=new BDSExtractO(filename);
    }


  // set up the case where halo is generated in shells of phasespace
  if((TheAccelerator->GetPhaseSpaceType()=="halo_flat")&&
     BDSGlobals->GetUseHaloRadius()) 
    itsBDSGen5Shell=new BDSGen5Shell(BDSGlobals->GetHaloInnerRadius(),
				     BDSGlobals->GetHaloOuterRadius());


  if(TheAccelerator->GetPhaseSpaceType()=="halo_one_over_r")
    {
      logXfactor=log(BDSGlobals->GetOuterHaloX()/BDSGlobals->GetInnerHaloX());
      logYfactor=log(BDSGlobals->GetOuterHaloY()/BDSGlobals->GetInnerHaloY());

      G4cout<<" sigma_x="<<TheAccelerator->GetSigmaX()/m<<" m"<<G4endl;
      G4cout<<" sigma_x-prime="<<TheAccelerator->GetSigmaXprime()<<G4endl;
      G4cout<<" sigma_y="<<TheAccelerator->GetSigmaY()/m<<" m"<<G4endl;
      G4cout<<" sigma_y-prime="<<TheAccelerator->GetSigmaYprime()<<G4endl;

    }

}

//===================================================

BDSPrimaryGeneratorAction::~BDSPrimaryGeneratorAction()
{
  delete particleGun; 
  delete gunMessenger;
  delete GaussGen;  
  delete FlatGen;   
  if(itsBDSExtract) delete itsBDSExtract;
}
//===================================================

void BDSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
#define  _READ(value) InputBunchFile>>value

  // temp:
  //GaussGen->shoot();
  // GaussGen->shoot();
  // GaussGen->shoot();

  //this function is called at the begining of event
  // 
  G4double x0 = 0.;
  G4double y0 = 0.;
  G4double z0 = 0.;

  // IA: added GetType()
  if(BDSGlobals->GetAcceleratorType()->GetType()!="atf")
    z0 = -BDSGlobals->GetWorldSizeZ();
  
  G4double t,dx,xp,dy,yp,zp,E,dz;
  
  BDSAcceleratorType* TheAccelerator=BDSGlobals->GetAcceleratorType();
  
  if (rndmFlag == "on")
    {
      
    if(BDSGlobals->GetExtractBunchFile())
      {
	itsBDSExtract->GenerateParticle(dx,xp,dy,yp,dz,E);
	E*=GeV;
	dx*= micrometer;
	dy*= micrometer;
	dz*= micrometer;
	xp*=1.e-6*radian;
	yp*=1.e-6*radian;
	t=-dz/c_light;

	G4cout<<" New:"<<G4endl;
	G4cout<<" E="<<E/GeV<<" dx="<<dx/m<<" dy="<<dy/m<<" dz="<<dz/m<<
	  "xp="<<xp<<" yp="<<yp<<" dz="<<dz/m<<G4endl;
	
	// gab tmp code for Daniel's off energy bunches:
	//subtract mean in yp for non-offset bunch
	yp-=0.82331E-06 *radian;


	/*
	// try the original
	itsBDSExtractO->GenerateParticle(dx,xp,dy,yp,dz,E);
	E*=GeV;
	dx*= micrometer;
	dy*= micrometer;
	dz*= micrometer;
	xp*=1.e-6*radian;
	yp*=1.e-6*radian;
	t=-dz/c_light;

	G4cout<<" Original:"<<G4endl;

	G4cout<<" E="<<E/GeV<<" dx="<<dx/m<<" dy="<<dy/m<<" dz="<<dz/m<<
	  "xp="<<xp<<" yp="<<yp<<" dz="<<dz/m<<G4endl;
	
	// gab tmp code for Daniel's off energy bunches:
	//subtract mean in yp for non-offset bunch
	yp-=0.82331E-06 *radian;
	*/
	
      }
    else if(BDSGlobals->GetReadBunchFile())
      {
	E=0.;
	dx=0.;
	dy=0.;
	dz=0.;
	xp=0.;
	yp=0.;
	if(_READ(E))
	  {
	   _READ(dx);
	   _READ(dy);
	   _READ(dz);
	   _READ(xp);
	   _READ(yp);
	   
	   E*=GeV;
	   dx*= micrometer;
	   dy*= micrometer;
           dz*= micrometer;
           xp*=1.e-6*radian;
           yp*=1.e-6*radian;
	   t=-dz/c_light;
	   // use the Kinetic energy:
	   E-=TheAccelerator->GetBeamParticleDefinition()->GetPDGMass();
	  }
      }
    else
      {
	t = -TheAccelerator->GetSigmaT()* (1.-2.*GaussGen->shoot());
	// minus sign because things are defined at a single starting z value.
	if(TheAccelerator->GetPhaseSpaceType()=="normal")
	  {
	    if(TheAccelerator->GetAlphaX())
	      {
		dx=TheAccelerator->GetSigmaX()*GaussGen->shoot();
		G4double t=TheAccelerator->GetSigmaX()*GaussGen->shoot();
		xp = (t-TheAccelerator->GetAlphaX()*dx)/
		  TheAccelerator->GetBetaX();
		  //dx=TheAccelerator->GetSigmaX()*GaussGen->shoot()*
		  //sin(phix);
		  //xp=TheAccelerator->GetSigmaXprime()*GaussGen->shoot()*
		  //(cos(phix)-TheAccelerator->GetAlphaX()*sin(phix));
	      }
	    else
	      {
		dx=TheAccelerator->GetSigmaX()*GaussGen->shoot();
		xp= TheAccelerator->GetSigmaXprime() * GaussGen->shoot();
	      }
	    
	    if(TheAccelerator->GetAlphaY())
	      {
		dy=TheAccelerator->GetSigmaY()*GaussGen->shoot();
		G4double t=TheAccelerator->GetSigmaY()*GaussGen->shoot();
		yp = (t-TheAccelerator->GetAlphaY()*dy)/
		  TheAccelerator->GetBetaY();
		//dy=TheAccelerator->GetSigmaY()*GaussGen->shoot()*
		// sin(phiy);
		//yp=TheAccelerator->GetSigmaYprime()*GaussGen->shoot()*
		//  (cos(phiy)-TheAccelerator->GetAlphaY()*sin(phiy));
	      }
	    else
	      {
		dy= TheAccelerator->GetSigmaY()      * GaussGen->shoot();
		yp= TheAccelerator->GetSigmaYprime() * GaussGen->shoot();
	      }
    
	    if(TheAccelerator->GetEDisType()=="gaussian")
	      {
		E = TheAccelerator->GetBeamKineticEnergy()
		  + TheAccelerator->GetSigmaE() *GaussGen->shoot();}
	    else
	      {
		E = TheAccelerator->GetBeamKineticEnergy()*
		  (1+TheAccelerator->GetFlatRelativeEnergySpread()/2.
		   *(1.-2.*FlatGen->shoot()));
	      }
	  }
	else if(TheAccelerator->GetPhaseSpaceType()=="halo_flat")
	  {

	    if(BDSGlobals->GetUseHaloRadius())
	      {
		// generate a point in a five dimensional shell
		// determined by variables HaloInnerRadius and HaloOuterRadius

		G4bool lEok=false;
		G4double dElo,dEhi;


		dElo=1.-TheAccelerator->GetHaloLowerRelativeEnergySpread();
		dEhi=TheAccelerator->GetHaloUpperRelativeEnergySpread()-1.;

		G4double dEmax=dElo;
		if(dEhi>dElo)dEmax=dEhi;
		
		do
		  {
		    G4double *genVec= itsBDSGen5Shell->GenPoint();


		    //G4double dE=TheAccelerator->GetBeamKineticEnergy()*
		    // (TheAccelerator->GetHaloUpperRelativeEnergySpread()-
		    // TheAccelerator->GetHaloLowerRelativeEnergySpread())
		    //*genVec[4]/2.;
		    G4double dE=dEmax*genVec[4];

		    //G4cout<<" dE="<<dE<<" dEmax="<<dEmax<<" dEhi="<<dEhi<<
		    //"dElo="<<dElo<<G4endl;
		    //  E = (TheAccelerator->GetHaloLowerRelativeEnergySpread()
		    // +TheAccelerator->GetHaloUpperRelativeEnergySpread())/2
		    // *TheAccelerator->GetBeamKineticEnergy()
		    // + dE;

		    if((dE>0 && dE<dEhi)||(dE<0)&&(-dE<dElo))
		      {
			lEok=true;
			E = TheAccelerator->GetBeamKineticEnergy()*(1.+ dE);
			dx= TheAccelerator->GetXCollimationDepthInSigma()*
			  TheAccelerator->GetSigmaX()*genVec[0];
			xp= TheAccelerator->GetXPrimeCollimationDepthInSigma()*
			  TheAccelerator->GetSigmaXprime()*genVec[1];
			dy= TheAccelerator->GetYCollimationDepthInSigma()*
			  TheAccelerator->GetSigmaY()*genVec[2];
			yp= TheAccelerator->GetYPrimeCollimationDepthInSigma()*
			  TheAccelerator->GetSigmaYprime()*genVec[3];
		      }
		  }while(lEok==false);
	      }
	    else
	      {
		dx= TheAccelerator->GetHaloSigmaX()*
		  (1.-2.*FlatGen->shoot());
		xp= TheAccelerator->GetHaloSigmaXprime()*
		  (1.-2.*FlatGen->shoot());
		dy= TheAccelerator->GetHaloSigmaY()*
		  (1.-2.*FlatGen->shoot());
		yp= TheAccelerator->GetHaloSigmaYprime()*
		  (1.-2.*FlatGen->shoot());
		E = TheAccelerator->GetBeamKineticEnergy()*
		  (TheAccelerator->GetHaloLowerRelativeEnergySpread() +
		   (TheAccelerator->GetHaloUpperRelativeEnergySpread() -
		    TheAccelerator->GetHaloLowerRelativeEnergySpread())
		   *(1.-2.*FlatGen->shoot()) );
	      }
	  }
	else if(TheAccelerator->GetPhaseSpaceType()=="halo_one_over_r")
	  {
	    G4double theta;
	    G4double r;

	    theta=twopi*FlatGen->shoot();
	    r=BDSGlobals->GetInnerHaloX()*exp(FlatGen->shoot()*logXfactor);
	    dx=TheAccelerator->GetSigmaX()*r*cos(theta);
	    xp=TheAccelerator->GetSigmaXprime()*r*sin(theta);

	    theta=twopi*FlatGen->shoot();
	    r=BDSGlobals->GetInnerHaloY()*exp(FlatGen->shoot()*logYfactor);
	    dy=TheAccelerator->GetSigmaY()*r*cos(theta);
	    yp=TheAccelerator->GetSigmaYprime()*r*sin(theta);

	    E = TheAccelerator->GetBeamKineticEnergy()*
	      (1. + 1.e-2*GaussGen->shoot());
	  }
      }
    }


  x0+=dx;
  y0+=dy;
 

  // tmp    
  /*
    xp=0.;
    yp=0.;
    E=TheAccelerator->GetBeamKineticEnergy();
  */  
		      //     t=0.;
     //    y0=1.e-6*m;

 
  /*
  E=TheAccelerator->GetBeamKineticEnergy();
  // tmp:
  G4double thetaTmp=twopi*FlatGen->shoot();

  x0=10*cm*cos(thetaTmp);
  y0=10*cm*sin(thetaTmp);
  yp=0;
  xp=0.;
  G4cout<<"Theta="<<thetaTmp<<" sec="<<G4int(twopi/thetaTmp)<<G4endl;

  */

  zp=sqrt(1.-xp*xp -yp*yp);  


  //  x0=4*mm;
  //y0= 0.001367*m;
  //z0= 8.192*m;
  //xp=0.0002396/22.72;
  //yp=0.0003195/22.72;
  //E=22.72*GeV ;


       //       x0 = 1*mm*(G4UniformRand()-0.5);
       //  xp=0;

  //          G4double percent=.01;
  //        E=KineticEnergy*(1. + 0.5*percent);  



  /*
       //x0 = (BDSDetector->GetBeamSizeX())*(G4UniformRand()-0.5);
       //      y0 = (BDSDetector->GetBeamSizeY())*(G4UniformRand()-0.5);
  // y0=30*cm*(G4UniformRand()-0.5);

  x0=LCBeampipeRadius*(G4UniformRand()-0.5);
  y0=LCBeampipeRadius*(G4UniformRand()-0.5);
  */
 



  //   E=KineticEnergy;  
  
  //  G4cout<<"mom dir="<<xp<<" "<< yp<<" "<<zp<<G4endl;
  //  G4cout<<"init pos="<<x0/m<<" "<< y0/m<<" "<<z0/m<<G4endl;
  // G4cout<<" E="<<E/GeV<<G4endl;
  

  // tmp:
  //      x0=3.*mm;
  //       xp=0.;
  //     E=KineticEnergy;
  //   yp=0;
  //   y0=0*cm;

  
  /*
  // temp code:
  E=TheAccelerator->GetBeamKineticEnergy();
  x0=-5.5*mm;
  y0=0.;
  xp=0.;
  yp=0.;
  zp=1.;
  */

  //----------------------	  
  //offsets:
  // Energy
  E+=BDSGlobals->GetEnergyOffset();

  // allow for any relative offsets between beamline and tunnel:
  x0+=BDSGlobals->GetHorizontalBeamlineOffset();
  y0+=BDSGlobals->GetVerticalBeamlineOffset();
  //----------------------	  

  // tmp code
  if(TheAccelerator->GetType()=="atf")
    {
      x0=0;
      y0=0;
      z0 = 1.e-4*m;
      xp=0.;
      yp=0.;
      zp=1;
      E=TheAccelerator->GetBeamKineticEnergy();
    }

  if(TheAccelerator->GetType()=="PETRA")
    {
      x0=-2.1*mm;
      y0=+3.3*mm;
      xp=0.;
      yp=0.;
      zp=1;
      E=TheAccelerator->GetBeamKineticEnergy();
    }


  /*
  // temp
//  x0=0.5*cm;
  x0=0;
  y0=0;
  xp=0.;
  yp=0.;
  zp=1;
  E=TheAccelerator->GetBeamKineticEnergy();
  // end of temp
  */

  G4ThreeVector PartMomDir=G4ThreeVector(xp,yp,zp);

  
  if(TheAccelerator->GetType()!="atf")
    PartMomDir.rotateY(BDSGlobals->GetGlobalBeamlineRotationY());

  particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  particleGun->SetParticleEnergy(E);
  particleGun->SetParticleMomentumDirection(PartMomDir);
  particleGun->SetParticleTime(t);

  particleGun->GeneratePrimaryVertex(anEvent);

  //  G4cout<<" BDSPrimaryGeneratorAction: mom="<<PartMomDir<<" Energy="<<E<<G4endl;

  // G4cout<<" BDSPrimaryGeneratorAction: z0="<<z0/m<<" m"<<G4endl;

  // save initial values outside scope for entry into the samplers:
  initial_x=x0;
  initial_xp=xp;
  initial_y=y0;
  initial_yp=yp;
  initial_z=-t*c_light;
  // total energy is used elsewhere:
  initial_E=E+TheAccelerator->GetBeamParticleDefinition()->GetPDGMass();

}


//===================================================

