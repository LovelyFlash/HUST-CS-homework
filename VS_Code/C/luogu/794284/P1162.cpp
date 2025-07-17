#include <bits/stdc++.h>
using namespace std;

void bfs(int x, int y, vector<vector<int>> &a, vector<vector<int>> &visited)
{
    queue<pair<int, int>> q;
    if (a[x][y] == 0 && !visited[x][y])
        q.push({x, y});
    visited[x][y] = 1;
    while (!q.empty())
    {
        auto [cx, cy] = q.front();
        q.pop();
        // 四个方向都要扩展
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        for (int d = 0; d < 4; d++)
        {
            int nx = cx + dx[d], ny = cy + dy[d];
            if (nx >= 0 && nx < a.size() && ny >= 0 && ny < a[0].size() && !visited[nx][ny] && a[nx][ny] == 0)
            {
                visited[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> visited(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        bfs(0, i, a, visited);
        bfs(i, 0, a, visited);
        bfs(n - 1, i, a, visited);
        bfs(i, n - 1, a, visited);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == 0 && !visited[i][j])
            {
                a[i][j] = 2;
            }
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}