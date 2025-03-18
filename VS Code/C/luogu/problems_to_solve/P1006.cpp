#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    int m, n;
    cin >> m >> n;
    ll dp[m + 1][n + 1][m + 1][n + 1], a[m + 1][n + 1];
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
        }
    }
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= m; k++)
            {
                for (int l = 1; l <= n; l++)
                {
                    dp[i][j][k][l] = max(dp[i - 1][j][k - 1][l], max(dp[i - 1][j][k][l - 1], max(dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l - 1]))) + a[i][j] + a[k][l];
                    if (i == k && j == l)
                        dp[i][j][k][l] -= a[i][j];
                }
            }
        }
    }
    cout << dp[m][n][m][n];
    return 0;
}
