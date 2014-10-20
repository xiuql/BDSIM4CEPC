/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 

   Modified 22.03.05 by J.C.Carter, Royal Holloway, Univ. of London.
   Changed Samplers to account for plane and cylinder types (GABs code)
*/

#include "BDSGlobalConstants.hh" 
#include "BDSExecOptions.hh"
#include "BDSDebug.hh"
#include "BDSParticle.hh"
#include "BDSSamplerSD.hh"
#include "BDSSamplerHit.hh"
#include "BDSTrajectory.hh"
#include "BDSTrajectoryPoint.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4ThreeVector.hh"

#include "G4AffineTransform.hh"

#include "G4RunManager.hh"
#include <vector>

#include "G4SDManager.hh"

BDSSamplerSD::BDSSamplerSD(G4String name, G4String type)
  :G4VSensitiveDetector(name),itsHCID(-1),SamplerCollection(NULL),
   itsType(type)
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

  // Record id for use in EventAction to save time
  if (itsHCID < 0){
    itsHCID = G4SDManager::GetSDMpointer()->GetCollectionID(itsCollectionName);}
  HCE->AddHitsCollection(itsHCID,SamplerCollection);
}

G4bool BDSSamplerSD::ProcessHits(G4Step*aStep,G4TouchableHistory*)
{
  G4Track* theTrack = aStep->GetTrack();
  BDSTrajectory* bdsTraj = new BDSTrajectory(theTrack);
  //bdsTraj->printRichDataOfSteps();
  // LN removed this because it only prints definition of types, not info itself
  
  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  //  G4StepPoint* postStepPoint = aStep->GetPostStepPoint();
  //  // tmp - only store muons
  //     G4String pName=theTrack->GetDefinition()->GetParticleName();
  //    if(pName=="mu+"||pName=="mu-")
  // 	{ // tm
  //Do not store hit if the particle is not on the boundary 
  if(preStepPoint->GetStepStatus()!=fGeomBoundary) return false;

  //unique ID of track
  G4int TrackID = theTrack->GetTrackID();
  //unique ID of track's mother
  G4int ParentID = theTrack->GetParentID();
  //time since track creation
  G4double t = theTrack->GetGlobalTime();
  //total track energy 
  G4double energy = theTrack->GetKineticEnergy()+theTrack->GetDefinition()->GetPDGMass();
  //Turn Number
  G4int turnstaken = BDSGlobalConstants::Instance()->GetTurnsTaken();  
  
  //current particle position (global)
  G4ThreeVector pos = theTrack->GetPosition();
  //total track length
  G4double s = theTrack->GetTrackLength();
  if(ParentID != 0) s = pos.z();
  //G4ThreeVector pos = preStepPoint->GetPosition();
  //current particle direction (global)
  G4ThreeVector momDir = theTrack->GetMomentumDirection();
  //G4ThreeVector momDir = preStepPoint->GetMomentumDirection();
  
  // Get Translation and Rotation of Sampler Volume w.r.t the World Volume
  // as described in Geant4 FAQ's: http://geant4.cern.ch/support/faq.shtml
  G4AffineTransform tf(preStepPoint->GetTouchableHandle()->GetHistory()->GetTopTransform());
  //      const G4RotationMatrix Rot=tf.NetRotation();
  //      const G4ThreeVector Trans=-tf.NetTranslation();
  
  //Old method - works for standard Samplers, but not samplers within a deeper
  //hierarchy of volumes (e.g. Mokka built samplers)
  //const G4RotationMatrix* Rot=theTrack->GetVolume()->GetFrameRotation();
  //const G4ThreeVector Trans=theTrack->GetVolume()->GetFrameTranslation();
  
  //      G4ThreeVector LocalPosition=pos+Trans; 
  //      G4ThreeVector LocalDirection=Rot*momDir; 
  G4ThreeVector LocalPosition = tf.TransformPoint(pos);
  G4ThreeVector LocalDirection = tf.TransformAxis(momDir);
  
  // Changed z output by Samplers to be the position of the sampler
  // not time of flight of the particle JCC 15/10/05
  //G4double z=-(time*c_light-(pos.z()+BDSGlobalConstants::Instance()->GetWorldSizeZ()));
  //G4double z=pos.z();

  G4double zPrime=LocalDirection.z();
  if(zPrime<0) energy*=-1;
  // apply a correction that takes ac... gab to do later!

  BDSParticle local(LocalPosition,LocalDirection,energy,t);

  G4int nEvent= 
    G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  
  nEvent+=BDSGlobalConstants::Instance()->GetEventNumberOffset();
  
  G4int nSampler=theTrack->GetVolume()->GetCopyNo()+1;
  G4String SampName = theTrack->GetVolume()->GetName()+"_"+BDSGlobalConstants::Instance()->StringFromInt(nSampler);
  G4int PDGtype=theTrack->GetDefinition()->GetPDGEncoding();
  
  G4String pName=theTrack->GetDefinition()->GetParticleName();
  
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "BDSSamplerSD> Particle name: " << pName << G4endl;  
  G4cout << __METHOD_NAME__ << "BDSSamplerSD> PDG encoding: " << PDGtype << G4endl;  
  G4cout << __METHOD_NAME__ << "BDSSamplerSD> TrackID: " << TrackID << G4endl;  
#endif
  
  G4ThreeVector vtx=theTrack->GetVertexPosition();
  G4ThreeVector dir=theTrack->GetVertexMomentumDirection();
  G4ThreeVector posLastScatter=bdsTraj->GetPositionOfLastScatter(theTrack);
  G4ThreeVector momDirLastScatter=bdsTraj->GetMomDirAtLastScatter(theTrack);
  G4double timeLastScatter=bdsTraj->GetTimeAtLastScatter(theTrack);
  G4double energyLastScatter=bdsTraj->GetEnergyAtLastScatter(theTrack);
  G4double vertexEnergy=theTrack->GetVertexKineticEnergy() + theTrack->GetParticleDefinition()->GetPDGMass();
  G4double vertexTime=bdsTraj->GetTimeAtVertex(theTrack);

  // store production/scatter point
  BDSParticle lastScatter(posLastScatter,momDirLastScatter,energyLastScatter,timeLastScatter);

  //production point
  BDSParticle production(vtx,dir,vertexEnergy,vertexTime);

  // global point
  BDSParticle global(pos,momDir,energy,t);

  G4double weight=theTrack->GetWeight();
 
  BDSSamplerHit* smpHit
    = new BDSSamplerHit(
			SampName,
			BDSGlobalConstants::Instance()->GetInitialPoint(),
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
			itsType);
  
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << " Sampler : " << SampName << G4endl;
  G4cout << __METHOD_NAME__ << " Storing hit: E, x, y, z, xPrime, yPrime" << G4endl;
  G4cout << __METHOD_NAME__ << " " << energy <<" "  << LocalPosition.x() << " " << LocalPosition.y() << " " << LocalPosition.z() << " " << LocalDirection.x() << " " << LocalDirection.y() << G4endl;
  G4cout << __METHOD_NAME__ << " Storing hit: E, x, y, z, xPrime, yPrime" << G4endl;
  G4cout << __METHOD_NAME__ << " " << energy <<" "  << pos.x() << " " << pos.y() << " " << pos.z() << " " << LocalDirection.x() << " " << LocalDirection.y() << G4endl;
  G4cout << __METHOD_NAME__ << " entries in hits collection before inserting hit: " << SamplerCollection->entries() << G4endl;
#endif
  SamplerCollection->insert(smpHit);
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << " entries in hits collection after inserting hit: " << SamplerCollection->entries() << G4endl;
#endif

  //The hit was stored, so the return value is "true".
  return true;
}

void BDSSamplerSD::EndOfEvent(G4HCofThisEvent* /*HCE*/)
{
  //G4SDManager * SDman = G4SDManager::GetSDMpointer();
  //G4int HCID = SDman->GetCollectionID(itsCollectionName);
  //HCE->AddHitsCollection(HCID, SamplerCollection );
}

void BDSSamplerSD::clear(){} 

void BDSSamplerSD::DrawAll(){} 

void BDSSamplerSD::PrintAll(){} 
