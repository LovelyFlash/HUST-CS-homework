#include <bits/stdc++.h>

status SaveGraph(ALGraph G, char FileName[])
// 将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE *fp = fopen(FileName, "w");
    if (fp == NULL)
    {
        return ERROR; // 打开文件失败
    }
    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
        auto *p = G.vertices[i].firstarc;
        while (p != NULL)
        {
            fprintf(fp, "%d ", p->adjvex);
            p = p->nextarc;
        }
        fprintf(fp, "-1\n");
    }
    fprintf(fp, "-1 nil %d %d", G.vexnum, G.arcnum);
    fclose(fp);
    return OK; // 保存成功
    /********** End 1 **********/
}
status LoadGraph(ALGraph &G, char FileName[])
// 读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE *fp = fopen(FileName, "r");
    if (fp == NULL)
    {
        return ERROR; // 打开文件失败
    }
    int i = 0, key;
    char others[20];
    while (fscanf(fp, "%d %s", &key, others) != EOF && key != -1 && strcmp(others, "nil"))
    {
        G.vertices[i].data.key = key;
        strcpy(G.vertices[i].data.others, others);
        G.vertices[i].firstarc = NULL;
        int adjvex;
        while (fscanf(fp, "%d", &adjvex) != EOF && adjvex != -1)
        {
            ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex = adjvex;
            p->nextarc = NULL;
            if (G.vertices[i].firstarc == NULL)
                G.vertices[i].firstarc = p;
            else
            {
                ArcNode *q = G.vertices[i].firstarc;
                while (q->nextarc != NULL)
                {
                    q = q->nextarc;
                }
                q->nextarc = p;
            }
            G.arcnum++;
        }
        i++;
    }
    fscanf(fp, "%d %d", &G.vexnum, &G.arcnum);
    if (G.vexnum < 20)
    {
        G.vertices[G.vexnum].data.key = -1;              // 设置结束标志
        strcpy(G.vertices[G.vexnum].data.others, "nil"); // 设置结束标志
    }
    fclose(fp);
    return OK; // 读入成功
    /********** End 2 **********/
}
