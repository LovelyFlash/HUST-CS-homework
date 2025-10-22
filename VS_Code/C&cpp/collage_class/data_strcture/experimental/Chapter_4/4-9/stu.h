status InsertArc(ALGraph &G, KeyType v, KeyType w)
// 在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            ArcNode *tmp = G.vertices[i].firstarc;
            while (tmp != NULL)
            {
                if (G.vertices[tmp->adjvex].data.key == w)
                {
                    return ERROR;
                }
                tmp = tmp->nextarc;
            }
            for (int j = 0; j < G.vexnum; j++)
            {
                if (G.vertices[j].data.key == w)
                {
                    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
                    p->adjvex = j;
                    p->nextarc = G.vertices[i].firstarc;
                    G.vertices[i].firstarc = p;
                    ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
                    q->adjvex = i;
                    q->nextarc = G.vertices[j].firstarc;
                    G.vertices[j].firstarc = q;
                    G.arcnum++;
                    return OK;
                }
            }
        }
    }
    return ERROR;
    /********** End **********/
}