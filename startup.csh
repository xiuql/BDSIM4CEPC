source /usr/local/gcc-alt-3.2/setup.csh
source env.csh


  setenv ROOTSYS /usr/local/root/v3.10.02/rh73_gcc32/root
  setenv CLHEP_BASE_DIR /home/carter/lib/CLHEP/1.8.1.0/
  setenv G4VIS_USE_OPENGLX 1
  setenv G4VIS_USE_OPENGLXM 1
  setenv PATH ${PATH}:$G4WORKDIR/bin/${G4SYSTEM}:${ROOTSYS}/bin
  setenv LD_LIBRARY_PATH ${CLHEP_BASE_DIR}/lib:${ROOTSYS}/lib:${G4INSTALL}/lib/${G4SYSTEM}:/usr/local/lib/:${LD_LIBRARY_PATH}

  
  
