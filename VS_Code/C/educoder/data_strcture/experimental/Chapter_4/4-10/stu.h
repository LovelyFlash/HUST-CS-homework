void free0(void *p);

status DeleteArc(ALGraph &G, KeyType v, KeyType w)
// 在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    static int flag = 0;
    if (G.vexnum == 0 || G.arcnum == 0)
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            ArcNode *p = G.vertices[i].firstarc;
            ArcNode *q = NULL;
            while (p != NULL)
            {
                if (G.vertices[p->adjvex].data.key == w)
                {
                    if (q == NULL)
                        G.vertices[i].firstarc = p->nextarc;
                    else
                        q->nextarc = p->nextarc;
                    free0(p);
                    flag++;
                    break;
                }
                q = p;
                p = p->nextarc;
            }
            if (flag == 1 || flag == 2)
                break;
        }
    }
    if (flag == 1)
    {
        DeleteArc(G, w, v);
        return OK;
    }
    else if (flag == 2)
    {
        G.arcnum--;
        return OK;
    }
    else
        return ERROR;
    /********** End **********/
}