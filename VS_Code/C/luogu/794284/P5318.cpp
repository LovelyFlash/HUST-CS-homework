#include <bits/stdc++.h>
using namespace std;

int m, n;

struct Graph
{
    int num;
    vector<Graph *> next;
};

void dfs(Graph *G, int *visited)
{
    cout << G->num << ' ';
    sort(G->next.begin(), G->next.end(), [](Graph *a, Graph *b)
         { return a->num < b->num; });
    for (int i = 0; i < G->next.size(); i++)
        if (!visited[G->next[i]->num - 1])
        {
            visited[G->next[i]->num - 1] = 1;
            dfs(G->next[i], visited);
        }
}

int main()
{
    cin >> n >> m;
    Graph G[n];
    int visited[n];
    memset(G, 0, n * sizeof(Graph));
    memset(visited, 0, n * sizeof(int));
    for (int i = 0; i < n; i++)
        G[i].num = i + 1;
    visited[0] = 1;
    for (int i = 0; i < m; i++)
    {
        int x, y, j;
        cin >> x >> y;
        G[x - 1].next.push_back(&G[y - 1]);
    }

    dfs(G, visited);
    cout << endl;
    // bfs
    queue<Graph *> q;
    memset(visited, 0, n * sizeof(int));
    q.push(&G[0]);
    while (!q.empty())
    {
        Graph *tmp = new Graph;
        tmp = q.front();
        q.pop();
        if (visited[tmp->num - 1])
            continue;
        visited[tmp->num - 1] = 1;

        cout << tmp->num << ' ';
        for (int i = 0; i < tmp->next.size(); i++)
            q.push(tmp->next[i]);
    }
    return 0;
}