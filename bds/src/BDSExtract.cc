/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// BDSExtract
// Generates individual particles from PLACET output file
// G.A.Blair (RHUL) 10.12.01
// adapted from code supplied by D.Schulte (CERN)

#include "BDSExtract.hh"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <tcl.h>
#include <tk.h>
#include <alloca.h>

#define SPLINE_NMAX 1000

#ifndef PI
#define PI 3.141592653589793
#endif

#ifndef max
#define max(a,b) (((a)<(b))?(b):(a))
#endif

#ifndef min
#define min(a,b) (((a)>(b))?(b):(a))
#endif

#define RNDM_EPS 6e-8

#include<vector>


// Class BDSExtract 
BDSExtract::BDSExtract(char* ExtractInputFilename )
{
  rndmst5(12,34,56,78);
  itsBunch=new BDSExtractBunch(ExtractInputFilename);
  G4int n = itsBunch->GetNumSlicesPerBunch();
  G4int nm=itsBunch->GetNumMacroparticles();

  s_transv=new BDSMspline(nm,11);

  s_e=new vSpline(nm);
  s_x=new vSpline(nm);
  s_xp=new vSpline(nm);
  s_y=new vSpline(nm);
  s_yp=new vSpline(nm);
  s_x_x=new vSpline(nm);
  s_x_xp=new vSpline(nm);
  s_xp_xp=new vSpline(nm);
  s_y_y=new vSpline(nm);
  s_y_yp=new vSpline(nm);
  s_yp_yp=new vSpline(nm);

  G4int i;
  for(i=0;i<nm;i++)
    {
      (*s_e)[i]=new BDSSpline(n);
      (*s_x)[i]=new BDSSpline(n);
      (*s_xp)[i]=new BDSSpline(n);
      (*s_y)[i]=new BDSSpline(n);
      (*s_yp)[i]=new BDSSpline(n);
      (*s_x_x)[i]=new BDSSpline(n);
      (*s_x_xp)[i]=new BDSSpline(n);
      (*s_xp_xp)[i]=new BDSSpline(n);
      (*s_y_y)[i]=new BDSSpline(n);
      (*s_y_yp)[i]=new BDSSpline(n);
      (*s_yp_yp)[i]=new BDSSpline(n);
    }
 
  //  xvalue= new G4double[max(n,nm)];
  //  yvalue= new G4double[max(n,nm)];
  //  ytransv=new G4double[nm*11];

  xvalue= new vDbl(max(n,nm));
  yvalue= new vDbl(max(n,nm));
  ytransv=new vDbl(nm*11);

}


/* can be avoided for gcc */




void BDSExtract::spline_delete(vSpline *splineVec)
{
  //size_t i;
  //  for(i=0;i<splineVec->size();i++)
  //  if((*splineVec)[i])delete (*splineVec)[i];
  delete splineVec;
}


static struct
{
  float u[97],c,cd,cm;
  int i,j;
} rndm5_store;

void BDSExtract::rndmst5(int na1,int na2,int na3, int nb1)
{
  int i,j,nat;
  float s,t;
  rndm5_store.i=96;
  rndm5_store.j=32;
  for (i=0;i<97;i++)
    {
      s=0.0;
      t=0.5;
      for (j=0;j<24;j++)
	{
	  nat=(((na1*na2) % 179)*na3) % 179;
	  na1=na2;
	  na2=na3;
	  na3=nat;
	  nb1=(53*nb1+1) % 169;
	  if ((nb1*nat) % 64 >= 32)
	    {
	      s+=t;
	    }
	  t*=0.5;
	}
      rndm5_store.u[i]=s;
    }
  rndm5_store.c=    362436.0/16777216.0;
  rndm5_store.cd=  7654321.0/16777216.0;
  rndm5_store.cm= 16777213.0/16777216.0;
}

float BDSExtract::rndm5()
{
  float temp;
  
  temp=rndm5_store.u[rndm5_store.i]-rndm5_store.u[rndm5_store.j];
  if (temp<0.0){
    temp+=1.0;
  }
  rndm5_store.u[rndm5_store.i]=temp;
  if (--rndm5_store.i<0) rndm5_store.i=96;
  if (--rndm5_store.j<0) rndm5_store.j=96;
  rndm5_store.c-=rndm5_store.cd;
  if (rndm5_store.c<0.0){
    rndm5_store.c+=rndm5_store.cm;
  }
  temp-=rndm5_store.c;
  if (temp<0.0){
    return temp+1.0;
  }
  else{
    return temp;
  }
}

static struct{
  int iset;
  float v1,v2;
} gasdev_data;

float BDSExtract::gasdev()
{
  float r;
  if (gasdev_data.iset==0){
    for (;;){
      gasdev_data.v1=2.0*rndm5()-1.0;
      gasdev_data.v2=2.0*rndm5()-1.0;
      r=gasdev_data.v1*gasdev_data.v1+gasdev_data.v2*gasdev_data.v2;
      if ((r<=1.0) && (r!=0)){
	break;
      }
    }
    gasdev_data.iset=1;
    r=sqrt(-2.0*log((double)r)/r);
    gasdev_data.v1*=r;
    gasdev_data.v2*=r;
    return gasdev_data.v1;
  }
  else{
    gasdev_data.iset=0;
    return gasdev_data.v2;
  }
}

#undef RNDM_EPS

void BDSExtract::GenerateParticle(G4double& x_rndm, 
				  G4double& xp_rndm,
				  G4double& y_rndm,
				  G4double& yp_rndm,
				  G4double& z_pos,
				  G4double& e_rndm)
{

  int i,j,n,nb,np=0;
  int n_particles=1;
  int slices;
  double sigma_z, z_rndm;
  double z_cut=3.5,e_cut=3.5;
  int n_count;
  slices = itsBunch->GetNumSlices();
  
  nb = itsBunch->GetNumBunches();
  n = itsBunch->GetNumSlicesPerBunch();
  const int nm=itsBunch->GetNumMacroparticles();
  n_count=nb*n*nm;



  vPART *pVec=itsBunch->GetParticleVector();
  vRMAT *mSigma=itsBunch->GetSigmaVector();
  vRMAT *mSigmaXX=itsBunch->GetSigmaXXVector();
  vRMAT *mSigmaXY=itsBunch->GetSigmaXYVector();
  
  vZpos* zpos=itsBunch->GetZPos();
  
  for (i=0;i<n;i++) {
    (*xvalue)[i]=(*zpos)[i];
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSParticle* part=(*pVec)[i*nm+j];
      (*yvalue)[i]=part->energy;
    }
    (*s_e)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSParticle* part=(*pVec)[i*nm+j];
      (*yvalue)[i]=part->x;
    }
    (*s_x)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSParticle* part=(*pVec)[i*nm+j];
      (*yvalue)[i]=part->xp;
      G4cout<<" xp="<<part->xp<<G4endl;
    }
    (*s_xp)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSParticle* part=(*pVec)[i*nm+j];
      (*yvalue)[i]=part->y;
    }
    (*s_y)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSParticle* part=(*pVec)[i*nm+j];
      (*yvalue)[i]=part->yp;
    }
    (*s_yp)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSRMatrix* rmat=(*mSigma)[i*nm+j];
      (*yvalue)[i]=rmat->r11;
    }
    (*s_x_x)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSRMatrix* rmat=(*mSigmaXX)[i*nm+j];
      (*yvalue)[i]=rmat->r12;
    }
    (*s_x_xp)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSRMatrix* rmat=(*mSigmaXX)[i*nm+j];
      (*yvalue)[i]=rmat->r22;
    }
    (*s_xp_xp)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSRMatrix* rmat=(*mSigma)[i*nm+j];
      (*yvalue)[i]=rmat->r11;
    }
    (*s_y_y)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSRMatrix* rmat=(*mSigma)[i*nm+j];
      (*yvalue)[i]=rmat->r12;
    }
    (*s_y_yp)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (j=0;j<nm;j++) {
    for (i=0;i<n;i++) {
      BDSRMatrix* rmat=(*mSigma)[i*nm+j];
      (*yvalue)[i]=rmat->r22;
    }
    (*s_yp_yp)[j]->initialise(xvalue,0,yvalue,0);
  }
  for (i=0;i<nm;i++) {
    (*xvalue)[i]=2.0*e_cut*(i+0.5)/(double)nm-e_cut;
  }
  sigma_z=((*zpos)[1]-(*zpos)[0])*n/(2.0*z_cut);

  for (np=0;np<n_particles;np++){
    while (fabs(z_rndm=gasdev())>3.0) {}
    while (fabs(e_rndm=gasdev())>3.0) {}

    z_pos=sigma_z*z_rndm;

    for (j=0;j<nm;j++){
      (*ytransv)[j*11]=(*s_e)[j]->integrate(z_pos);
      (*ytransv)[j*11+1]=(*s_x)[j]->integrate(z_pos);
      (*ytransv)[j*11+2]=(*s_xp)[j]->integrate(z_pos);
      (*ytransv)[j*11+3]=(*s_y)[j]->integrate(z_pos);
      (*ytransv)[j*11+4]=(*s_yp)[j]->integrate(z_pos);
      (*ytransv)[j*11+5]=(*s_x_x)[j]->integrate(z_pos);
      (*ytransv)[j*11+6]=(*s_x_xp)[j]->integrate(z_pos);
      (*ytransv)[j*11+7]=(*s_xp_xp)[j]->integrate(z_pos);
      (*ytransv)[j*11+8]=(*s_y_y)[j]->integrate(z_pos);
      (*ytransv)[j*11+9]=(*s_y_yp)[j]->integrate(z_pos);
      (*ytransv)[j*11+10]=(*s_yp_yp)[j]->integrate(z_pos);   
    }
    s_transv->initialise(xvalue,0,ytransv,0);
    s_transv->integrate(e_rndm,yvalue);

    x_rndm=gasdev()*sqrt((*yvalue)[5]);

    G4cout<<" yvalue 1 ="<<(*yvalue)[1]<<G4endl;
    G4cout<<" yvalue 2 ="<<(*yvalue)[2]<<G4endl;
    G4cout<<" yvalue 3 ="<<(*yvalue)[3]<<G4endl;
    G4cout<<" yvalue 4 ="<<(*yvalue)[4]<<G4endl;
    G4cout<<" yvalue 5 ="<<(*yvalue)[5]<<G4endl;
    G4cout<<" yvalue 6 ="<<(*yvalue)[6]<<G4endl;
    G4cout<<" yvalue 7 ="<<(*yvalue)[7]<<G4endl;
    G4cout<<" yvalue 8 ="<<(*yvalue)[8]<<G4endl;
    G4cout<<" yvalue 9 ="<<(*yvalue)[9]<<G4endl;
    G4cout<<" yvalue 10 ="<<(*yvalue)[10]<<G4endl;

    // tmp 
    G4double tmpval=(*yvalue)[7]-(*yvalue)[6]*(*yvalue)[6]/(*yvalue)[5];
    G4cout<<" val="<<tmpval<<G4endl;
    if(tmpval>0)
      xp_rndm=gasdev()*sqrt((*yvalue)[7]-(*yvalue)[6]*(*yvalue)[6]/(*yvalue)[5])
	+x_rndm*(*yvalue)[6]/(*yvalue)[5];
    else
      xp_rndm=0.;
    //tmp comment out 
    //      xp_rndm=gasdev()*sqrt((*yvalue)[7]-(*yvalue)[6]*(*yvalue)[6]/(*yvalue)[5])
    //+x_rndm*(*yvalue)[6]/(*yvalue)[5];


    y_rndm=gasdev()*sqrt((*yvalue)[8]);
    yp_rndm=gasdev()*sqrt((*yvalue)[10]-(*yvalue)[9]*(*yvalue)[9]/(*yvalue)[8])
      +y_rndm*(*yvalue)[9]/(*yvalue)[8];


    x_rndm+=(*yvalue)[1];
    xp_rndm+=(*yvalue)[2];

    G4cout<<" xp_rndm="<<xp_rndm<<G4endl;
    y_rndm+=(*yvalue)[3];
    yp_rndm+=(*yvalue)[4];
    e_rndm=(*yvalue)[0];
  }

}


BDSExtract::~BDSExtract()
{


  if(s_e) delete s_e;
  if(s_x) delete s_x;
  if(s_xp) delete s_xp;
  if(s_y) delete s_y;
  if(s_yp) delete s_yp;
  if(s_x_x) delete s_x_x;
  if(s_x_xp) delete s_x_xp;
  if(s_xp_xp)  delete s_xp_xp;
  if(s_y_y) delete  s_y_y;
  if(s_y_yp) delete s_y_yp;
  if(s_yp_yp) delete s_yp_yp;

  if(s_transv)delete s_transv;

  //if(&xvalue)delete &xvalue;
  //if(&yvalue) delete &yvalue;
  //if(&ytransv) delete &ytransv;
}

