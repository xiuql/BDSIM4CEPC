#ifndef BDSMODULARPHYSICSLIST_H
#define BDSMODULARPHYSICSLIST_H

#include "G4VModularPhysicsList.hh"
#include "G4OpticalPhysics.hh"
#include "G4VPhysicsConstructor.hh"

#include <map>
#include <string>
#include <vector>

class BDSGlobalConstants;
class BDSModularPhysicsList;

/// Typedef for function pointers to simplify syntax.
typedef void(BDSModularPhysicsList::*Constructor)(void);

class BDSModularPhysicsList: public G4VModularPhysicsList
{
public:
  BDSModularPhysicsList();
  virtual ~BDSModularPhysicsList();
  void Print();
  virtual void SetCuts();

private:
  G4bool verbose;
#ifdef BDSDEBUG 
  bool debug = true;
#else 
  bool debug = false;
#endif

  /// A map of physics list names to their constructors.
  std::map<std::string, Constructor> physicsConstructors;

  /// A vector of all the physics list names for searching. This is
  /// constructed from the above map physicsConstructors.
  std::vector<G4String> physicsLists;

  /// Many physics lists require other physics lists - keep a record
  /// of which ones have been activated and if the required ones haven't,
  /// activate them. This is also constructed from the physicsConstructors map.
  std::map<G4String, G4bool> physicsActivated;
  
  void SetParticleDefinition();
  void ConstructMinimumParticleSet();
  G4OpticalPhysics* opticalPhysics;
  std::vector<G4VPhysicsConstructor*> constructors;
  void ParsePhysicsList();
  void ConfigurePhysics();
  void ConfigureOptical();
  void Register();
  G4String physListName;

  /// Keep a local reference to global constants to avoid getting it all the time
  BDSGlobalConstants* globals;

  /// @{Physics constructor loader.
  void ParameterisationPhysics();  
  void CutsAndLimits();
  void Em();
  void EmLow();
  void Hadronic();
  void HadronicHP();
  void SynchRad();
  void Muon();					
  void Optical();
  void NoDecay();
  void QGSPBERT();
  void QGSPBERTHP();
  void QGSPBIC();
  void QGSPBICHP();
  void FTFP();
  void FTFPBERT();
  void FTFPBERTHP();
  /// @}
};

#endif

