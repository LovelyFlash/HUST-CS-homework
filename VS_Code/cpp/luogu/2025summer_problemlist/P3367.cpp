#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int father[N];
int n, m;

int find(int x)
{
    if (father[x] == x)
        return x;
    else
        return father[x] = find(father[x]);
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        father[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
        {
            x = find(x), y = find(y);
            if (x == y)
                continue;
            father[x] = y;
        }
        else
        {
            x = find(x), y = find(y);
            if (x == y)
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
    }
    return 0;
}
