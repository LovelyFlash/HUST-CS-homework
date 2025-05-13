using namespace std;

template <class Gra>
class Graph
{
private:
    Gra G;

    void DFS(Gra &G, int v, void (*visit)(VertexType), int *visited)
    // 辅助函数：递归实现深度优先搜索
    {
        visited[v] = 1;            // 标记当前顶点为已访问
        visit(G.vertices[v].data); // 访问当前顶点

        ArcNode *p = G.vertices[v].firstarc;
        while (p != NULL)
        {
            if (visited[p->adjvex] == 0)
            {
                DFS(G, p->adjvex, visit, visited); // 递归访问未访问的邻接顶点
            }
            p = p->nextarc;
        }
    }

    int FindNum(Gra &G, VNode v)
    {
        int i;
        for (i = 0; i < G.vexnum; i++)
        {
            if (G.vertices[i].data.key == v.data.key)
                return i;
        }
        return -1; // 未找到
    }

    int FindVex(Gra &G, KeyType v)
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.vertices[i].data.key == v)
                return i;
        }
        return -1; // 未找到
    }

    status Delete(int v, int w)
    {
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
                        free(p);
                        return OK;
                        break;
                    }
                    q = p;
                    p = p->nextarc;
                }
            }
        }
        return ERROR;
    }

public:
    Gra GetGraph()
    {
        return G;
    }
    AdjList *GetGraphList()
    {
        return G.vertices;
    }
    int GetVexNum()
    {
        return G.vexnum;
    }
    int GetArcNum()
    {
        return G.arcnum;
    }

    status CreateGraph()
    {

        VertexType V[30];
        KeyType VR[100][2];
        int i = 0, j;
        do
        {
            scanf("%d%s", &V[i].key, V[i].others);
        } while (V[i++].key != -1);
        i = 0;
        do
        {
            scanf("%d%d", &VR[i][0], &VR[i][1]);
        } while (VR[i++][0] != -1);
        G.vexnum = 0;
        G.arcnum = 0;

        // 检查是否有重复关键字
        for (i = 0; V[i].key != -1; i++)
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
    }
    status DestroyGraph()
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            ArcNode *p = G.vertices[i].firstarc;
            while (p != NULL)
            {
                ArcNode *temp = p;
                p = p->nextarc;
                free(temp);
            }
            G.vertices[i].firstarc = NULL;
        }
        G.vexnum = 0; // 清空顶点数
        G.arcnum = 0; // 清空边数
        return OK;
    }
    int LocateVex(KeyType u)
    {
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
    }
    status PutVex(KeyType u, VertexType value)
    {
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
    }
    int FirstAdjVex(KeyType u)
    {
        int i = 0, flag = ERROR, res = 0;

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
    }
    int NextAdjVex(KeyType v, KeyType w)
    {
        int i = 0, flag = ERROR, res = 0;

        for (i = 0; i < G.vexnum; i++)
        {
            if (G.vertices[i].data.key == v)
            {
                res = G.vertices[i].firstarc->adjvex;
                flag = OK;
                break;
            }
        }

        if (flag == OK)
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
    }

    status InsertVex(VertexType v)
    {
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
    }

    status DeleteVex(KeyType v)
    {
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
                    free(q);
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
                                free(p);
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
    }
    status InsertArc(KeyType v, KeyType w)
    {
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
    }
    status DeleteArc(KeyType v, KeyType w)
    {
        static int flag = 0;
        if (G.vexnum == 0 || G.arcnum == 0)
            return ERROR;
        if (Delete(v, w) == OK && Delete(w, v) == OK)
            return OK;
        else
            return ERROR;
    }
    status DFSTraverse(void (*visit)(VertexType))
    {
        int *visited = (int *)malloc(G.vexnum * sizeof(int)); // 动态分配 visited 数组
        if (visited == NULL)
        {
            return ERROR; // 分配失败
        }

        for (int i = 0; i < G.vexnum; i++)
        {
            visited[i] = 0; // 初始化为未访问
        }

        for (int i = 0; i < G.vexnum; i++)
        {
            if (visited[i] == 0)
            {
                DFS(G, i, visit, visited); // 调用辅助函数进行深度优先搜索
            }
        }

        free(visited); // 释放动态分配的内存
        return OK;
    }
    status BFSTraverse(void (*visit)(VertexType))
    {
        int *visited = (int *)malloc(G.vexnum * sizeof(int));
        if (visited == NULL)
        {
            return ERROR; // 分配失败
        }

        for (int i = 0; i < G.vexnum; i++)

            visited[i] = 0; // 初始化为未访问

        queue<VNode> q;
        int first = 0;
        while (first != G.vexnum)
        {
            for (first = 0; first < G.vexnum && visited[first]; first++)
                ;
            if (first == G.vexnum)
                break;
            q.push(G.vertices[first]);
            visited[first] = 1;
            while (!q.empty())
            {
                auto tmp = q.front();
                q.pop();
                int j = FindNum(G, tmp);
                visit(G.vertices[j].data);
                auto p = tmp.firstarc;
                while (p != nullptr)
                {
                    if (visited[p->adjvex])
                    {
                        p = p->nextarc;
                        continue;
                    }
                    q.push(G.vertices[p->adjvex]);
                    visited[p->adjvex] = 1;
                    p = p->nextarc;
                }
            }
        }
        free(visited); // 释放内存
        return OK;     // 遍历成功
    }

    status VerticesSetLessThanK(KeyType v, int k, void (*visit)(VertexType))
    {
        if (k < 0)
            return ERROR;
        int *visited = (int *)malloc(G.vexnum * sizeof(int));
        if (visited == NULL)
        {
            return ERROR; // 分配失败
        }

        for (int i = 0; i < G.vexnum; i++)

            visited[i] = 0; // 初始化为未访问

        queue<VNode> q;
        q.push(G.vertices[FindVex(G, v)]);
        visited[FindVex(G, v)] = 1;
        while (!q.empty())
        {
            auto tmp = q.front();
            q.pop();
            auto p = tmp.firstarc;
            while (p != nullptr)
            {
                if (visited[p->adjvex] || visited[FindNum(G,tmp)] >= k + 1)
                {
                    p = p->nextarc;
                    continue;
                }
                q.push(G.vertices[p->adjvex]);
                visited[p->adjvex] = visited[FindNum(G,tmp)] + 1;
                p = p->nextarc;
            }
        }
        free(visited); // 释放内存
        return OK;
    }

    int ShortestPathLength(KeyType v1, KeyType v2)
    {
        int res = -1;
        int *visited = (int *)malloc(G.vexnum * sizeof(int));
        if (visited == NULL)
        {
            return ERROR; // 分配失败
        }

        for (int i = 0; i < G.vexnum; i++)

            visited[i] = 0; // 初始化为未访问

        queue<VNode> q;

        q.push(G.vertices[FindVex(G, v1)]);
        visited[FindVex(G, v1)] = 1;
        while (!q.empty())
        {
            auto tmp = q.front();
            q.pop();
            auto p = tmp.firstarc;
            while (p != nullptr)
            {
                if (G.vertices[p->adjvex].data.key == v2)
                {
                    res = visited[tmp.data.key];
                    free(visited);
                    return res;
                }
                if (visited[p->adjvex])
                {
                    p = p->nextarc;
                    continue;
                }
                q.push(G.vertices[p->adjvex]);
                visited[p->adjvex] = visited[FindNum(G,tmp)] + 1;
                p = p->nextarc;
            }
        }

        free(visited); // 释放内存
        return res;
    }
    int ConnectedComponentsNums()
    {
        int *visited = (int *)malloc(G.vexnum * sizeof(int));
        if (visited == NULL)
        {
            return ERROR; // 分配失败
        }

        for (int i = 0; i < G.vexnum; i++)
            visited[i] = 0; // 初始化为未访问

        int count = 0;
        for (int i = 0; i < G.vexnum; i++)
        {
            if (visited[i] == 0)
            {
                count++;
                DFS(G, i, [](VertexType v) {}, visited);
            }
        }

        free(visited); // 释放内存
        return count;  // 返回连通分量个数
    }
    status SaveToFile(char FileName[])
    {
        FILE *fp = fopen(FileName, "w");
        if (fp == NULL)
        {
            return ERROR; // 打开文件失败
        }
        for (int i = 0; i < G.vexnum; i++)
        {
            fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
            auto *p = G.vertices[i].firstarc;
            while (p != NULL)
            {
                fprintf(fp, "%d ", p->adjvex);
                p = p->nextarc;
            }
            fprintf(fp, "-1\n");
        }
        fprintf(fp, "-1 nil %d %d", G.vexnum, G.arcnum);
        fclose(fp);
        return OK; // 保存成功
    }
    status LoadFromFile(char FileName[])
    {
        FILE *fp = fopen(FileName, "r");
        if (fp == NULL)
        {
            return ERROR; // 打开文件失败
        }
        int i = 0, key;
        char others[20];
        while (fscanf(fp, "%d %s", &key, others) != EOF && key != -1 && strcmp(others, "nil"))
        {
            G.vertices[i].data.key = key;
            strcpy(G.vertices[i].data.others, others);
            G.vertices[i].firstarc = NULL;
            int adjvex;
            while (fscanf(fp, "%d", &adjvex) != EOF && adjvex != -1)
            {
                ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex = adjvex;
                p->nextarc = NULL;
                if (G.vertices[i].firstarc == NULL)
                    G.vertices[i].firstarc = p;
                else
                {
                    ArcNode *q = G.vertices[i].firstarc;
                    while (q->nextarc != NULL)
                    {
                        q = q->nextarc;
                    }
                    q->nextarc = p;
                }
                G.arcnum++;
            }
            i++;
        }
        fscanf(fp, "%d %d", &G.vexnum, &G.arcnum);
        if (G.vexnum < 20)
        {
            G.vertices[G.vexnum].data.key = -1;              // 设置结束标志
            strcpy(G.vertices[G.vexnum].data.others, "nil"); // 设置结束标志
        }
        fclose(fp);
        return OK; // 读入成功
    }
};

template <class ElemType>
class List
{
private:
    ElemType *elem;
    char **name;
    int listlength;

public:
    List() : elem(nullptr), name(nullptr), listlength(0)
    {
        name = (char **)malloc(20 * sizeof(char *)); // 初始化name
        for (int i = 0; i < 20; ++i)
        {
            name[i] = (char *)malloc(20 * sizeof(char)); // 初始化每个name元素
        }
        strcpy(name[0], "默认第一张图");
    }
    ElemType GetGraph(int index)
    {
        return elem[index];
    }
    char *GetGraphName(int index)
    {
        if (index == -1)
        {
            printf("请选择正确的图");
            return nullptr;
        }
        else
            return name[index];
    }
    // 多图管理
    AddGraph(Graph<ALGraph> &newG)
    {
        if (!elem)
        {
            elem = new ElemType();
        }

        if (!name)
        {
            name = new char *[1];
            name[0] = new char[20];
            std::cout << "\t请输入二叉树名称: ";
            std::cin >> name[0];
        }
        else
        {
            char tempName[20];
            bool isDuplicate;
            do
            {
                isDuplicate = false;
                std::cout << "\t请输入二叉树名称: ";
                std::cin >> tempName;

                // 检查名称是否重复
                for (int i = 0; i < listlength; ++i)
                {
                    if (strcmp(name[i], tempName) == 0)
                    {
                        isDuplicate = true;
                        std::cout << "\t二叉树名称重复，请重新输入。" << std::endl;
                        break;
                    }
                }
            } while (isDuplicate);

            char **newname = new char *[listlength + 1];
            for (int i = 0; i < listlength; ++i)
            {
                newname[i] = name[i];
            }
            newname[listlength] = new char[20];
            strcpy(newname[listlength], tempName);
            delete[] name;
            name = newname;
        }

        elem[listlength] = newG;
        listlength++;
        return OK; // 添加成功
    }
    status DeleteGraph(char *name)
    {
        if (!elem)
        {
            std::cout << "\t没有可删除的图。" << std::endl;
            return ERROR;
        }

        for (int i = 0; i < listlength; ++i)
        {
            if (strcmp(this->name[i], name) == 0)
            {
                delete[] this->name[i]; // 删除旧名称
                this->name[i] = nullptr;
                for (int j = i; j < listlength - 1; ++j)
                {
                    this->name[j] = this->name[j + 1];
                    elem[j] = elem[j + 1];
                }
                listlength--;
                return OK; // 删除成功
            }
        }

        std::cout << "\t未找到名称为 " << name << " 的图。" << std::endl;
        return ERROR; // 删除失败
    }
    int SelectGraph(char *name)
    {
        if (!elem)
        {
            std::cout << "\t没有可选择的图。" << std::endl;
            return -1;
        }

        for (int i = 0; i < listlength; ++i)
        {
            if (strcmp(this->name[i], name) == 0)
            {
                std::cout << "\t选择的图名称: " << this->name[i] << std::endl;
                return i; // 选择成功
            }
        }

        std::cout << "\t未找到名称为 " << name << " 的图。" << std::endl;
        return -1; // 选择失败
    }
    status ModifyGraphName(char *oldName, char *newName)
    {
        if (!elem)
        {
            std::cout << "\t没有可修改的图。" << std::endl;
            return ERROR;
        }

        for (int i = 0; i < listlength; ++i)
        {
            if (strcmp(this->name[i], oldName) == 0)
            {
                delete[] this->name[i]; // 删除旧名称
                this->name[i] = new char[20];
                strcpy(this->name[i], newName);
                return OK; // 修改成功
            }
        }

        std::cout << "\t未找到名称为 " << oldName << " 的图。" << std::endl;
        return ERROR; // 修改失败
    }
    status PrintGraphName()
    {
        if (!elem)
        {
            std::cout << "\t没有可打印的图名称。" << std::endl;
            return ERROR;
        }

        for (int i = 0; i < listlength; ++i)
        {
            std::cout << "\t图名称 " << i + 1 << ": " << name[i] << std::endl;
        }
        return OK; // 打印成功
    }
};