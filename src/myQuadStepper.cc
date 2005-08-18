/* BDSIM code.    Version 1.0
   Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 
*/

#include "BDSGlobalConstants.hh" 
#include "myQuadStepper.hh"
#include "G4ThreeVector.hh"
#include "G4LineSection.hh"
#include "G4TransportationManager.hh"

using std::max;
extern G4double BDSLocalRadiusOfCurvature;
extern G4int event_number;

myQuadStepper::myQuadStepper(G4Mag_EqRhs *EqRhs)
  : G4MagIntegratorStepper(EqRhs,6)  // integrate over 6 variables only !!
                                       // position & velocity
{
  fPtrMagEqOfMot = EqRhs;
}


void myQuadStepper::AdvanceHelix( const G4double  yIn[],
				  G4ThreeVector Bfld,
				  G4double  h,
				  G4double  yOut[])
{

  //G4cout<<"myQuadStepper: advancing through "<<h/m<<"  m "<<
  //"x="<<yIn[0] /m<<" y="<<yIn[1]/m<<" z="<<yIn[2]/m<<G4endl; 

  G4ThreeVector positionMove, endTangent;

  const G4double *pIn = yIn+3;
  G4ThreeVector v0= G4ThreeVector( pIn[0], pIn[1], pIn[2]);  

  G4ThreeVector GlobalPosition= G4ThreeVector( yIn[0], yIn[1], yIn[2]);  
  G4double InitMag=v0.mag();
  G4ThreeVector InitMomDir=v0.unit();

  G4double h2=h*h;


  G4Navigator* HelixNavigator=
    G4TransportationManager::GetTransportationManager()->
    GetNavigatorForTracking();
  
  G4AffineTransform LocalAffine=HelixNavigator-> 
    GetLocalToGlobalTransform();
  
  G4AffineTransform GlobalAffine=HelixNavigator->
    GetGlobalToLocalTransform();

  G4ThreeVector LocalR=GlobalAffine.TransformPoint(GlobalPosition); 
  G4ThreeVector LocalRp=GlobalAffine.TransformAxis(InitMomDir);
  
  
  // advance the orbit
 

  LocalR=GlobalPosition;
  LocalRp=v0.unit();

  G4ThreeVector itsFinalPoint,itsFinalDir;
  
  G4ThreeVector yhat(0.,1.,0.);

  G4ThreeVector vhat=LocalRp;
  
  G4ThreeVector vnorm=vhat.cross(yhat);
   
  G4double R;

   if(BDSGlobals->GetSynchRescale())
    {
      G4double B[3];
      fPtrMagEqOfMot->GetFieldValue(yIn, B);
      R=-(InitMag/GeV)/(0.299792458 * B[1]/tesla) *m;
    }
  else
    {
      R=-(InitMag/GeV)/(0.299792458 * itsBField/tesla) * m;
    }

 // include the sign of the charge of the particles

  if(  fPtrMagEqOfMot->FCof()<0) R*=-1.;
  else if ( fPtrMagEqOfMot->FCof()==0) R=DBL_MAX;


  // check that the approximations are valid, else do a linear step:
  if(abs(R)<DBL_MAX) 
    { 
  
      G4double Theta   = h/R;

      G4double CosT_ov_2, SinT_ov_2, CosT, SinT;
      CosT_ov_2=cos(Theta/2);
      SinT_ov_2=sin(Theta/2);

      CosT=(CosT_ov_2*CosT_ov_2)- (SinT_ov_2*SinT_ov_2);
      SinT=2*CosT_ov_2*SinT_ov_2;

      BDSLocalRadiusOfCurvature=R;

      itsDist=abs(R)*(1.-CosT_ov_2);

      G4ThreeVector dPos=R*(SinT*vhat + (1-CosT)*vnorm);
 	
      itsFinalPoint=LocalR+dPos;
      itsFinalDir=CosT*vhat +SinT*vnorm;


    }
  else
    {
      itsFinalPoint=LocalR + h * LocalRp;
      itsFinalDir=LocalRp;
      itsDist=0.;
    }


  G4ThreeVector GlobalTangent;

  GlobalPosition=itsFinalPoint;
  GlobalTangent=itsFinalDir;


  GlobalTangent*=InitMag;


  yOut[0]   = GlobalPosition.x(); 
  yOut[1]   = GlobalPosition.y(); 
  yOut[2]   = GlobalPosition.z(); 
  
  yOut[3] = GlobalTangent.x();
  yOut[4] = GlobalTangent.y();
  yOut[5] = GlobalTangent.z();

 
  G4double kappa= - fPtrMagEqOfMot->FCof()* ( itsBGrad) /InitMag; // was ist das? 

  if(fabs(kappa)<1.e-12) return; // no gradient

  kappa= - fPtrMagEqOfMot->FCof()* ( 1/R + itsBGrad) /InitMag; // was ist das?
  

  // add up the betetron oscillations



  G4double x1,x1p,y1,y1p,z1,z1p;
 
  G4double x0=LocalR.x();
  G4double y0=LocalR.y();
  G4double z0=LocalR.z();
  G4double xp=LocalRp.x();
  G4double yp=LocalRp.y();
  G4double zp=LocalRp.z();
  
  // local r'' (for curvature)
  G4ThreeVector LocalRpp;
  LocalRpp.setX(-zp*x0);
  LocalRpp.setY( zp*y0);
  LocalRpp.setZ( x0*xp - y0*yp);
  
  LocalRpp*=kappa;

  
  // determine effective curvature
  G4double R_1 = LocalRpp.mag();
  if(R_1>0.)
    {
      R=1./R_1;
      
      // Save for Synchrotron Radiation calculations:
      BDSLocalRadiusOfCurvature=R;
      
      // chord distance (simple quadratic approx)
      itsDist= h2/(8*R);
      
      // check for paraxial approximation:
      if((abs(zp)>0.99)&&(abs(kappa)<1.e-6))
	{
	  G4double rootK=sqrt(abs(kappa*zp));
	  G4double rootKh=rootK*h*zp;
	  G4double X11,X12,X21,X22;
	  G4double Y11,Y12,Y21,Y22;
	  
	  if (kappa>0)
	    {
	      X11= cos(rootKh);
	      X12= sin(rootKh)/rootK;
	      X21=-abs(kappa)*X12;
	      X22= X11;
	      
	      Y11= cosh(rootKh);
	      Y12= sinh(rootKh)/rootK;
	      Y21= abs(kappa)*Y12;
	      Y22= Y11;
	    }
	  else if (kappa<0)
	    {
	      X11= cosh(rootKh);
	      X12= sinh(rootKh)/rootK;
	      X21= abs(kappa)*X12;
	      X22= X11;
	      
	      Y11= cos(rootKh);
	      Y12= sin(rootKh)/rootK;
	      Y21= -abs(kappa)*Y12;
	      Y22= Y11;
	    }
	  
	  x1      = X11*x0 + X12*xp;    
	  x1p     = X21*x0 + X22*xp;
	  
	  y1      = Y11*y0 + Y12*yp;    
	  y1p= Y21*y0 + Y22*yp;
	  
	  z1p=sqrt(1 - x1p*x1p -y1p*y1p);
	  
	  G4double dx=x1-x0;
	  G4double dy=y1-y0;
	  // Linear chord length
	  G4double dR2=dx*dx+dy*dy;
	  G4double dz=sqrt(h2*(1.-h2/(12*R*R))-dR2);
	  
	  // check for precision problems
	  G4double ScaleFac=(dx*dx+dy*dy+dz*dz)/h2;
	  if(ScaleFac>1.0000001)
	    {
	      ScaleFac=sqrt(ScaleFac);
	      dx/=ScaleFac;
	      dy/=ScaleFac;
	      dz/=ScaleFac;
	      x1=x0+dx;
	      y1=y0+dy;
	    }
	  z1=z0+dz;
	}
      else
	// perform local helical steps (paraxial approx not safe)
	{
	  // simple quadratic approx:	      
	  G4double quadX= - kappa*x0*zp;
	  G4double quadY=   kappa*y0*zp;
	  G4double quadZ=   kappa*(x0*xp - y0*yp);
	  
	  // determine maximum curvature:
	  G4double maxCurv=max(abs(quadX),abs(quadY));
	  maxCurv=max(maxCurv,abs(quadZ));
	  
	  x1=x0 + h*xp + quadX*h2/2;
	  y1=y0 + h*yp + quadY*h2/2; 
	  z1=z0 + h*zp   + quadZ*h2/2;
	  
	  x1p=xp + quadX*h;
	  y1p=yp + quadY*h;
	  z1p=zp + quadZ*h;
	  
	  // estimate parameters at end of step:
	  G4double quadX_end= - kappa*x1*z1p;
	  G4double quadY_end=   kappa*y1*z1p;
	  G4double quadZ_end=   kappa*(x1*x1p - y1*y1p);
	  
	  // determine maximum curvature:
	  maxCurv=max(maxCurv,abs(quadX_end));
	  maxCurv=max(maxCurv,abs(quadY_end));
	  maxCurv=max(maxCurv,abs(quadZ_end));
	  
	  itsDist=maxCurv*h2/4;
	  
	  
	  // use the average:
	  G4double quadX_av=(quadX+quadX_end)/2;
	  G4double quadY_av=(quadY+quadY_end)/2;
	  G4double quadZ_av=(quadZ+quadZ_end)/2;
	  
	  G4double x_prime_av=(xp + x1p)/2;
	  G4double y_prime_av=(yp + y1p)/2;
	  G4double z_prime_av=(zp + z1p)/2;
	  
	  x1=x0 + h*x_prime_av + quadX_av * h2/2;
	  y1=y0 + h*y_prime_av + quadY_av * h2/2; 
	  z1=z0 + h*z_prime_av + quadZ_av * h2/2;
	  
	  x1p=xp + quadX_av*h;
	  y1p=yp + quadY_av*h;
	  z1p=zp + quadZ_av*h;
	  
	  G4double dx=(x1-x0);
	  G4double dy=(y1-y0);
	  G4double dz=(z1-z0);
	  G4double chord2=dx*dx + dy*dy + dz*dz;
	  if(chord2>h2)
	    {
	      G4double hnew=h*sqrt(h2/chord2);
	      x1=x0 + hnew*x_prime_av + quadX_av * hnew*hnew/2;
	      y1=y0 + hnew*y_prime_av + quadY_av * hnew*hnew/2; 
	      z1=z0 + hnew*z_prime_av + quadZ_av * hnew*hnew/2;
	      
	      x1p=xp + quadX_av*hnew;
	      y1p=yp + quadY_av*hnew;
	      z1p=zp + quadZ_av*hnew;
	    }
	}
      
      LocalR.setX(x1);
      LocalR.setY(y1);
      LocalR.setZ(z1);
      
      LocalRp.setX(x1p);
      LocalRp.setY(y1p);
      LocalRp.setZ(z1p);
      
    }
  else
    {
      LocalR += h*LocalRp;
      itsDist=0.;
    }
  

  GlobalPosition=LocalAffine.TransformPoint(LocalR); 

  GlobalTangent=LocalAffine.TransformAxis(LocalRp);
  
  GlobalTangent*=InitMag;
  
  yOut[0] += GlobalPosition.x(); 
  yOut[1] += GlobalPosition.y(); 
  yOut[2] += GlobalPosition.z(); 
  
  
  yOut[3] += GlobalTangent.x();
  yOut[4] += GlobalTangent.y();
  yOut[5] += GlobalTangent.z();
  
  //G4cout<<"done"<<G4endl;


}    


void myQuadStepper::Stepper( const G4double yInput[],
			     const G4double dydx[],
			     const G4double hstep,
			     G4double yOut[],
			     G4double yErr[]      )
{  
  const G4int nvar = 6 ;

  for(G4int i=0;i<nvar;i++) yErr[i]=0;

  AdvanceHelix(yInput,0,hstep,yOut);

  return ;
}

G4double myQuadStepper::DistChord()   const 
{

return itsDist;
  // This is a class method that gives distance of Mid 
  //  from the Chord between the Initial and Final points.
}

myQuadStepper::~myQuadStepper()
{}
