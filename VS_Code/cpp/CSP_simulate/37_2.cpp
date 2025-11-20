#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int n, m;
    // 输入总苹果数（背包容量）n 和 投喂方式数量 m
    cin >> n >> m;

    vector<int> A(m);
    // 输入m个整数，代表每种投喂方式对应的收益(物品的重量为i+1,价值为A[i])
    for (int i = 0; i < m; i++)
        cin >> A[i];

    // 创建 dp 数组，初始化为 0， dp[i] 代表容量为 i 时的最大价值
    vector<int> dp(n + 1, 0);

    // 遍历每个投喂方式(物品)
    for (int i = 0; i < m; i++)
        // 遍历容量，从当前投喂方式的数量开始，直到容量为 n
        // 这里 i+1 表示的是当前投喂方式对应的苹果数，因为 A[i] 代表每种方式的收益（苹果数）
        for (int j = i + 1; j <= n; j++)
            // 计算在当前容量下能获得的最大价值
            dp[j] = max(dp[j], dp[j - (i + 1)] + A[i]);

    // 输出最大值，即 dp[n]，代表容量为 n 时的最大快乐值
    cout << dp[n] << endl;

    return 0;
}
