/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSAcceleratorType_h
#define BDSAcceleratorType_h 1

#include "globals.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

class BDSAcceleratorType
{
  
public:
  //	Constructor taking the id of the dipole, the length
  //	(meter) and curvature (1/meter) of the dipole geometry,
  //	and the vertical magnetic field in Tesla.
  BDSAcceleratorType (const G4String& type, const G4String& PhaseSpace);
  
  ~BDSAcceleratorType();
  
  void SetUpTesla();
  void SetUpClic();
  void SetUpClic500();
  void SetUpNLC();
  void SetUpATF();
  void SetUpPETRA();
  void SetUpILC();


  G4String GetType();
  
  G4double GetXEmittance();
  G4double GetYEmittance();
  G4double GetBunchCharge();
  G4double GetBetaX();
  G4double GetBetaY();
  G4double GetSigmaZ();
  G4double GetSigmaE();
  G4double GetGaussianRelativeEnergySpread();
  G4double GetFlatRelativeEnergySpread();
  G4double GetBeamKineticEnergy();
  G4double GetBeamTotalEnergy();
  G4double GetBeamMomentum();
  
  G4ParticleDefinition* GetBeamParticleDefinition();
  G4double GetSigmaX();
  G4double GetSigmaXprime();
  G4double GetSigmaY();
  G4double GetSigmaYprime();
  G4double GetSigmaT();
  G4double GetAlphaX();
  G4double GetAlphaY();
  
  
  G4double GetHaloSigmaX();
  G4double GetHaloSigmaY();
  G4double GetHaloSigmaZ();
  G4double GetHaloSigmaXprime();
  G4double GetHaloSigmaYprime();
  G4double GetHaloLowerRelativeEnergySpread();
  G4double GetHaloUpperRelativeEnergySpread();

  G4double GetXCollimationDepthInSigma();
  G4double GetYCollimationDepthInSigma();
  G4double GetXPrimeCollimationDepthInSigma();
  G4double GetYPrimeCollimationDepthInSigma();
  
  G4String GetPhaseSpaceType();
  G4String GetEDisType();
  
  G4double GetTemperature();

protected:
  //  void BuildSectorBendMaterial();
  
private:
  
  G4double itsBetaX;
  G4double itsBetaY;
  G4double itsXEmittance;
  G4double itsYEmittance;
  G4double itsSigmaX;
  G4double itsSigmaY;
  G4double itsSigmaXprime;
  G4double itsSigmaYprime;
  G4double itsSigmaZ;
  G4double itsSigmaE;  
  G4double itsSigmaT;
  G4double itsBunchCharge;
  G4double itsGaussianRelativeEnergySpread;
  G4double itsFlatRelativeEnergySpread;
  G4double itsBeamTotalEnergy;
  G4double itsBeamKineticEnergy;
  
  G4double itsHaloSigmaX;
  G4double itsHaloSigmaY;
  G4double itsHaloSigmaZ;
  G4double itsHaloSigmaXprime;
  G4double itsHaloSigmaYprime;
  G4double itsHaloLowerRelativeEnergySpread;
  G4double itsHaloUpperRelativeEnergySpread;

  G4ParticleDefinition* itsBeamParticleDefinition;

  G4double itsGamma;
  G4double itsNormalisedXEmittance;
  G4double itsNormalisedYEmittance;
  
  G4double itsXCollimationDepthInSigma;
  G4double itsYCollimationDepthInSigma;
  G4double itsXPrimeCollimationDepthInSigma;
  G4double itsYPrimeCollimationDepthInSigma;
  
  G4String itsPhaseSpaceType;
  G4String itsType;
  G4String itsEDisType;
  
  G4double itsTemperature;
  G4double itsBeamMomentum;

  G4double itsAlphaX;
  G4double itsAlphaY;
};

inline G4double BDSAcceleratorType::GetXEmittance()
{return itsXEmittance; };
inline G4double BDSAcceleratorType::GetYEmittance(){return itsYEmittance;};
inline G4double BDSAcceleratorType::GetBunchCharge(){return itsBunchCharge ;};
inline G4double BDSAcceleratorType::GetBetaX(){return itsBetaX ;};
inline G4double BDSAcceleratorType::GetBetaY(){return itsBetaY ;};
inline G4double BDSAcceleratorType::GetSigmaZ(){return itsSigmaZ ;};
inline G4double BDSAcceleratorType::GetSigmaE(){return itsSigmaE ;};
inline G4double BDSAcceleratorType::GetGaussianRelativeEnergySpread()
{return itsGaussianRelativeEnergySpread ;};
inline G4double BDSAcceleratorType::GetFlatRelativeEnergySpread()
{return itsFlatRelativeEnergySpread ;};
inline G4double BDSAcceleratorType::GetBeamKineticEnergy()
{return itsBeamKineticEnergy;};
inline G4double BDSAcceleratorType::GetBeamTotalEnergy()
{return itsBeamTotalEnergy ;};
inline G4double BDSAcceleratorType::GetBeamMomentum()
{return itsBeamMomentum ;};
inline G4ParticleDefinition* BDSAcceleratorType::GetBeamParticleDefinition()
{return itsBeamParticleDefinition ;};
inline G4double BDSAcceleratorType::GetSigmaX(){return itsSigmaX ;};
inline G4double BDSAcceleratorType::GetSigmaXprime(){return itsSigmaXprime;};
inline G4double BDSAcceleratorType::GetSigmaY(){return itsSigmaY ;};
inline G4double BDSAcceleratorType::GetSigmaYprime(){return itsSigmaYprime;};
inline G4double BDSAcceleratorType::GetSigmaT(){return itsSigmaT ;};

inline G4double BDSAcceleratorType::GetAlphaX(){return itsAlphaX;};
inline G4double BDSAcceleratorType::GetAlphaY(){return itsAlphaY;};

inline G4double BDSAcceleratorType::GetHaloSigmaX(){return itsHaloSigmaX;};
inline G4double BDSAcceleratorType::GetHaloSigmaY(){return itsHaloSigmaY;};
inline G4double BDSAcceleratorType::GetHaloSigmaZ(){return itsHaloSigmaZ;};
inline G4double BDSAcceleratorType::GetHaloSigmaXprime()
{return itsHaloSigmaXprime ;};
inline G4double BDSAcceleratorType::GetHaloSigmaYprime()
{return itsHaloSigmaYprime ;};
inline G4double BDSAcceleratorType::GetHaloUpperRelativeEnergySpread()
{return itsHaloUpperRelativeEnergySpread;};
inline G4double BDSAcceleratorType::GetHaloLowerRelativeEnergySpread()
{return itsHaloLowerRelativeEnergySpread;};

inline G4String BDSAcceleratorType::GetPhaseSpaceType()
{return itsPhaseSpaceType;};
inline G4String BDSAcceleratorType::GetType()
{return itsType;};
inline G4String BDSAcceleratorType::GetEDisType()
{return itsEDisType;};

inline G4double BDSAcceleratorType::GetTemperature()
{return itsTemperature;};


inline G4double BDSAcceleratorType::GetXCollimationDepthInSigma()
{return itsXCollimationDepthInSigma ;}

inline G4double BDSAcceleratorType::GetYCollimationDepthInSigma()
{return itsYCollimationDepthInSigma ;}
inline G4double BDSAcceleratorType::GetXPrimeCollimationDepthInSigma()
{return itsXPrimeCollimationDepthInSigma ;}
inline G4double BDSAcceleratorType::GetYPrimeCollimationDepthInSigma()
{return itsYPrimeCollimationDepthInSigma ;}
  


#endif
