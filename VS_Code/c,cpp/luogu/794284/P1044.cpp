#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    long long a[19] = {0};
    a[0] = 1;
    a[1] = 1;
    a[2] = 2;
    for (int i = 3; i <= 18; i++)
    {
        for (int j = 0; j < i; j++)
        {
            a[i] += a[j] * a[i - j -1];
        }
    }
    cout << a[n];
    return 0;
}