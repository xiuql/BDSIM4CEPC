#include "BDSGlobalConstants.hh" 
#include "BDSExecOptions.hh"
#include "BDSDebug.hh"
#include "BDSParticle.hh"
#include "BDSRunManager.hh"
#include "BDSSamplerRegistry.hh"
#include "BDSSamplerSD.hh"
#include "BDSSamplerHit.hh"
#include "BDSTrajectory.hh"

#include "globals.hh" // geant4 types / globals
#include "G4AffineTransform.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"

#include <vector>

BDSSamplerSD::BDSSamplerSD(G4String name, G4String type):
  G4VSensitiveDetector(name),
  itsHCID(-1),
  SamplerCollection(nullptr),
  itsType(type),
  registry(nullptr),
  globals(nullptr)
{
  itsCollectionName="Sampler_"+type;
  collectionName.insert(itsCollectionName);
}

BDSSamplerSD::~BDSSamplerSD()
{;}

void BDSSamplerSD::Initialize(G4HCofThisEvent* HCE)
{
  // Create Sampler hits collection
  SamplerCollection = new BDSSamplerHitsCollection(SensitiveDetectorName,itsCollectionName);

  // Record id for use in EventAction to save time - slow string lookup by collection name
  if (itsHCID < 0)
    {itsHCID = G4SDManager::GetSDMpointer()->GetCollectionID(itsCollectionName);}
  HCE->AddHitsCollection(itsHCID,SamplerCollection);

  registry = BDSSamplerRegistry::Instance(); // cache pointer to registry
  globals  = BDSGlobalConstants::Instance(); // cache pointer to globals
}

G4bool BDSSamplerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  // Do not store hit if the particle pre step point is not on the boundary
  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  if(preStepPoint->GetStepStatus() != fGeomBoundary)
    {
#ifdef BDSDEBUG
      G4cout << __METHOD_NAME__ << "not storing as not on geometry boundary" << G4endl;
#endif
      return false; // this step was not stored
    }
  
  G4Track* track    = aStep->GetTrack();
  BDSTrajectory* bdsTraj = new BDSTrajectory(track); // prepares extra info from track
  G4int TrackID     = track->GetTrackID();     // unique ID of track
  G4int ParentID    = track->GetParentID();    // unique ID of track's mother
  G4double t        = track->GetGlobalTime();  // time since beginning of event
  G4double energy   = track->GetTotalEnergy(); // total track energy
  G4int turnstaken  = globals->GetTurnsTaken();// turn Number 
  G4ThreeVector pos = track->GetPosition();    // current particle position (global)
  G4ThreeVector mom = track->GetMomentumDirection();// current particle direction (global)
  G4double weight   = track->GetWeight();      // weighting

  // The copy number of physical volume is the sampler ID in BDSIM scheme.
  // track->GetVolume gives the volume in the mass world. pre/postStepPoint->->GetVolume()
  // give the ones in the parallel sampler world this SD is attached to. If the post step
  // point is on a boundary, it belongs to the next volume - ie not the one of interest
  // so always use the pre step point for volume identification.
  G4int samplerID   = preStepPoint->GetTouchable()->GetVolume()->GetCopyNo();
  
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "Sampler ID: " << samplerID << G4endl;
#endif

  // Get coordinate transform and prepare local coordinates
  G4Transform3D localToGlobal = registry->GetTransformInverse(samplerID);
  G4AffineTransform tf;
  if (localToGlobal == G4Transform3D::Identity) // no transform was provided - look it up
    {tf = G4AffineTransform(preStepPoint->GetTouchableHandle()->GetHistory()->GetTopTransform());}
  else
    {tf = G4AffineTransform(localToGlobal.getRotation(),localToGlobal.getTranslation());}
  
  G4ThreeVector localPosition  = tf.TransformPoint(pos);
  G4ThreeVector localDirection = tf.TransformAxis(mom);
  BDSParticle   local(localPosition,localDirection,energy,t);

  G4String samplerName = registry->GetName(samplerID);      // name
  G4double s           = registry->GetSPosition(samplerID); // S position
  G4int nEvent = BDSRunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  nEvent += globals->GetEventNumberOffset();
  G4int    PDGtype     = track->GetDefinition()->GetPDGEncoding();
  G4String pName       = track->GetDefinition()->GetParticleName();

  // more advanced / detailed information
  G4ThreeVector vtx               = track->GetVertexPosition();
  G4ThreeVector dir               = track->GetVertexMomentumDirection();
  G4ThreeVector posLastScatter    = bdsTraj->GetPositionOfLastScatter(track);
  G4ThreeVector momDirLastScatter = bdsTraj->GetMomDirAtLastScatter(track);
  G4double timeLastScatter        = bdsTraj->GetTimeAtLastScatter(track);
  G4double energyLastScatter      = bdsTraj->GetEnergyAtLastScatter(track);
  G4double vertexEnergy           = track->GetVertexKineticEnergy() + track->GetParticleDefinition()->GetPDGMass();
  G4double vertexTime             = bdsTraj->GetTimeAtVertex(track);

  // store production/scatter point
  BDSParticle lastScatter(posLastScatter,momDirLastScatter,energyLastScatter,timeLastScatter);
  BDSParticle production(vtx,dir,vertexEnergy,vertexTime); //production point
  BDSParticle global(pos,mom,energy,t); // global point
 
  // process that creating the particle
  G4String process = "";
  if(track->GetCreatorProcess()) 
    {process = track->GetCreatorProcess()->GetProcessName();}
  
  BDSSamplerHit* smpHit = new BDSSamplerHit(samplerName,
                                            samplerID,
					    globals->GetInitialPoint(),
					    production,
					    lastScatter,
					    local,
					    global,
					    s,
					    weight,
					    PDGtype,
					    nEvent, 
					    ParentID, 
					    TrackID,
					    turnstaken,
					    itsType,
					    process);
  
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << *smpHit;
#endif
  SamplerCollection->insert(smpHit);

  delete bdsTraj;
  return true;    //The hit was stored
}
