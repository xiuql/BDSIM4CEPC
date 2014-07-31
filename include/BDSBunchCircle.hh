#ifndef BDSBunchCircle_h
#define BDSBunchCircle_h 

#include "BDSBunchInterface.hh"
#include "BDSGlobalConstants.hh"
#include "Randomize.hh"

namespace CLHEP {
  class RandFlat;
}

class BDSBunchCircle : public BDSBunchInterface { 
protected : 
  G4double envelopeX; 
  G4double envelopeY;
  G4double envelopeXp; 
  G4double envelopeYp; 
  G4double envelopeT;
  G4double envelopeE; 
  
  CLHEP::RandFlat  *FlatGen;    

public: 
  BDSBunchCircle(); 
  BDSBunchCircle(G4double envelopeX , G4double envelopeY,
		 G4double envelopeXp, G4double envelopeYp,
		 G4double envelopeT , G4double envelopeE);
  ~BDSBunchCircle(); 
  void SetOptions(struct Options& opt);
  void GetNextParticle(G4double& x0, G4double& y0, G4double& z0, 
		       G4double& xp, G4double& yp, G4double& zp,
		       G4double& t , G4double&  E, G4double& weight);  
  
  G4double GetEnvelopeX() {return envelopeX;}
  G4double GetEnvelopeY() {return envelopeY;}
  G4double GetEnvelopeXp(){return envelopeXp;}
  G4double GetEnvelopeYp(){return envelopeYp;}
  G4double GetEnvelopeT() {return envelopeT;}
  G4double GetEnvelopeE() {return envelopeE;}

  void SetEnvelopeX(G4double envelopeXIn)  {envelopeX = envelopeXIn;}
  void SetEnvelopeY(G4double envelopeYIn)  {envelopeY = envelopeYIn;}
  void SetEnvelopeXp(G4double envelopeXpIn){envelopeXp= envelopeXpIn;}
  void SetEnvelopeYp(G4double envelopeYpIn){envelopeYp= envelopeYpIn;}
  void SetEnvelopeT(G4double envelopeTIn)  {envelopeT = envelopeTIn;}
  void SetEnvelopeE(G4double envelopeEIn)  {envelopeE = envelopeEIn;}



};

#endif
