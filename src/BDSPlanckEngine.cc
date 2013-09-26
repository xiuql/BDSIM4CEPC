/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
//      ------------ BDSPlanckEngine physics process --------
//                     by Grahame Blair, 19 October 2001

#include "BDSPlanckEngine.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh" 

 
BDSPlanckEngine::BDSPlanckEngine(G4double Temperature)
  : itsTemperature(Temperature)
{
 if(itsTemperature<=0.)
      {G4Exception("BDSPlanckEngine: Invalid Temperature", "-1", FatalException, "");}
  kT=CLHEP::k_Boltzmann*Temperature;

  a=1.266;
  b=-0.6;
  c=0.648;

  x1=c;
  x2=(log(c)-a)/b;

  area1 = x1*x1/2;
  area2 = area1 + c*(x2-x1);
  area3=(- exp(a+b*x2)/b);
  TotalArea = area2 + area3;

} 
 
 
BDSPlanckEngine::~BDSPlanckEngine(){}


G4LorentzVector BDSPlanckEngine::PerformPlanck()
{

  // Generate Planck Spectrum photon; using method described by
  // H.Burkardt, SL/Note 93-73

  G4double phi=CLHEP::twopi * G4UniformRand() ;
  G4double sinphi=sin(phi);
  G4double cosphi=cos(phi);

  G4double costh=2.*G4UniformRand()-1.;
  G4double sinth=sqrt(1-costh*costh);

  G4int ntry=0;



 G4double x;
 G4bool repeat=true;

 do {ntry++;
      G4double area=TotalArea*G4UniformRand();
      if(area<=area1)
	{x=sqrt(2.*area);
	if(x*G4UniformRand()<=PlanckSpectrum(x))repeat=false;    
	}
      else
	{ if(area<=area2)
	   {x=x1+ (area-area1)/c ;
	    if(c*G4UniformRand()<=PlanckSpectrum(x))repeat=false;    
	   }
	  else
	   {x= (log((area-TotalArea)*b) - a)/b; 
	    if(exp(a+b*x)*G4UniformRand()<=PlanckSpectrum(x))repeat=false;    
	   }
	}
  }while(ntry<ntryMax && repeat);


 if(ntry==ntryMax)G4Exception("BDSPlanckEngine:Max number of loops exceeded", "-1", FatalException, "");

 G4double Egam=kT*x;

 itsFourMom.setPx(Egam*sinth*cosphi);
 itsFourMom.setPy(Egam*sinth*sinphi);
 itsFourMom.setPz(Egam*costh);
 itsFourMom.setE(Egam);
 
 return itsFourMom;
}


