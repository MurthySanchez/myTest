#include <stdio.h>
#include <math.h>
#include <omp.h>
#define MAX 1000000000
int main(){
	double pi,tmp=0.0;
	int i;
	#pragma omp for
	for(i=0;i<MAX;i++)
		if(i%2==0)	tmp+=1.0/(2*i+1);
		else		tmp-=1.0/(2*i+1);
	pi=4.0*tmp;
	printf("%.50f\n",pi);
	return 0;
}
