#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

int main()
{
    ull n;
    cin >> n;
    pair<ull, ull> p[n + 1];
    for (ull i = 0; i < n + 1; i++)
        cin >> p[i].first >> p[i].second;

    sort(p + 1, p + n + 1, [](const pair<ull, ull> a, const pair<ull, ull> b)
         { return a.first * a.second < b.first * b.second; });

    unsigned long long ans = 0, tem = p[0].first;
    for (ull i = 1; i < n + 1; i++)
    {
        ans = max(ans, tem / p[i].second);
        tem = tem * p[i].first % 1000000000;
    }

    cout << ans;
    return 0;
}