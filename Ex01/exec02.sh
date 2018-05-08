#!/bin/bash
#SBATCH -p short
#SBATCH --mem=200
#SBATCH -o Ex01_02.out
#SBATCH -e Ex01_02.err
#SBATCH --constraint=XEON_E5_4650

./Benchmark

