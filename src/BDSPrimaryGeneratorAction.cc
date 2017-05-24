#include "BDSGlobalConstants.hh"
#include "BDSPrimaryGeneratorAction.hh"
#include "BDSBunch.hh"
#include "BDSParticle.hh"
#include "BDSDebug.hh"
#include "BDSExecOptions.hh"

#include "BDSAcceleratorModel.hh"
#include "BDSBeamline.hh"
#include "BDSParser.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"

BDSPrimaryGeneratorAction::BDSPrimaryGeneratorAction(BDSBunch* bdsBunchIn):
  G4VUserPrimaryGeneratorAction(),
  weight(1),
  bdsBunch(bdsBunchIn)
{
  particleGun  = new G4ParticleGun(1); // 1-particle gun

#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << "Primary particle is "
	 << BDSGlobalConstants::Instance()->GetParticleDefinition()->GetParticleName() << G4endl;
#endif
  
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  particleGun->SetParticlePosition(G4ThreeVector(0.*CLHEP::cm,0.*CLHEP::cm,0.*CLHEP::cm));
  particleGun->SetParticleEnergy(BDSGlobalConstants::Instance()->GetBeamKineticEnergy());
  particleGun->SetParticleTime(0);
  
  startElementName = BDSParser::Instance()->GetOptions().trackingStart;
  if(startElementName==""){
    startPointFlag=false;
  }else{
    startPointFlag=true;
  }
  firstTimeFlag=true;
}

BDSPrimaryGeneratorAction::~BDSPrimaryGeneratorAction()
{delete particleGun;}

void BDSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of event

  //Start Point
  if(firstTimeFlag){
    BDSBeamline* beamline = BDSAcceleratorModel::Instance()->GetFlatBeamline();
    BDSBeamline::iterator it = beamline->begin();
    BDSBeamlineElement* startElement = (*it);

    if(startPointFlag){
      for(; it != beamline->end(); ++it)
      {
        if((*it)->GetPlacementName()==startElementName){
          startElement = *it;
          break;
        }
      }

      if(it==beamline->end()){
        G4cerr << __METHOD_NAME__ << "ERROR - Can't find start element "<< startElementName << G4endl;
        exit(1);
      }
      startPointFlag=false;

    }
    

    startPosition = startElement->GetReferencePositionStart();
    startRotation = startElement->GetReferenceRotationStart();
    firstTimeFlag=false;
    
    G4cout << __METHOD_NAME__ << "Primary particle is " << BDSGlobalConstants::Instance()->GetParticleDefinition()->GetParticleName() <<", Start Element: "<<startElement->GetName()<<", PlacementName: "<<startElement->GetPlacementName()<<", CopyNumber: "<<startElement->GetCopyNo()<<", StartPosition: "<<startPosition<<", StartRotation: "<<(*startRotation)<<G4endl;
  }

  G4double x0=0.0, y0=0.0, z0=0.0, xp=0.0, yp=0.0, zp=0.0, t=0.0, E=0.0;

  particleGun->SetParticleDefinition(BDSGlobalConstants::Instance()->GetParticleDefinition());
  bdsBunch->GetNextParticle(x0,y0,z0,xp,yp,zp,t,E,weight); // get next starting point
  if(E==0) G4cout << __METHOD_NAME__ << "Particle energy is 0! This will not be tracked." << G4endl;

#ifdef BDSDEBUG 
  G4cout <<"Local: " << __METHOD_NAME__ 
	 << x0 << " " << y0 << " " << z0 << " " 
	 << xp << " " << yp << " " << zp << " " 
	 << t  << " " << E  << " " << weight << G4endl;
#endif

  G4ThreeVector LocalPos;
  G4ThreeVector LocalMomDir;

  G4ThreeVector PartMomDir(xp,yp,zp);
  G4ThreeVector PartPosition(x0,y0,z0);

  if(BDSParser::Instance()->GetOptions().distribType != "userfile"){
    G4cout << __METHOD_NAME__ <<", StartPosition: "<<startPosition<<", StartRotation: "<<(*startRotation)<<G4endl;
    PartMomDir = (*startRotation)*PartMomDir;
    PartPosition = startPosition+PartPosition;
  }

  if(BDSParser::Instance()->GetOptions().distribType == "userfile" && BDSParser::Instance()->GetOptions().beamOutputPath != ""){
    G4cout << __METHOD_NAME__ <<", StartPosition: "<<startPosition<<", StartRotation: "<<(*startRotation)<<G4endl;
    PartMomDir = (*startRotation)*PartMomDir;
    PartPosition = startPosition+PartPosition;
  }
  
  particleGun->SetParticlePosition(PartPosition);
  particleGun->SetParticleEnergy(E);
  particleGun->SetParticleMomentumDirection(PartMomDir);
  particleGun->SetParticleTime(t);
  
  particleGun->GeneratePrimaryVertex(anEvent);

  //Set the weight
#ifdef BDSDEBUG
  G4cout << "BDSPrimaryGeneratorAction: setting weight = " << weight << G4endl;
#endif
  anEvent->GetPrimaryVertex()->SetWeight(weight);
  
  G4double totalE = E+particleGun->GetParticleDefinition()->GetPDGMass();

  if(BDSExecOptions::Instance()->GetVerboseStep()){
//#ifdef BDSDEBUG
    G4cout
      << "BDSPrimaryGeneratorAction: " << G4endl
      << "  position= " << particleGun->GetParticlePosition()/CLHEP::m<<" m"<<G4endl
      << "  kinetic energy= " << E/CLHEP::GeV << " GeV" << G4endl
      << "  total energy= " << totalE/CLHEP::GeV << " GeV" << G4endl
      << "  momentum direction= " << PartMomDir << G4endl
      << "  weight= " << anEvent->GetPrimaryVertex()->GetWeight() << G4endl;
//#endif
  }

  // save initial values outside scope for entry into the samplers:
  BDSParticle initialPoint(x0,y0,z0,xp,yp,zp,totalE,t,weight);
  BDSGlobalConstants::Instance()->SetInitialPoint(initialPoint);
}
