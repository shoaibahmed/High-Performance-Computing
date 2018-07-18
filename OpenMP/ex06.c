#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000;
double step;

int main(int argv, char* argc)
{
	int i;
	double x, pi, sum = 0.0;
	step = 1.0 / (double) num_steps;

	double startTime = omp_get_wtime();
	#pragma omp parallel
	{
		double x;
		#pragma omp for reduction (+:sum)
			for (i = 0; i < num_steps; i++)
			{
				x = (i + 0.5) * step;
				sum += 4.0 / (1.0 + x * x);
			}
	}

	pi = step * sum;
	double endTime = omp_get_wtime();

	printf ("Computed integral: %f\n", pi);
	printf ("Time elapsed: %f secs\n", (endTime - startTime));

	return 0;
}