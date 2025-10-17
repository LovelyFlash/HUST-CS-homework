void DFS(ALGraph &G, int v, void (*visit)(VertexType), int *visited);

status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
// 对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
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
            DFS(G, i, visit, visited); // 调用辅助函数进行深度优先搜索
        }
    }

    free(visited); // 释放动态分配的内存
    return OK;
    /********** End **********/
}

void DFS(ALGraph &G, int v, void (*visit)(VertexType), int *visited)
// 辅助函数：递归实现深度优先搜索
{
    visited[v] = 1;            // 标记当前顶点为已访问
    visit(G.vertices[v].data); // 访问当前顶点

    ArcNode *p = G.vertices[v].firstarc;
    while (p != NULL)
    {
        if (visited[p->adjvex] == 0)
        {
            DFS(G, p->adjvex, visit, visited); // 递归访问未访问的邻接顶点
        }
        p = p->nextarc;
    }
}