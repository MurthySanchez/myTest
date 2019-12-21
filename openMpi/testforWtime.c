#include <stdio.h>
#include <omp.h>

int main(){
	double start=omp_get_wtime();
	usleep(1000);
	double end=omp_get_wtime();
	double wtick=omp_get_wtick();
	printf("start=%.16g\nend=%.16g\ndiff=%.16g\n",start,end,wtick);
	return 0;
}
