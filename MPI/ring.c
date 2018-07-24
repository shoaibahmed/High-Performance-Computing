#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank = 0, size = 1, sender = 0, receiver = 0, tag = 99, token;
	
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

	MPI_Status status;
	if (rank == 0)
	{
		token = -1;
	}
	else
	{
		// Receive data from your left neighbour
		MPI_Recv(&token, 1, MPI_INT, (rank - 1), tag, MPI_COMM_WORLD, &status);
		printf ("Data received at process %d: %d\n", rank, token);
	}
	MPI_Send(&token, 1, MPI_FLOAT, (rank + 1) % size, tag, MPI_COMM_WORLD);

	if (rank == 0)
	{
		MPI_Recv(&token, 1, MPI_INT, (size - 1), tag, MPI_COMM_WORLD, &status);
		printf ("Data received at process %d: %d\n", rank, token);
	}

	// Finalize the MPI environment
	MPI_Finalize();

	return 0;
}
