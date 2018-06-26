#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

#define STARTUP_TIME_ITERATIONS 10

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
  char received = 'r';

  // Log file
  MPI_File fh;
  MPI_File_open(MPI_COMM_WORLD, "results.out", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

  // If process 0
  if (rank == 0)
  {
    // Warmup
    MPI_Send(&received, 0, MPI_CHAR, receiver, tag, MPI_COMM_WORLD);

    // Compute startup time
    double avgStartupTime = 0.0;
    for(i = 0; i < STARTUP_TIME_ITERATIONS; i++)
    {
      double startupTime = MPI_Wtime();
      MPI_Send(&received, 0, MPI_CHAR, receiver, tag, MPI_COMM_WORLD);
      MPI_Recv(&received, 0, MPI_CHAR, receiver, tag, MPI_COMM_WORLD, &status);
      startupTime = (MPI_Wtime() - startupTime) / 2.0;
      avgStartupTime += startupTime;
    }
    avgStartupTime /= STARTUP_TIME_ITERATIONS;
    printf("Startup time: %f\n", avgStartupTime);

    for (i = 0; i < NUM_MESSAGES; i++)
    {
      printf("Sending a message of size: %d\n", MESSAGE_LENGTHS[i]);
      char* text = malloc(sizeof(char) * MESSAGE_LENGTHS[i]);
      for (j = 0; j < MESSAGE_LENGTHS[i] - 1; j++)
        text[j] = 'a';
      text[j] = '\0';

      double startTime = MPI_Wtime(); // Log the start time

      MPI_Send(text, MESSAGE_LENGTHS[i], MPI_CHAR, receiver, tag, MPI_COMM_WORLD);
      MPI_Recv(&received, 0, MPI_CHAR, receiver, tag, MPI_COMM_WORLD, &status);

      double endTime = MPI_Wtime(); // Log the end time
      double elapsedTime = endTime - startTime;
      if (elapsedTime - avgStartupTime < 0.0)
      {
        printf("Warning: Elapsed time is less than startup time!");
        MPI_File_close(&fh);
        MPI_Finalize();
        exit(-1);
      }

      // Print the status
      printf("Start time: %f | End time: %f | Elapsed time: %f | Actual elapsed time: %f\n", startTime, endTime, elapsedTime, elapsedTime - avgStartupTime);
      char textBuffer[200];
      snprintf(textBuffer, 200, "%d,%f,%f,%f,%f\n", MESSAGE_LENGTHS[i], startTime, endTime, avgStartupTime, elapsedTime);
      MPI_File_write(fh, textBuffer, strlen(textBuffer), MPI_CHAR, MPI_STATUS_IGNORE);

      // Free memory
      free(text);
    }
  }
  // If process 1
  else
  {
    // Warmup
    MPI_Recv(&received, 0, MPI_CHAR, sender, tag, MPI_COMM_WORLD, &status);

    // Compute startup time
    for(i = 0; i < STARTUP_TIME_ITERATIONS; i++)
    {
      MPI_Recv(&received, 0, MPI_CHAR, sender, tag, MPI_COMM_WORLD, &status);
      MPI_Send(&received, 0, MPI_CHAR, sender, tag, MPI_COMM_WORLD);
    }

    for (i = 0; i < NUM_MESSAGES; i++)
    {
      char* buffer = malloc(sizeof(char) * MESSAGE_LENGTHS[i]);

      double startTime = MPI_Wtime(); // Log the start time

      MPI_Recv(buffer, MESSAGE_LENGTHS[i], MPI_CHAR, sender, tag, MPI_COMM_WORLD, &status);
      MPI_Send(&received, 0, MPI_CHAR, sender, tag, MPI_COMM_WORLD);

      printf("Process %d received text: %c of length: %d\n", rank, buffer[0], MESSAGE_LENGTHS[i]);

      // Free memory
      free(buffer);
    }
  }

  //fprintf(outputFile, "%d, %f, %f, %f\n", MESSAGE_LENGTHS[i], startTime, endTime, endTime - startTime);

  // Kill all deamons
  MPI_File_close(&fh);
  MPI_Finalize();

  //fclose(outputFile);
}
