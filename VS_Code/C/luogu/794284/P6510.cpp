#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<unsigned long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    stack<int> s;
    int ans = 0;
    int left[n], right[n];
    for (int i = n - 1; i >= 0; i--)
    {
        while (!s.empty() && a[s.top()] > a[i])
            s.pop();
        right[i] = s.empty() ? n : s.top();
        s.push(i);
    }
    while (!s.empty())
        s.pop();
    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && a[s.top()] < a[i])
            s.pop();
        left[i] = s.empty() ? -1 : s.top();
        s.push(i);
        for (int j = left[i]; j < i; j++)
        {
            if (j == -1)
                j++;
            if (i < right[j])
                ans = max(ans, (i - j + 1));
        }
    }

    cout << (ans == 1 ? 0 : ans);
    return 0;
}