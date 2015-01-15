#include "BDSBunchPtc.hh"
#include "BDSDebug.hh"

#include <fstream>
#if __cplusplus!=199711 // test for c++11 features
#include <regex>
#endif 

BDSBunchPtc::BDSBunchPtc() { 
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif

  // load inrays file in current directory 
  this->fileName = "./inrays.madx";
  // Set ray counter to zero
  this->iRay = 0;
}

BDSBunchPtc::~BDSBunchPtc() { 
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  for(std::vector<double*>::iterator i = this->ptcData.begin();i!=this->ptcData.end();++i) {
    delete *i;
  }
}

void BDSBunchPtc::LoadPtcFile() { 
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif

  // open file and read line by line and extract values
  std::ifstream ifstr(this->fileName);

  if (!ifstr)
    { G4cout << __METHOD_NAME__ << "\"" << this->fileName << "\" file doesn't exist - exiting as no input" << G4endl;
      exit(1);
    }

  std::string line; 
  // read single line 
  while(std::getline(ifstr,line)) { 
    
    // variable for storage
    double x=0.0;
    double y=0.0;
    double px=0.0;
    double py=0.0; 
    double t=0.0;
    double pt=0.0;
    
#if __cplusplus==199711 

#else 
    // create regular expressions 
    std::regex rex("\\sx\\s*=\\s*([0-9eE.+-]+)");
    std::regex rey("\\sy\\s*=\\s*([0-9eE.+-]+)");
    std::regex repx("px\\s*=\\s*([0-9eE.+-]+)");
    std::regex repy("py\\s*=\\s*([0-9eE.+-]+)");
    std::regex ret("\\st\\s*=\\s*([0-9eE.+-]+)");
    std::regex rept("pt\\s*=\\s*([0-9eE.+-]+)");

    // return search match objects 
    std::smatch smx;
    std::smatch smy;
    std::smatch smpx;
    std::smatch smpy;
    std::smatch smt;    
    std::smatch smpt;

    // perform search
    std::regex_search(line,smx, rex);
    std::regex_search(line,smy, rey);
    std::regex_search(line,smpx,repx);
    std::regex_search(line,smpy,repy);
    std::regex_search(line,smt, ret);
    std::regex_search(line,smpt, rept);

    if(smx.size() == 2)  x  = std::stod(smx[1]);
    if(smy.size() == 2)  y  = std::stod(smy[1]);
    if(smpx.size() == 2) px = std::stod(smpx[1]);
    if(smpy.size() == 2) py = std::stod(smpy[1]);
    if(smt.size() == 2)  t  = std::stod(smt[1]);
    if(smpt.size() == 2) pt = std::stod(smpt[1]);
#endif


#ifdef BDSDEBUG 
    G4cout << __METHOD_NAME__ << "read line " << line << G4endl;
    G4cout << __METHOD_NAME__ << "values    " << x << " " << px << " " << y << " " << py << " " << t << " " << pt << G4endl;   
#endif 
    
    double *values = new double[6]; 
    values[0] = x;
    values[1] = px;
    values[2] = y; 
    values[3] = py;
    values[4] = t; 
    values[5] = pt; 
    
    // append values to storage vector
    this->ptcData.push_back(values);
  }

    // set number of available rays in options 
  this->nRays = this->ptcData.size();
  BDSGlobalConstants::Instance()->SetNumberToGenerate(this->nRays);

  return;
}

void BDSBunchPtc::SetOptions(struct Options& opt) {
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << " " << opt.distribFile << G4endl;
#endif

  BDSBunchInterface::SetOptions(opt);
  this->SetDistribFile((G4String)opt.distribFile); 
  this->LoadPtcFile();
}

void BDSBunchPtc::GetNextParticle(G4double& x0, G4double& y0, G4double& z0, 
				  G4double& xp, G4double& yp, G4double& zp,
				  G4double& t , G4double&  E, G4double& weight) {
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  x0     = this->ptcData[this->iRay][0]*CLHEP::m+X0;
  y0     = this->ptcData[this->iRay][2]*CLHEP::m+Y0;
  z0     = this->ptcData[this->iRay][4]+Z0;
  xp     = this->ptcData[this->iRay][1]*CLHEP::rad+Xp0;
  yp     = this->ptcData[this->iRay][3]*CLHEP::rad+Yp0;
  t      = (z0-Z0)/CLHEP::c_light+T0;
  E      = BDSGlobalConstants::Instance()->GetParticleKineticEnergy() * (this->ptcData[this->iRay][5]+1.0);
  zp     = CalculateZp(xp,yp,Zp0);
  weight = 1.0; 

  this->iRay++;

  // if all particles are read, start at 0 again
  if (this->iRay == this->nRays) this->iRay=0;

  return;
}

