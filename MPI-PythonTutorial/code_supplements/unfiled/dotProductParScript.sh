#!/bin/bash

#PBS -l nodes=1:ppn=5,pmem=2gb,walltime=00:01:00
#PBS -N dotProduct

# Set the max number of threads to use for programs using OpenMP. Should be <= ppn. Does nothing if the program doesn't use OpenMP.
export OMP_NUM_THREADS=4
OUTFILE="dotProd.out"



# The following line changes to the directory that you submit your job from
cd "$PBS_O_WORKDIR"

mpiexec python26 /fslhome/jmbejara/codeMPI4py/dotProductParallel.py > "$OUTFILE"

exit 0
