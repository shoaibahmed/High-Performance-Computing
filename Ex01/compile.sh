#!/bin/bash

#echo "Compiling world.c using ICC"
#module load intel/latest
#icc -o world_icc world.c
#module purge
 
echo "Compiling world.c using GCC"
module load gcc/latest
gcc -o world_gcc world.c
module purge

