#include <stdio.h>
#include <stdlib.h> // For malloc
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank = 0, size = 1, sender = 1, receiver = 0, tag = 99;
	
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
		MPI_Request req[9]; // TODO: Dynamic allocation
		float sum = 0.0;
		float* buffer = (float*) malloc(sizeof(float) * (size - 1));
		for (sender = 1; sender < size; sender++)
		{
			MPI_Irecv(&buffer[sender-1], 1, MPI_FLOAT, sender, tag, MPI_COMM_WORLD, &req[sender-1]);
		}

		// Check if the values are received
		sender = 1;
		for (int iterator = 1; iterator < size; iterator++)
		{
			MPI_Status status;
			int received;
			for (received = 0; !received; sender = (sender % (size - 1)) + 1)
			{
				MPI_Test(&req[sender-1], &received, &status);
			}

			printf ("Received value of %f from process %d\n", buffer[sender-1], sender);
			sum += buffer[sender-1];
		}	

		printf("Final value accumulated at the master process: %f\n", sum);
	}
	else
	{
		MPI_Request req;
		float value = (float) rank;
		printf ("Sending value of %f from process %d\n", value, rank);
		MPI_Send(&value, 1, MPI_FLOAT, receiver, tag, MPI_COMM_WORLD);
		// MPI_Isend(&value, 1, MPI_FLOAT, receiver, tag, MPI_COMM_WORLD, &req);
	}

	// Finalize the MPI environment
	MPI_Finalize();

	return 0;
}
