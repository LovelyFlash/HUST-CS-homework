int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = 0, flag = ERROR,res=0;

    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            res = G.vertices[i].firstarc->adjvex;
            flag = OK;
            break;
        }
    }

    if(flag == OK)
    {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL)
        {
            if (G.vertices[p->adjvex].data.key == w)
            {
                if (p->nextarc != NULL)
                    return p->nextarc->adjvex;
                else
                    return -1;
            }
            p = p->nextarc;
        }
    }

    return -1;

    /********** End **********/
}
