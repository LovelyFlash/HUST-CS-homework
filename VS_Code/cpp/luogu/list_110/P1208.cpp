#include <bits/stdc++.h>

using namespace std;

int main()
{
    long n, m, x, y, ans = 0;
    cin >> n >> m;
    map<long, long> mp;
    for (long i = 0; i < m; i++)
    {
        cin >> x >> y;
        mp[x] += y;
    }
    for (pair<long, long> i : mp)
    {
        if (n <= 0)
            break;
        ans += (i.first) * min(n, i.second);
        n -= i.second;
    }
    cout << ans;
    return 0;
}