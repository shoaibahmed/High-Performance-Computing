#include <stdio.h>
#include "Benchmark.h"

#ifdef DOUBLE
double GLOBAL_VAR = 2.03;
#else
float GLOBAL_VAR = 2.03f;
#endif

void benchmark(int N)
{
    #ifdef DOUBLE
    extern double GLOBAL_VAR;
    
    // Allocate arrays
    double *x, *y;
    x = malloc(sizeof(double) * N);
    y = malloc(sizeof(double) *  N);

    #else
    extern float GLOBAL_VAR;
    
    // Allocate arrays
    float *x, *y;
    x = malloc(sizeof(float) * N);
    y = malloc(sizeof(float) *  N);
    #endif

    int i;
    for(i = 0; i < N; i++)
    {
        x[i] = drand(-1.0, 1.0);
	y[i] = drand(-1.0, 1.0);
    }

    double startTime = getTimeInSeconds();
    for(i = 0; i < N; i++)
    {
        y[i] = GLOBAL_VAR * x[i] + y[i];
    }
    double endTime = getTimeInSeconds();

    printf("Total time elapsed (in seconds): %f\n", endTime - startTime);
}

int main()
{
    long i;

    #ifdef LOOP_OVER_VALUES
    for (i = 10000; i < 100000000; i = i * 2)
    {
        printf("Using N = %d\n", i);
        benchmark(i);
    }
    #else
    long n_list[3] = {10000, 1000000, 100000000}; 
 
    for (i = 0; i < 3; i++)
    {
        printf("Using N = %d\n", n_list[i]);
        benchmark(n_list[i]);
    }
    #endif

    return 0;
}
