#include <bits/stdc++.h>
using namespace std;

const int N = 5100, M = 2e5 + 100;

int n, m, fa[N], cnt, sum;

struct node
{
    int x, y, z;
} a[M];

bool cmp(node a1, node a2)
{
    return a1.z < a2.z;
}

int set_find(int dx)
{
    return dx == fa[dx] ? dx : fa[dx] = set_find(fa[dx]);
}

void set_merge(int dx, int dy)
{
    int gx = set_find(dx), gy = set_find(dy);
    if (gx != gy)
        fa[gx] = gy;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
        cin >> a[i].x >> a[i].y >> a[i].z;
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= m; i++)
    {
        if (set_find(a[i].x) != set_find(a[i].y))
        {
            set_merge(a[i].x, a[i].y);
            cnt++, sum += a[i].z;
        }
        if (cnt == n - 1)
            break;
    }
    cnt < n - 1 ? cout << "orz" : cout << sum;
    return 0;
}
