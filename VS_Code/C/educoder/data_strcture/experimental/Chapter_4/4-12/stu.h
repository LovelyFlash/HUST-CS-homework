#include <bits/stdc++.h>

using namespace std;

int FindNum(ALGraph &G, VNode v);

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
    int first = 0;
    while (first != G.vexnum)
    {
        for (first = 0; first < G.vexnum && visited[first]; first++)
            ;
        if (first == G.vexnum)
            break;
        q.push(G.vertices[first]);
        visited[first] = 1;
        while (!q.empty())
        {
            auto tmp = q.front();
            q.pop();
            int j = FindNum(G, tmp);
            visit(G.vertices[j].data);
            auto p = tmp.firstarc;
            while (p != nullptr)
            {
                if (visited[p->adjvex])
                {
                    p = p->nextarc;
                    continue;
                }
                q.push(G.vertices[p->adjvex]);
                visited[p->adjvex] = 1;
                p = p->nextarc;
            }
        }
    }
    free(visited); // 释放内存
    return OK;     // 遍历成功
    /********** End **********/
}

int FindNum(ALGraph &G, VNode v)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v.data.key)
            return i;
    }
    return -1; // 未找到
}
