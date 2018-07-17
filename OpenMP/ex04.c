#include <stdio.h>
#include <omp.h>

#define ATOMIC 1

static long num_steps = 1000000;
double step;

int main(int argv, char* argc)
{
	int total_threads;
	double pi, total_sum = 0.0;
	step = 1.0 / (double) num_steps;

	int num_procs = omp_get_num_procs();
	omp_set_num_threads(num_procs);

	int steps_per_thread = num_steps / num_procs;
	// int num_threads = omp_get_num_threads(); // Sequential section always returns 1 thread -> Move to parallel section
	printf ("Found %d CPUs. Using %d threads and computing %d steps per thread.\n", num_procs, num_procs, steps_per_thread);

	double startTime = omp_get_wtime();
	#pragma omp parallel
	{
		int num_threads = omp_get_num_threads();
		int i, id = omp_get_thread_num();
		printf("Executing thread %d out of %d\n", id, num_threads);
		double x, sum;
		for (i = id * steps_per_thread; i < (id + 1) * steps_per_thread; i++)
		{
			x = (i + 0.5) * step;
			sum += 4.0 / (1.0 + x * x);
		}

		#ifdef ATOMIC
			#pragma omp atomic
			total_sum += sum;
		#else
			#pragma omp critical
			total_sum += sum;
		#endif
	}

	pi = step * total_sum;
	double endTime = omp_get_wtime();

	printf ("Computed integral: %f\n", pi);
	printf ("Time elapsed: %f secs\n", (endTime - startTime));

	return 0;
}
