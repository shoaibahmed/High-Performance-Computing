#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank = 0, size = 1, sender = 0, receiver = 0, tag = 99;
	
	// Initialize MPI
	MPI_Init(&argc, &argv);

	// Get the size of the world and the rank
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (size < 2)
	{
		printf("Error: Program requires atleast 2 processes!\n");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	if (rank == 0) // Master process
	{
		MPI_Status status;
		float sum = 0.0, value = 0.0;
		for (sender = 1; sender < size; sender++)
		{
			MPI_Recv(&value, 1, MPI_FLOAT, sender, tag, MPI_COMM_WORLD, &status);
			sum += value;
		}

		printf("Final value accumulated at the master process: %f\n", sum);
	}
	else
	{
		float value = (float) rank;
		MPI_Send(&value, 1, MPI_FLOAT, receiver, tag, MPI_COMM_WORLD);
	}

	// Finalize the MPI environment
	MPI_Finalize();

	return 0;
}
