/* BDSIM code.    Version 2.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 9.4.2004
   Copyright (c) 2004 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
// BDSAcceleratorType
#include "BDSAcceleratorType.hh"

// Class BDSAcceleratorType 
BDSAcceleratorType::BDSAcceleratorType( const G4String& Type, 
                                  const G4String& PhaseSpace)
 :itsPhaseSpaceType(PhaseSpace),itsType(Type)
{
  if(Type=="tesla"){SetUpTesla();}
  if(Type=="clic"){SetUpClic();}
  if(Type=="clic500"){SetUpClic500();}
  if(Type=="nlc"){SetUpNLC();}
  if(Type=="atf"){SetUpATF();}
  if(Type=="PETRA"){SetUpPETRA();}
  if(Type=="ILC"){SetUpILC();}

  itsBeamKineticEnergy=itsBeamTotalEnergy-
                         itsBeamParticleDefinition->GetPDGMass();
  itsGamma = itsBeamTotalEnergy/(itsBeamParticleDefinition->GetPDGMass());
  itsXEmittance=itsNormalisedXEmittance /itsGamma ;
  itsYEmittance=itsNormalisedYEmittance /itsGamma ;
  itsSigmaE= itsGaussianRelativeEnergySpread*itsBeamTotalEnergy;

  itsSigmaT=itsSigmaZ/c_light;
  itsSigmaX=sqrt(itsBetaX * itsXEmittance);
  itsSigmaXprime =sqrt(itsXEmittance/itsBetaX);
  itsSigmaY=sqrt(itsBetaY * itsYEmittance);
  itsSigmaYprime =sqrt(itsYEmittance/itsBetaY);

  itsHaloSigmaX=      1.25*itsXCollimationDepthInSigma*itsSigmaX;
  itsHaloSigmaXprime= 1.25*itsXPrimeCollimationDepthInSigma*itsSigmaXprime;
  itsHaloSigmaY=      1.25*itsYCollimationDepthInSigma*itsSigmaY;
  itsHaloSigmaYprime= 1.25*itsYPrimeCollimationDepthInSigma*itsSigmaYprime;

}


void BDSAcceleratorType::SetUpILC()
{// GAB Dec04
                                                                                
   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   itsBeamParticleDefinition= particleTable->FindParticle("e-");
   // tmp for muon studies
   //itsBeamParticleDefinition= particleTable->FindParticle("mu-");
                                                                                
   itsBeamTotalEnergy= 250*GeV;
                                                                                
   itsBeamMomentum=sqrt(pow(itsBeamTotalEnergy,2)-
                        pow(itsBeamParticleDefinition->GetPDGMass(),2));
                                                                                
   itsBetaX  = 50.525915605603 *m ;
   itsBetaY  = 9.563928674469  *m ;
                                                                                
   itsAlphaX=-2.379589233378;
   itsAlphaY=0.51099718123;
                                                                                
   itsSigmaZ = 0.0003*m ;   //please change
                                                                                
   itsNormalisedXEmittance = 3.6e-06*m  ;
   itsNormalisedYEmittance = 0.04e-06*m  ;
   itsBunchCharge          = 0.75e+10;
                                                                                
  // electrons (after undulator for positron production:)
     //itsRelativeEnergySpread=1.5e-3;
  // positrons (no undulator)
   itsGaussianRelativeEnergySpread=3.2e-4 ;  //please change
   itsEDisType="gaussian";
   
   // Halo variables:
   itsXCollimationDepthInSigma      = 27.;
   itsXPrimeCollimationDepthInSigma = 27.;
   itsYCollimationDepthInSigma      = 115.;
   itsYPrimeCollimationDepthInSigma = 115.;
   
   itsHaloLowerRelativeEnergySpread = 0.99;    //please change
   itsHaloUpperRelativeEnergySpread = 1.01;   //please change
   
   // may need to be updated to take account of supercondicting linac:
   itsTemperature=300*kelvin;
   
}



void BDSAcceleratorType::SetUpATF()
{

   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   itsBeamParticleDefinition= particleTable->FindParticle("e-");

   itsBeamTotalEnergy= 1.542282 * GeV;

   itsBeamMomentum=sqrt(pow(itsBeamTotalEnergy,2)-
			pow(itsBeamParticleDefinition->GetPDGMass(),2));

   itsBetaX  = 5.198*m ;
   itsBetaY  = 2.515*m ;  

   itsAlphaX=0; 
   itsAlphaY=0; 

   itsSigmaZ = 0.0003*m ;   //please change

   itsNormalisedXEmittance = 4.e-06*m  ; 
   itsNormalisedYEmittance = 3.e-08*m  ;
   itsBunchCharge          = 2.e+10;     


  // electrons (after undulator for positron production:)
     //itsRelativeEnergySpread=1.5e-3;
  // positrons (no undulator)
    itsGaussianRelativeEnergySpread=0. ;  //please change
   itsEDisType="gaussian";


    // Halo variables:
   itsXCollimationDepthInSigma      = 27.;    
   itsXPrimeCollimationDepthInSigma = 27.;
   itsYCollimationDepthInSigma      = 115.;
   itsYPrimeCollimationDepthInSigma = 115.;

   itsHaloLowerRelativeEnergySpread = 0.99;    //please change
   itsHaloUpperRelativeEnergySpread = 1.01;   //please change

   // may need to be updated to take account of supercondicting linac:
   itsTemperature=300*kelvin;
}

void BDSAcceleratorType::SetUpNLC()
{

   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   itsBeamParticleDefinition= particleTable->FindParticle("e-");

   itsBeamTotalEnergy= 250*GeV;

   itsBeamMomentum=sqrt(pow(itsBeamTotalEnergy,2)-
			pow(itsBeamParticleDefinition->GetPDGMass(),2));

   itsBetaX  = 3.583020037e1*m ;
   itsBetaY  = 7.070002341*m ;  

   itsAlphaX=6.981042876e-3; 
   itsAlphaY=2.089118084e-2; 

   itsSigmaZ = 0.0003*m ;   //please change

   itsNormalisedXEmittance = 3.6e-06*m  ; 
   itsNormalisedYEmittance = 0.04e-06*m  ;
   itsBunchCharge          = 0.75e+10;     


  // electrons (after undulator for positron production:)
     //itsRelativeEnergySpread=1.5e-3;
  // positrons (no undulator)
    itsGaussianRelativeEnergySpread=3.2e-4 ;  //please change
   itsEDisType="gaussian";


    // Halo variables:
   itsXCollimationDepthInSigma      = 27.;    
   itsXPrimeCollimationDepthInSigma = 27.;
   itsYCollimationDepthInSigma      = 115.;
   itsYPrimeCollimationDepthInSigma = 115.;

   itsHaloLowerRelativeEnergySpread = 0.99;    //please change
   itsHaloUpperRelativeEnergySpread = 1.01;   //please change

   // may need to be updated to take account of supercondicting linac:
   itsTemperature=300*kelvin;
}





void BDSAcceleratorType::SetUpTesla()
{

   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   itsBeamParticleDefinition= particleTable->FindParticle("e-");

   itsBeamTotalEnergy= 250*GeV;

   itsBeamMomentum=sqrt(pow(itsBeamTotalEnergy,2)-
			pow(itsBeamParticleDefinition->GetPDGMass(),2));

   itsBetaX  = 163.0*m ;
   itsBetaY  = 54.5*m ;

   itsAlphaX=0.;
   itsAlphaY=0.;

   itsSigmaZ = 0.0003*m ;

   itsNormalisedXEmittance = 10.0e-06*m  ;
   itsNormalisedYEmittance = 0.03e-06*m  ;
   itsBunchCharge          = 2.0e+10;


   // electrons (after undulator for positron production:)
   itsGaussianRelativeEnergySpread=1.5e-3;
   // positrons (no undulator)
   //itsGaussianRelativeEnergySpread=3.2e-4 ;
   itsEDisType="gaussian";


    // Halo variables:
   itsXCollimationDepthInSigma      = 13.;
   itsXPrimeCollimationDepthInSigma = 13.;
   itsYCollimationDepthInSigma      = 80.;
   itsYPrimeCollimationDepthInSigma = 80.;

   itsHaloLowerRelativeEnergySpread = 0.97;
   itsHaloUpperRelativeEnergySpread = 1.005;

   // may need to be updated to take account of supercondicting linac:
   itsTemperature=300*kelvin;
}

void BDSAcceleratorType::SetUpClic()
{
   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   itsBeamParticleDefinition= particleTable->FindParticle("e-");

   itsBeamTotalEnergy= 1500*GeV;

   itsBeamMomentum=sqrt(pow(itsBeamTotalEnergy,2)-
			pow(itsBeamParticleDefinition->GetPDGMass(),2));

   //   itsBetaX  = 65.0*m ;
   //   itsBetaY  = 18.0*m ;
   itsBetaX = 64.171*m;
   itsBetaY = 18.2438*m;

   itsAlphaX=-1.95133;
   itsAlphaY= 0.605865;

   itsSigmaZ = 30.e-6*m ;

   itsNormalisedXEmittance = 0.68e-06*m  ;
   itsNormalisedYEmittance = 0.01e-06*m  ;
   itsBunchCharge          = 4.0e+9;


   itsEDisType="flat";
   // gaussian equivalent
   itsGaussianRelativeEnergySpread = 2.8e-3 ;
   // flat distribution
   itsFlatRelativeEnergySpread = 1.e-2 ;

    // Halo variables:
   itsXCollimationDepthInSigma      = 10.;
   itsXPrimeCollimationDepthInSigma = 10.;
   itsYCollimationDepthInSigma      = 70.;
   itsYPrimeCollimationDepthInSigma = 70.;

   itsHaloLowerRelativeEnergySpread = 0.98;
   itsHaloUpperRelativeEnergySpread = 1.02;

   itsTemperature=300*kelvin;

}

void BDSAcceleratorType::SetUpPETRA()
{

   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   itsBeamParticleDefinition= particleTable->FindParticle("e-");

   itsBeamTotalEnergy= 7*GeV;

   itsBeamMomentum=sqrt(pow(itsBeamTotalEnergy,2)-
			pow(itsBeamParticleDefinition->GetPDGMass(),2));

   itsBetaX  = 163.0*m ;
   itsBetaY  = 54.5*m ;

   itsAlphaX=0.;
   itsAlphaY=0.;

   itsSigmaZ = 0.0003*m ;

   itsNormalisedXEmittance = 0*m  ;
   itsNormalisedYEmittance = 0*m  ;
   itsBunchCharge          = 1.0e+9;


   // electrons (after undulator for positron production:)
   itsGaussianRelativeEnergySpread=0;
   // positrons (no undulator)
   //itsGaussianRelativeEnergySpread=3.2e-4 ;
   itsEDisType="gaussian";


    // Halo variables:
   itsXCollimationDepthInSigma      = 13.;
   itsXPrimeCollimationDepthInSigma = 13.;
   itsYCollimationDepthInSigma      = 80.;
   itsYPrimeCollimationDepthInSigma = 80.;

   itsHaloLowerRelativeEnergySpread = 0.97;
   itsHaloUpperRelativeEnergySpread = 1.005;

   // may need to be updated to take account of supercondicting linac:
   itsTemperature=300*kelvin;
}



void BDSAcceleratorType::SetUpClic500()
{
   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   itsBeamParticleDefinition= particleTable->FindParticle("e-");

   // parameter updated after email from F.Zimmermann 21.8.02
   itsBeamTotalEnergy= 250*GeV;

   itsBeamMomentum=sqrt(pow(itsBeamTotalEnergy,2)-
			pow(itsBeamParticleDefinition->GetPDGMass(),2));

   itsBetaX  = 8.44404*m ;
   itsBetaY  = 28.4579*m ;
   itsSigmaZ = 30.e-6*m ;

   itsNormalisedXEmittance = 2.0e-06*m  ;
   itsNormalisedYEmittance = 0.01e-06*m  ;
   itsBunchCharge          = 4.0e+9;

   //   itsRelativeEnergySpread = 2.8e-3 ;

    // Halo variables:
   itsXCollimationDepthInSigma      = 10.;
   itsXPrimeCollimationDepthInSigma = 10.;
   itsYCollimationDepthInSigma      = 70.;
   itsYPrimeCollimationDepthInSigma = 70.;

   itsHaloLowerRelativeEnergySpread = 0.98;
   itsHaloUpperRelativeEnergySpread = 1.02;


   itsAlphaX=0.62103;
   itsAlphaY=-1.91574;

   itsTemperature=300*kelvin;

   // the following are just copied from CLIC 3 TeV part
   itsEDisType="flat";
   // gaussian equivalent
   itsGaussianRelativeEnergySpread = 2.8e-3 ;
   // flat distribution
   itsFlatRelativeEnergySpread = 1.e-2 ;

}

BDSAcceleratorType::~BDSAcceleratorType()
{}

