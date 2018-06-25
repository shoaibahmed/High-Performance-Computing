#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int NUM_MESSAGES = 6;
int MESSAGE_LENGTHS[] = {1000, 10000, 100000, 1000000, 10000000, 100000000};

int main(int argc, char** argv)
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

  int i, j;
  //FILE* outputFile = fopen("output.txt", "w");
  char received = 'r';

  // If process 0
  if (rank == 0)
  {
    for (i = 0; i < NUM_MESSAGES; i++)
    {
      printf("Sending a message of size: %d\n", MESSAGE_LENGTHS[i]);
      char* text = malloc(sizeof(char) * MESSAGE_LENGTHS[i]);
      for (j = 0; j < MESSAGE_LENGTHS[i] - 1; j++)
        text[j] = 'a';
      text[j] = '\0';

      MPI_Send(text, MESSAGE_LENGTHS[i], MPI_CHAR, receiver, tag, MPI_COMM_WORLD);
      MPI_Recv(&received, 0, MPI_CHAR, receiver, tag, MPI_COMM_WORLD, &status);

      // Free memory
      free(text);
    }
  }
  // If process 1
  else
  {
    for (i = 0; i < NUM_MESSAGES; i++)
    {
      char* buffer = malloc(sizeof(char) * MESSAGE_LENGTHS[i]);

      // Log the start time
      double startTime = MPI_Wtime();

      MPI_Recv(buffer, MESSAGE_LENGTHS[i], MPI_CHAR, sender, tag, MPI_COMM_WORLD, &status);
      MPI_Send(&received, 0, MPI_CHAR, sender, tag, MPI_COMM_WORLD);

      // Log the end time
      double endTime = MPI_Wtime();

      printf("Process %d received text: %c of length: %d\n", rank, buffer[0], MESSAGE_LENGTHS[i]);
      printf("Start time: %f | End time: %f | Elapsed time: %f\n", startTime, endTime, endTime - startTime);

      // Free memory
      free(buffer);
    }
  }

  //fprintf(outputFile, "%d, %f, %f, %f\n", MESSAGE_LENGTHS[i], startTime, endTime, endTime - startTime);

  // Kill all deamons
  MPI_Finalize();

  //fclose(outputFile);
}
