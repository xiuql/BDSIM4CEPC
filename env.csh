# bds startup for csh
# legacy
######################################
#
# g4system.U
#
#+
setenv G4SYSTEM "Linux-g++"
echo "On this machine the G4SYSTEM=$G4SYSTEM"

#
# g4dirs.U
#
#+
setenv G4INSTALL "/home/carter/Geant4/geant4.6.0"
echo "On this machine the G4INSTALL=$G4INSTALL"

#+
if ( X != X ) then
setenv G4INCLUDE ""
echo "On this machine the G4INCLUDE=$G4INCLUDE"
endif

#+
if ( X/home/carter/Geant4/geant4.6.0/lib != X ) then
setenv G4LIB "/home/carter/Geant4/geant4.6.0/lib"
echo "On this machine the G4LIB=$G4LIB"
endif

#+
if ( X/home/carter/Geant4/geant4.6.0/data/PhotonEvaporation != X ) then
setenv G4LEVELGAMMADATA "/home/carter/Geant4/geant4.6.0/data/PhotonEvaporation"
echo "On this machine the G4LEVELGAMMADATA=$G4LEVELGAMMADATA"
endif

#+
if ( X/home/carter/Geant4/geant4.6.0/data/RadiativeDecay != X ) then
setenv G4RADIOACTIVEDATA "/home/carter/Geant4/geant4.6.0/data/RadiativeDecay"
echo "On this machine the G4RADIOACTIVEDATA=$G4RADIOACTIVEDATA"
endif

#+
if ( X/home/carter/Geant4/geant4.6.0/data/G4EMLOW2.3 != X ) then
setenv G4LEDATA "/home/carter/Geant4/geant4.6.0/data/G4EMLOW2.3"
echo "On this machine the G4LEDATA=$G4LEDATA"
endif

#+
if ( X/home/carter/Geant4/geant4.6.0/data/G4NDL3.7 != X ) then
setenv NeutronHPCrossSections "/home/carter/Geant4/geant4.6.0/data/G4NDL3.7"
echo "On this machine the NeutronHPCrossSections=$NeutronHPCrossSections"
endif

#
# g4clhep.U
#
if ( X/home/carter/lib/CLHEP/1.8.1.0 != X ) then
setenv CLHEP_BASE_DIR "/home/carter/lib/CLHEP/1.8.1.0"
echo "On this machine the CLHEP_BASE_DIR=$CLHEP_BASE_DIR"
endif

#+
if ( X/home/carter/lib/CLHEP/1.8.1.0/include != X ) then
setenv CLHEP_INCLUDE_DIR "/home/carter/lib/CLHEP/1.8.1.0/include"
echo "On this machine the CLHEP_INCLUDE_DIR=$CLHEP_INCLUDE_DIR"
endif

#+
if ( X/home/carter/lib/CLHEP/1.8.1.0/lib != X ) then
setenv CLHEP_LIB_DIR "/home/carter/lib/CLHEP/1.8.1.0/lib"
echo "On this machine the CLHEP_LIB_DIR=$CLHEP_LIB_DIR"
endif

#+
if ( XCLHEP != X ) then
setenv CLHEP_LIB "CLHEP"
echo "On this machine the CLHEP_LIB=$CLHEP_LIB"
endif

#+
#
# g4debug
#
if ( X1 != X ) then
setenv G4DEBUG "1"
echo "On this machine the G4DEBUG=$G4DEBUG"
endif

#
# g4analysis
#
#+
if ( Xn == Xy ) then
setenv G4ANALYSIS_USE 1
echo "On this machine the G4ANALYSIS_USE=$G4ANALYSIS_USE"
endif

#
# g4ui
#
#+
if ( Xy == Xy ) then
setenv G4UI_BUILD_XAW_SESSION 1
echo "On this machine the G4UI_BUILD_XAW_SESSION=$G4UI_BUILD_XAW_SESSION"
endif

#+
if ( Xy == Xy ) then
setenv G4UI_USE_XAW 1
echo "On this machine the G4UI_USE_XAW=$G4UI_USE_XAW"
endif

#+
if ( Xy == Xy ) then
setenv G4UI_BUILD_XM_SESSION 1
echo "On this machine the G4UI_BUILD_XM_SESSION=$G4UI_BUILD_XM_SESSION"
endif

#+
if ( Xy == Xy ) then
setenv G4UI_USE_XM 1
echo "On this machine the G4UI_USE_XM=$G4UI_USE_XM"
endif

#+
if ( Xn == Xy ) then
setenv G4UI_BUILD_WIN32_SESSION 1
echo "On this machine the G4UI_BUILD_WIN32_SESSION=$G4UI_BUILD_WIN32_SESSION"
endif

#+
if ( Xn == Xy ) then
setenv G4UI_USE_WIN32 1
echo "On this machine the G4UI_USE_WIN32=$G4UI_USE_WIN32"
endif

#
# g4vis
#
#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_DAWN_DRIVER 1
echo "On this machine the G4VIS_BUILD_DAWN_DRIVER=$G4VIS_BUILD_DAWN_DRIVER"
endif

#+
if ( Xy == Xy ) then
setenv G4VIS_BUILD_OPENGLX_DRIVER 1
echo "On this machine the G4VIS_BUILD_OPENGLX_DRIVER=$G4VIS_BUILD_OPENGLX_DRIVER"
endif

#+
if ( Xy == Xy ) then
setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
echo "On this machine the G4VIS_BUILD_OPENGLXM_DRIVER=$G4VIS_BUILD_OPENGLXM_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_OPENGLWIN32_DRIVER 1
echo "On this machine the G4VIS_BUILD_OPENGLWIN32_DRIVER=$G4VIS_BUILD_OPENGLWIN32_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_OIX_DRIVER 1
echo "On this machine the G4VIS_BUILD_OIX_DRIVER=$G4VIS_BUILD_OIX_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_OIWIN32_DRIVER 1
echo "On this machine the G4VIS_BUILD_OIWIN32_DRIVER=$G4VIS_BUILD_OIWIN32_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_VRML_DRIVER 1
echo "On this machine the G4VIS_BUILD_VRML_DRIVER=$G4VIS_BUILD_VRML_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_DAWN 1
echo "On this machine the G4VIS_USE_DAWN=$G4VIS_USE_DAWN"
endif

#+
if ( Xy == Xy ) then
setenv G4VIS_USE_OPENGLX 1
echo "On this machine the G4VIS_USE_OPENGLX=$G4VIS_USE_OPENGLX"
endif

#+
if ( Xy == Xy ) then
setenv G4VIS_USE_OPENGLXM 1
echo "On this machine the G4VIS_USE_OPENGLXM=$G4VIS_USE_OPENGLXM"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_OPENGLWIN32 1
echo "On this machine the G4VIS_USE_OPENGLWIN32=$G4VIS_USE_OPENGLWIN32"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_OIX 1
echo "On this machine the G4VIS_USE_OIX=$G4VIS_USE_OIX"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_OIWIN32 1
echo "On this machine the G4VIS_USE_OIWIN32=$G4VIS_USE_OIWIN32"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_VRML 1
echo "On this machine the G4VIS_USE_VRML=$G4VIS_USE_VRML"
endif

#+
if ( X != X )  then
setenv OGLHOME ""
echo "On this machine the OGLHOME=$OGLHOME"
endif 

#
# Use G3TOG4 module
#
#+
if ( Xn == Xy )  then
setenv G4LIB_BUILD_G3TOG4 1
echo "On this machine the G4LIB_BUILD_G3TOG4=$G4LIB_BUILD_G3TOG4"
endif 

if ( Xn == Xy )  then
setenv G4USE_G3TOG4 1
echo "On this machine the G4USE_G3TOG4=$G4USE_G3TOG4"
endif 

#+
#
# g4shared
#
if ( Xy == Xy ) then
setenv G4LIB_BUILD_SHARED 1
echo "On this machine the G4LIB_BUILD_SHARED=$G4LIB_BUILD_SHARED"
endif

if ( Xy == Xy ) then
setenv G4LIB_BUILD_STATIC 1
echo "On this machine the G4LIB_BUILD_STATIC=$G4LIB_BUILD_STATIC"
endif

#+
#
# g4granular
#
if ( Xy == Xy ) then
setenv G4LIB_USE_GRANULAR 1
echo "On this machine the G4LIB_USE_GRANULAR=$G4LIB_USE_GRANULAR"
endif

#####################################################################


#+
#
# G4WORKDIR
#
if ( ${?G4WORKDIR} ) then
echo "In your environment you have the G4WORKDIR=$G4WORKDIR"
else
# Check for Windows!
if ( "X$G4SYSTEM" == "XWIN32-VC" || "X$G4SYSTEM" == "XWIN32-VC7" ) then

setenv checkdrive `echo $HOME|cut -d"/" -f2`

if ( "X$checkdrive" == "Xcygdrive" ) then

setenv windrive `echo $HOME|cut -d"/" -f3`
setenv winpath `echo $HOME|cut -d"/" -f4-`

setenv fullwinpath "$windrive:/$winpath"
setenv G4WORKDIR $fullwinpath

endif # if cygwin syntax is used

if ( "X$winpath" == "X" ) then
echo "G4WORKDIR will be set to ${G4WORKDIR}geant4 (in "native" Windows syntax)."
setenv G4WORKDIR ${G4WORKDIR}geant4
else
echo "G4WORKDIR will be set to $G4WORKDIR/geant4 (in "native" Windows syntax)."
setenv G4WORKDIR $G4WORKDIR/geant4
endif


else # if Unix

echo "G4WORKDIR will be set to /home/carter/BDS_Geant4/4.6.0/cal_addition"
setenv G4WORKDIR /home/carter/BDS_Geant4/4.6.0/cal_addition

endif
endif

