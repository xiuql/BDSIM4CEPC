 
/** BDSIM, v0.1   

Last modified 01.02.2006 by Ilya Agapov

**/


#ifndef BDSPhysicsList_h
#define BDSPhysicsList_h

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

#define kNuCut  5*m

class BDSPhysicsList: public G4VUserPhysicsList
{
public:
  BDSPhysicsList();
  virtual ~BDSPhysicsList();

public:

 void AddParallelWorldName(G4String& pname)
         {paraWorldName.push_back(pname);}


  void AddScoringProcess();
  
  void ConstructParticle();
  void ConstructProcess();

  void SetCuts();

  // construct particular physics list processes

  void ConstructEM();
  void ConstructEM_db();

  void ConstructEM_LPB(); //added by M.D. Salt, R.B. Appleby, 15/10/09

  void ConstructMuon();

  void ConstructMuon_LPB(); 

  void ConstructMuon_XSBias(); 

  void ConstructMerlin();

  void ConstructEM_Low_Energy();

  void ConstructSR();

  void ConstructLaserWire();

  void ConstructHadronic();
  
  // method not finished? (and not used) 
  // I comment it out for now -- J. Snuverink, 16/07/12 
  // void ConstructPhotolepton_Hadron();

  void ConstructHad();

  void ConstructQGSP();

  void ConstructDecay();

private:
    std::vector<G4String>  paraWorldName;
};

#endif



