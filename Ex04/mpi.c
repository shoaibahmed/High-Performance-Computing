#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int MESSAGE_LENGTHS[6] = {1000, 10000, 100000, 1000000, 10000000, 100000000};

int main(int argc, char** argv)
{
  // FILE* outputFile = fopen("output.txt", "w");

  int i, j;
  for (i = 0; i < 6; i++)
  {
    // Initalize string
    char* text = malloc(sizeof(char) * MESSAGE_LENGTHS[i]);
    for (j = 0; j < MESSAGE_LENGTHS[i] - 1; j++)
      text[j] = 'a';

    printf("Sending a message of size: %d\n", strlen(text));
    int myID, size, sender = 0, receiver = 1, tag = 99;

    MPI_Status status;

    // Initialize the MPI library
    MPI_Init(&argc, &argv);

    // Get current process ID and total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &myID);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verify the number of processes
    if (size != 2)
    {
      printf("Error: Program limited to only 2 tasks!\n");
      MPI_Finalize();
      exit (-1);
    }

    // Log the start time
    double startTime = MPI_Wtime();

    // If process 0
    if (myID == 0)
    {
      // strcpy(text, sprintf("Hello there from process %d\n", myID));
      sprintf(text, "Hello there from process %d\n", myID);
      MPI_Send(text, strlen(text), MPI_CHAR, receiver, tag, MPI_COMM_WORLD);
    }
    // If process 1
    else
    {
      MPI_Recv(text, MESSAGE_LENGTHS[i], MPI_CHAR, sender, tag, MPI_COMM_WORLD, &status);
      printf("Process %d received text: %s\n", myID, text);
    }

    // Log the end time
    double endTime = MPI_Wtime();

    printf("Start time: %f | End time: %f | Elapsed time: %f\n", startTime, endTime, endTime - startTime);
    // fprintf(outputFile, "%f, %f, %f\n", startTime, endTime, endTime - startTime);

    // Free memory
    free(text);

    // Kill all deamons
    MPI_Finalize();
  }

  // fclose(outputFile);
}
