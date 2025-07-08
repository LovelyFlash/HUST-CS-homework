#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < p; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        for (int j = x - 1; j < y; j++)
        {
            a[j] += z;
        }
    }
    int result = 0x7fffffff;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < result)
        {
            result = a[i];
        }
    }
    cout << result;
    return 0;
}