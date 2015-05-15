#include "BDSBunchUserFile.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "BDSDebug.hh"

BDSBunchUserFile::BDSBunchUserFile():nlinesIgnore(0){
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif
}

BDSBunchUserFile::~BDSBunchUserFile(){
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  CloseBunchFile();
}

void BDSBunchUserFile::OpenBunchFile(){
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  InputBunchFile.open(distribFile);
  if(!InputBunchFile.good()){ 
    G4cerr<<"Cannot open bunch file "<< distribFile <<G4endl; 
    exit(1); 
  } 
}

void BDSBunchUserFile::CloseBunchFile(){
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  InputBunchFile.close();
}

void BDSBunchUserFile::ParseFileFormat(){
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  G4String unparsed_str = bunchFormat;
  G4int pos = unparsed_str.find(":");
  
  struct BDSBunchUserFile::Doublet sd;
  
  while(pos > 0){
    pos = unparsed_str.find(":");
    G4String token = unparsed_str.substr(0,pos);
    
    unparsed_str = unparsed_str.substr(pos+1);
#ifdef BDSDEBUG 
    G4cout<< __METHOD_NAME__ <<"token -> "<<token<<G4endl;
    G4cout<< __METHOD_NAME__ <<"token.substr(0,1) -> " << token.substr(0,1) << G4endl;
    G4cout<< __METHOD_NAME__ <<"unparsed_str -> "<<unparsed_str<<G4endl;
    G4cout<< __METHOD_NAME__ <<"pos -> "<<pos<<G4endl;
#endif
    if(token.substr(0,1)=="E" || token.substr(0,1)=="P") {
      G4String name = token.substr(0,1);
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ << name << "!"<<G4endl;
#endif
      G4String rest = token.substr(1);
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ <<"rest ->"<<rest<<G4endl;
#endif
      G4int pos1 = rest.find("[");
      G4int pos2 = rest.find("]");
      if(pos1 < 0 || pos2 < 0) {
	G4cerr<<"unit format wrong!!!"<<G4endl;
      } else {
	G4String fmt = rest.substr(pos1+1,pos2-1);
#ifdef BDSDEBUG 
	G4cout<< __METHOD_NAME__ <<"fmt ->"<<fmt<<G4endl;
#endif
	sd.name = name;
	sd.unit = ParseEnergyUnit(fmt);
	fields.push_back(sd);
      }
    } else if(token.substr(0,1)=="t") {
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ <<"t!"<<G4endl;
#endif
      G4String rest = token.substr(1);
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ <<"rest ->"<<rest<<G4endl;
#endif
      G4int pos1 = rest.find("[");
      G4int pos2 = rest.find("]");
      if(pos1 < 0 || pos2 < 0) {
	G4cerr<<"unit format wrong!!!"<<G4endl;
      } else {
	G4String fmt = rest.substr(pos1+1,pos2-1);
#ifdef BDSDEBUG 
	G4cout<< __METHOD_NAME__ <<"fmt ->"<<fmt<<G4endl;
#endif
	sd.name = "t"; 
        sd.unit = ParseTimeUnit(fmt);
	fields.push_back(sd);
      }
    } else if( ( token.substr(0,1)=="x" && token.substr(1,1)!="p" ) ||
	       ( token.substr(0,1)=="y" && token.substr(1,1)!="p" ) ||
	       ( token.substr(0,1)=="z" && token.substr(1,1)!="p" ) ) {
      G4String name = token.substr(0,1);
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ << name << "!"<<G4endl;
#endif
      G4String rest = token.substr(1);
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ <<"rest ->"<<rest<<G4endl;
#endif
      G4int pos1 = rest.find("[");
      G4int pos2 = rest.find("]");
      if(pos1 < 0 || pos2 < 0) {
	G4cerr<<"unit format wrong!!!"<<G4endl;
      } else {
	G4String fmt = rest.substr(pos1+1,pos2-1);
#ifdef BDSDEBUG 
	G4cout<< __METHOD_NAME__ <<"fmt ->"<<fmt<<G4endl;
#endif
	sd.name=name;
	sd.unit=ParseLengthUnit(fmt);	
	fields.push_back(sd);	
      }
    } else if ( (token.substr(0,2)=="xp") ||
		(token.substr(0,2)=="yp") ||
		(token.substr(0,2)=="zp") ) {
      G4String name = token.substr(0,2);
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ << name << "!"<<G4endl;
#endif
      G4String rest = token.substr(2);
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ <<"rest ->"<<rest<<G4endl;
#endif
      G4int pos1 = rest.find("[");
      G4int pos2 = rest.find("]");
      if(pos1 < 0 || pos2 < 0) {
	G4cerr<<"unit format wrong!!!"<<G4endl;
      } else {
	G4String fmt = rest.substr(pos1+1,pos2-1);
#ifdef BDSDEBUG 
	G4cout<< __METHOD_NAME__ <<"fmt ->"<<fmt<<G4endl;
#endif
	sd.name=name;
	sd.unit=ParseAngleUnit(fmt);
	fields.push_back(sd);
      }
    }else if(token.substr(0,2)=="pt") {
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ <<"pt!"<<G4endl;
#endif
      sd.name="pt";
      sd.unit=1;
      fields.push_back(sd);
    } else if(token.substr(0,1)=="w") {
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ <<"weight!"<<G4endl;
#endif
      sd.name="weight";
      sd.unit=1;
      fields.push_back(sd);
    } else if (token.substr(0,1)=="-") {
      // skip
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ << "skip token " <<G4endl;
#endif
      sd.name="skip";
      sd.unit=1;
      fields.push_back(sd);
    } else {
      G4cerr << "Cannot determine bunch data format" << G4endl; exit(1);
    }
  } 
  return;
}

void BDSBunchUserFile::skip(G4int nvalues){
  G4double dummy_val;
  for(G4int i=0;i<nvalues;i++) ReadValue(dummy_val);
}

void BDSBunchUserFile::SetOptions(struct Options &opt) {
  BDSBunchInterface::SetOptions(opt);
  SetDistribFile((G4String)opt.distribFile); 
  SetBunchFormat((G4String)opt.distribFileFormat); 
  SetNLinesIgnore(opt.nlinesIgnore);
  ParseFileFormat();
  OpenBunchFile(); //
  return; 
}

G4double BDSBunchUserFile::ParseEnergyUnit(G4String &fmt)
{
  G4double unit=1.;
  if(fmt=="GeV") unit=1;
  else if(fmt=="MeV") unit=1.e-3;
  else if(fmt=="KeV") unit=1.e-6;
  else if(fmt=="eV") unit=1.e-9;
  else {
    G4cout << __METHOD_NAME__ << "Unrecognised energy unit! " << fmt << G4endl;
    exit(1);
  }
  return unit;
}

G4double BDSBunchUserFile::ParseLengthUnit(G4String &fmt)
{
  G4double unit=1.;
  if(fmt=="m") unit=1;
  else if(fmt=="cm") unit=1.e-2;
  else if(fmt=="mm") unit=1.e-3;
  else if(fmt=="mum" || fmt=="um") unit=1.e-6;
  else if(fmt=="nm") unit=1.e-9;
  else {
    G4cout << __METHOD_NAME__ << "Unrecognised length unit! " << fmt << G4endl;
    exit(1);
  }
  return unit;
}

G4double BDSBunchUserFile::ParseAngleUnit(G4String &fmt)
{
  G4double unit=1.;
  if(fmt=="rad") unit=1;
  else if(fmt=="mrad") unit=1.e-3;
  else if(fmt=="murad" || fmt=="urad") unit=1.e-6;
  else {
    G4cout << __METHOD_NAME__ << "Unrecognised angle unit! " << fmt << G4endl;
    exit(1);
  }
  return unit;
}

G4double BDSBunchUserFile::ParseTimeUnit(G4String &fmt)
{
  G4double unit=1.;
  if(fmt=="s") unit=1;
  else if(fmt=="ms") unit=1.e-3;
  else if(fmt=="mus" || fmt=="us") unit=1.e-6;
  else if(fmt=="ns") unit=1.e-9;
  else if(fmt=="mm/c") unit=(CLHEP::mm/CLHEP::c_light)/CLHEP::s;
  else if(fmt=="nm/c") unit=(CLHEP::nm/CLHEP::c_light)/CLHEP::s;
  else {
    G4cout << __METHOD_NAME__ << "Unrecognised time unit! " << fmt << G4endl;
    exit(1);
  }
  return unit;
}

void BDSBunchUserFile::GetNextParticle(G4double& x0, G4double& y0, G4double& z0, 
		     G4double& xp, G4double& yp, G4double& zp,
		     G4double& t , G4double&  E, G4double& weight) {

  E = x0 = y0 = z0 = xp = yp = zp = t = 0;
  weight = 1;
  
  bool zpdef = false; //keeps record whether zp has been read from file
  bool tdef = false; //keeps record whether t has been read from file
  
  G4int type;
  
  //Skip the a number of lines defined by the user option.
#ifdef BDSDEBUG 
  G4cout << __METHOD_NAME__ << "UDEF_BUNCH: skipping " << nlinesIgnore << " lines" << G4endl;
#endif
  skip((G4int)(nlinesIgnore * fields.size()));
  
  std::list<struct BDSBunchUserFile::Doublet>::iterator it;
  for(it=fields.begin();it!=fields.end();it++)
    {
#ifdef BDSDEBUG 
      G4cout<< __METHOD_NAME__ <<it->name<<"  ->  "<<it->unit<<G4endl;
#endif
      if(it->name=="E") { 
	ReadValue(E); E *= ( CLHEP::GeV * it->unit ); 
#ifdef BDSDEBUG 
	G4cout << "******** Particle Mass = " << BDSGlobalConstants::Instance()->GetParticleDefinition()->GetPDGMass() << G4endl;
	G4cout << "******** Particle Total Energy = " << E << G4endl;
#endif
	E-=BDSGlobalConstants::Instance()->GetParticleDefinition()->GetPDGMass();
#ifdef BDSDEBUG 
	G4cout << "******** Particle Kinetic Energy = " << E << G4endl;
	G4cout<< __METHOD_NAME__ << E <<G4endl;
#endif
      }
      else if(it->name=="P") { 
	G4double P=0;
	ReadValue(P); P *= ( CLHEP::GeV * it->unit ); //Paticle momentum
	G4double particleMass = BDSGlobalConstants::Instance()->GetParticleDefinition()->GetPDGMass();
	G4double totalEnergy = sqrt(P*P + particleMass*particleMass);
	E = totalEnergy - particleMass;
#ifdef BDSDEBUG 
	G4cout << "******** Particle Mass = " << particleMass << G4endl;
	G4cout << "******** Particle Total Energy = " << totalEnergy << G4endl;
	G4cout << "******** Particle Kinetic Energy = " << E << G4endl;
	G4cout<< __METHOD_NAME__ << E <<G4endl;
#endif
      }
      else if(it->name=="t") { ReadValue(t); t *= ( CLHEP::s * it->unit ); tdef = true; }
      else if(it->name=="x") { ReadValue(x0); x0 *= ( CLHEP::m * it->unit ); 
#ifdef BDSDEBUG 
	G4cout<< __METHOD_NAME__ << x0 <<G4endl;
#endif
      }
      else if(it->name=="y") { 
	ReadValue(y0); y0 *= ( CLHEP::m * it->unit ); 
#ifdef BDSDEBUG 
	G4cout<< __METHOD_NAME__ << y0 <<G4endl;
#endif
      }
      else if(it->name=="z") { 
	ReadValue(z0); z0 *= ( CLHEP::m * it->unit ); 
#ifdef BDSDEBUG 
	G4cout<< __METHOD_NAME__ << z0 <<G4endl;
#endif
      }
      else if(it->name=="xp") { ReadValue(xp); xp *= ( CLHEP::radian * it->unit ); }
      else if(it->name=="yp") { ReadValue(yp); yp *= ( CLHEP::radian * it->unit ); }
      else if(it->name=="zp") { ReadValue(zp); zp *= ( CLHEP::radian * it->unit ); zpdef = true;}
      else if(it->name=="pt") {
	ReadValue(type);
	if(InputBunchFile.good()){
	  BDSGlobalConstants::Instance()->SetParticleName(G4ParticleTable::GetParticleTable()->FindParticle(type)->GetParticleName());
	  BDSGlobalConstants::Instance()->SetParticleDefinition(G4ParticleTable::
								GetParticleTable()
								->FindParticle(type));
	  if(!BDSGlobalConstants::Instance()->GetParticleDefinition()) 
	    {
	      G4Exception("Particle not found, quitting!", "-1", FatalErrorInArgument, "");
	      exit(1);
	    }
	}
      }
      else if(it->name=="weight") ReadValue(weight);
      
      else if(it->name=="skip") {double dummy; ReadValue(dummy);}
      
      // compute zp from xp and yp if it hasn't been read from file
      if (!zpdef) zp = CalculateZp(xp,yp,1);
      // compute t from z0 if it hasn't been read from file
      if (!tdef) t=0; 
      // use the Kinetic energy:
      //          if(BDSGlobalConstants::Instance()->GetParticleDefinition()->GetPDGEncoding() != 22){
      //}
    }
  //Add the global offset Z
  z0=z0+Z0*CLHEP::m;
}

template <typename Type> G4bool  BDSBunchUserFile::ReadValue(Type &value){
  InputBunchFile>>value; 
  if (InputBunchFile.eof()){ //If the end of the file is reached go back to the beginning of the file.
    //this re reads the same file again to avoid crash - must always print warning
    G4cout << __METHOD_NAME__ << "End of file reached. Returning to beginning of file." << G4endl;
    CloseBunchFile();
    OpenBunchFile();
    InputBunchFile>>value; 
  } 
  return !InputBunchFile.eof();
}
