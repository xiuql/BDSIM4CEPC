// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: SQCalorHit.hh,v 1.1.1.1 2004/11/18 17:42:41 ilia Exp $
// GEANT4 tag $Name:  $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef SQCalorHit_h
#define SQCalorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class SQCalorHit : public G4VHit
{
  public:

      SQCalorHit();
     ~SQCalorHit();
      SQCalorHit(const SQCalorHit&);
      const SQCalorHit& operator=(const SQCalorHit&);
      int operator==(const SQCalorHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();
      
  public:
  
      void AddAbs(G4double de, G4double dl) {EdepAbs += de; TrackLengthAbs += dl;};
      void AddGap(G4double de, G4double dl) {EdepGap += de; TrackLengthGap += dl;};      
                 
      G4double GetEdepAbs()     { return EdepAbs; };
      G4double GetTrakAbs()     { return TrackLengthAbs; };
      G4double GetEdepGap()     { return EdepGap; };
      G4double GetTrakGap()     { return TrackLengthGap; };
     
  private:
  
      G4double EdepAbs, TrackLengthAbs;
      G4double EdepGap, TrackLengthGap;
      
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

typedef G4THitsCollection<SQCalorHit> SQCalorHitsCollection;

extern G4Allocator<SQCalorHit> SQCalorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void* SQCalorHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) SQCalorHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void SQCalorHit::operator delete(void* aHit)
{
  SQCalorHitAllocator.FreeSingle((SQCalorHit*) aHit);
}

#endif


