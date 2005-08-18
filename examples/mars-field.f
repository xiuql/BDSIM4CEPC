      SUBROUTINE FIELD(N,X,Y,Z,BX,BY,BZ,BBB)
C....................................................
C   FINDS COMPONENTS OF THE MAGNETIC FIELD FOR A GIVEN POINT
C   DEFINED BY A REGION NUMBER "N" OR BY ITS COORDINATES "X,Y,Z"
C
C   "N" and "X,Y,Z" CAN BE USED ALTERNATIVELY:
C   Use "N" if there is no field variation in that region !
C   Use "X,Y,Z" if there is a field variation in that region !
C
C   INPUT:  N - REGION NUMBER (> 0 !!!)
C               OR
C           X,Y,Z - COORDINATES
C
C           FIELD MAPS
C           QUADS GRADIENTS IN T/CM
C           G>0 FOR FOC QUADS, G<0 FOR DEFOC QUADS
C
C   OUTPUT: BX,BY,BZ,BBB IN TESLA
C
C   DON'T FORGET TO CALCULATE  BBB=SQRT(BX*BX+BY*BY+BZ*BZ) AFTERALL !!!
C
C     REVISION: 16-DEC-1999 BY NVM
C     REVISION: 04-DEC-2003 BY NVM
C
C     PP-HORIZONTAL CROSSING and 4 T (BEG1, FIELD)
C   SUFI (OPEN & CLOSE):
C
C   LBQ-KEK.MAP  (UNIT=21)   IS FOR G=-224 T/M
C   LBQ-FNAL.MAP (UNIT=22)   IS FOR G=+205 T/M
C
C     REVISION: 25-APR-2005
C....................................................
      IMPLICIT DOUBLE PRECISION (A-H,O-Z), INTEGER (I-N)

      LOGICAL IND(20)
      COMMON/LOGIND/IND

C- - - - - - - - - - - - - - - - - - - -
      BX=0.D0
      BY=0.D0
      BZ=0.D0
      BBB=0.D0

      R2=X*X+Y*Y
      R=SQRT(R2)
      IF(Z.LT.650.D0) THEN
         IF(R.LT.300.D0) THEN

            BZ=4.D0        ! 4 T CMS

            BBB=BZ
         END IF
         RETURN
      END IF

      IF(R.LE.25.D0) THEN
         IF(Z.GE.2300.D0) THEN
            CALL MAGFLD(X,Y,Z,BTX,BTY,BTZ,B)
            BBB=B
            BX=BTX*BBB
            BY=BTY*BBB
            BZ=BTZ*BBB
         END IF
      END IF

C=== MAD-MARS BEAMLINE BUILDER MMBLB ===
C=== EXAMPLE OF REAL WORK (uncomment and modify * whereever needed) ===

*      IF (IND(13)) THEN
*         CALL SET_CURRENT_BEAMLINE(1)
*         CALL BLFIELD( X, Y, Z, BX, BY, BZ, BBB )

*         CALL SET_CURRENT_BEAMLINE(2)
*         CALL BLFIELD( X, Y, Z, BX, BY, BZ, BBB )
*      END IF
C=====================================================

      RETURN
      END    
C----------------------------------------------------
      SUBROUTINE MAGFLD ( XX, YY, ZZ, BTX, BTY, BTZ, B)
************************************************************************
C-----
C     CREATED:     1992        BY NVM BASED ON G. STEVENSON'S
C     MODIFIED:    1994-2000   BY NVM   
C     LAST CHANGE: 13-SEP-2001 BY NVM
C     ...          08-Mar-2001 by IR 
C     REVISION     04-DEC-2001 by NVM
C     REVISION     25-APR-2005 by NVM
C
C-----
C     LHC2000: IP5(R) and IP1(R)
*      DATA XSING/'ODD'/
*      DATA ICLOCK/1/  ! IP5->IP6, from IP to LBQ
*      ANGLE>0
C
************************************************************************
*  In FLUKA/MARS geometry x-vertical up, y-horizontal right and
*  z in the beam direction away from the observer the field map
*  is for a horizontally focussing, F, quadrupole
*
*  The Low-Beta structure differs in sign in an odd or even crossing.
*  The x-ing ANGLE must also have the correct sign.
*
*  CLOCKWISE BEAM (IP5->IP6), ICLOCK=1
*  Odd:  DFFD-IP-FDDF, ANGLE>0
*  Even: FDDF-IP-DFFD, ANGLE<0
*
*  COUNTERCLOCKWISE BEAM (IP5->IP4), ICLOCK=-1
*  Odd:  DFFD-IP-FDDF, ANGLE<0
*  Even: FDDF-IP-DFFD, ANGLE>0
*
*  The direction of the field in D1 must be correctly chosen to deflect
*  in the same direction as THETA, while D2 has a field of the opposite
*  sign.
*  Set XSING='ODD ' for an odd-numbered intersection,
*  Set XSING='EVEN' for an even-numbered intersection,
*
*    For an EVEN crossing,   FOCUS=1  and BTX in D1 is -1, in D2 is +1
*    For an ODD  crossing,   FOCUS=-1 and BTX in D1 is +1, in D2 is -1
*
C   SUFI (OPEN & CLOSE):
C
C   LBQ-KEK.MAP  (UNIT=21)   IS FOR G=-224 T/M
C   LBQ-FNAL.MAP (UNIT=22)   IS FOR G=+205 T/M
C
C   ODD CROSSING:
C   (FOCUS=-1 and BTX in D1 is +1, in D2 is -1, in MB is +1)
C
C   IP5:
C   Q1    G=-205 T/M   -->  -199.4591 T/m                         Corr 8, Mar 5/2001
C   Q2A   G= 205 T/M   -->   199.4591 ..                          ..
C   Q2B   G= 205 T/M   -->   199.4591 ..                          ..
C   Q3    G=-205 T/M   -->  -199.4591 ..                          ..
C
      IMPLICIT DOUBLE PRECISION (A-H,O-Z), INTEGER (I-N)

      CHARACTER*4 EVEN,ODD,XSING
      COMMON
     & /FMAP/BX(106,106,2),BY(106,106,2),XBM(106,2),YBM(106,2),DLXM(2),
     &  DLYM(2)
     & /FMPSIZ/NXYSIZ(2)
      DATA ODD/'ODD '/,EVEN/'EVEN'/

C!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      DATA XSING/'ODD'/
      DATA ICLOCK/1/  ! IP5->IP6, from IP to LBQ
C!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      DATA RQ/3.5D0/
      
C  IP5(R) NOMINAL FIELDS:
      PARAMETER (GLB5 =1.994591D0)              ! ..

C  MAP NOMINAL FIELDS:
      PARAMETER (GLBFNAL =2.05D0)
      PARAMETER (GLBKEK  =2.24D0)

C  RENORMALIZATION:
      PARAMETER (SCF11= GLB5/GLBKEK)
      PARAMETER (SCF12= GLB5/GLBFNAL)           ! ..

      !INCLUDE 'tally1.inc'
       CALL SUFI
C- - - - - - - - - - - - - - - - - - - - - - - - -      

      FOCUS=1.0D0
      IF(XSING.EQ.ODD) FOCUS=-1.0D0
      IF(ICLOCK.EQ.-1) FOCUS=-FOCUS

      R   =SQRT(XX**2+YY**2)
      XMAP=ABS(XX)
      YMAP=ABS(YY)
      ZMAP=ABS(ZZ)
      YS  =YY

      BXX=0.D0
      BYY=0.D0
      BZZ=0.D0

C=== LBQ-new: 25-Apr-2005 ===      

      if(zmap.gt.2300.d0.and.zmap.lt.2930.d0) then
         SCF=SCF11              ! Q1
         RAP=0.1D0
         FOCUS=-FOCUS
         LL=1

      else if(zmap.gt.3205.d0.and.zmap.lt.3755.d0) then

         SCF=SCF12              ! Q2A
         RAP=0.1D0
         LL=2

      else if(zmap.gt.3855.d0.and.zmap.lt.4405.d0) then

         SCF=SCF12              ! Q2B
         RAP=0.1D0
         LL=2

      else if(zmap.gt.4730.d0.and.zmap.lt.5360.d0) then

         SCF=SCF11              ! Q3
         RAP=0.1D0
         FOCUS=-FOCUS
         LL=1

      else

         GO TO 1
      end if

      IF(R.GT.25.D0) GO TO 1
      IF(R.LT.RAP) THEN
        BXX=-GLB5*YMAP
        BYY=-GLB5*XMAP
        GO TO 1777
      END IF

C=== ALL MAPS CALCULATED FOR NEGATIVE FIELDS, BUT LBQ-FNAL FOR POSITIVE
C=== SO, CONVERT IT TO NEGATIVE
      IF(LL.EQ.2) FOCUS=-FOCUS

C=== DEALING WITH MAPS ===

 776  NX=NXYSIZ(LL)
      IX=INT(XMAP/DLXM(LL))+1
      IY=INT(YMAP/DLYM(LL))+1

      IF((IX.LE.NX).AND.(IY.LE.NX)) THEN
        CALL LITWOD(XMAP,YMAP,LL,1,FOUT)
        BXX=FOUT
        CALL LITWOD(XMAP,YMAP,LL,2,FOUT)
        BYY=FOUT
      ELSE
        GO TO 1
      ENDIF

 777  BXX=BXX*SCF
      BYY=BYY*SCF
 1777 B=SQRT(BXX**2+BYY**2+BZZ**2)
      IF(B.LT.1.0D-06) GO TO 1
      BTZ=0.0D0

      IF(XX.LT.0.0D0) BYY=-BYY
      IF(YY.LT.0.0D0) BXX=-BXX
      
      BTX=FOCUS*BXX/B
      BTY=FOCUS*BYY/B

      RETURN

 1    BTX=0.0D0
      BTY=0.0D0
      BTZ=0.0D0
      B=0.0D0
      RETURN
      END
C---------------------------------------------------------------------------
      SUBROUTINE LITWOD(XX,YY,LL,IXY,FOUT)
C     NVM: ADJUSTMENTS AND MAPS FOR
C          LL=1: LBQKEK  (Q1,Q3)
C          LL=2: LBQFNAL (Q2A,Q2B)
C          IXY=1 -> BX
C          IXY=2 -> BY
*  Linearly interpolates a value from a two-dimensional mesh
C-----
C     CREATED:     1992        BY G. STEVENSON
C     MODIFIED:    1994-2000   BY NVM   
C     LAST CHANGE: 22-FEB-2000 BY NVM
C     LAST CHANGE: 25-APR-2005 BY NVM
C-----
      IMPLICIT DOUBLE PRECISION (A-H,O-Z), INTEGER (I-N)

      COMMON
     & /FMAP/BX(106,106,2),BY(106,106,2),XBM(106,2),YBM(106,2),DLXM(2),
     &  DLYM(2)
     & /FMPSIZ/NXYSIZ(2)
C- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      FOUT=0.0D0
      IF(XX.LT.XBM(1,LL)) RETURN
      IF(YY.LT.YBM(1,LL)) RETURN
      
      M=LL
      J1=NXYSIZ(M)-1
      DO IX=1,J1
        IF(XX.LE.XBM(IX+1,M)) GO TO 15
      END DO
      RETURN
 15   J2=NXYSIZ(M)-1
      DO IY=1,J2
        IF(YY.LE.YBM(IY+1,M)) GO TO 25
      END DO
      RETURN
      
 25   CONTINUE
      X1=XBM(IX,M)
      X2=XBM(IX+1,M)
      Y1=YBM(IY,M)
      Y2=YBM(IY+1,M)

      IF(IXY.EQ.1) THEN
        F1=BX(IX,IY,M)  +(XX-X1)*(BX(IX+1,IY,M)  -BX(IX,IY,M))/(X2-X1)
        F2=BX(IX,IY+1,M)+(XX-X1)*(BX(IX+1,IY+1,M)-BX(IX,IY+1,M))/(X2-X1)
      ELSE
        F1=BY(IX,IY,M)  +(XX-X1)*(BY(IX+1,IY,M)  -BY(IX,IY,M))/(X2-X1)
        F2=BY(IX,IY+1,M)+(XX-X1)*(BY(IX+1,IY+1,M)-BY(IX,IY+1,M))/(X2-X1)
      END IF

      FOUT=F1+(YY-Y1)*(F2-F1)/(Y2-Y1)
      RETURN
      END    
C----------------------------------------------------
      SUBROUTINE SUFI
C................................................................
C     READS MAGNETIC FIELD MAP
C
C   SUFI (OPEN & CLOSE):
C
C   LBQ-KEK.MAP  (UNIT=21)   IS FOR G=-224 T/M
C   LBQ-FNAL.MAP (UNIT=22)   IS FOR G=+205 T/M
C
C   EVEN CROSSING:
C   (FOCUS=-1 and BTX in D1 is +1, in D2 is -1, in MB is +1)
C
C   Q1    G=-205 T/M   SCF11= 0.915179
C   Q2A   G= 205 T/M   SCF12= 1.
C   Q2B   G= 205 T/M   SCF12= 1.
C   Q3    G=-205 T/M   SCF13= 0.915179
C
C   MAP : Y - UP, X - RIGHT
C   MARS: X - UP, Y - RIGHT
C
C     REVISION: 22-FEB-2000
c     ...       15-Oct-2000
C     REVISION: 22-MAR-2001
C     REVISION: 25-APR-2005
C................................................................
      IMPLICIT DOUBLE PRECISION (A-H,O-Z), INTEGER (I-N)

      COMMON
     & /FMAP/BX(106,106,2),BY(106,106,2),XBM(106,2),YBM(106,2),DLXM(2),
     &  DLYM(2)
     & /FMPSIZ/NXYSIZ(2)
      DIMENSION LUN(2)

      DATA DL11,DL12,DL2/0.25D0,0.20D0,1.D0/
      DATA LUN/21,22/

      DATA LUNMA/2/
      DATA ITEST/1/
c- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

      OPEN (UNIT=LUN(1),  FILE='LBQ-KEK.MAP', STATUS='OLD')
      OPEN (UNIT=LUN(2),  FILE='LBQ-FNAL.MAP', STATUS='OLD')
      
      NXYSIZ(1)=97
      NXYSIZ(2)=106
      
      DLXM(1)=DL11
      DLYM(1)=DL11
      DLXM(2)=DL12
      DLYM(2)=DL12
      
      DO LL=1,LUNMA
         DO I=0,105
            XBM(I+1,LL)=DBLE(I)*DLXM(LL)
            YBM(I+1,LL)=DBLE(I)*DLYM(LL)
            DO I1=0,105
               BX(I1+1,I+1,LL)=0.D0
               BY(I1+1,I+1,LL)=0.D0
            END DO
         END DO
      END DO
      
      DO LL=1,LUNMA
         IF(LL.EQ.1) THEN
            DL=DL11       ! cm, KEK
         ELSE IF(LL.EQ.2) THEN
            DL=DL12*10.D0 ! mm, FNAL
         END IF

 100     continue
         read(LUN(LL),*,end=200) xx,yy,bxx,byy
        
C=== MAP-TO-MARS REVERSE ===
         IX=INT(YY/DL+.00005D0)+1
         IY=INT(XX/DL+.00005D0)+1

         BXXX= BXX
         BYYY= BYY
            
         BX(IX,IY,LL)=BYYY
         BY(IX,IY,LL)=BXXX

         IF(LL.EQ.2.AND.IX.NE.IY) THEN
            BX(IY,IX,LL)=BXXX
            BY(IY,IX,LL)=BYYY
         END IF
        go to 100
 200    continue
      END DO

      DO L=1,2
        CLOSE(UNIT=LUN(L))
      END DO
      
      RETURN
      END
