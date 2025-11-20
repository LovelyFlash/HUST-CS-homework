#include <bits/stdc++.h>

using namespace std;

int main()
{
    int w, n, ans = 0, tem = 0;
    cin >> w >> n;
    int p[n];
    for (int i = 0; i < n; ++i)
        cin >> p[i];
    sort(p, p + n);
    for (int i = 0, j = n - 1; i <= j; ++i, --j)
    {
        if (i == j)
        {
            ++ans;
            break;
        }
        if (p[i] + p[j] <= w)
            ++ans;
        else
            ++ans, --i;
    }
    cout << ans;
    return 0;
}