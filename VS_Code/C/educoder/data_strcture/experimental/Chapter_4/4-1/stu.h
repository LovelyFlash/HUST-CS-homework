status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    // 初始化图
    G.vexnum = 0;
    G.arcnum = 0;

    // 创建顶点表
    for (int i = 0; V[i].key != -1; i++)
    {
        // 检查顶点关键字是否唯一
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.vertices[j].data.key == V[i].key)
                return ERROR; // 关键字重复，返回ERROR
        }

        // 添加顶点到图中
        G.vertices[G.vexnum].data = V[i];
        G.vertices[G.vexnum].firstarc = NULL;
        G.vexnum++;
    }

    // 检查顶点数是否超过最大限制
    if (G.vexnum > MAX_VERTEX_NUM)
        return ERROR;

    // 创建边表
    for (int i = 0; VR[i][0] != -1; i++)
    {
        int v1 = -1, v2 = -1;

        // 查找边的两个顶点在顶点表中的位置
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.vertices[j].data.key == VR[i][0])
                v1 = j;
            if (G.vertices[j].data.key == VR[i][1])
                v2 = j;
        }

        // 如果顶点不存在，返回ERROR
        if (v1 == -1 || v2 == -1)
            return ERROR;

        // 添加边到邻接表（首插法）
        ArcNode *arc1 = (ArcNode *)malloc(sizeof(ArcNode));
        arc1->adjvex = v2;
        arc1->nextarc = G.vertices[v1].firstarc;
        G.vertices[v1].firstarc = arc1;

        ArcNode *arc2 = (ArcNode *)malloc(sizeof(ArcNode));
        arc2->adjvex = v1;
        arc2->nextarc = G.vertices[v2].firstarc;
        G.vertices[v2].firstarc = arc2;

        G.arcnum++;
    }

    return OK;
    /********** End **********/
}
