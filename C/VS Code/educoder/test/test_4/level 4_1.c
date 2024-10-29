/*
任务描述
教材P108 跟踪调试第（1）题。
本关任务：求斐波那契级数前n项的和。
题目要求详见教材，线下完成跟踪调试任务后，提交最后一问的程序(去掉原题中的输入提示语句)进行评测,注意题目要求，要用递归，不能用循环，否则计0分。
*/
#include <stdio.h>
void Fibonacci(unsigned long k, int n, unsigned long a,unsigned long b)
{
    k = k + a + b;
    if (n > 1) Fibonacci(k, n-2, a+b, (a+b)+b);
    else if(n == 1) printf("%lu", k-b);
    else if(n == 0) printf("%lu", k-a-b);
};

int main(void)
{
    int n;
    unsigned long x=1, y=1, k = 0;
    scanf("%d", &n);
    Fibonacci(k, n, x, y);
    return 0;
};