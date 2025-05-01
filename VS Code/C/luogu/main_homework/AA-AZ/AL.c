#include <stdio.h>

int main()
{
    long long n, m, c = 1;
    scanf("%lld %lld", &n, &m);
    int a[n], b[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        c *= a[i];
    }
    c /= a[n - 1];
    for (int i = n - 2; i >= 0; c /= a[i], i--)
    {
        b[i + 1] = m / c;
        m %= c;
    }
    b[0] = m;
    for (int i = 0; i < n; i++)
    {
        printf("%d", b[i]);
        if (i != n - 1)
            putchar(' ');
    }
    return 0;
}