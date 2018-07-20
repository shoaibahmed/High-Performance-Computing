#include <stdio.h>
#include <omp.h>

#define NUM_ELEMENTS 10

int main(int argv, char* argc)
{
	double A[NUM_ELEMENTS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int num_threads, i;
	double avg = 0.0;

	int num_procs = omp_get_num_procs();

	double startTime = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp single
		{
			num_threads = omp_get_num_threads();

			printf ("Found %d CPUs. Using %d threads.\n", num_procs, num_threads);
			// Implicit barrier at the end
		}

		#pragma omp for reduction (+:avg)
			for (i = 0; i < NUM_ELEMENTS; i++)
				avg += A[i];
	}

	avg = avg / NUM_ELEMENTS;
	double endTime = omp_get_wtime();

	printf ("Computed avg: %f\n", avg);
	printf ("Time elapsed: %f secs\n", (endTime - startTime));

	return 0;
}
