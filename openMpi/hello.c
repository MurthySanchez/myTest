#include <stdio.h>
#include <omp.h>

int main(){
	#pragma omp parallel
	{printf("Hello,world. With Thread NO.%d\n",omp_get_thread_num());
		;
	}
	
	return 0;
}
