#include <stdio.h>

int main()
{
    int n, d;
    scanf("%d %d", &n, &d);

    int Q[10010][25], K[10010][25], V[10010][25];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            scanf("%d", &Q[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            scanf("%d", &K[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            scanf("%d", &V[i][j]);
        }
    }

    // 读入向量 W，大小为 n
    int W[10010];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &W[i]);
    }

    // 第一步：计算 A = diag(W) * Q,  A 是 n x d
    long long A[10010][25];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            A[i][j] = (long long)W[i] * Q[i][j];
        }
    }

    // 第二步：计算 B = K^T * V.
    long long B[25][25] = {0};
    for (int r = 0; r < d; r++)
    {
        for (int s = 0; s < d; s++)
        {
            long long sum = 0;
            for (int i = 0; i < n; i++)
            {
                sum += (long long)K[i][r] * V[i][s];
            }
            B[r][s] = sum;
        }
    }

    // 第三步：计算 result = A * B.
    long long result[10010][25] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int s = 0; s < d; s++)
        {
            long long sum = 0;
            for (int r = 0; r < d; r++)
            {
                sum += A[i][r] * B[r][s];
            }
            result[i][s] = sum;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%lld ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
