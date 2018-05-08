#include <stdio.h>
#include "Benchmark.h"

void benchmark(int N)
{
    // Allocate arrays
    double *x, *y;
    x = malloc(sizeof(double) * N);
    y = malloc(sizeof(double) *  N);

    int i;
    for(i = 0; i < N; i++)
    {
        x[i] = drand(-1.0, 1.0);
	y[i] = drand(-1.0, 1.0);
    }

    double startTime = getTimeInSeconds();
    for(i = 0; i < N; i++)
    {
        y[i] = 2.3 * x[i] + y[i];
    }
    double endTime = getTimeInSeconds();

    printf("Total time elapsed (in seconds): %f\n", endTime - startTime);
}

int main()
{
    long i;
    for (i = 10000; i < 100000000; i = i * 2)
    {
       printf("Using N = %d\n", i);
       benchmark(i);
    }
    return 0;
}
