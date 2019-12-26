#include <stdio.h>
#include <stdarg.h>

void fun(int a, const char *data, ...)
{
    va_list ap;
    char *str;
    va_start(ap, data);
    int i;
    for (i = 0; i < a; i++)
    {
        sprintf(str, va_arg(ap, const char *));
    }
    va_end(ap);
    printf("%s\n",str);
}

int main()
{
    fun(4, "1", "2", "0", "4");
    printf("--------------------------------\n");
    fun(4, "1", "2", "ab", "cd", "fd");
    return 0;
}