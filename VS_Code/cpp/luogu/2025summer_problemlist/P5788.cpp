#include <bits/stdc++.h>
using namespace std;

int main()
{
    stack<int> s;
    long long n;
    cin >> n;
    long long ans[3000005] = {0}, num[3000005] = {0};
    for (int i = 0; i < n; i++)
        cin >> num[i];
    for (int i = n - 1; i > -1; i--)
    {
        while (!s.empty() && num[s.top()] <= num[i])
            s.pop();
        if (s.empty())
            ans[i] = 0;
        else
            ans[i] = s.top() + 1;
        s.push(i);
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
    return 0;
}