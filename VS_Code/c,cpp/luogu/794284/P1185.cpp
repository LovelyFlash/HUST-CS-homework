#include <bits/stdc++.h>
using namespace std;

int m, n, width, height, node_num = 0, x, y;

int main()
{
    cin >> m >> n;
    width = pow(2, m - 2) * 6 - 1, height = width / 2 + 1;
    char graph[height][width];
    memset(graph, ' ', width * height);
    for (int i = 0; i < width;)
    {
        node_num++;
        graph[height - 1][i] = 'o';
        if (node_num % 2)

            i += 4;

        else
            i += 2;
    }
    for (int i = height - 2; i >= 0; i--)
    {
        node_num = 0;
        for (int j = height - i - 2; j < width - (height - i - 2); j++)
        {
            if (graph[i + 1][j] == 'o')
            {
                if (node_num % 2)
                    graph[i][j - 1] = '\\';
                else
                    graph[i][j + 1] = '/';
                node_num++;
            }
            if (graph[i + 1][j + 1] == '\\' && graph[i + 1][j - 1] == '/')
                graph[i][j] = 'o';
            else if (graph[i + 1][j - 1] == '/')
                graph[i][j] = '/';
            else if (graph[i + 1][j + 1] == '\\')
                graph[i][j] = '\\';
        }
    }
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        if (x != m)
        {
            x = 3 * pow(2, m - x - 1);

            int center = (2 * y - 1) * (x - 1) + 2 * y - 2;
            for (int t = height - 2 * x + 1; t < height; t++)
            {
                for (int k = center - x + 1; k < center + x; k++)
                    if (graph[t][k] != ' ')
                        graph[t][k] = ' ';
            }
        }
        else
        {
            if (y % 2)
            {
                y = 6 * (y / 2);
                graph[height - 1][y] = ' ';
                graph[height - 2][y + 1] = ' ';
            }
            else
            {
                y = 4 + 6 * (y / 2 - 1);
                graph[height - 1][y] = ' ';
                graph[height - 2][y - 1] = ' ';
            }
        }
    }
    for (int i = 0.; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            cout << graph[i][j];
        cout << endl;
    }
    return 0;
}