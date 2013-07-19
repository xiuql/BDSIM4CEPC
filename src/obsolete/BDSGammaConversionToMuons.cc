//         ------------ G4GammaConversionToMuons physics process ------
//         by H.Burkhardt, S. Kelner and R. Kokoulin, April 2002
//
//
// 07-08-02: missprint in OR condition in DoIt : f1<0 || f1>f1_max ..etc ...
// 25-10-04: migrade to new interfaces of ParticleChange (vi)
// ---------------------------------------------------------------------------

#include "BDSGammaConversionToMuons.hh"
#include "G4EnergyLossTables.hh"
#include "G4UnitsTable.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

using namespace std;

BDSGammaConversionToMuons::BDSGammaConversionToMuons(const G4String& processName,
    G4ProcessType type):G4VDiscreteProcess (processName, type),
    LowestEnergyLimit (4*G4MuonPlus::MuonPlus()->GetPDGMass()), // 4*Mmuon
    HighestEnergyLimit(1e21*eV), // ok to 1e21eV=1e12GeV, then LPM suppression
    MeanFreePath(-1.0),CrossSecFactor(1.)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

// destructor

BDSGammaConversionToMuons::~BDSGammaConversionToMuons() // (empty) destructor
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4bool BDSGammaConversionToMuons::IsApplicable(
                                        const G4ParticleDefinition& particle)
{
   return ( &particle == G4Gamma::Gamma() );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BDSGammaConversionToMuons::BuildPhysicsTable(const G4ParticleDefinition&)
// Build cross section and mean free path tables
{  //here no tables, just calling PrintInfoDefinition
   PrintInfoDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double BDSGammaConversionToMuons::GetMeanFreePath(const G4Track& aTrack,
                                              G4double, G4ForceCondition*)

// returns the photon mean free path in GEANT4 internal units
// (MeanFreePath is a private member of the class)

{
   const G4DynamicParticle* aDynamicGamma = aTrack.GetDynamicParticle();
   G4double GammaEnergy = aDynamicGamma->GetKineticEnergy();
   G4Material* aMaterial = aTrack.GetMaterial();

   if (GammaEnergy <  LowestEnergyLimit)
     MeanFreePath = DBL_MAX;
   else
     MeanFreePath = ComputeMeanFreePath(GammaEnergy,aMaterial);

   return MeanFreePath * 1.e-4;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double BDSGammaConversionToMuons::ComputeMeanFreePath(G4double GammaEnergy,
                                                       G4Material* aMaterial)

// computes and returns the photon mean free path in GEANT4 internal units
{
  const G4ElementVector* theElementVector = aMaterial->GetElementVector();
  const G4double* NbOfAtomsPerVolume = aMaterial->GetVecNbOfAtomsPerVolume();

  G4double SIGMA = 0 ;

  for ( size_t i=0 ; i < aMaterial->GetNumberOfElements() ; i++ )
  {
    G4double AtomicZ = (*theElementVector)[i]->GetZ();
    G4double AtomicA = (*theElementVector)[i]->GetA()/(g/mole);
    SIGMA += NbOfAtomsPerVolume[i] *
      ComputeCrossSectionPerAtom(GammaEnergy,AtomicZ,AtomicA);
  }
  return SIGMA > DBL_MIN ? 1./SIGMA : DBL_MAX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double BDSGammaConversionToMuons::GetCrossSectionPerAtom(
                                   const G4DynamicParticle* aDynamicGamma,
                                         G4Element*         anElement)

// gives the total cross section per atom in GEANT4 internal units
{
   G4double GammaEnergy = aDynamicGamma->GetKineticEnergy();
   G4double AtomicZ = anElement->GetZ();
   G4double AtomicA = anElement->GetA()/(g/mole);
   G4double crossSection =
        ComputeCrossSectionPerAtom(GammaEnergy,AtomicZ,AtomicA);
   return crossSection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4double BDSGammaConversionToMuons::ComputeCrossSectionPerAtom(
                         G4double Egam, G4double Z, G4double A)
			 
// Calculates the microscopic cross section in GEANT4 internal units.
// Total cross section parametrisation from H.Burkhardt
// It gives a good description at any energy (from 0 to 10**21 eV)
{ static const G4double Mmuon=G4MuonPlus::MuonPlus()->GetPDGMass();
  static const G4double Mele=electron_mass_c2;
  static const G4double Rc=elm_coupling/Mmuon; // classical particle radius
  static const G4double sqrte=sqrt(exp(1.));
  static const G4double PowSat=-0.88;

  static G4double CrossSection = 0.0 ;

  if ( A < 1. ) return 0;
  if ( Egam < 4*Mmuon ) return 0 ; // below threshold return 0

  static G4double EgamLast=0,Zlast=0,PowThres,Ecor,B,Dn,Zthird,Winfty,WMedAppr,
      Wsatur,sigfac;
  
  if(Zlast==Z && Egam==EgamLast) return CrossSection; // already calculated
  EgamLast=Egam;
  
  if(Zlast!=Z) // new element
  { Zlast=Z;
    if(Z==1) // special case of Hydrogen
    { B=202.4;
      Dn=1.49;
    }
    else
    { B=183.;
      Dn=1.54*pow(A,0.27);
    }
    Zthird=pow(Z,-1./3.); // Z**(-1/3)
    Winfty=B*Zthird*Mmuon/(Dn*Mele);
    WMedAppr=1./(4.*Dn*sqrte*Mmuon);
    Wsatur=Winfty/WMedAppr;
    sigfac=4.*fine_structure_const*Z*Z*Rc*Rc;
    PowThres=1.479+0.00799*Dn;
    Ecor=-18.+4347./(B*Zthird);
  }
  G4double CorFuc=1.+.04*log(1.+Ecor/Egam);
  G4double Eg=pow(1.-4.*Mmuon/Egam,PowThres)*pow( pow(Wsatur,PowSat)+
              pow(Egam,PowSat),1./PowSat); // threshold and saturation
  CrossSection=7./9.*sigfac*log(1.+WMedAppr*CorFuc*Eg);
  CrossSection*=CrossSecFactor; // increase the CrossSection by  (by default 1)
  return CrossSection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void BDSGammaConversionToMuons::SetCrossSecFactor(G4double fac)
// Set the factor to artificially increase the cross section
{ CrossSecFactor=fac;
  G4cout << "The cross section for GammaConversionToMuons is artificially "
         << "increased by the CrossSecFactor=" << CrossSecFactor << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4VParticleChange* BDSGammaConversionToMuons::PostStepDoIt(
                                                        const G4Track& aTrack,
                                                        const G4Step&  aStep)
//
// generation of gamma->mu+mu-
//
{
  aParticleChange.Initialize(aTrack);
  G4Material* aMaterial = aTrack.GetMaterial();

  static const G4double Mmuon=G4MuonPlus::MuonPlus()->GetPDGMass();
  static const G4double Mele=electron_mass_c2;
  static const G4double sqrte=sqrt(exp(1.));

  // current Gamma energy and direction, return if energy too low
  const G4DynamicParticle *aDynamicGamma = aTrack.GetDynamicParticle();
  G4double Egam = aDynamicGamma->GetKineticEnergy();
  if (Egam < 4*Mmuon) return G4VDiscreteProcess::PostStepDoIt(aTrack,aStep);
  G4ParticleMomentum GammaDirection = aDynamicGamma->GetMomentumDirection();

  // select randomly one element constituting the material
  const G4Element& anElement = *SelectRandomAtom(aDynamicGamma, aMaterial);
  G4double Z = anElement.GetZ();
  G4double A = anElement.GetA()/(g/mole);

  static G4double Zlast=0,B,Dn,Zthird,Winfty,A027,C1Num2,C2Term2;
  if(Zlast!=Z) // the element has changed
  { Zlast=Z;
    if(Z==1) // special case of Hydrogen
    { B=202.4;
      Dn=1.49;
    }
    else
    { B=183.;
      Dn=1.54*pow(A,0.27);
    }
    Zthird=pow(Z,-1./3.); // Z**(-1/3)
    Winfty=B*Zthird*Mmuon/(Dn*Mele);
    A027=pow(A,0.27);
    G4double C1Num=0.35*A027;
    C1Num2=C1Num*C1Num;
    C2Term2=Mele/(183.*Zthird*Mmuon);
  }

  G4double GammaMuonInv=Mmuon/Egam;
  G4double sqrtx=sqrt(.25-GammaMuonInv);
  G4double xmax=.5+sqrtx;
  G4double xmin=.5-sqrtx;

  // generate xPlus according to the differential cross section by rejection
  G4double Ds2=(Dn*sqrte-2.);
  G4double sBZ=sqrte*B*Zthird/Mele;
  G4double LogWmaxInv=1./log(Winfty*(1.+2.*Ds2*GammaMuonInv)
                             /(1.+2.*sBZ*Mmuon*GammaMuonInv));
  G4double xPlus,xMinus,xPM,result,W;
  do
  { xPlus=xmin+G4UniformRand()*(xmax-xmin);
    xMinus=1.-xPlus;
    xPM=xPlus*xMinus;
    G4double del=Mmuon*Mmuon/(2.*Egam*xPM);
    W=Winfty*(1.+Ds2*del/Mmuon)/(1.+sBZ*del);
    if(W<1.) W=1.; // to avoid negative cross section at xmin
    G4double xxp=1.-4./3.*xPM; // the main xPlus dependence
    result=xxp*log(W)*LogWmaxInv;
    if(result>1.)
    { 
      G4Exception("BDSGammaConversionToMuons::PostStepDoIt: Error in dSigxPlusGen, result > 1", "-1", FatalException, "");
      exit(1);
    }
  }
  while (G4UniformRand() > result);

  // now generate the angular variables via the auxilary variables t,psi,rho
  G4double t;
  G4double psi;
  G4double rho;

  G4double thetaPlus,thetaMinus,phiHalf; // final angular variables

  do      // t, psi, rho generation start  (while angle < pi)
  {
    //generate t by the rejection method
    G4double C1=C1Num2* GammaMuonInv/xPM;
    G4double f1_max=(1.-xPM) / (1.+C1);
    G4double f1; // the probability density
    do
    { t=G4UniformRand();
      f1=(1.-2.*xPM+4.*xPM*t*(1.-t)) / (1.+C1/(t*t));
      if(f1<0 || f1> f1_max) // should never happend
      {
        G4Exception("BDSGammaConversionToMuons::PostStepDoIt: f1 outside allowed range", "-1", FatalException, "");
        exit(1);
      }
    }
    while ( G4UniformRand()*f1_max > f1);
    // generate psi by the rejection method
    G4double f2_max=1.-2.*xPM*(1.-4.*t*(1.-t));

    // long version
    G4double f2;
    do
    { psi=2.*pi*G4UniformRand();
      f2=1.-2.*xPM+4.*xPM*t*(1.-t)*(1.+cos(2.*psi));
      if(f2<0 || f2> f2_max) // should never happend
      { 
	G4Exception("BDSGammaConversionToMuons::PostStepDoIt: f2 outside allowed range", "-1", FatalException, "");
        exit(1);
      }
    }
    while ( G4UniformRand()*f2_max > f2);

    // generate rho by direct transformation
    G4double C2Term1=GammaMuonInv/(2.*xPM*t);
    G4double C2=4./sqrt(xPM)*pow(C2Term1*C2Term1+C2Term2*C2Term2,2.);
    G4double rhomax=1.9/A027*(1./t-1.);
    G4double beta=log( (C2+pow(rhomax,4.))/C2 );
    rho=pow(C2 *( exp(beta*G4UniformRand())-1. ) ,0.25);

    //now get from t and psi the kinematical variables
    G4double u=sqrt(1./t-1.);
    G4double xiHalf=0.5*rho*cos(psi);
    phiHalf=0.5*rho/u*sin(psi);

    thetaPlus =GammaMuonInv*(u+xiHalf)/xPlus;
    thetaMinus=GammaMuonInv*(u-xiHalf)/xMinus;

  } while ( std::abs(thetaPlus)>pi || std::abs(thetaMinus) >pi);

  // now construct the vectors
  // azimuthal symmetry, take phi0 at random between 0 and 2 pi
  G4double phi0=2.*pi*G4UniformRand(); 
  G4double EPlus=xPlus*Egam;
  G4double EMinus=xMinus*Egam;

  // mu+ mu- directions for gamma in z-direction
  G4ThreeVector MuPlusDirection  ( sin(thetaPlus) *cos(phi0+phiHalf),
                   sin(thetaPlus)  *sin(phi0+phiHalf), cos(thetaPlus) );
  G4ThreeVector MuMinusDirection (-sin(thetaMinus)*cos(phi0-phiHalf),
                  -sin(thetaMinus) *sin(phi0-phiHalf), cos(thetaMinus) );
  // rotate to actual gamma direction
  MuPlusDirection.rotateUz(GammaDirection);
  MuMinusDirection.rotateUz(GammaDirection);
  aParticleChange.SetNumberOfSecondaries(2);
  // create G4DynamicParticle object for the particle1
  G4DynamicParticle* aParticle1= new G4DynamicParticle(
                           G4MuonPlus::MuonPlus(),MuPlusDirection,EPlus-Mmuon);
  aParticleChange.AddSecondary(aParticle1);
  // create G4DynamicParticle object for the particle2
  G4DynamicParticle* aParticle2= new G4DynamicParticle(
                       G4MuonMinus::MuonMinus(),MuMinusDirection,EMinus-Mmuon);
  aParticleChange.AddSecondary(aParticle2);
  //
  // Kill the incident photon
  //
  aParticleChange.ProposeMomentumDirection( 0., 0., 0. ) ;
  aParticleChange.ProposeEnergy( 0. ) ;
  aParticleChange.ProposeTrackStatus( fStopAndKill ) ;
  //  Reset NbOfInteractionLengthLeft and return aParticleChange
  return G4VDiscreteProcess::PostStepDoIt( aTrack, aStep );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4Element* BDSGammaConversionToMuons::SelectRandomAtom(
                                        const G4DynamicParticle* aDynamicGamma,
                                              G4Material* aMaterial)
{
  // select randomly 1 element within the material, invoked by PostStepDoIt

  const G4int NumberOfElements            = aMaterial->GetNumberOfElements();
  const G4ElementVector* theElementVector = aMaterial->GetElementVector();
  if (NumberOfElements == 1) return (*theElementVector)[0];

  const G4double* NbOfAtomsPerVolume = aMaterial->GetVecNbOfAtomsPerVolume();

  G4double PartialSumSigma = 0. ;
  G4double rval = G4UniformRand()/MeanFreePath;


  for ( G4int i=0 ; i < NumberOfElements ; i++ )
      { PartialSumSigma += NbOfAtomsPerVolume[i] *
                 GetCrossSectionPerAtom(aDynamicGamma, (*theElementVector)[i]);
        if (rval <= PartialSumSigma) return ((*theElementVector)[i]);
      }
  G4cout << " WARNING !!! - The Material '"<< aMaterial->GetName()
       << "' has no elements, NULL pointer returned." << G4endl;
  return NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void BDSGammaConversionToMuons::PrintInfoDefinition()
{
  G4String comments ="gamma->mu+mu- Bethe Heitler process.\n";
  G4cout << G4endl << GetProcessName() << ":  " << comments
         << "        good cross section parametrization from "
         << G4BestUnit(LowestEnergyLimit,"Energy")
         << " to " << HighestEnergyLimit/GeV << " GeV for all Z." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
