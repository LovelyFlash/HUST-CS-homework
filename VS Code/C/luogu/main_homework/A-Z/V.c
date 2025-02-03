#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_M 100
typedef struct
{
    int x, y;
    int cost;
    int magic; // 0: 未使用魔法，1: 刚使用魔法到达当前格子（无法再次使用）
} State;

int mat[MAX_M][MAX_M];
int minCost[MAX_M][MAX_M][2]; // [x][y][magic_used], 存储到达该状态的最小花费
int m;

int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 优先队列实现
State heap[MAX_M * MAX_M * 2];
int heapSize = 0;

void push(State state)
{
    int i = heapSize++;
    while (i > 0)
    {
        int p = (i - 1) / 2;
        if (heap[p].cost <= state.cost)
            break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = state;
}

State pop()
{
    State ret = heap[0];
    State x = heap[--heapSize];
    int i = 0;
    while (i * 2 + 1 < heapSize)
    {
        int a = i * 2 + 1, b = i * 2 + 2;
        if (b < heapSize && heap[b].cost < heap[a].cost)
            a = b;
        if (heap[a].cost >= x.cost)
            break;
        heap[i] = heap[a];
        i = a;
    }
    heap[i] = x;
    return ret;
}

void initMinCost()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            minCost[i][j][0] = minCost[i][j][1] = INT_MAX;
        }
    }
}

int dijkstra()
{
    initMinCost();
    if (mat[0][0] == 2)
        return -1; // 起点无色，但题目保证有颜色
    minCost[0][0][0] = 0;
    push((State){0, 0, 0, 0});

    while (heapSize > 0)
    {
        State curr = pop();
        if (curr.x == m - 1 && curr.y == m - 1)
        {
            return curr.cost;
        }
        if (curr.cost > minCost[curr.x][curr.y][curr.magic])
            continue;

        for (int d = 0; d < 4; d++)
        {
            int nx = curr.x + dirs[d][0];
            int ny = curr.y + dirs[d][1];
            if (nx < 0 || nx >= m || ny < 0 || ny >= m)
                continue;

            int currColor = mat[curr.x][curr.y];
            if (curr.magic == 1)
            {
                // 当前处于魔法状态，无法再次使用魔法，必须移动到有颜色的格子
                if (mat[nx][ny] == 2)
                    continue;
                int nextColor = mat[nx][ny];
                int cost = (currColor != nextColor) ? 1 : 0;
                int total = curr.cost + cost;
                if (total < minCost[nx][ny][0])
                {
                    minCost[nx][ny][0] = total;
                    push((State){nx, ny, total, 0});
                }
            }
            else
            {
                // 正常移动或使用魔法
                if (mat[nx][ny] != 2)
                {
                    // 目标格子有颜色，正常移动
                    int nextColor = mat[nx][ny];
                    int cost = (currColor != nextColor) ? 1 : 0;
                    int total = curr.cost + cost;
                    if (total < minCost[nx][ny][0])
                    {
                        minCost[nx][ny][0] = total;
                        push((State){nx, ny, total, 0});
                    }
                }
                else
                {
                    // 目标格子无色，必须使用魔法
                    // 选择颜色与当前格子相同，避免花费
                    int cost = 2;
                    int total = curr.cost + cost;
                    if (total < minCost[nx][ny][1])
                    {
                        minCost[nx][ny][1] = total;
                        push((State){nx, ny, total, 1});
                    }
                }
            }
        }
    }
    return -1;
}

int main()
{
    int n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mat[i][j] = 2; // 初始化为无色
        }
    }
    for (int i = 0; i < n; i++)
    {
        int x, y, c;
        scanf("%d %d %d", &x, &y, &c);
        mat[x - 1][y - 1] = c;
    }

    int result = dijkstra();
    printf("%d\n", result);
    return 0;
}