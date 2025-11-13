#include <bits/stdc++.h>

using namespace std;
using INT = int;

#define int unsigned long long

INT main()
{
    int n, x, ans = 0;
    cin >> n >> x;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%llu", &a[i]);
        if (a[i] > x)
        {
            ans += a[i] - x;
            a[i] = x;
        }
    }

    for (int i = 1; i < n; i++)
        if (a[i] + a[i - 1] > x)
        {
            ans += a[i] + a[i - 1] - x;
            a[i] = x - a[i - 1];
        }

    cout << ans;
    return 0;
}