#!/bin/bash

#echo "Compiling using GCC"
#module load gcc/latest
#make gcc
#exit

echo "Compiling using ICC"
module load intel/latest
make icc
