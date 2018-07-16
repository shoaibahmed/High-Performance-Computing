#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main(int argv, char* argc)
{
	int inode = 1, nnode = 1;
	#ifdef _OPENMP
	nnode = omp_get_num_procs();
	omp_set_num_threads(nnode);
	#endif

	printf ("Found %d CPUs. Using all of them!\n", nnode);

	#pragma omp parallel private(inode)
	{
		#ifdef _OPENMP
		inode = omp_get_thread_num();
		#endif
		printf ("Hello world from node %d!\n", inode);
	}

	return 0;
}
