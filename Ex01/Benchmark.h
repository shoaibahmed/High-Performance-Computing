#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdlib.h>

#ifdef __linux__
	#include <unistd.h>
	#include <errno.h>
	#include <time.h>
	#include <sys/time.h>
	#include <sys/times.h>
	#include <time.h>
#elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
	#include <windows.h>
#endif


double getTimeInSeconds() 
{ 
#ifdef __linux__
    double rt;
	struct timeval r_zeiten;
	struct timezone z_zeiten;
	gettimeofday(&r_zeiten,&z_zeiten);
	rt=(double)r_zeiten.tv_sec+((double)r_zeiten.tv_usec)*0.000001;
    return(rt);
#elif defined(WIN32) || defined(WIN64) || defined(WINDOWS)
	LONGLONG current;
	LONGLONG tmp;
	QueryPerformanceFrequency((LARGE_INTEGER*)&tmp);
	double cpuFrequency = (double)tmp;
	QueryPerformanceCounter((LARGE_INTEGER*)&current);
	return (double)(current / cpuFrequency); 
#endif
}

inline int irand(int a, int b)
{
	double r = b - a + 1;
	return a + (int)(r * rand()/(RAND_MAX+1.0));
};

inline double drand(double a, double b)
{
	double range = b - a;
	double div = RAND_MAX / range;
	return (a + (rand() / div));
};

#endif
