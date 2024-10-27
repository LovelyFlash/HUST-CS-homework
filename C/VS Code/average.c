#include<stdio.h>
int main()
{
    int n=0, k, a;
    for(k=1, k<=10; k++)
    {
        scanf("%d", &a);
        n = n + a;
    }
    printf("累加和：%d\n平均值：%.1f", n, n/k);
    return 0;
}