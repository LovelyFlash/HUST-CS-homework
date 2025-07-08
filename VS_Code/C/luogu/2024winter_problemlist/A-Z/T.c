#include <stdio.h>

void dfs(int task[], int taskCount[], int n, int current, int graph[n][n])
{
    if (taskCount[current])
        return;             // 如果这个任务已经被计算过了，直接返回
    taskCount[current] = 1; // 标记当前任务已完成
    for (int i = 0; i < n; i++)
    {
        if (graph[i][current] == 1) // 任务i依赖于当前任务
        {
            dfs(task, taskCount, n, i, graph); // 递归计算任务i
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int graph[n][n];      // 邻接矩阵
    int taskCount[n];     // 标记任务是否完成

    for (int i = 0; i < n; i++)
    {
        taskCount[i] = 0; // 初始化所有任务的计数为0
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = 0; // 初始化任务依赖关系
        }
    }

    // 读取任务依赖关系
    for (int i = 0; i < n; i++)
    {
        int ci;
        scanf("%d", &ci);
        for (int j = 0; j < ci; j++)
        {
            int x;
            scanf("%d", &x);
            graph[x - 1][i] = 1; // 任务x依赖任务i，注意编号是从1开始的，所以需要减1
        }
    }

    // 计算任务1的依赖任务数量
    int result = 0;
    dfs(taskCount, taskCount, n, 0, graph); // 从任务1开始，索引是0

    // 计算至少需要完成的任务数
    for (int i = 0; i < n; i++)
    {
        if (taskCount[i])
        {
            result++;
        }
    }

    printf("%d\n", result); // 输出至少需要完成的任务数
    return 0;
}
