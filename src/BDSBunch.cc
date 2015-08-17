#include "BDSBunch.hh"
#include "BDSBunchFactory.hh"
#include "BDSDebug.hh"

BDSBunch::BDSBunch() {
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif

  // Construct default reference type 
  distribType = std::string("reference");
  bdsBunch    = new BDSBunchInterface(); 
}

BDSBunch::~BDSBunch() {
  delete bdsBunch;
}

void BDSBunch::SetOptions(GMAD::Options& opt) {
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif

  // check options and construct corrrect bdsBunchInterface
  delete bdsBunch;

  bdsBunch = BDSBunchFactory::createBunch(opt.distribType);

  bdsBunch->SetOptions(opt);
  return;
}


void BDSBunch::GetNextParticle(G4double& x0, G4double& y0, G4double& z0, 
			       G4double& xp, G4double& yp, G4double& zp,
			       G4double& t , G4double&  E, G4double& weight) {
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif

  bdsBunch->GetNextParticle(x0,y0,z0,xp,yp,zp,t,E,weight);
  return;
}
