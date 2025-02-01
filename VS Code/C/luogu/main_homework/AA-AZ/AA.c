#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int mian()
{
    int N, B, sum = 0, k;
    scanf("%d %d", &N, &B);
    int height[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &height[i]);
    qsort(height, N, sizeof(int), cmpfunc);
    for (k = N - 1; k >= 0; k--)
    {
        sum += height[k];
        if (sum >= B)
            break;
    }
    printf("%d", N - k);
    return 0;
}