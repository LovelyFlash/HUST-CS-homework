void free0(void *p);

status DeleteVex(ALGraph &G, KeyType v)
// 在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (G.vexnum == 1)
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            ArcNode *p = G.vertices[i].firstarc;
            while (p != NULL)
            {
                ArcNode *q = p;
                p = p->nextarc;
                free0(q);
            }
            for (int j = i; j < G.vexnum - 1; j++)
            {
                G.vertices[j] = G.vertices[j + 1];
            }
            for (int j = 0; j < G.vexnum - 1; j++)
            {
                if (G.vertices[j].firstarc != NULL)
                {
                    ArcNode *p = G.vertices[j].firstarc;
                    ArcNode *q = NULL;
                    while (p != NULL)
                    {
                        if (p->adjvex == i)
                        {
                            if (q == NULL)
                            {
                                G.vertices[j].firstarc = p->nextarc;
                                G.arcnum--;
                            }
                            else
                            {
                                q->nextarc = p->nextarc;
                                G.arcnum--;
                            }
                            free0(p);
                            break;
                        }
                        q = p;
                        p = p->nextarc;
                    }
                    ArcNode *p2 = G.vertices[j].firstarc;
                    ArcNode *q2 = NULL;
                    while (p2 != NULL)
                    {
                        if (p2->adjvex > i)
                            p2->adjvex--;
                        q2 = p2;
                        p2 = p2->nextarc;
                    }
                }
            }
            G.vexnum--;
            return OK;
        }
    }
    return ERROR;
    /********** End **********/
}