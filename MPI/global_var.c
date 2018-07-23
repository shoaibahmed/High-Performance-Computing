#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank = 0, size = 1;
	int randomGlobalVar = 100;
	int array[4] = {0, 1, 2, 3};

	// Initialize MPI
	MPI_Init(&argc, &argv);

	// Get the size of the world and the rank
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("Hello world from process %d out of %d processes (Global var=%d)!\n", rank, size, randomGlobalVar);
	for (int i = 0; i < 4; i++) printf("Process %d: %d\n", rank, array[i]);

	// Finalize the MPI environment
	MPI_Finalize();

	return 0;
}
