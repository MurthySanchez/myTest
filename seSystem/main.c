#include "gtk/gtk.h"
#include "stdio.h"
#include "stdlib.h"
#include  "test.h"

int main()
{
    int a = 1,b =2;
   int c = add(a,b);   //这里是对function.c中的add函数的调用
   printf("c=%d",c);

   return 0;   
}