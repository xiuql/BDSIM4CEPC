#!/bin/sh
# This script submits a job for each line of the file
# It will submit 'joboptions.csh' to queue 'short'
# (check queue names on your system
# with qstat -q) passing the environment variable cards which job.sh will use.
# Jobs are given a name including a sequence number but this is only aesthetic.

# loop over lines read from the seeds.dat file
i=0
while read seeds
do
  i=`expr $i + 1`
  echo "$i: $seeds"
  # submit job
  qsub -q medium -v BDS_SEED=$seeds,BDS_FILENAME=PETRA_Laserwire$i -N BDSim$i joboptions_cal.csh
done < seeds.dat
