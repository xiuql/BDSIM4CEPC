/*
 * GMAD interface 
 * I. Agapov 2005
*/

#ifndef _GMAD_H
#define _GMAD_H

#define _RESERVED 1

#include <iostream>
#include <stdio.h>
#include <list>
#include <string>

using namespace std;

// types of elements

const int _NONE = -1;
const int _MARKER = 1;
const int _DRIFT = 2;
const int _SBEND = 3; 
const int _QUAD  = 4;
const int _SEXTUPOLE  = 5;
const int _OCTUPOLE = 6;
const int _MULT  = 7;
const int _SOLENOID = 8;
const int _ELEMENT = 9;
const int _LINE = 10;
const int _COLLIMATOR = 11;
const int _ECOL = 12;
const int _RCOL = 13;
const int _LASER=14;

const int _SAMPLER = 16;
const int _CSAMPLER = 17;

const int _TRANSFORM3D = 29;

const char *typestr(int type);


// geometry and field formats

const int _GMAD = 0;
const int _MOKKA = 1;

const int _GAUSSIAN = 0;
const int _RING = 1;
const int _SQUARE = 2;
const int _CIRCLE = 3; 
const int _GUINEAPIG_BUNCH = 4;
const int _GUINEAPIG_PAIRS = 5;
const int _GUINEAPIG_SLAC = 6;

struct Options {
  double beamEnergy;
  double beamEnergySpread;

  string particleName;
  string distribType;
  string distribFile;

  int numberOfParticles;

  double sigmaX;
  double sigmaY;
  double sigmaT;
  double sigmaXp;
  double sigmaYp;

  // for element specification
  double X0;
  double Y0;
  double Rmin;
  double Rmax;

  double xsize, ysize;

  int numberToGenerate;
  int numberOfEventsPerNtuple;
  int backgroundScaleFactor;
  double componentBoxSize;
  double tunnelRadius;
  double beampipeRadius;
  double beampipeThickness;
  double thresholdCutCharged;
  double thresholdCutPhotons;
  double trackWeightFactor;
  double deltaChord;
  double chordStepMinimum;
  double deltaIntersection;
  bool turnOnInteractions;
  int useLowEMPhysics;
  int synchRadOn;
  int synchRescale;
  int synchTrackPhotons;
  double synchLowX;
  double synchLowGamE;
  int synchPhotonMultiplicity;
  int synchMeanFreeFactor;
  int planckOn;
  int eBremOn;
  double lengthSafety;
  long int randomSeed;

  int verboseStep;
  int verboseEventNumber;

  int useTimer;
  int useEMHadronic;
  int useMuonPairProduction;
  double muonProductionScaleFactor;
  double hadronInelasticScaleFactor;
  int storeMuonTrajectories;
  int storeTrajectory;
  int stopTracks;
  int useMuonShowers;
  double muonLowestGeneratedEnergy;


};

struct Element {
  short type;
  char * name;

  
  double l,k0,k1,k2,k3,angle,aper,tilt,xsize,ysize,r;
  double xdir, ydir, zdir, waveLength; // for laser wire and 3d transforms

  double phi, theta, psi; // for 3d transforms

  list<double> knl;
  list<double> ksl;

  string geometryFile;
  string bmapFile;
  string material;
  
  // in case the element is a list itself (line)
  list <Element> *lst;

  
};


struct Parameters {
  double l;  int lset;    // length
  double k0; int k0set;   // dipole 
  double k1; int k1set;   // quadrupole
  double k2; int k2set;   // sextupole
  double k3; int k3set;   // octupole

  double r; int rset; //radius, i.e cylindrical sampler
  
  double angle; int angleset;   // bending angle
  double aper; int aperset;   // aperture (circular)
  double phi, theta, psi; // for 3d transforms
  int phiset, thetaset, psiset;

  double xsize, ysize; int xsizeset, ysizeset; // aperture (or laser spotsize for laser)
  double xdir, ydir, zdir, waveLength; int xdirset, ydirset, zdirset, waveLengthset;

  double tilt; int tiltset;   // tilt
  
  list<double> knl;           // multipole expansion coefficients
  list<double> ksl;           // skew multipole expansion
  
  int knlset; int kslset;

  // for external geometry and field definition files
  char geometry[32]; int geomset;
  char bmap[32]; int bmapset;
  char emap[32];
  char material[32]; int materialset;
  
  void flush() {
    l=0; lset = 0;
    r = 0; rset = 0;

    angle = 0; angleset = 0;
    xsize = 0; xsizeset = 0;
    ysize = 0; ysizeset = 0;
    
    xdir = 0; xdirset = 0;
    ydir = 0; ydirset = 0;
    zdir = 0; zdirset = 0; 
    waveLength = 0; waveLengthset = 0; 

    phi = 0; phiset = 0;
    theta = 0; thetaset = 0;
    psi = 0; psiset = 0;

    aper = 0; aperset = 0;
    tilt = 0; tiltset = 0;

    k0 = 0; k0set = 0;
    k1 = 0; k1set = 0;
    k2 = 0; k2set = 0;
    k3 = 0; k3set = 0;
    
    knlset = 0; kslset=0;


    knl.erase(knl.begin(),knl.end());
    ksl.erase(ksl.begin(),ksl.end());
    
    geomset = 0; bmapset = 0;
    strcpy(geometry,"");
    strcpy(bmap,"");
    strcpy(material,"");
  }

  
};


extern list<Element> beamline_list;
extern Options options;

// parse the input file and construct beamline_list and options 
int gmad_parser(FILE *f);

int gmad_parser(string name);


#endif
