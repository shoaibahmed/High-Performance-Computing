#!/bin/bash
#SBATCH -p short
#SBATCH --mem=200
#SBATCH -o Ex01.out
#SBATCH -e Ex01.err
#SBATCH --constraint=XEON_E5_4650

lstopo --of png > XEON_E5_4650.png

