/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/
// BDSExtract
// Generates individual particles from PLACET output file
// G.A.Blair (RHUL) 10.12.01
// adapted from code supplied by D.Schulte (CERN)

#include "BDSMspline.hh"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <tcl.h>
#include <tk.h>
#include <alloca.h>

BDSMspline::BDSMspline(G4int nIn,G4int nvalIn):n(nIn),nval(nvalIn)
{ 


  /*
  x= new G4double[n];
  y= new G4double[n*nval];
  y2=new G4double[n*nval];
  u= new G4double[n];
  */

  x= *(new vDbl(n));
  y= *(new vDbl(n*nval));
  y2=*(new vDbl(n*nval));
  u= *(new vDbl(n));



}


void BDSMspline::initialise(vDbl* xIn,G4int xscalIn, 
			    vDbl* yIn,G4int yscalIn)
{
  G4int i,j;
  G4double sig,p;

  xscal=xscalIn;
  yscal=yscalIn;

  for (j=0;j<nval;j++){
    y2[j]=0.0;
  }
  for (i=0;i<n;i++){
    switch (xscal){
    case 0:
      x[i]=(*xIn)[i];
      break;
    case 1:
      x[i]=log((*xIn)[i]);
      break;
    }
    for (j=0;j<nval;j++){
      switch (yscal){
      case 0:
	y[i*nval+j]=(*yIn)[i*nval+j];
	break;
      case 1:
	y[i*nval+j]=log((*yIn)[i*nval+j]);
	break;
      }
    }	    
  }
  for (j=0;j<nval;j++){
    u[0]=0.0;
    for (i=1;i<n-1;i++){
      sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
      p=1.0/(sig*y2[(i-1)*nval+j]+2.0);
      y2[i*nval+j]=(sig-1.0)*p;
      u[i]=(6.0*((y[(i+1)*nval+j]-y[i*nval+j])/(x[i+1]-x[i])
		 -(y[i*nval+j]-y[(i-1)*nval+j])/(x[i]-x[i-1]))
	    /(x[i+1]-x[i-1])-sig*u[i-1])*p;
    }
    y2[(n-1)*nval+j]=0.0;
    for (i=n-2;i>=0;i--){
      y2[i*nval+j]=y2[i*nval+j]*y2[(i+1)*nval+j]+u[i];
    }
  }
}



void BDSMspline::integrate(G4double xIn,vDbl* yOut)
{
  int kmin,kmax,kpoint,j,nval;
  double a,b,w,tmp;
  
  kmin=0;
  kmax=n-1;
  switch (xscal){
  case 0:	
    break;
  case 1:
    xIn=log(xIn);
    break;
  }
  if (xIn>x[kmax]){
    if (yscal)
      for (j=0;j<nval;j++) (*yOut)[j]=exp(y[kmax*nval+j]);
    else
      for (j=0;j<nval;j++) (*yOut)[j]=y[kmax*nval+j];
    return;
  }
  if (xIn<x[0]){
    if (yscal)
      for (j=0;j<nval;j++) (*yOut)[j]=exp(y[j]);
    else
      for (j=0;j<nval;j++) (*yOut)[j]=y[j];
    return;
    for (j=0;j<nval;j++) (*yOut)[j]=0.0;
    return;
  }
  while (kmax-kmin>1){
    kpoint=(kmax+kmin)/2;
    if (x[kpoint]>xIn){
      kmax=kpoint;
    }
    else{
      kmin=kpoint;
    }
  }
  w=x[kmax]-x[kmin];
  a=(x[kmax]-xIn)/w;
  b=(xIn-x[kmin])/w;
  for (j=0;j<nval;j++){
    tmp=a*y[kmin*nval+j]+b*y[kmax*nval+j]+
      (a*(a*a-1.0)*y2[kmin*nval+j]
       +b*(b*b-1.0)*y2[kmax*nval+j])*w*w/6.0;
    switch(yscal){
    case 0:
      (*yOut)[j]=tmp;
      break;
    case 1:
      (*yOut)[j]=exp(tmp);
      break;
    }
  }
}



BDSMspline::~BDSMspline()
{ 
  //  if(&x)delete &x;
  //  if(&y)delete &y;
  //  if(&y2)delete &y2;

  //if(&u)delete &u;
}



