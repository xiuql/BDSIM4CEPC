// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: SQCalorimeterSD.hh,v 1.1.1.1 2004/11/18 17:42:41 ilia Exp $
// GEANT4 tag $Name:  $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef SQCalorimeterSD_h
#define SQCalorimeterSD_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class SQDetectorConstruction;
class G4HCofThisEvent;
class G4Step;
#include "SQCalorHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class SQCalorimeterSD : public G4VSensitiveDetector
{
  public:
  
      SQCalorimeterSD(G4String, SQDetectorConstruction* );
     ~SQCalorimeterSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*,G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
      void clear();
      void DrawAll();
      void PrintAll();

  private:
  
      SQCalorHitsCollection*  CalCollection;      
      SQDetectorConstruction* Detector;
      G4int*                   HitID;
};

#endif

