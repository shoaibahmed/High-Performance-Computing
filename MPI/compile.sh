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

echo ""
echo "~~~~~~~~~~~~~ Executing reduction program! ~~~~~~~~~~~~~"
mpiexec -n 10 ./reduce

echo ""
echo "~~~~~~~~~~~~~ Executing non-blocking reduction program! ~~~~~~~~~~~~~"
mpiexec -n 10 ./non_blocking_reduce

echo ""
echo "~~~~~~~~~~~~~ Executing broadcast program! ~~~~~~~~~~~~~"
mpiexec -n 10 ./broadcast

echo ""
echo "~~~~~~~~~~~~~ Executing ring program! ~~~~~~~~~~~~~"
mpiexec -n 10 ./ring
