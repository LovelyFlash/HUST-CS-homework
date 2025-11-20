#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, t;
    cin >> n;
    map<int, int> a;
    for (int i = 0; i < n; i++)
    {
        cin >> t;
        ++a[t];
    }

    int ans = n;
    while (!a.empty())
    {
        int man = 1, first = a.begin()->first;
        while (a[first + 1] >= a[first])
        {
            ++man;
            --a[first];
            ++first;
        }
        --a[first];
        if (man < ans)
            ans = man;
        while (a.begin()->second == 0 && !a.empty())
            a.erase(a.begin());
    }

    cout << ans;
    return 0;
}
