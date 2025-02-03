#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, m, k, flag = 0;
    scanf("%d %d %d", &n, &m, &k);
    int vem[n][m], height[k];
    for (int i = 0; i < k; i++)
        scanf("%d", &height[i]);
    qsort(height, k, sizeof(int), cmpfunc);
    for (int i = 0; i < n + m && i < k; i++)
    {
        if (height[i] < (i / m + 1))
        {
            flag = 1;
            break;
        }
    }
    if (flag)
        printf("No");
    else
        printf("Yes");
    return 0;
}