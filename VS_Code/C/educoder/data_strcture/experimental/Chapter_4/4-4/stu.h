status PutVex(ALGraph &G, KeyType u, VertexType value)
// 根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
// 如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = 0, flag = OK;
    for (i = 0; i <= G.vexnum; i++)
    {
        if (i == G.vexnum)
            break;
        VNode *p = &G.vertices[i];
        if (p->data.key != u && p->data.key == value.key)
        {
            flag = ERROR;
            break;
        }
    }

    if (flag == OK)
    {
        flag = ERROR;
        for (i = 0; i < G.vexnum; i++)
        {
            if (G.vertices[i].data.key == u)
            {
                G.vertices[i].data = value;
                flag = OK;
                break;
            }
        }
    }

    if (flag == OK)
        return OK;
    else
        return ERROR;
    /********** End **********/
}
