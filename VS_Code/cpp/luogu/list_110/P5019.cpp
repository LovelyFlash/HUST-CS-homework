#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, ans = 0;
    cin >> n;
    int a[n + 1] = {0};
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
    {
        if (a[i] > a[i + 1])
            ans += a[i] - a[i + 1];
    }
    cout << ans;
    return 0;
}