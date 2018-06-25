#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

#define STR_LEN 100

int main(int argc, char** argv)
{
  char text[STR_LEN];
  int rank, size, sender = 0, receiver = 1, tag = 99;

  MPI_Status status;

  // Initialize the MPI library
  MPI_Init(&argc, &argv);

  // Get current process ID and total number of processes
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size != 2)
  {
    printf("Error: Program limited to only 2 tasks!\n");
    MPI_Finalize();
    exit (-1);
  }

  // If process 0
  if (rank == 0)
  {
    // strcpy(text, sprintf("Hello there from process %d\n", rank));
    sprintf(text, "Hello there from process %d\n", rank);
    MPI_Send(text, strlen(text), MPI_CHAR, receiver, tag, MPI_COMM_WORLD);
  }
  else
  {
    MPI_Recv(text, STR_LEN, MPI_CHAR, sender, tag, MPI_COMM_WORLD, &status);
    printf("Process %d received text: %s\n", rank, text);
  }

  // Kill all deamons
  MPI_Finalize();
}
