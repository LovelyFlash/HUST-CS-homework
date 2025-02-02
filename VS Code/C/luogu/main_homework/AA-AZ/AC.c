#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353
long long *qmult(long long *mat, long long n);
long long *matmult(long long *mat);

int main()
{
    long long n, f1, f2, a, b, c;
    scanf("%llu", &n);
    scanf("%llu %llu", &f1, &f2);
    scanf("%llu %llu %llu", &a, &b, &c);

    // 转移矩阵初始化
    long long mat[3][3] = {{a, b, 1}, {1, 0, 0}, {0, 0, 1}};
    long long *result = qmult((long long *)mat, n - 2);

    // 结果计算
    long long fn = ((result[0] * f2) % MOD + (result[1] * f1) % MOD + (result[2] * c) % MOD) % MOD;
    printf("%llu", fn);
    return 0;
}

// 快速幂函数
long long *qmult(long long *mat, long long n)
{
    long long i = 1, *tem = mat;
    for (; 2 * i <= n; i += i)
        mat = matmult(mat);
    if (i != n)
        return qmult(tem, n - i);
    else
        return mat;
}

// 矩阵乘法函数
long long *matmult(long long *mat)
{
    long long tem[9];
    for (int i = 0; i < 9; i++)
        tem[i] = *(mat + i);
    *mat = ((*tem) * (*tem) + (*(tem + 1)) * (*(tem + 3)) + (*(tem + 2)) * (*(tem + 6))) % MOD;
    *(mat + 1) = ((*tem) * (*(tem + 1)) + (*(tem + 1)) * (*(tem + 4)) + (*(tem + 2)) * (*(tem + 7))) % MOD;
    *(mat + 2) = ((*tem) * (*(tem + 2)) + (*(tem + 1)) * (*(tem + 5)) + (*(tem + 2)) * (*(tem + 8))) % MOD;
    *(mat + 3) = ((*(tem + 3)) * (*(tem)) + (*(tem + 4)) * (*(tem + 3)) + (*(tem + 5)) * (*(tem + 6))) % MOD;
    *(mat + 4) = ((*(tem + 3)) * (*(tem + 1)) + (*(tem + 4)) * (*(tem + 4)) + (*(tem + 5)) * (*(tem + 7))) % MOD;
    *(mat + 5) = ((*(tem + 3)) * (*(tem + 2)) + (*(tem + 4)) * (*(tem + 5)) + (*(tem + 5)) * (*(tem + 8))) % MOD;
    return mat;
}