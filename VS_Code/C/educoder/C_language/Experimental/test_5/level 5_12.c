/*
任务描述
实验指导书 P144 程序设计第（11）题
本关任务：迷宫问题。编程找出从入口（左上角方格）经过迷宫到达出口（右下角方格）的所有路径，迷宫问题示意如下方数字阵列所示，0所表示的地方是不可以通行的，只能从1走到与它相邻（四邻域：上、下、左、右相邻）的1上，且不能走重复路径。
迷宫问题示意图：
1 0 0 0 0 0 0 0 0 0
1 0 1 1 0 1 1 1 1 0
1 1 1 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1

本任务由键盘输入迷宫的行数和列数，以及迷宫的图案。

示例
输入：(前两位数字分别为迷宫的行数和列数)
6 10
1 0 0 0 0 0 0 0 0 0
1 0 1 1 0 1 1 1 1 0
1 1 1 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1
输出（解的编号、路径）：
1
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 1 1 1 0 0 0 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1
2
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 1 1 1 0
1 0 0 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1 1
3
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 1 1 1 1 0
1 0 0 0 0 1 0 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1 1

开始你的任务吧，祝你成功！
*/
#include <stdio.h>

#define MAX 100

// 迷宫的行数和列数
int maze[MAX][MAX];
int visited[MAX][MAX]; // 记录访问过的方格
int path[MAX][MAX];    // 存储当前路径
int count = 0;         // 路径计数

void printMaze(int n, int m)
{
    // 输出当前路径
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (path[i][j])
            {
                printf("1"); // 如果在路径中，输出 1
                if (j != m - 1)
                    printf(" ");
            }
            else
            {
                printf("0"); // 否则输出 0
                if (j != m - 1)
                    printf(" ");
            }
        }
        printf("\n");
    }
}

void dfs(int x, int y, int n, int m)
{
    // 如果到达右下角
    if (x == n - 1 && y == m - 1)
    {
        count++;
        // printf("%d\n", count);
        printMaze(n, m); // 输出当前路径
        // printf("\n");
        return;
    }

    // 四个方向
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // 遍历四个方向
    for (int i = 0; i < 4; i++)
    {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];

        // 检查新位置是否在范围内且可通行
        if (newX >= 0 && newX < n && newY >= 0 && newY < m && maze[newX][newY] == 1 && !visited[newX][newY])
        {
            visited[newX][newY] = 1; // 标记为已访问
            path[newX][newY] = 1;    // 加入路径

            dfs(newX, newY, n, m); // 递归

            // 回溯
            visited[newX][newY] = 0;
            path[newX][newY] = 0;
        }
    }
}

int main()
{
    int n, m;
    // 输入迷宫的行数和列数
    scanf("%d %d", &n, &m);

    // 输入迷宫
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &maze[i][j]);
        }
    }

    // 初始化访问记录
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            visited[i][j] = 0;
            path[i][j] = 0; // 初始化路径
        }
    }

    // 从入口开始搜索路径
    if (maze[0][0] == 1)
    {
        visited[0][0] = 1; // 标记入口为已访问
        path[0][0] = 1;    // 加入路径
        dfs(0, 0, n, m);   // 从(0, 0)开始搜索
    }
    else
    {
        printf("不可通行\n");
    }

    return 0;
}