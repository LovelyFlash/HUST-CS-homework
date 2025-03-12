#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353

// 修改函数原型，添加结果矩阵参数
long long *matmult(long long mat1[3][3], long long mat2[3][3], long long res[3][3]);
long long *qmult(long long mat[3][3], long long n, long long res[3][3]);

int main()
{
    long long n, f1, f2, a, b, c;
    scanf("%lld", &n);
    scanf("%lld %lld", &f1, &f2);
    scanf("%lld %lld %lld", &a, &b, &c);

    // 转移矩阵初始化（第三列为1）
    long long mat[3][3] = {{a, b, 1}, {1, 0, 0}, {0, 0, 1}};
    long long result[3][3]; // 存储矩阵幂结果

    // 计算 mat^(n-2)
    qmult(mat, n - 2, result);

    // 结果计算：使用第一行元素组合
    long long fn = (
        (result[0][0] * f2) % MOD + 
        (result[0][1] * f1) % MOD + 
        (result[0][2] * c) % MOD
    ) % MOD;
    
    printf("%lld", fn);
    return 0;
}

// 矩阵乘法：res = mat1 * mat2
long long *matmult(long long mat1[3][3], long long mat2[3][3], long long res[3][3]) 
{
    long long temp[3][3] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                temp[i][j] = (temp[i][j] + mat1[i][k] * mat2[k][j]) % MOD;
            }
        }
    }
    memcpy(res, temp, sizeof(temp)); // 拷贝结果到res
    return (long long *)res;
}

// 快速幂：res = mat^n
long long *qmult(long long mat[3][3], long long n, long long res[3][3]) 
{
    if (n == 0) { // 单位矩阵
        long long ident[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};
        memcpy(res, ident, sizeof(ident));
        return (long long *)res;
    } else if (n == 1) {
        memcpy(res, mat, sizeof(long long)*9);
        return (long long *)res;
    }

    long long half[3][3];
    qmult(mat, n/2, half); // 计算 mat^(n/2)
    
    long long squared[3][3];
    matmult(half, half, squared); // squared = half^2
    
    if (n % 2 == 0) {
        memcpy(res, squared, sizeof(squared));
    } else {
        matmult(squared, mat, res); // res = squared * mat
    }
    return (long long *)res;
}