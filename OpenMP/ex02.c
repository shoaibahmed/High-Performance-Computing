#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000;
double step;

int main(int argv, char* argc)
{
	int num_threads;
	double pi, total_sum = 0.0;
	step = 1.0 / (double) num_steps;

	int num_procs = omp_get_num_procs();
	// omp_set_num_threads(num_procs);
	double* sum;

	int steps_per_thread;
	// int num_threads = omp_get_num_threads(); // Sequential section always returns 1 thread -> Move to parallel section
	
	double startTime = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp single
		{
			num_threads = omp_get_num_threads();
			
			steps_per_thread = num_steps / num_threads;
			sum = (double*) malloc(sizeof(double) * num_threads);

			printf ("Found %d CPUs. Using %d threads and computing %d steps per thread.\n", num_procs, num_threads, steps_per_thread);
			// Implicit barrier at the end
		}

		int i, id = omp_get_thread_num();
		printf("Executing thread %d out of %d\n", id, num_threads);
		double x;
		for (i = id * steps_per_thread; i < (id + 1) * steps_per_thread; i++)
		{
			x = (i + 0.5) * step;
			sum[id] += 4.0 / (1.0 + x * x);
		}
	}

	int i;
	for (i = 0; i < num_procs; i++)
		total_sum += sum[i];

	pi = step * total_sum;
	double endTime = omp_get_wtime();

	printf ("Computed integral: %f\n", pi);
	printf ("Time elapsed: %f secs\n", (endTime - startTime));

	return 0;
}

int main_serial(int argv, char* argc)
{
	int i;
	double x, pi, sum = 0.0;
	step = 1.0 / (double) num_steps;

	for (i = 0; i < num_steps; i++)
	{
		x = (i + 0.5) * step;
		sum = sum + 4.0 / (1.0 + x * x);
	}
	pi = step * sum;
	printf ("Computed integral: %f\n", pi);

	return 0;
}