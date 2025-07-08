#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, sum = 0, t, flag = 0;
    scanf("%d", &n);
    int matrix[n][n];
    while (sum < n * n)
    {
        scanf("%d", &t);
        for (int i = sum; i < (sum + t); i++)
            matrix[i / n][i % n] = flag;
        sum += t;
        flag = 1 - flag;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}