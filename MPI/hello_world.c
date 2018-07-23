#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank = 0, size = 1;

	// Initialize MPI
	MPI_Init(&argc, &argv);

	// Get the size of the world and the rank
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("Hello world from process %d out of %d processes!\n", rank, size);

	// Finalize the MPI environment
	MPI_Finalize();

	return 0;
}
