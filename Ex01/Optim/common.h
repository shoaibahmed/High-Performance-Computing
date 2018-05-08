#ifndef COMMON_H
#define COMMON_H


#define FIX 0
#define FIX_ITERATIONS 12

#include <sys/time.h>

// Prototypes
void matrix(int rank, int *chunks, int n, float *A);
void zeros(int n, float *v);
void printm(int n, int m, float *A);
void printv(int n, float *x);
void rmatrix(int rank, int *chunks, int n, float *A);
int getsize(int argc, char **argv);
int getopt(int argc, char **argv, const char *options);
void rvector(int chunk, float *x);
int irand( int a, int b);
int timestamp(void);
extern char *optarg;

// Returns a timestamp in millisecond resolution
int timestamp(void)
{
        struct timeval timeValue;
        gettimeofday(&timeValue,NULL);
        return (int)(timeValue.tv_sec*1000 + (timeValue.tv_usec / 1000));
}

// Returns the size command line parameter
int getsize(int argc, char **argv)
{
	int maxn = 0;
	int arg = -1;

	while ((arg = getopt(argc, argv, "n:d:amcg:")) != -1) {
		switch (arg) {   
	   	case 'n':
			maxn = atoi(optarg);
	    		break;
		}
	}
	
	return maxn;
}

// Prints a vector of size n
void printv(int n, float *x)
{
	int i = 0;
	for(i = 0; i < n; i++)
	{
		printf("%.8f ", x[i]);
	}
}

// Prints a matrix of rows n and columns m
void printm(int n, int m, float *A)
{
	int i = 0, j = 0;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			printf("%.6f ", A[i*m+j]);
		}
		printf("\n");
	}
}

// Creates a random in intervall [a,b]
int irand( int a, int b)
{
    double r = b - a + 1;
    return a + (int)(r * rand()/(RAND_MAX+1.0));
}

// Creates a random vector of size chunk
void rvector(int chunk, float *x)
{
	int i = 0;
	for(i = 0; i <  chunk; i++)
	{
		x[i] = ((float)irand(1,9)/10.0f);
		x[i] += ((float)irand(1,9)/100.0f);
		x[i] += ((float)irand(1,9)/1000.0f);
		x[i] += ((float)irand(1,9)/10000.0f);
	}
}

// Creates the random matrix for rank with rows chunks and columns n
void rmatrix(int rank, int *chunks, int n, float *A)
{
	int i = 0, j = 0;
	unsigned int offset = 0;
	for(i = 0; i < rank; i++) offset += chunks[i];

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if((i < offset+chunks[rank]) && (i >= offset))
			if(i == j)
			{
				if(rank == 0)
					A[i*n+j] = 4.0f;
				else
					A[(i-offset)*n+j] = 4.0f;
			} 
			else 
			{
				if(rank == 0)
					A[i*n+j] = (i+j)/(float)(n);
				else
					A[(i-offset)*n+j] = (i+j)/(float)(n);
			} 
		}
	}
	if (rank == 0) { A[0] = 4.0f; }
}

// Creates the matrix for rank with rows chunks and columns n
void matrix(int rank, int *chunks, int n, float *A)
{
	int i = 0, j = 0;
	unsigned int offset = 0;
	for(i = 0; i < rank; i++) offset += chunks[i];
	for(i = 0; i < chunks[rank]; i++)
	{
		int min = i + offset - 2;
		int max = i + offset + 2;
		for(j = 0; j < n; j++)
		{
			if((i+offset) == j)
			{
				A[i*n+j] = 2.3f;
			} else if ((j >= min) && (j <= max)) {
				A[i*n+j] = 1.0f;
			} else {
				A[i*n+j] = 0;
			}
		}
	}
	if (rank == 0) { A[0] = 6.0f; A[1] = 1.0f; }
}

// Sets a vector of size n to zero
void zeros(int n, float *v)
{
	int i = 0;
	for(i = 0; i < n; i++) v[i] = 0;
}

#endif
