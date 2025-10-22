#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int a[m];
    for (int i = 0; i < m; i++)
        cin >> a[i];
    int dp[n];
    for (int i = 0; i < n; i++)
        dp[i] = 0;
    for (int i = n - 1; i >= n - m; i--)
        dp[i] = a[n - i - 1];
    for (int i = n - m - 1; i >= 0; i--)
    {
        int max = dp[i];
        for (int j = 0; j < m; j++)
        {
            if (dp[i + j + 1] + a[j] > max)
                max = dp[i + j + 1] + a[j];
        }
        dp[i] = max;
    }
    cout << dp[0];
}