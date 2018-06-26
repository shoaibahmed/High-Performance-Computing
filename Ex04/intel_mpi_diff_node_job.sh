#!/bin/bash
#SBATCH -p short	# select a project or insert # in first column
##SBATCH --mail-type=END		# want a mail notification at end of job
#SBATCH -J MPI-Test		# name of the job
#SBATCH -o MPI-Test-DiffNode.%j.out	# Output: %j expands to jobid
#SBATCH -e MPI-Test-DiffNode.%j.err	# Error: %j expands to jobid
#SBATCH -C XEON_E5_2670		# selects only nodes of that type
#SBATCH -C IB			# node s
#SBATCH -L impi			# request a license for intel mpi
#SBATCH --nodes=2		# requesting 2 nodes (identical -N 2)
#SBATCH --ntasks=2		# requesting 4 MPI tasks (identical -n 4)
#SBATCH --ntasks-per-node=1     # 2 MPI tasks will be started per node
##SBATCH --cpus-per-task=4       # each MPI task starts 4 OpenMP threads

#Empty line above indicates end of SBATCH options
module purge			# clean all module versions
module load intel/latest	# load your version of Intel compilers

mpiexec.hydra ./mpi
