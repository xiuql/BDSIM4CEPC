/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 * 
 * Class library version 2.0 (1999)
 * 
 * file Merlin\MADInterface\MADInterface.h
 * last modified 11/07/00 20:43:06
 */
/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * MERLIN C++ class library for 
 * Charge Particle Accelerator Simulations
 * Copyright (c) 1999 by N.J.Walker.  ALL RIGHTS RESERVED. 
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * No representations about the suitability of this software for
 * any purpose is made. It is provided "as is" without express
 * or implied warranty.
 */

#ifndef BDSMADInterface_h
#define BDSMADInterface_h 1

//#include "merlin_config.h"

#include <fstream>
#include <string>
#include <set>
#include <list>

using std::ifstream;
using std::ostream;
using std::list;

typedef list<BDSAcceleratorComponent*>  BDSBeamline;

#include"BDSAcceleratorComponent.hh"

//	Class used to construct a MERLIN model from a MAD optics
//	output listing. The file should be generated using the
//	following MAD commands:
//
//	OPTICS, NAME, KEYWORD ,S, L ,K0L , K1L, K2L,&
//	               K3L,TILT,TYPE

class BDSMADInterface 
{
  public:
      //	Constructor taking the name of the MAD optics file, and
      //	the momentum in GeV/c.
      BDSMADInterface (const G4String& madFileName, G4double P0);
      ~BDSMADInterface();

     BDSBeamline ConstructModel();

     void SetLogFile(ofstream & os);

  protected:
  private:
    // Data Members for Class Attributes

  G4double brho;
  ifstream ifs;
  ifstream synch_file;
  G4double synch_factor;
  G4double E_Synch;

  ostream* log;

  G4double ReadComponent ();
  BDSBeamline* ctor;
};

inline void BDSMADInterface::SetLogFile(ofstream & os)
{
log=&os;
}


#endif
