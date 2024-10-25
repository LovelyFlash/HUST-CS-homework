#include <stdio.h>

int Fibonacci();

int main(void)
{
    int n;
    unsigned long long x=1, y=1;
    scanf("%d", &n);
    Fibonacci(n, x, y);
    return 0;
}

int Fibonacci(int n, unsigned long long a,unsigned long long b)
{
    printf("%llu\n", (a+b+b));
    if (n > 1) return Fibonacci(n-1, a+b, (a+b)+b);
    else return a+b+b;
}    