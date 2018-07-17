#include <stdio.h>
#include <omp.h>

int main(int argv, char* argc)
{
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		printf ("Hello (%d) ", id);
		printf ("World (%d)!\n", id);
	}

	return 0;
}