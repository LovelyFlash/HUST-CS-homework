#include <bits/stdc++.h>

#define ull unsigned long long

using namespace std;

int main()
{
    int n;
    ull ans = 0;
    cin >> n;
    int h[n + 1] = {0};
    for (int i = 1; i < n + 1; i++)
        cin >> h[i];
    sort(h, h + n + 1);
    for (int i = 0; i < (n + 1) / 2; i++)
    {
        ans += (h[i] - h[n - i]) * (h[i] - h[n - i]);
        ans += (h[i + 1] - h[n - i]) * (h[i + 1] - h[n - i]);
    }
    cout << ans;
    return 0;
}