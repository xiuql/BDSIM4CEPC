#include "BDSSteppingAction.hh"
#include "BDSExecOptions.hh"
#include "BDSGlobalConstants.hh"

#include "BDSSamplerRegistry.hh"
#include "G4AffineTransform.hh"
#include "G4NavigationHistory.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "BDSParser.hh"

#include "BDSDebug.hh"

#include "BDSAcceleratorModel.hh"
#include "BDSBeamline.hh"
#include "BDSSamplerPlane.hh"
#include "G4Point3D.hh"

#include "CLHEP/Units/SystemOfUnits.h"

BDSSteppingAction::BDSSteppingAction():_step(nullptr){
  G4String physicsListName = BDSParser::Instance()->GetOptions().physicsList;
  G4String synFileName = BDSParser::Instance()->GetOptions().synchOutputPath;
  G4String beamFileName = BDSParser::Instance()->GetOptions().beamOutputPath;
  if(synFileName==""){
    m_foutSyn=NULL;
    m_foutSynStatistic=NULL;
  }else{
    if(physicsListName=="synchrad"){
      m_foutSyn = new std::ofstream(synFileName.c_str());
      m_foutSynStatistic=NULL;
    }else{
      m_foutSyn=NULL;
      m_foutSynStatistic = new std::ofstream(synFileName.c_str());
    }
  }
  if(beamFileName==""){
    m_foutBeam=NULL;
  }else{
    m_foutBeam = new std::ofstream(beamFileName.c_str());
  }
  m_synchHitPosUpstream = BDSParser::Instance()->GetOptions().synchHitPosUpstream;
  m_synchHitPosDownstream = BDSParser::Instance()->GetOptions().synchHitPosDownstream;
  G4cout<<"SynchHitPosUpstream: "<<m_synchHitPosUpstream<<" m, SynchHitPosDownstream: "<<m_synchHitPosDownstream<<" m"<<G4endl;

  m_endElementName = BDSParser::Instance()->GetOptions().trackingEnd;
  if(m_endElementName==""){
    m_endPointFlag=false;
  }else{
    m_endPointFlag=true;
  }
  m_endElement=NULL;

  G4String biasType = BDSParser::Instance()->GetOptions().biasType;
  if(biasType.find("Bias")==std::string::npos){
    m_bias=false;
  }else{
    m_bias=true;
  }
  m_nofScat=0;
  m_maxNofScat = BDSParser::Instance()->GetOptions().maxNofScat;
}

BDSSteppingAction::~BDSSteppingAction()
{;}

void BDSSteppingAction::UserSteppingAction(const G4Step* ThisStep)
{
  _step = ThisStep;

  if(m_endPointFlag){

    BDSBeamline* beamline = BDSAcceleratorModel::Instance()->GetFlatBeamline();
    BDSBeamline::iterator it = beamline->begin();
    for(; it != beamline->end(); ++it)
    {
      if((*it)->GetPlacementName()==m_endElementName){
        m_endElement = *it;
        break;
      }
    }
    
    if(!m_endElement){
      G4cerr << __METHOD_NAME__ << "WARNING - Can't find end element "<< m_endElementName << G4endl;
    }

    G4cout<<"End Element: "<<m_endElement->GetName()<<", PlacementName: "<<m_endElement->GetPlacementName()<<", CopyNumber: "<<m_endElement->GetCopyNo()<<G4endl;
    m_endPosition = m_endElement->GetReferencePositionStart();
    m_endRotation = m_endElement->GetReferenceRotationStart();
    G4cout<<"Position of the end element: "<<m_endPosition<<G4endl;
    G4cout<<""<<G4endl;

    m_endPointFlag=false;
  }

  if(BDSExecOptions::Instance()->GetVerboseStep())
  {VerboseSteppingAction();}
    
  if(m_foutSynStatistic){
    SynchrotronStatistic();
  }

  if(m_foutSyn){
    SynchrotronSteppingAction();
  }

  if(m_endElement){
    TerminateSteppingAction();
  }
}

void BDSSteppingAction::ThresholdCutSteppingAction()
{;}
  
void BDSSteppingAction::VerboseSteppingAction()
{ 
  //output in case of verbose step
  int ID=_step->GetTrack()->GetTrackID();
  int G4precision = G4cout.precision();
  G4cout.precision(10);
  G4cout<<"This volume="<< _step->GetTrack()->GetVolume()->GetName()<<G4endl;
	
  G4LogicalVolume* LogVol=_step->GetTrack()->GetVolume()->GetLogicalVolume();
  G4cout<<"This log volume="<<LogVol->GetName() <<G4endl;
	
  G4cout<<"ID="<<ID<<" part="<<
    _step->GetTrack()->GetDefinition()->GetParticleName()<<
    " Energy="<<_step->GetTrack()->GetTotalEnergy()/CLHEP::GeV<<
    " KineticE="<<_step->GetTrack()->GetKineticEnergy()/CLHEP::GeV<<
    " mom Px="
	<<_step->GetTrack()->GetMomentum()[0]/CLHEP::GeV<<
    " Py="<<_step->GetTrack()->GetMomentum()[1]/CLHEP::GeV<<
    " Pz="<<_step->GetTrack()->GetMomentum()[2]/CLHEP::GeV<<" vol="<<
    _step->GetTrack()->GetVolume()->GetName()<<G4endl;
	
  G4cout<<" Global Position="<<_step->GetTrack()->GetPosition()<<G4endl;
  G4AffineTransform tf(_step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetTopTransform());
  G4cout<<" Local Position="<< tf.TransformPoint(_step->GetTrack()->GetPosition()) <<G4endl;
  
  G4StepPoint* prePoint = _step->GetPreStepPoint();
  G4StepPoint* postPoint = _step->GetPostStepPoint();
  G4cout<<" Pre Position="<< prePoint->GetPosition()<<", Post Position: "<<postPoint->GetPosition()<<", StepLength: "<<_step->GetStepLength() <<G4endl;

  if(_step->GetTrack()->GetMaterial()->GetName() !="LCVacuum")
    G4cout<<"material="<<_step->GetTrack()->GetMaterial()->GetName()<<G4endl;

  G4VProcess* proc=(G4VProcess*)(_step->GetPostStepPoint()->
				 GetProcessDefinedStep() );

  if(proc)G4cout<<" post-step process="<<proc->GetProcessName()<<G4endl<<G4endl;


  proc=(G4VProcess*)(_step->GetPreStepPoint()->
		     GetProcessDefinedStep() );

  if(proc)G4cout<<" pre-step process="<<proc->GetProcessName()<<G4endl<<G4endl;

  // set precision back
  G4cout.precision(G4precision);

}

void BDSSteppingAction::SynchrotronSteppingAction(){
  G4Track* _track = _step->GetTrack();
  if(_track->GetDefinition()->GetPDGEncoding() != 22) return;  
  
  const G4VProcess* _vp = _track->GetCreatorProcess();
  if(!_vp) return;
  G4String proName = _vp->GetProcessName();
  if(proName.find("SynRad") == std::string::npos) return;
  
  G4String materialName = _track->GetMaterial()->GetName();
  if(materialName.find("G4_Galactic") != std::string::npos) return;
  if(materialName.find("vacuum") != std::string::npos) return;
  
  G4StepPoint* prePoint = _step->GetPreStepPoint();
  G4StepPoint* postPoint = _step->GetPostStepPoint();
  if(!prePoint->GetPhysicalVolume()) return;
  if(!postPoint->GetPhysicalVolume()) return;
 
  CLHEP::Hep3Vector vtxPos = _track->GetVertexPosition() / CLHEP::nm; //GuineaPig Interface
  CLHEP::Hep3Vector vtxMomDir = _track->GetVertexMomentumDirection();
  G4double vtxKE = _track->GetVertexKineticEnergy() / CLHEP::GeV;
  //G4double mass = _track->GetDefinition()->GetPDGMass() / CLHEP::GeV;
  CLHEP::Hep3Vector vtxMom = vtxKE*vtxMomDir;
  CLHEP::Hep3Vector prePos = prePoint->GetPosition() / CLHEP::m;
  CLHEP::Hep3Vector preMom = prePoint->GetMomentum() / CLHEP::GeV;
  G4double preE = prePoint->GetTotalEnergy() / CLHEP::GeV;

  if(prePos.z()>m_synchHitPosUpstream && prePos.z()<m_synchHitPosDownstream){

    m_foutSyn->setf(std::ios::showpos);
    m_foutSyn->setf(std::ios::scientific);

    //(*m_foutSyn)<<std::setprecision(9)<<vtxPos.x()<<std::setw(18)<<vtxPos.y()<<std::setw(18)<<vtxPos.z()<<std::setw(18)<<vtxMomDir.x()<<std::setw(18)<<vtxMomDir.y()<<std::setw(18)<<vtxMomDir.z()<<std::setw(18)<<preE<<std::setw(18)<<prePos.x()<<std::setw(18)<<prePos.y()<<std::setw(18)<<prePos.z()<<std::endl;
    (*m_foutSyn)<<"22"<<std::setw(21)<<std::setprecision(12)<<vtxKE<<std::setw(21)<<vtxMomDir.x()<<std::setw(21)<<vtxMomDir.y()<<std::setw(21)<<vtxMomDir.z()<<std::setw(21)<<vtxPos.x()<<std::setw(21)<<vtxPos.y()<<std::setw(21)<<vtxPos.z()<<std::setw(6)<<_track->GetTrackID()<<std::endl;

    m_foutSyn->unsetf(std::ios::scientific);
    m_foutSyn->unsetf(std::ios::showpos);
  }

  if(BDSExecOptions::Instance()->GetVerboseStep()){
    CLHEP::Hep3Vector postPos = postPoint->GetPosition() / CLHEP::m;
    CLHEP::Hep3Vector postMom = postPoint->GetMomentum() / CLHEP::GeV;

    G4String preVolName,postVolName;
    preVolName = prePoint->GetPhysicalVolume()->GetName();
    postVolName = postPoint->GetPhysicalVolume()->GetName();

    G4cout << "GeneratorProcess: "<<proName<<G4endl;
    G4cout << "VertexPosition: "<<vtxPos<<" m"<<G4endl;
    G4cout << "VertexMomentum: "<<vtxMom<<" GeV"<<G4endl;
    G4cout << "PreHitPosition: "<<prePos<<" m"<<G4endl;
    G4cout << "PreHitMom: "<<preMom<<" GeV"<<G4endl;
    G4cout << "PostHitPosition: "<<postPos<<" m"<<G4endl;
    G4cout << "PostHitMom: "<<postMom<<" GeV"<<G4endl;
    G4cout << "Pre Volume Name: "<<preVolName<<", Post Volume Name: "<<postVolName<<G4endl;
    G4cout << "Material: "<<materialName<<G4endl;
    G4cout<<""<<G4endl;
  }

  _track->SetTrackStatus(fStopAndKill);
  return;
}

void BDSSteppingAction::SynchrotronStatistic(){

  G4Track* _track = _step->GetTrack();
  if(_track->GetDefinition()->GetPDGEncoding() != 22) return;  
  G4int parentId = _track->GetParentID();
  if(parentId!=0){
    //G4int trkId = _track->GetTrackID();
    //G4cout<<"Current Particle PDGcode: "<<_track->GetDefinition()->GetPDGEncoding()<<", TrackID: "<<trkId<<", ParentID: "<<parentId<<G4endl;
    return;
  }
 
  G4int stepNumber = _track->GetCurrentStepNumber();
  G4String materialName = _track->GetMaterial()->GetName();
  
  G4StepPoint* prePoint = _step->GetPreStepPoint();
  G4StepPoint* postPoint = _step->GetPostStepPoint();
  if(!prePoint->GetPhysicalVolume()) return;
  if(!postPoint->GetPhysicalVolume()) return;
  
  G4VProcess* preProc=(G4VProcess*)(prePoint->GetProcessDefinedStep());
  G4VProcess* postProc=(G4VProcess*)(postPoint->GetProcessDefinedStep());
  if(postProc==NULL) return;
  G4String preProcName;
  G4String postProcName;
  postProcName=postProc->GetProcessName();
  if(stepNumber>1){
    if(preProc==NULL) return;
    if(postProcName.find("Transportation") != std::string::npos) return;
    if(postProcName.find("Limiter") != std::string::npos) return;
    if(postProcName.find("Sampler") != std::string::npos) return;
    //if(preProcName.find("Sampler") != std::string::npos && postProcName.find("Sampler") != std::string::npos) return;
    preProcName=preProc->GetProcessName();
  }

  if(stepNumber==1) m_nofScat=0;


  CLHEP::Hep3Vector prePos = prePoint->GetPosition() / CLHEP::m;
  CLHEP::Hep3Vector postPos = postPoint->GetPosition() / CLHEP::m;
  CLHEP::Hep3Vector preMom = prePoint->GetMomentum() / CLHEP::GeV;
  CLHEP::Hep3Vector postMom = postPoint->GetMomentum() / CLHEP::GeV;
  G4double preE = prePoint->GetTotalEnergy() / CLHEP::GeV;
  G4double postE = postPoint->GetTotalEnergy() / CLHEP::GeV;

  const G4VTouchable *preTouchable = prePoint->GetTouchable();
  G4String preSolidName = preTouchable->GetVolume(0)->GetLogicalVolume()->GetSolid()->GetName();
  const G4VTouchable *postTouchable = postPoint->GetTouchable();
  G4String postSolidName = postTouchable->GetVolume(0)->GetLogicalVolume()->GetSolid()->GetName();
  
  CLHEP::Hep3Vector itaPos = postPos;
  CLHEP::Hep3Vector itaMom = postMom;
  G4double itaE = postE;
  G4String itaSolidName = postSolidName;
  if(stepNumber==1){
    itaPos = prePos;
    itaMom = preMom;
    itaE = preE;
    itaSolidName = preSolidName;
  }

  if(m_bias){
    m_nofScat++;
    if(m_nofScat>m_maxNofScat){
      postProcName="killed";
      _track->SetTrackStatus(fStopAndKill);
    }
  }
  
  //m_foutSynStatistic->setf(std::ios::showpos);
  m_foutSynStatistic->setf(std::ios::scientific);
  
  (*m_foutSynStatistic)<<std::setprecision(9)<<stepNumber<<std::setw(18)<<itaPos.x()<<std::setw(18)<<itaPos.y()<<std::setw(18)<<itaPos.z()<<std::setw(18)<<itaMom.x()<<std::setw(18)<<itaMom.y()<<std::setw(18)<<itaMom.z()<<std::setw(18)<<itaE<<"  "<<postProcName<<"  "<<materialName<<"  "<<itaSolidName<<std::endl;
  
  m_foutSynStatistic->unsetf(std::ios::scientific);
  //m_foutSynStatistic->unsetf(std::ios::showpos);

  if(BDSExecOptions::Instance()->GetVerboseStep()){
    //const G4VTouchable *preTouchable = prePoint->GetTouchable();
    //for(int iH=0;iH<preTouchable->GetHistoryDepth();iH++){
    //  G4cout<<"preTouchableVolume: "<<iH<<", "<<preTouchable->GetVolume(iH)->GetName()<<", Material: "<<preTouchable->GetVolume(iH)->GetLogicalVolume()->GetMaterial()->GetName()<<", SolidName: "<<preTouchable->GetVolume(iH)->GetLogicalVolume()->GetSolid()->GetName()<<G4endl;
    //}

    //const G4VTouchable *postTouchable = postPoint->GetTouchable();
    //for(int iH=0;iH<postTouchable->GetHistoryDepth();iH++){
    //  G4cout<<"postTouchableVolume: "<<iH<<", "<<postTouchable->GetVolume(iH)->GetName()<<", Material: "<<postTouchable->GetVolume(iH)->GetLogicalVolume()->GetMaterial()->GetName()<<", SolidName: "<<postTouchable->GetVolume(iH)->GetLogicalVolume()->GetSolid()->GetName()<<G4endl;
    //}

    G4String preVolName,postVolName;
    preVolName = prePoint->GetPhysicalVolume()->GetName();
    postVolName = postPoint->GetPhysicalVolume()->GetName();

    G4cout << "CurrentStepNumber: "<<stepNumber<<G4endl;
    G4cout << "PrePosition: "<<prePos<<" m"<<G4endl;
    G4cout << "PostPosition: "<<postPos<<" m"<<G4endl;
    G4cout << "PreHitMom: "<<preMom<<" GeV"<<G4endl;
    G4cout << "PostHitMom: "<<postMom<<" GeV"<<G4endl;
    G4cout << "Pre Volume Name: "<<preVolName<<", Post Volume Name: "<<postVolName<<G4endl;
    G4cout << "Material: " << materialName<<G4endl;
    if(preProc) G4cout << "preProcess=" << preProcName<<G4endl;
    G4cout << "postProcess=" << postProcName<<G4endl;
    G4cout << "" <<G4endl;
  }

}

void BDSSteppingAction::TerminateSteppingAction(){
  G4Track* _track = _step->GetTrack();
  G4int parentId = _track->GetParentID();
  if(parentId!=0){
    //G4int trkId = _track->GetTrackID();
    //G4cout<<"Current Particle PDGcode: "<<_track->GetDefinition()->GetPDGEncoding()<<", TrackID: "<<trkId<<", ParentID: "<<parentId<<G4endl;
    return;
  }

  G4StepPoint* prePoint = _step->GetPreStepPoint();
  G4StepPoint* postPoint = _step->GetPostStepPoint();
  if(!postPoint->GetPhysicalVolume()) return;

  G4String preVolName,postVolName;
  preVolName = prePoint->GetPhysicalVolume()->GetName();
  postVolName = postPoint->GetPhysicalVolume()->GetName();
  
  CLHEP::Hep3Vector prePos = prePoint->GetPosition() / CLHEP::m;
  CLHEP::Hep3Vector postPos = postPoint->GetPosition() / CLHEP::m;
  CLHEP::Hep3Vector preMom = prePoint->GetMomentum() / CLHEP::GeV;
  CLHEP::Hep3Vector postMom = postPoint->GetMomentum() / CLHEP::GeV;
  G4double preE = prePoint->GetTotalEnergy() / CLHEP::GeV;
  G4double postE = postPoint->GetTotalEnergy() / CLHEP::GeV;

  if(postVolName.find(m_endElementName)!=std::string::npos){

    if(BDSExecOptions::Instance()->GetVerboseStep()){
      CLHEP::Hep3Vector vtxPos = _track->GetVertexPosition() / CLHEP::m;
      G4cout << "VertexPosition: "<<vtxPos<<" m"<<G4endl;
      G4cout << "HitPosition: "<<postPos<<" m"<<G4endl;
      G4cout << "Pre Volume Name: "<<preVolName<<", Post Volume Name: "<<postVolName<<G4endl;
      G4cout << "Particle "<<_track->GetDefinition()->GetParticleName()<<" will be killed because it has reached the end element: "<<m_endElementName<<"!!!"<<G4endl;
      G4cout<<""<<G4endl;
    }

    if(m_foutBeam){  
      //Transform to local coordinate from global coordinate
      G4ThreeVector localPos = postPos-m_endPosition/CLHEP::m;
      G4ThreeVector localMom = (m_endRotation->inverse())*postMom;

      m_foutBeam->setf(std::ios::showpos);
      m_foutBeam->setf(std::ios::scientific);

      (*m_foutBeam)<<std::setprecision(9)<<localPos.x()<<std::setw(18)<<localPos.y()<<std::setw(18)<<localPos.z()<<std::setw(18)<<localMom.x()<<std::setw(18)<<localMom.y()<<std::setw(18)<<localMom.z()<<std::setw(18)<<postE<<std::endl;

      m_foutBeam->unsetf(std::ios::scientific);
      m_foutBeam->unsetf(std::ios::showpos);
    }

    _track->SetTrackStatus(fStopAndKill);

  }

  return;
}
