#include <bits/stdc++.h>

using namespace std;
void BFS(ALGraph &G, int v, void (*visit)(VertexType), int *visited);
status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
// 对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int *visited = (int *)malloc(G.vexnum * sizeof(int)); // 动态分配 visited 数组
    if (visited == NULL)
    {
        return ERROR; // 分配失败
    }

    for (int i = 0; i < G.vexnum; i++)
    {
        visited[i] = 0; // 初始化为未访问
    }

    for (int i = 0; i < G.vexnum; i++)
    {
        if (visited[i] == 0)
        {
            BFS(G, i, visit, visited); // 调用辅助函数进行深度优先搜索
        }
    }

    free(visited); // 释放动态分配的内存
    return OK;
    /********** End **********/
}

void BFS(ALGraph &G, int v, void (*visit)(VertexType), int *visited)
{
    visited[v] = 1;            // 标记当前顶点为已访问
    visit(G.vertices[v].data); // 访问当前顶点

    queue<VNode> q;
    q.push(G.vertices[v]);

}