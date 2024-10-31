#include <stdio.h>

int digit(long n, int k)
{
    int i;
    if(n == 0 && k == 1) return 0;
    for (i = 0; n > 0 && i < k; i++) {
        if (i == k - 1)  // 找到第 k 位
            return n % 10;
        n /= 10;  // 去掉最后一位
    }
    return -1;  // 若 k 超出范围则返回 -1
}
