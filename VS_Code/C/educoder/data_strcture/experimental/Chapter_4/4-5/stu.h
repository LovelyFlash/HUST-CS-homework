int FirstAdjVex(ALGraph G, KeyType u)
// 根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = 0, flag = ERROR,res=0;

    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
        {
            res = G.vertices[i].firstarc->adjvex;
            flag = OK;
            break;
        }
    }

    if (flag == OK)
        return res;
    else
        return -1;
    /********** End **********/
}
