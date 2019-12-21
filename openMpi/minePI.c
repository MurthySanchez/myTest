#include <stdio.h>
#include "omp.h"
#define MAX 100000000
int main(){
	double pi,tmp=0.0,start,end;
	int i,s=1;
	start=omp_get_wtime();
	for(i=0;i<MAX;i++,s=-s){
		tmp+=1.0/(s*(2*i+1));
	}
	pi=4.0*tmp;
	printf("%.50f\n",pi);
	end=omp_get_wtime();
	printf("time=%g\n",end-start);
	return 0;
}
