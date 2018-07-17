#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;

int main(int argv, char* argc)
{
	int total_threads;
	double pi, total_sum = 0.0;
	step = 1.0 / (double) num_steps;

	int num_procs = omp_get_num_procs();
	omp_set_num_threads(num_procs);
	total_threads = omp_get_num_threads();

	int steps_per_thread = num_steps / total_threads;
	printf ("Using %d threads and computing %d steps per thread.\n", total_threads, steps_per_thread);

	double startTime = omp_get_wtime();
	#pragma omp parallel
	{
		int i, ID = omp_get_thread_num();
		double x, sum = 0.0;
		for (i = ID * steps_per_thread; i < (ID + 1) * steps_per_thread; i++)
		{
			x = (i + 0.5) * step;
			sum = sum + 4.0 / (1.0 + x * x);
		}

		// Race condition
		total_sum = total_sum + sum;
	}

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