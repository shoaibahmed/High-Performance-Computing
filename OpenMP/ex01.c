#include <stdio.h>
#include <omp.h>

int main(int argv, char* argc)
{
	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		printf ("Hello (%d) ", ID);
		printf ("World (%d)!\n", ID);
	}

	return 0;
}