#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> dp(n, vector<int>(2, 0));
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++)
    {
        if (a[i] < a[dp[i - 1][0]])
        {
            dp[i][0] = i;
            dp[i][1] = i;
        }
        else if (a[i] > a[dp[i - 1][1]])
            dp[i][1] = i;
        else
        {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = dp[i - 1][1];
        }
    }
    for (int i = 0; i < n; i++)
        a[i] = dp[i][1] - dp[i][0];
    int ans = -1;
    for (int i = 0; i < n; i++)
        if (a[i] > ans)
            ans = a[i];
    if (ans)
        cout << ans + 1;
    else
        cout << 0;
    return 0;
}