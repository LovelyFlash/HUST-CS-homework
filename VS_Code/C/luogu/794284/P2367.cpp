#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = n; i > 0; i--)
        a[i] -= a[i - 1];
    for (int i = 0; i < p; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        a[x - 1] += z;
        if (y < n)
            a[y] -= z;
    }
    int result = 0x7fffffff;
    for (int i = 0; i < n; i++)
    {
        a[i] += (i > 0 ? a[i - 1] : 0);
        result = min(result, a[i]);
    }
    cout << result;
    return 0;
}