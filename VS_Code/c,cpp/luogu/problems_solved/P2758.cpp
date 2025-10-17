#include <bits/stdc++.h>
using namespace std;
int main()
{
    char a[2005], b[2005];
    cin >> a >> b;
    int la = strlen(a), lb = strlen(b);
    int dp[la + 1][lb + 1];
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= la; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 0; j <= lb; j++)
    {
        dp[0][j] = j;
    }
    // dp[1][1]=a[0]==b[0]?0:1;
    for (int i = 1; i <= la; i++)
    {
        for (int j = 1; j <= lb; j++)
        {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            else
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
            dp[i][j] = min(dp[i][j], min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
        }
    }
    cout << dp[la][lb];
    return 0;
}
