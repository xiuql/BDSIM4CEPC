/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#ifndef BDSDECSTEPPER_HH
#define BDSDECSTEPPER_HH
#include "globals.hh"
#include "G4MagIntegratorStepper.hh"
//#include "G4MagHelicalStepper.hh"
#include "G4Mag_EqRhs.hh"
#include "G4ThreeVector.hh"
#include "G4Navigator.hh"

class BDSDecStepper : public G4MagIntegratorStepper
{

  public:  // with description

    BDSDecStepper(G4Mag_EqRhs *EqRhs);

    ~BDSDecStepper();

      void Stepper( const G4double y[],
		  const G4double dydx[],
		  const G4double h,
		  G4double yout[],
		  G4double yerr[]  );
      // The stepper for the Runge Kutta integration.
      // The stepsize is fixed, equal to h.
      // Integrates ODE starting values y[0 to 6]
      // Outputs yout[] and its estimated error yerr[].

    G4double DistChord()   const;
      // Estimate maximum distance of curved solution and chord ... 
 
     void SetBQuadPrime(G4double aBQuadPrime);
     G4double GetBQuadPrime();

     void StepperName();

  /*
   void DumbStepper( const G4double yInput[],
		     G4ThreeVector Bfld,
		     G4double hstep,
		     G4double yOut[]);

  */
  public: // without description
  
    G4int IntegratorOrder()const { return 2; }

  protected:
    //  --- Methods used to implement all the derived classes -----

    void AdvanceHelix( const G4double  yIn[],
                       G4ThreeVector Bfld,
		       G4double  h,
		       G4double  yDec[]);    // output 
      // A first order Step along a dec inside the field.

  private:
  
    G4ThreeVector yInitial, yMidPoint, yFinal;
      // Data stored in order to find the chord.

    G4Mag_EqRhs*  fPtrMagEqOfMot;

    G4double itsBQuadPrime;
  //    G4ThreeVector itsInitialPoint, itsFinalPoint, itsMidPoint,itsDistVec;
    G4double itsDist;

};

inline  void BDSDecStepper::SetBQuadPrime(G4double aBQuadPrime)
{itsBQuadPrime=aBQuadPrime;
}
inline G4double BDSDecStepper::GetBQuadPrime()
{return itsBQuadPrime;}

inline void BDSDecStepper::StepperName()
{G4cout<<"BDSDecStepper"<<G4endl;}

#endif /* BDSDECSTEPPER_HH */
