/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Last modified 24.7.2002
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

// BDSExtractBunch
// Bunch format interfacing to PLACET output file
// G.A.Blair (RHUL) 10.12.01
// adapted from code supplied by D.Schulte (CERN)

#include "BDSExtractBunch.hh"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <tcl.h>
#include <tk.h>


BDSExtractBunch::BDSExtractBunch(char* ExtractBunchInputFilename )
{
  //                  Number of bunches----| 
  read_beam_file(ExtractBunchInputFilename,0);
}


void 
BDSExtractBunch::bunch_make(int n_bunch,int n_slice,int n_macro,int n_field)
{
  bunches=n_bunch;
  slices_per_bunch=n_slice;
  macroparticles=n_macro;
  n_slice*=n_macro*n_bunch;

 
  slices=n_slice;
 
  //particle=(PARTICLE*)malloc(sizeof(PARTICLE)*n_slice);
  //sigma=(R_MATRIX*)malloc(sizeof(R_MATRIX)*n_slice);
  //sigma_xx=(R_MATRIX*)malloc(sizeof(R_MATRIX)*n_slice);
  //sigma_xy=(R_MATRIX*)malloc(sizeof(R_MATRIX)*n_slice);
  //z_position=(double*)malloc(sizeof(double)*n_slice);
  
  G4int i;
  partVec=new vPART(n_slice);
  for (i=0;i<n_slice;i++)
    (*partVec)[i]=new BDSParticle();
  //  (*particle)[i]=(PARTICLE*)malloc(sizeof(PARTICLE));

  sigmaVec=new vRMAT(n_slice);
  for (i=0;i<n_slice;i++)
    (*sigmaVec)[i]=new BDSRMatrix();
  //  (*sigma)[i]=(R_MATRIX*)malloc(sizeof(R_MATRIX));

  sigma_xxVec=new vRMAT(n_slice);
  for (i=0;i<n_slice;i++)
    (*sigma_xxVec)[i]=new BDSRMatrix();
  //  (*sigma_xx)[i]=(R_MATRIX*)malloc(sizeof(R_MATRIX));

  sigma_xyVec=new vRMAT(n_slice);
  for (i=0;i<n_slice;i++)
    (*sigma_xyVec)[i]=new BDSRMatrix();
  //  (*sigma_xy)[i]=(R_MATRIX*)malloc(sizeof(R_MATRIX));

  z_position=new vZpos(n_slice);

  
}

void BDSExtractBunch::read_beam_file(char *name,int ibunch0)
{
  FILE *file;
  char buffer[1000],*point;
  int nbunch,nslice,nmacro,ibunch,islice,imacro,k=0;
  //  BEAM *beam;

  file=fopen(name,"r");
  point=fgets(buffer,1000,file);
  nbunch=strtol(point,&point,10);
  nslice=strtol(point,&point,10);
  nmacro=strtol(point,&point,10);
  if (nmacro==0) {
    nmacro=1;
  }
  for (ibunch=0;ibunch<ibunch0;ibunch++){
    for (islice=0;islice<nslice;islice++){
      for (imacro=0;imacro<nmacro;imacro++){
	point=fgets(buffer,1000,file);
      }
    }
    point=fgets(buffer,1000,file);
  }

  G4cout<<"extractbunch: nslice="<<nslice<<" nmacro="<<nmacro<<G4endl;

  bunch_make(1,nslice,nmacro,0);

  
  for (islice=0;islice<nslice;islice++){
    for (imacro=0;imacro<nmacro;imacro++){
      point=fgets(buffer,1000,file);

      G4cout<<" point="<<point<<G4endl;

      (*z_position)[islice]=strtod(point,&point);

      G4cout<<" zpos="<<(*z_position)[islice]<<G4endl;

      BDSParticle* part=(*partVec)[k];
      BDSRMatrix *mSigma=(*sigmaVec)[k];
      BDSRMatrix *mSigmaXX=(*sigma_xxVec)[k];
      BDSRMatrix *mSigmaXY=(*sigma_xyVec)[k];

      part->wgt=strtod(point,&point);
      G4cout<<"wgt="<<part->wgt<<G4endl;

      part->energy=strtod(point,&point);
      G4cout<<"energy="<<part->energy<<G4endl;

      part->x=strtod(point,&point);
      G4cout<<"x="<<part->x<<G4endl;
      part->xp=strtod(point,&point);

      G4cout<<" BDSExtract xp="<< part->xp<<G4endl;

      part->y=strtod(point,&point);
      part->yp=strtod(point,&point);
      mSigmaXX->r11=strtod(point,&point);
      mSigmaXX->r12=strtod(point,&point);
      mSigmaXX->r22=strtod(point,&point);
      mSigmaXX->r21=mSigmaXX->r12;
      mSigma->r11=strtod(point,&point);
      mSigma->r12=strtod(point,&point);
      mSigma->r22=strtod(point,&point);
      mSigma->r21=mSigma->r12;
      mSigmaXY->r11=strtod(point,&point);
      mSigmaXY->r12=strtod(point,&point);
      mSigmaXY->r21=strtod(point,&point);
      mSigmaXY->r22=strtod(point,&point);

      
    //  (*particle)[k].wgt=strtod(point,&point);
    //  particle[k].energy=strtod(point,&point);
    //  particle[k].x=strtod(point,&point);
    //  particle[k].xp=strtod(point,&point);
    //  particle[k].y=strtod(point,&point);
    //  particle[k].yp=strtod(point,&point);
    //  sigma_xx[k].r11=strtod(point,&point);
    //  sigma_xx[k].r12=strtod(point,&point);
    //  sigma_xx[k].r22=strtod(point,&point);
     // sigma_xx[k].r21=sigma_xx[k].r12;
    //  sigma[k].r11=strtod(point,&point);
    //  sigma[k].r12=strtod(point,&point);
    //  sigma[k].r22=strtod(point,&point);
     // sigma[k].r21=sigma[k].r12;
    //  sigma_xy[k].r11=strtod(point,&point);
    //  sigma_xy[k].r12=strtod(point,&point);
    //  sigma_xy[k].r21=strtod(point,&point);
    //  sigma_xy[k].r22=strtod(point,&point);
      
      k++;
    }
  }
  
  fclose(file);

}


BDSExtractBunch::~BDSExtractBunch()
{
  delete  partVec;
  delete  sigmaVec;
  delete  sigma_xxVec;
  delete  sigma_xyVec;
  delete  z_position;
}

