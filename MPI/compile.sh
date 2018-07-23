#!/bin/bash
mpicc ./hello_world.c -o hello_world
mpiexec -n 10 ./hello_world
