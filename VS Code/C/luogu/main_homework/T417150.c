#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool visited[100][100];

int dps(int **mat, int m, int s, int t);
int minpath(int **mat, int m, int s, int t);

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int **mat = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        mat[i] = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++)
        {
            mat[i][j] = 2;
            visited[i][j] = false;
        }
    }
    int x, y, z;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &z);
        mat[x - 1][y - 1] = z;
    }
    int result = dps(mat, m, 0, 0);
    if (result == -1)
        printf("-1");
    else
    {
        result = minpath(mat, m, 0, 0);
        printf("%d", result);
    }
    return 0;
}

int dps(int **mat, int m, int s, int t)
{
    visited[s][t] = true;
    if (s == m - 1 && t == m - 1)
        return 0;
    else
    {
        if ((mat[s][t] != 2 || mat[s + 1][t] != 2) && !visited[s + 1][t])
            dps(mat, m, s + 1, t);
        else if ((mat[s][t] != 2 || mat[s][t + 1] != 2) && !visited[s][t + 1])
            dps(mat, m, s, t + 1);
        visited[s][t] = false;
        return -1;
    }
}

int minpath(int **mat, int m, int s, int t)
{
    int result = 0;
    if (s == m - 1 && t == m - 1)
        return result;
    else
    {
        result += mat[s][t];
        if (visited[s + 1][t])
            minpath(mat, m, s + 1, t);
        else if (visited[s][t + 1])
            minpath(mat, m, s, t + 1);
    }
}