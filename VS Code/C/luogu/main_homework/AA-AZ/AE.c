#include <stdio.h>

long long fastPow(long long base, long long exp)
{
    long long res = 1;
    while (exp)
    {
        if (exp & 1)
            res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

// 采用质因数分解，返回乘积：只将指数 >= k 的质因子乘入结果
long long prime_factorization(long long a, long long k)
{
    long long result = 1;

    // 从2开始试除法分解，遍历到 i*i <= a
    for (long long i = 2; i * i <= a; i++)
    {
        if (a % i == 0)
        {
            long long count = 0;
            while (a % i == 0)
            {
                a /= i;
                count++;
            }
            // 如果 i 的指数 >= k，则乘入结果
            if (count >= k)
            {
                result *= fastPow(i, count);
            }
        }
    }

    // 如果 a 大于 1，则说明 a 本身是一个质因子，其指数为 1
    if (a > 1)
    {
        if (1 >= k)
            result *= a;
    }

    return result;
}

int main()
{
    long long q;
    scanf("%lld", &q);

    while (q--)
    {
        long long a, k;
        scanf("%lld %lld", &a, &k);
        printf("%lld\n", prime_factorization(a, k));
    }

    return 0;
}
