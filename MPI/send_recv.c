#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank = 0, size = 1, sender = 0, receiver = 1, tag = 99;
	
	// Initialize MPI
	MPI_Init(&argc, &argv);

	// Get the size of the world and the rank
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (size < 2)
	{
		printf("Error: Program requires atleast 2 processes!\n");
		MPI_Finalize();
		return -1;
	}

	if (rank == 0) // Master process
	{
		int array[4] = {0, 1, 2, 3};
		for (int i = 0; i < 4; i++) printf("Sending %d\n", array[i]);
		MPI_Send(&array, 4, MPI_INT, receiver, tag, MPI_COMM_WORLD);
	}
	else
	{
		MPI_Status status;
		int array[4];
		MPI_Recv(&array, 4, MPI_INT, sender, tag, MPI_COMM_WORLD, &status);
		for (int i = 0; i < 4; i++) printf("Received %d\n", array[i]);
	}

	// Finalize the MPI environment
	MPI_Finalize();

	return 0;
}
