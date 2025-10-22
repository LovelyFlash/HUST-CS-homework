#include <stdio.h>
#include <limits.h> // 提供 LLONG_MAX

// 替代宏定义，使用内联函数
long long num(long long x, long long y) {
    return (x > y) ? (x - y) : (y - x);
}

int main() {
    long long n, m, p1, s1, s2, p2, t = LLONG_MAX;
    scanf("%lld", &n);

    long long war[n];
    for (long long i = 0; i < n; i++)
        scanf("%lld", &war[i]);

    scanf("%lld %lld %lld %lld", &m, &p1, &s1, &s2);

    // 计算 sum1 和 sum2
    long long sum1 = 0, sum2 = 0;
    for (long long i = 0; i < m - 1; i++)
        sum1 += num(i + 1, m) * war[i];
    if (p1 < m)
        sum1 += num(p1, m) * s1;
    else if (p1 > m)
        sum2 += num(p1, m) * s1;
    for (long long i = m; i < n; i++)
        sum2 += num(i + 1, m) * war[i];

    // 寻找最优位置 p2
    for (long long i = 0; i < n; i++) {
        long long w;
        if (i + 1 < m)
            w = num(sum1 + s2 * num(i + 1, m), sum2);
        else if (i + 1 > m)
            w = num(sum1, sum2 + s2 * num(i + 1, m));
        else
            w = num(sum1, sum2);

        if (w < t) {
            t = w;
            p2 = i + 1;
        }
    }

    // 输出结果
    printf("%lld\n", p2);
    return 0;
}
