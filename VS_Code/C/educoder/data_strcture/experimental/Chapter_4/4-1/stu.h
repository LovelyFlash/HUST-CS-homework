status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    // 初始化图
    // 初始化图
    G.vexnum = 0;
    G.arcnum = 0;

    // 检查是否有重复关键字
    int i = 0;
    for (; V[i].key != -1; i++)
    {
        for (int j = i + 1; V[j].key != -1; j++)
        {
            if (V[i].key == V[j].key)
            {
                return ERROR;
            }
        }
    }
    if (i > MAX_VERTEX_NUM || i < 1)
        return ERROR;
    G.vexnum = i;

    int flag0 = 0;
    for (i = 0; i < 100; i++)
    {
        if (VR[i][0] == -1 && VR[i][1] == -1)
        {
            flag0 = 1;
            break;
        }
    }
    if (!flag0)
        return ERROR;

    // 开始构造点集
    for (i = 0; i < G.vexnum; i++)
    {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
    }

    // 辅助函数：查找顶点索引
    auto Find = [&](int key) -> int
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.vertices[j].data.key == key)
                return j;
        }
        return -1;
    };

    // 检查VR的顶点是否全部存在
    for (i = 0; VR[i][0] != -1; i++)
    {
        if (Find(VR[i][0]) == -1 || Find(VR[i][1]) == -1)
            return ERROR;
    }

    // 辅助函数：添加边
    auto AddArc = [&](int index1, int index2) -> status
    {
        // 检查边是否已存在
        ArcNode *p = G.vertices[index1].firstarc;
        while (p != NULL)
        {
            if (p->adjvex == index2)
            {
                return ERROR; // 边已存在
            }
            p = p->nextarc;
        }

        ArcNode *currentNode = (ArcNode *)malloc(sizeof(ArcNode));
        if (currentNode == NULL)
            return OVERFLOW;
        currentNode->adjvex = index2;
        currentNode->nextarc = G.vertices[index1].firstarc;
        G.vertices[index1].firstarc = currentNode;
        return OK;
    };

    // 开始构造边
    for (i = 0; VR[i][0] != -1 && VR[i][1] != -1; i++)
    {
        if (i >= 100)
            return ERROR;
        int key1 = VR[i][0], key2 = VR[i][1];
        int index1 = Find(key1), index2 = Find(key2);
        if (AddArc(index2, index1) == ERROR || AddArc(index1, index2) == ERROR)
            return ERROR;
        G.arcnum++;
    }
    return OK;
    /********** End **********/
}
