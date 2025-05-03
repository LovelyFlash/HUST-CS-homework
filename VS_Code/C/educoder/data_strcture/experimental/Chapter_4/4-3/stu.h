int LocateVex(ALGraph G, KeyType u)
// 根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = 0;
    for (i = 0; i <= G.vexnum; i++)
    {
        if (i == G.vexnum)
            break;
        VNode *p = &G.vertices[i];
        if (p->data.key == u)
            break;
    }

    if (i >= G.vexnum)
        return -1;
    else
        return i;
    /********** End **********/
}
