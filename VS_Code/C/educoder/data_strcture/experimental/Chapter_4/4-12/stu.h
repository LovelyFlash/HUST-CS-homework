#include <bits/stdc++.h>

using namespace std;
status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
// 对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int *visited = (int *)malloc(G.vexnum * sizeof(int));
    if (visited == NULL)
    {
        return ERROR; // 分配失败
    }

    for (int i = 0; i < G.vexnum; i++)

        visited[i] = 0; // 初始化为未访问

    queue<VNode> q;
    q.push(G.vertices[0]);
    visit[0] = 1;
    while (!q.empty())
    {
        auto tmp = q.front();
        q.pop();
        int j = FindNum(G, tmp);
        visit(G.vertices[j].data);
        auto p = tmp.FirstAdjVex;
        while (p != nullptr)
        {
            if (visited[p.adjvex])
                continue;
            q.push(G.vertices[p.adjvex]);
            visited[p.adjvex] = 1;
            p = p.nextarc;
        }
    }
    /********** End **********/
}

int FindNum(ALGraph &G; VNode v)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].key == v.key)
            return i;
    }
}
