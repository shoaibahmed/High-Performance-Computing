#!/bin/bash
#SBATCH -p short
#SBATCH --mem=200
#SBATCH -o Ex00.out
#SBATCH -e Ex00.err

echo "Executing world_gcc"
module load gcc/latest # whatever you used for compilation
./world_gcc
module purge # clean environment
echo "Executing world_icc"
module load intel/latest # whatever you used for compilation
./world_icc
