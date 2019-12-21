#include <stdio.h>
#include <math.h>
#include "omp.h"
#define MAX 1000000000
int main(){
	double pi,tmp=0.0,start,end;
	int i;
	start=omp_get_wtime();
	#pragma omp for
	for(i=0;i<MAX;i++)
		tmp+=1.0/(pow((-1),i)*(2*i+1));
	pi=4.0*tmp;
	printf("%.50f\n",pi);
	end=omp_get_wtime();
	printf("time = %g\n",end-start);
	return 0;
}
