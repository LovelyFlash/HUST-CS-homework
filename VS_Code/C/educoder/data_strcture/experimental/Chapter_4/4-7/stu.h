status InsertVex(ALGraph &G, VertexType v)
// 在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v.key)
            return ERROR;
    }
    if (G.vexnum >= MAX_VERTEX_NUM)
        return ERROR;

    G.vertices[G.vexnum] = *(VNode *)malloc(sizeof(VNode));
    if (G.vertices == NULL)
        return ERROR;
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
    /********** End **********/
}
