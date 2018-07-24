#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank = 0, size = 1;
	int randomGlobalVar;

	// Initialize MPI
	MPI_Init(&argc, &argv);

	// Get the size of the world and the rank
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Only the master thread has the initalized value
	if (rank == 0)
		randomGlobalVar = 100;

	MPI_Bcast(&randomGlobalVar, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("Global var value at process %d (out of %d) is: %d\n", rank, size, randomGlobalVar);

	// Finalize the MPI environment
	MPI_Finalize();

	return 0;
}
