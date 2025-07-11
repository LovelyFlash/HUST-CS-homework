#include <bits/stdc++.h>
using namespace std;

int main()
{
    stack<int> s;
    int n, count = 0, i;
    cin >> n;
    int pos[n] = {0}, num[n] = {0};
    for (int i = 0; i < n; i++)
        cin >> num[i];
    for (int i = 0; i < n; i++)
    {
        if (s.empty())
            s.push(i);
        while (!s.empty() && num[s.top()] < num[i])
            s.pop();
        pos[i] = s.top();
        s.push(i);
    }
}