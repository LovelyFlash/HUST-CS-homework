// #include <stdio.h>
// #include <math.h>

// int main()
// {
//     long n, m;
//     scanf("%ld %ld", &n, &m);
//     long i, right = 0, left = n;
//     while (right != left && right + 1 != left)
//     {
//         i = (left + right) / 2;
//         long long p = 1;
//         for (long k = 0; k < m; k++) // 手动计算 mid^m
//         {
//             p *= i;
//             if (p > n) // 提前终止，防止溢出
//             {
//                 left = i;
//                 break;
//             }
//         }
        
//         if (p < n)
//             right = i;
//         else if (p == n)
//             break;
//         else
//             left = i;
//     }
//     i = (left + right) / 2;
//     printf("%ld", i);
//     return 0;
// }
#include <stdio.h>

int main()
{
    long n, m;
    scanf("%ld %ld", &n, &m);

    long left = 1, right = n, result = 0;

    while (left <= right)
    {
        long mid = left + (right - left) / 2;
        long long power = 1; // 防止溢出
        int valid = 1;

        for (long i = 0; i < m; i++) // 手动计算 mid^m
        {
            power *= mid;
            if (power > n) // 提前终止，防止溢出
            {
                valid = 0;
                break;
            }
        }

        if (valid && power <= n) // mid^m <= n
        {
            result = mid; // 更新结果
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    printf("%ld", result);
    return 0;
}
