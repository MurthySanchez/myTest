#include <stdio.h>
#define MAX 10000
int main(){
	double pi = 0.0;
	int i;
	double x,step = 1.0/MAX;
	for(i=0; i<MAX; i++){
		x=(i+0.5)*step;
		pi += 4.0/(x*x + 1.0);
	}
	pi = step*pi;
	printf("pi=%.56f\n",pi);
}
