/////////////////////////////////////////////////
// gettime function for algorithm execution time
/////////////////////////////////////////////////

//#define Linux
#define Windows

// gettime for Windows
#ifdef Windows
#include <stdlib.h>
#include <time.h>
#include <windows.h>
double gettime(void);

double gettime(){
    LARGE_INTEGER f, n;

    memset(&f, 0x00, sizeof f);
    memset(&n, 0x00, sizeof n);

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&n);

    return (double)n.QuadPart / f.QuadPart;
}
#endif

// gettime for Linux
#ifdef Linux
#include <stdlib.h>
#include <time.h>
double gettime(void);

double gettime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double)tv.tv_usec * 1e-6;
}
#endif