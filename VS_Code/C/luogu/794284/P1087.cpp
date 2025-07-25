#include <bits/stdc++.h>
using namespace std;

string s;
int n;
void solve(int l, int r)
{
    int mid = (l + r) / 2, c0 = 0, c1 = 0;
    if (l != r)
        solve(l, mid), solve(mid + 1, r);
    for (int i = l; i <= r; i++)
    {
        if (s[i] == '0')
            c0++;
        else
            c1++;
    }
    if (c0 && c1)
        cout << 'F';
    else if (c0)
        cout << 'B';
    else
        cout << 'I';
}

int main()
{
    cin >> n >> s, solve(0, pow(2, n) - 1);
}