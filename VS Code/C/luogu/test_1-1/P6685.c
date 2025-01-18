#include <stdio.h>
#include <math.h>

int main()
{
    long n, m;
    scanf("%ld %ld", &n, &m);
    long i, right = 0, left = n;
    while (right != left && right + 1 != left)
    {
        i = (left + right) / 2;
        long long p = 1;
        for (long k = 0; k < m; k++) // 手动计算 mid^m
        {
            p *= i;
            if (p > n) // 提前终止，防止溢出
            {
                left = i;
                break;
            }
        }
        
        if (p < n)
            right = i;
        else if (p == n)
            break;
        else
            left = i;
    }
    i = (left + right) / 2;
    printf("%ld", i);
    return 0;
}
