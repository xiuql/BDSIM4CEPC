#!/bin/tcsh
# mail me whenever a job finishes or aborts
# not used PBS -m ae 
# address to mail me at
# not used PBS -M carter@pp.rhul.ac.uk
cd ~
cd BDS_Geant4/4.6.0/cal_addition
source startup.csh
cd bds/
./../bin/Linux-g++/BDS_run
