/** BDSIM, v0.1   

Last modified 15.11.2005 by Ilya Agapov

**/


//
//  Physics list
//


const int DEBUG = 1;

#include "BDSGlobalConstants.hh" // must be first in include list
#include "BDSPhysicsList.hh"

#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4ios.hh"
#include <iomanip>   

#include "GeneralPhysics.hh"
//#include "EM_GNPhysics.hh"
//#include "EMPhysics.hh"
#include "MuonPhysics.hh"
//#include "HadronPhysicsQGSP_HP.hh"
//#include "IonPhysics.hh"


// physics processes

// EM

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4MultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"


// Low EM

#include "G4LowEnergyRayleigh.hh"
#include "G4LowEnergyPhotoElectric.hh"
#include "G4LowEnergyCompton.hh"
#include "G4LowEnergyGammaConversion.hh"

// e-
#include "G4LowEnergyIonisation.hh"
#include "G4LowEnergyBremsstrahlung.hh"

#include "G4hLowEnergyIonisation.hh"


//#include "BDSLaserWirePhysics.hh"
//#include "BDSPlanckScatterPhysics.hh"
//#include "BDSSynchRadPhysics.hh"
//#include "BDSeBremPhysics.hh"
#include "BDSGammaConversionPhysics.hh"
#include "BDSLowEMPhysics.hh"


// particle definition

// Bosons
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"

// leptons
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

// Hadrons
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"

//ShortLived
#include "G4ShortLivedConstructor.hh"


extern G4bool verbose;

BDSPhysicsList::BDSPhysicsList():  G4VModularPhysicsList()
{
  // construct particles

  defaultCutValue = 0.7*mm;  

  SetVerboseLevel(1);
   
}

BDSPhysicsList::~BDSPhysicsList()
{
}

void BDSPhysicsList::ConstructProcess()
{
  // register physics processes here
  AddTransportation();

  // standard e+/e-/gamma electromagnetic interactions
  if(BDSGlobals->GetPhysListName() == "em_standard") 
    {
      ConstructEM();
      return;
    }

  // low energy em processes
  if(BDSGlobals->GetPhysListName() == "em_low") 
    {
      ConstructEM_Low_Energy();
      return;
    }

  // standard electromagnetic + muon
  if(BDSGlobals->GetPhysListName() == "em_muon") 
    {
      RegisterPhysics(  new MuonPhysics("muon"));
      RegisterPhysics( new BDSGammaConversionPhysics("BDSGamConv"));
      return;
    }

  // standard hadronic - photo-nuclear etc.
  if(BDSGlobals->GetPhysListName() == "hadronic_standard") 
    {
      return;
    }


  //default - standard

  if(BDSGlobals->GetPhysListName() != "standard")
    {
      G4cerr<<"WARNING : Unknown physics list "<<BDSGlobals->GetPhysListName()<<
	"  using transportation only (standard) "<<G4endl;
    } 

  
       
      
      // Special process
      //  if(BDSGlobals->GetPlanckOn())
      // 	RegisterPhysics( new BDSPlanckScatterPhysics("BDSPlanckScatter"));
      
      //       if(BDSGlobals->GetLaserwireWavelength())
      // 	RegisterPhysics( new BDSLaserWirePhysics("BDSLaserWire"));
      
      //       if(BDSGlobals->GetSynchRadOn())
      // 	RegisterPhysics( new BDSSynchRadPhysics("BDSSynchRad"));
      
      //       if(BDSGlobals->GetBDSeBremOn())
      // 	RegisterPhysics( new BDSeBremPhysics("BDSeBrem"));
      
      //       if(BDSGlobals->GetUseMuonPairProduction())
      // 	RegisterPhysics( new BDSGammaConversionPhysics("BDSGamConv"));
      
     
}

void BDSPhysicsList::ConstructParticle()
{

  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();
  
  // gamma
  G4Gamma::GammaDefinition();
  
  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();
  
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();  
  
  // mesons
  G4MesonConstructor mConstructor;
  mConstructor.ConstructParticle();
  
  // barions
  G4BaryonConstructor bConstructor;
  bConstructor.ConstructParticle();
  
  // ions
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();
  
  //  Construct  resonaces and quarks
  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();



  // set primary particle definition and kinetic beam parameters other than total energy


  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  BDSGlobals->SetParticleDefinition(particleTable->
					FindParticle(BDSGlobals->tmpParticleName) );
  
  if(!BDSGlobals->GetParticleDefinition()) 
    {
      G4cerr<<"particle  "<<BDSGlobals->tmpParticleName<<" not found, quitting!"<<G4endl;
      exit(1);
    }

  // set kinetic beam parameters other than total energy

  BDSGlobals->SetBeamMomentum( sqrt(pow(BDSGlobals->GetBeamTotalEnergy(),2)-
			       pow(BDSGlobals->GetParticleDefinition()->GetPDGMass(),2)) );
  
  BDSGlobals->SetBeamKineticEnergy(BDSGlobals->GetBeamTotalEnergy() - 
				   BDSGlobals->GetParticleDefinition()->GetPDGMass() );

  G4cout<<"Beam Energy : "<< BDSGlobals->GetBeamTotalEnergy()<<G4endl;
  G4cout<<"Beam Kinetic  Energy : "<< BDSGlobals->GetBeamKineticEnergy()<<G4endl;
  
  
  
  
}

void BDSPhysicsList::SetCuts()
{
  if (verbose){
    G4cout << "BDSPhysicsList:: setting cuts";
    
  }
  
  SetCutsWithDefault();   
  
  if(verbose)
    DumpCutValuesTable(); 
  
}


// particular physics process constructors

void BDSPhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    
    if (particleName == "gamma") {
      // gamma         
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);
      
    } else if (particleName == "e-") {
      //electron
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);      
      
    } else if (particleName == "e+") {
      //positron
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1,4);
      
    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      //muon  
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4MuIonisation,      -1, 2,2);
      pmanager->AddProcess(new G4MuBremsstrahlung,  -1, 3,3);
      pmanager->AddProcess(new G4MuPairProduction,  -1, 4,4);       
      
    } else if ((!particle->IsShortLived()) &&
	       (particle->GetPDGCharge() != 0.0) && 
	       (particle->GetParticleName() != "chargedgeantino")) {
      //all others charged particles except geantino
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4hIonisation,       -1, 2,2);
      //step limit
      //pmanager->AddProcess(new G4StepLimiter,       -1,-1,3);         
      ///pmanager->AddProcess(new G4UserSpecialCuts,   -1,-1,4);  
    }
  }
}


void BDSPhysicsList::ConstructEM_Low_Energy()
{

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {
     
      pmanager->AddDiscreteProcess(new G4LowEnergyRayleigh());
      pmanager->AddDiscreteProcess(new G4LowEnergyPhotoElectric);
      pmanager->AddDiscreteProcess(new G4LowEnergyCompton);
      pmanager->AddDiscreteProcess(new G4LowEnergyGammaConversion);
      
    } else if (particleName == "e-") {
  
      pmanager->AddProcess(new G4MultipleScattering, -1, 1,1);
      pmanager->AddProcess(new G4LowEnergyIonisation,        -1, 2,2);
      pmanager->AddProcess(new G4LowEnergyBremsstrahlung,    -1, 3,3);
	    
    } else if (particleName == "e+") {

      pmanager->AddProcess(new G4MultipleScattering, -1, 1,1);
      pmanager->AddProcess(new G4eIonisation,        -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,    -1, 3,3);
      pmanager->AddProcess(new G4eplusAnnihilation,   0,-1,4);
      
    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {

      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4MuIonisation,      -1, 2,2);
      pmanager->AddProcess(new G4MuBremsstrahlung,  -1, 3,3);
      pmanager->AddProcess(new G4MuPairProduction,  -1, 4,4);       

    } else if (particleName == "GenericIon") {

      pmanager->AddProcess(new G4MultipleScattering, -1, 1,1);
      pmanager->AddProcess(new G4hLowEnergyIonisation,       -1,2,2);
      //      pmanager->AddProcess(new G4ionIonisation,      -1, 2,2);
      // it dose not work here
    } else if ((!particle->IsShortLived()) &&
	       (particle->GetPDGCharge() != 0.0) && 
	       (particle->GetParticleName() != "chargedgeantino")) {

      pmanager->AddProcess(new G4MultipleScattering,-1,1,1);
      pmanager->AddProcess(new G4hLowEnergyIonisation,       -1,2,2);
    }
  }
}
