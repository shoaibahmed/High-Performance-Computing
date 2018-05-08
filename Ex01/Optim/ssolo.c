#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "blas_net.h"

int main(int argc, char **argv)
{
	// Allocate
	int n = getsize(argc, argv);
	int start = 0, end = 0;
	int k = 0;
#if FIX
	int max = FIX_ITERATIONS;
#else
	int max = n;
#endif
	float eps = 0.00001f;
	float rnorm = 0;
	float alpha, beta = 0, rho = 0, mu = 0;

	// Allocate system memory
	float *A = (float*)malloc(sizeof(float)*n*n);
	float *x = (float*)malloc(sizeof(float)*n);
	float *b = (float*)malloc(sizeof(float)*n);
	float *r = (float*)malloc(sizeof(float)*n);
	float *q = (float*)malloc(sizeof(float)*n);
	float *p = (float*)malloc(sizeof(float)*n);
	float *s = (float*)malloc(sizeof(float)*n);
	float *c = (float*)malloc(sizeof(float)*n);

	if(n <= 0)
	{
		printf("Please set a size with [-n #]\n");
		return 0;
	}

	// Initialize
	matrix(0, &n, n, A);	
	rvector(n, b);
	zeros(n, x);
	zeros(n, r);
	zeros(n, q);
	zeros(n, p);
	zeros(n, s);
	zeros(n, c);

	// Start CG-Algorithm -------------------------------------------
	scopy(n, b, 1, r, 1);
	sgemv("N", n, n, -1.0f, A, n, x, 1, 1.0f, r, 1);
	sgemv("N", n, n, 1.0f, A, n, r, 1, 0, q, 1);
	rho = sdot(n, r, 1, r, 1);
	mu = sdot(n, q, 1, r, 1);
	alpha = rho / mu;

	rnorm = rho;
	printf (" Size  Norm(start) Norm(end) Iterations Time(msec)\n");
	printf("%d ", n);		
	printf("%.8f ", rnorm);
	start = timestamp();
#if FIX
	while(k < max)
#else
	while((rnorm > eps*eps) && (k < max))
#endif
	{
		sscal(n, beta, p, 1);
		saxpy(n, 1.0f, r, 1, p, 1);
		saxpy(n, alpha, p, 1, x, 1);
		sscal(n, beta, s, 1);
		saxpy(n, 1.0f, q, 1, s, 1);
		saxpy(n, (-1)*alpha, s, 1, r, 1);
		sgemv("N", n, n, 1.0f, A, n, r, 1, 0.f, q, 1);
		beta = rho;
		rho = sdot(n, r, 1, r, 1);
		mu = sdot(n, q, 1, r, 1);
		beta = rho / beta;
		alpha = rho/(mu-rho*beta/alpha);
		rnorm = rho;
		k++;
	}
	end = timestamp();
	// End CG-Algorithm ----------------------------------------------

	int diff = end - start;

	// End norm, iter, time
	printf("%.8f %d %d \n", rnorm, k, diff);

	// Free used memory	
	if(A) free(A);
	if(x) free(x);
	if(q) free(q);
	if(p) free(p);
	if(s) free(s);
	if(r) free(r);
	if(b) free(b);
	
	return 0;
}

