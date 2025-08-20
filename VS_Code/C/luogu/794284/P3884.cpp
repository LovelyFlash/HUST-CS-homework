#include <bits/stdc++.h>
using namespace std;

int n, m, fa[1005], de[1005], tot, head[1005], s, kuan, shen, pika[1005];

struct node
{
    int to, next;
} edge[1005];

void add(int u, int v)
{
    edge[++tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot;
}
void dfs(int x, int fath)
{
    fa[x] = fath;
    de[x] = de[fath] + 1;
    for (int i = head[x]; i; i = edge[i].next)
    {
        if (edge[i].to != fath)
        {
            dfs(edge[i].to, x);
        }
    }
}
int getlca(int x, int y)
{
    while (x != y)
    {
        if (de[x] >= de[y])
        {
            x = fa[x];
        }
        else
            y = fa[y];
    }
    return x;
}
int getdis(int x, int y)
{
    return (de[x] - de[getlca(x, y)]) * 2 + de[y] - de[getlca(x, y)];
}
int main()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
    {
        shen = max(de[i], shen);
        pika[de[i]]++;
    }
    for (int i = 1; i <= shen; i++)
    {
        kuan = max(kuan, pika[i]);
    }
    int u, v;
    cin >> u >> v;
    cout << shen << endl
         << kuan << endl
         << getdis(u, v) << endl;
    return 0;
}