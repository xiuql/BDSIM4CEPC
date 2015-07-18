/** BDSIM, v0.4   

Last modified 23.10.2007 by Steve Malton

**/

#include <cstdlib>

#include "BDSGlobalConstants.hh"

#include "parser/options.h"

#include "BDSBeamPipeType.hh"
#include "BDSDebug.hh"
#include "BDSExecOptions.hh"
#include "BDSTunnelInfo.hh"

#include "G4Colour.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4ThreeVector.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"

extern Options options;

BDSGlobalConstants* BDSGlobalConstants::_instance = 0;

BDSGlobalConstants* BDSGlobalConstants::Instance(){
  if(_instance==0) {
    _instance = new BDSGlobalConstants(options);
  }
  return _instance;
}

BDSGlobalConstants::BDSGlobalConstants(struct Options& opt):
  itsBeamParticleDefinition(NULL),itsBeamMomentum(0.0),itsBeamKineticEnergy(0.0),itsParticleMomentum(0.0),itsParticleKineticEnergy(0.0),itsSMax(0.0)
{
  itsPhysListName       = opt.physicsList;
  itsBeamPipeMaterial   = opt.beampipeMaterial;
  itsApertureType       = BDS::DetermineBeamPipeType(opt.apertureType);
  itsVacuumMaterial     = opt.vacMaterial;
  itsEmptyMaterial      = "G4_Galactic"; // space vacuum

  itsSampleDistRandomly = true;
  itsGeometryBias = opt.geometryBias;
  
  itsSensitiveComponents=opt.sensitiveBeamlineComponents;
  itsSensitiveBeamPipe=opt.sensitiveBeamPipe;
  itsSensitiveBLMs=opt.sensitiveBLMs;
  itsDefaultRangeCut=opt.defaultRangeCut * CLHEP::m;
  itsElossHistoBinWidth=opt.elossHistoBinWidth; //Longitudinal and transverse energy loss histogram bin widths
  itsElossHistoTransBinWidth=opt.elossHistoTransBinWidth;
  itsFFact=opt.ffact;
  itsParticleName=G4String(opt.particleName);
  itsBeamTotalEnergy = opt.beamEnergy * CLHEP::GeV;
  if (itsBeamTotalEnergy == 0) {
    G4cerr << __METHOD_NAME__ << "Error: option \"beamenergy\" is not defined or must be greater than 0" <<  G4endl;
    exit(1);
  }
  itsParticleTotalEnergy = opt.E0 * CLHEP::GeV; 
  if (itsParticleTotalEnergy == 0) {
    itsParticleTotalEnergy = itsBeamTotalEnergy;
  }

  itsPlanckScatterFe = opt.planckScatterFe;
  //Fraction of events with leading particle biasing.

  //beampipe
  itsBeamPipeRadius = opt.beampipeRadius * CLHEP::m;
  itsAper1 = opt.aper1*CLHEP::m;
  itsAper2 = opt.aper2*CLHEP::m;
  itsAper3 = opt.aper3*CLHEP::m;
  itsAper4 = opt.aper4*CLHEP::m;
  // note beampipetype already done before these checks! at top of this function
  BDS::CheckApertureInfo(itsApertureType,itsBeamPipeRadius,itsAper1,itsAper2,itsAper3,itsAper4);
  
  itsBeamPipeThickness = opt.beampipeThickness * CLHEP::m;

  //magnet geometry
  itsOuterDiameter = opt.outerDiameter * CLHEP::m;
  if (itsOuterDiameter < 2*(itsBeamPipeThickness + itsBeamPipeRadius)){
    G4cerr << __METHOD_NAME__ << "Error: option \"outerDiameter\" must be greater than 2x (\"beampipeRadius\" + \"beamPipeThickness\") " << G4endl;
    exit(1);
  }
  itsMagnetGeometryType = BDS::DetermineMagnetGeometryType(opt.magnetGeometryType);
  itsOuterMaterialName  = opt.outerMaterialName;

  // tunnel
  tunnelInfo = new BDSTunnelInfo();
  tunnelInfo->sensitive=true;
  // set defaults here

  //Beam loss monitor (BLM) geometry
  itsBlmRad = opt.blmRad * CLHEP::m;
  itsBlmLength = opt.blmLength * CLHEP::m;
  itsSamplerDiameter = opt.samplerDiameter * CLHEP::m;
  itsSamplerLength = 4E-8 * CLHEP::m;
  itsThresholdCutCharged = opt.thresholdCutCharged * CLHEP::GeV;
  itsThresholdCutPhotons = opt.thresholdCutPhotons * CLHEP::GeV;
  itsProdCutPhotons = opt.prodCutPhotons * CLHEP::m;
  itsProdCutPhotonsP = opt.prodCutPhotonsP * CLHEP::m;
  itsProdCutPhotonsA = opt.prodCutPhotonsA * CLHEP::m;
  itsProdCutElectrons = opt.prodCutElectrons * CLHEP::m;
  itsProdCutElectronsP = opt.prodCutElectronsP * CLHEP::m;
  itsProdCutElectronsA = opt.prodCutElectronsA * CLHEP::m;
  itsProdCutPositrons = opt.prodCutPositrons * CLHEP::m;
  itsProdCutPositronsP = opt.prodCutPositronsP * CLHEP::m;
  itsProdCutPositronsA = opt.prodCutPositronsA * CLHEP::m;
 
  itsDeltaChord = opt.deltaChord * CLHEP::m;
  itsChordStepMinimum = opt.chordStepMinimum * CLHEP::m;
  itsDeltaIntersection= opt.deltaIntersection * CLHEP::m;
  itsMinimumEpsilonStep = opt.minimumEpsilonStep;
  itsMaximumEpsilonStep = opt.maximumEpsilonStep;
  itsMaxTime = opt.maximumTrackingTime * CLHEP::s;
  
  itsDeltaOneStep = opt.deltaOneStep * CLHEP::m;
  itsDoPlanckScattering = opt.doPlanckScattering;
  itsCheckOverlaps = opt.checkOverlaps;
  itsTurnOnCerenkov = opt.turnOnCerenkov;
  itsTurnOnOpticalAbsorption = opt.turnOnOpticalAbsorption;
  itsTurnOnRayleighScattering = opt.turnOnRayleighScattering;
  itsTurnOnMieScattering = opt.turnOnMieScattering;
  itsTurnOnOpticalSurface = opt.turnOnOpticalSurface;
  itsTurnOnBirksSaturation = opt.turnOnBirksSaturation;
  itsScintYieldFactor=opt.scintYieldFactor;
  itsSynchRadOn = opt.synchRadOn;
  G4cout << "BDSGlobalConstants::Instance() synchRadOn = " << itsSynchRadOn << G4endl;
  itsDecayOn = opt.decayOn;
  itsSynchTrackPhotons= opt.synchTrackPhotons;
  G4cout << __METHOD_NAME__ << "synchTrackphotons = " << itsSynchTrackPhotons << G4endl;
  itsSynchLowX = opt.synchLowX;
  itsSynchLowGamE = opt.synchLowGamE * CLHEP::GeV;  // lowest gamma energy
  itsSynchPhotonMultiplicity = opt.synchPhotonMultiplicity;
  itsSynchMeanFreeFactor = opt.synchMeanFreeFactor;
  itsLengthSafety = opt.lengthSafety;

  // set the number of primaries to generate - exec options overrides whatever's in gmad
  G4int nToGenerate = BDSExecOptions::Instance()->GetNGenerate();
  if (nToGenerate < 0)
    {itsNumberToGenerate = opt.numberToGenerate;}
  else
    {itsNumberToGenerate = nToGenerate;}
  
  itsNumberOfEventsPerNtuple = opt.numberOfEventsPerNtuple;
  itsEventNumberOffset = opt.eventNumberOffset;
  itsRandomSeed = opt.randomSeed;
  itsGammaToMuFe= opt.gammaToMuFe;
  itsAnnihiToMuFe= opt.annihiToMuFe;
  itsEeToHadronsFe=opt.eeToHadronsFe;
  itsUseEMLPB=opt.useEMLPB;
  itsUseHadLPB=opt.useHadLPB;
  itsDecayOn=opt.decayOn;
  SetLPBFraction(opt.LPBFraction);
  itsStoreMuonTrajectories = opt.storeMuonTrajectories;
  itsTrajCutGTZ = opt.trajCutGTZ;
  itsTrajCutLTR = opt.trajCutLTR;
  itsStoreNeutronTrajectories = opt.storeNeutronTrajectories;
  itsStoreTrajectory = opt.storeTrajectory;
  //G4cout<<"STOREA TRAJ = "<< itsStoreTrajectory<<G4endl;
  stopTracks = opt.stopTracks; 
  // defaults - parameters of the laserwire process
  itsLaserwireWavelength = 0.532 * CLHEP::micrometer;
  itsLaserwireDir = G4ThreeVector(1,0,0);
  itsLaserwireTrackPhotons = 1;
  itsLaserwireTrackElectrons = 1;
  isWaitingForDump = false;
  isDumping = false;
  isReading = false;
  isReadFromStack = false;
  itsFifo = opt.fifo;
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "itsFifo = " << itsFifo << G4endl;
  G4cout << __METHOD_NAME__ << "GetFifo() = " << GetFifo() << G4endl;
#endif
  itsIncludeIronMagFields = opt.includeIronMagFields;
  zeroMagField = new G4UniformMagField(G4ThreeVector());
  itsZeroFieldManager=new G4FieldManager();
  itsZeroFieldManager->SetDetectorField(zeroMagField);
  itsZeroFieldManager->CreateChordFinder(zeroMagField);
  itsTurnsTaken = 1; //counting from 1
  if(opt.nturns < 1)
    itsTurnsToTake = 1;
  else
    itsTurnsToTake = opt.nturns;
  teleporterdelta     = G4ThreeVector(0.,0.,0.);
  teleporterlength    = 0.0;

  InitRotationMatrices();
  
  // options that are never used (no set method):
  itsLWCalWidth       = 0.0;
  itsLWCalOffset      = 0.0;
  itsMagnetPoleRadius = 0.0;
  itsMagnetPoleSize   = 0.0;

  // initialise the default vis attributes and user limits that
  // can be copied by various bits of geometry
  InitVisAttributes();
  InitDefaultUserLimits();
}

void BDSGlobalConstants::InitVisAttributes()
{
  //for vacuum volumes
  invisibleVisAttr = new G4VisAttributes(G4Colour::Black());
  invisibleVisAttr->SetVisibility(false);
  invisibleVisAttr->SetForceLineSegmentsPerCircle(50);

  //for normally invisible volumes like marker / container volumes in debug mode
  visibleDebugVisAttr = new G4VisAttributes(); //green
  visibleDebugVisAttr->SetColour(0,0.6,0,0.1);
  visibleDebugVisAttr->SetVisibility(true);
  visibleDebugVisAttr->SetForceLineSegmentsPerCircle(50);
}

void BDSGlobalConstants::InitDefaultUserLimits()
{
  //these must be copied and not attached directly
  defaultUserLimits = new G4UserLimits("default_cuts");
  defaultUserLimits->SetUserMinEkine( GetThresholdCutCharged() );
  //user must set step length manually
}

void BDSGlobalConstants::InitRotationMatrices(){
  _RotY90       = new G4RotationMatrix();
  _RotYM90      = new G4RotationMatrix();
  _RotX90       = new G4RotationMatrix();
  _RotXM90      = new G4RotationMatrix();
  _RotYM90X90   = new G4RotationMatrix();
  _RotYM90XM90  = new G4RotationMatrix();
  G4double pi_ov_2 = asin(1.);
  _RotY90->rotateY(pi_ov_2);
  _RotYM90->rotateY(-pi_ov_2);
  _RotX90->rotateX(pi_ov_2);
  _RotXM90->rotateX(-pi_ov_2);
  _RotYM90X90->rotateY(-pi_ov_2);
  _RotYM90X90->rotateX( pi_ov_2);
  _RotYM90XM90->rotateY(-pi_ov_2);
  _RotYM90XM90->rotateX(-pi_ov_2);
}

//Methods to get the rotation matrices
G4RotationMatrix* BDSGlobalConstants::RotY90() const{
  return _RotY90;
}

G4RotationMatrix* BDSGlobalConstants::RotYM90() const{
  return _RotYM90;
}

G4RotationMatrix* BDSGlobalConstants::RotX90() const{
  return _RotX90;
}

G4RotationMatrix* BDSGlobalConstants::RotXM90() const{
  return _RotXM90;
}

G4RotationMatrix* BDSGlobalConstants::RotYM90X90() const{
  return _RotYM90X90;
}

G4RotationMatrix* BDSGlobalConstants::RotYM90XM90() const{
  return _RotYM90XM90;
}

BDSGlobalConstants::~BDSGlobalConstants()
{  
  delete itsZeroFieldManager;
  delete zeroMagField;
  delete defaultUserLimits;
  _instance = 0;
}
