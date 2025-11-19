#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    vector<int> man;
    int ans = n;
    for (int i = 1, j = 1; i < n; i++)
    {
        if (a[i] == a[i - 1] + 1)
            ++j;
        else
        {
            man.push_back(j);
            j = 1;
        }
    }
    for (int i : man)
        if (i < ans)
            ans = i;
    cout << ans;
    return 0;
}