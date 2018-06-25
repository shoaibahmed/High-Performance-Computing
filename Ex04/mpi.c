#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int NUM_MESSAGES = 2;
//int MESSAGE_LENGTHS[] = {1000, 10000, 100000, 1000000, 10000000, 100000000};
int MESSAGE_LENGTHS[2] = {10, 100};

int main(int argc, char** argv)
{
  int i, j;
  //FILE* outputFile = fopen("output.txt", "w");
  //int maxMessageLength = MESSAGE_LENGTHS[NUM_MESSAGES - 1];

  for (i = 0; i < NUM_MESSAGES; i++)
  {
    // Initialize the MPI library
    MPI_Init(&argc, &argv);

    MPI_Status status;
    int rank, size, sender = 0, receiver = 1, tag = 99;

    // Get current process ID and total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verify the number of processes
    if (size != 2)
    {
      printf("Error: Program limited to only 2 tasks!\n");
      MPI_Finalize();
      exit (-1);
    }

    printf("Sending a message of size: %d\n", MESSAGE_LENGTHS[i]);

    char* text = malloc(sizeof(char) * MESSAGE_LENGTHS[i]);
    for (j = 0; j < MESSAGE_LENGTHS[i] - 2; j++)
      text[j] = 'a';
    char received = 'r';

    // Log the start time
    double startTime = MPI_Wtime();

    // If process 0
    if (rank == 0)
    {
      MPI_Send(text, MESSAGE_LENGTHS[i], MPI_CHAR, receiver, tag, MPI_COMM_WORLD);
      MPI_Recv(&received, 0, MPI_CHAR, receiver, tag, MPI_COMM_WORLD, &status);
    }
    // If process 1
    else
    {
      MPI_Recv(text, MESSAGE_LENGTHS[i], MPI_CHAR, sender, tag, MPI_COMM_WORLD, &status);
      MPI_Send(&received, 0, MPI_CHAR, sender, tag, MPI_COMM_WORLD);
    }

    // Log the end time
    double endTime = MPI_Wtime();

    printf("Process %d received text: %s of length: %d\n", rank, text[0], MESSAGE_LENGTHS[i]);
    printf("Start time: %f | End time: %f | Elapsed time: %f\n", startTime, endTime, endTime - startTime);
    //fprintf(outputFile, "%d, %f, %f, %f\n", MESSAGE_LENGTHS[i], startTime, endTime, endTime - startTime);

    // Free memory
    free(text);

    // Kill all deamons
    MPI_Finalize();
  }

  //fclose(outputFile);
}
