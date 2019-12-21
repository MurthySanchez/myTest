#include <stdio.h>

int main(){
	double my_pi=2;
	int _jingdu=1000,i;
	for(i=_jingdu;i>0;i--)
		my_pi=my_pi*i/(2*i+1)+2;
	printf("%.320f\n",my_pi);
	return 0;
}
