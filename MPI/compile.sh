#!/bin/bash

make

echo ""
echo "~~~~~~~~~~~~~ Executing hello world program! ~~~~~~~~~~~~~"
mpiexec -n 10 ./hello_world

echo ""
echo "~~~~~~~~~~~~~ Executing global var program! ~~~~~~~~~~~~~"
mpiexec -n 2 ./global_var

echo ""
echo "~~~~~~~~~~~~~ Executing send and receive program! ~~~~~~~~~~~~~"
mpiexec -n 2 ./send_recv
