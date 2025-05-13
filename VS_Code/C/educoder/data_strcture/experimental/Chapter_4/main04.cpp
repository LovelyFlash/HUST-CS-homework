#include <bits/stdc++.h>
#include <windows.h>
#include "graph_def.h" // 图相关数据类型的定义
#include "graph_func.h"

using namespace std;
void visit(VertexType v)
{
    printf(" %d %s", v.key, v.others);
}
int main()
{
    SetConsoleOutputCP(65001); // 设置控制台输出编码为UTF-8
    Graph<ALGraph> G;
    List<Graph<ALGraph>> Graphs;
    static int n = 0;
    int op = 1;
    VNode lis;
    while (op)
    {
        printf("\n\n");
        printf("      图操作菜单 \n");
        printf("===============================================\n");
        printf("  基本操作：\n");
        printf("    1. 创建图               2. 销毁图\n");
        printf("    3. 查找顶点             4. 顶点赋值\n");
        printf("    5. 获得第一邻接点       6. 获得下一邻接点\n");
        printf("-----------------------------------------------\n");
        printf("  修改操作：\n");
        printf("    7. 插入顶点             8. 删除顶点\n");
        printf("    9. 插入弧              10. 删除弧\n");
        printf("-----------------------------------------------\n");
        printf("  遍历操作：\n");
        printf("   11. 深度优先遍历        12. 广度优先遍历\n");
        printf("-----------------------------------------------\n");
        printf("  附加功能：\n");
        printf("   13. 距离小于k的顶点集合 14. 顶点间最短路径长度\n");
        printf("   15. 图的连通分量        16. 保存图到文件\n");
        printf("   17. 从文件加载图\n");
        printf("-----------------------------------------------\n");
        printf("  多图管理：\n");
        printf("   18. 添加图              19. 删除图\n");
        printf("   20. 定位图              21. 修改图名称\n");
        printf("   22. 输出所有图名称\n");
        printf("    0. 退出程序\n");
        printf("===============================================\n");
        if (n != 0)
            printf("  正在操作的图为：%s\n", Graphs.GetGraphName(n - 1));
        printf("  请选择你的操作 [0 ~ 22]: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\t创建图\n");
            if (G.CreateGraph() == OK)
            {
                Graphs.AddGraph(G);
                n++;
                printf("\t创建成功！\n");
            }
            else
                printf("\t创建失败！\n");
            break;
        case 2:
            printf("\t销毁图\n");
            if (G.DestroyGraph() == OK)
                printf("\t销毁成功！\n");
            else
                printf("\t销毁失败！\n");
            break;
        case 3:
            printf("\t查找顶点\n");
            printf("\t请输入顶点关键字：");
            int key;
            scanf("%d", &key);
            int pos;
            pos = G.LocateVex(key);
            if (pos != -1)
                printf("\t顶点位置为：%d\n", pos + 1);
            else
                printf("\t顶点不存在！\n");
            break;
        case 4:
            printf("\t顶点赋值\n");
            printf("\t请输入顶点关键字：");
            int u;
            VertexType value;
            scanf("%d", &u);
            printf("\t请输入新值：");
            scanf("%d %s", &value.key, value.others);
            if (G.PutVex(u, value) == OK)
                printf("\t赋值成功！\n");
            else
                printf("\t赋值失败！\n");
            break;
        case 5:
            printf("\t获得第一邻接点\n");
            printf("\t请输入顶点关键字：");
            int v;
            scanf("%d", &v);
            int firstAdj;
            firstAdj = G.FirstAdjVex(v);
            lis=G.GetNode(firstAdj);
            if (firstAdj != -1)
                printf("\t第一邻接点为：%d %s\n", lis.data.key,lis.data.others);
            else
                printf("\t没有邻接点！\n");
            break;
        case 6:
            printf("\t获得下一邻接点\n");
            printf("\t请输入顶点关键字和当前邻接点关键字：");
            int w;
            scanf("%d %d", &v, &w);
            int nextAdj;
            nextAdj = G.NextAdjVex(v, w);

            lis = G.GetNode(nextAdj);
            if (nextAdj != -1)
                printf("\t下一邻接点为：%d %s\n", lis.data.key, lis.data.others);
            else
                printf("\t没有下一邻接点！\n");
            break;
        case 7:
            printf("\t插入顶点\n");
            printf("\t请输入顶点关键字：");
            VertexType newVex;
            scanf("%d %s", &newVex.key, newVex.others);
            if (G.InsertVex(newVex) == OK)
                printf("\t插入成功！\n");
            else
                printf("\t插入失败！\n");
            break;
        case 8:
            printf("\t删除顶点\n");
            printf("\t请输入顶点关键字：");
            int delVex;
            scanf("%d", &delVex);
            if (G.DeleteVex(delVex) == OK)
                printf("\t删除成功！\n");
            else
                printf("\t删除失败！\n");
            break;
        case 9:
            printf("\t插入弧\n");
            printf("\t请输入弧的起点和终点关键字：");
            int v1, v2;
            scanf("%d %d", &v1, &v2);
            if (G.InsertArc(v1, v2) == OK)
                printf("\t插入成功！\n");
            else
                printf("\t插入失败！\n");
            break;
        case 10:
            printf("\t删除弧\n");
            printf("\t请输入弧的起点和终点关键字：");
            scanf("%d %d", &v1, &v2);
            if (G.DeleteArc(v1, v2) == OK)
                printf("\t删除成功！\n");
            else
                printf("\t删除失败！\n");
            break;
        case 11:
            printf("\t深度优先遍历\n");
            if (G.DFSTraverse(visit) == OK)
                printf("\t遍历成功！\n");
            else
                printf("\t遍历失败！\n");
            break;
        case 12:
            printf("\t广度优先遍历\n");
            if (G.BFSTraverse(visit) == OK)
                printf("\t遍历成功！\n");
            else
                printf("\t遍历失败！\n");
            break;
        case 13:
            printf("\t距离小于k的顶点集合\n");
            printf("\t请输入顶点关键字和距离k：");
            int k;
            scanf("%d %d", &v, &k);

            if (G.VerticesSetLessThanK(v, k, visit) == OK)
                printf("\t操作成功！\n");
            else
                printf("\t操作失败！\n");
            break;
        case 14:
            printf("\t顶点间最短路径长度\n");
            printf("\t请输入两个顶点关键字：");
            scanf("%d %d", &v1, &v2);
            int length;
            length = G.ShortestPathLength(v1, v2);
            if (length != -1)
                printf("\t最短路径长度为：%d\n", length);
            else
                printf("\t路径不存在！\n");
            break;
        case 15:
            printf("\t图的连通分量\n");
            int components;
            components = G.ConnectedComponentsNums();
            printf("\t连通分量个数为：%d\n", components);
            break;
        case 16:
            printf("\t保存图到文件\n");
            printf("\t请输入文件名：");
            char saveFile[100];
            scanf("%s", saveFile);
            if (G.SaveToFile(saveFile) == OK)
                printf("\t保存成功！\n");
            else
                printf("\t保存失败！\n");
            break;
        case 17:
            printf("\t从文件加载图\n");
            printf("\t请输入文件名：");
            char loadFile[100];
            scanf("%s", loadFile);
            if (G.LoadFromFile(loadFile) == OK)
                printf("\t加载成功！\n");
            else
                printf("\t加载失败！\n");
            break;
        case 18:
            printf("\t添加图\n");
            if (Graphs.AddGraph(G) == OK)
            {
                n++;
                printf("\t添加成功！\n");
            }
            else
                printf("\t添加失败！\n");
            break;
        case 19:
            printf("\t删除图\n");
            printf("\t请输入图名称：");
            char delGraphName[20];
            scanf("%s", delGraphName);
            if (Graphs.DeleteGraph(delGraphName) == OK)
                printf("\t删除成功！\n");
            else
                printf("\t删除失败！\n");
            break;
        case 20:
            printf("\t定位图\n");
            printf("\t请输入图名称：");
            char locateGraphName[20];
            scanf("%s", locateGraphName);
            int temp;
            temp = n;
            n = Graphs.SelectGraph(locateGraphName);
            if (n != -1)
            {
                G = Graphs.GetGraph(n);
                printf("\t定位成功！\n");
            }
            else
            {
                n = temp;
                printf("\t定位失败！\n");
            }
            break;
        case 21:
            printf("\t修改图名称\n");
            printf("\t请输入当前图名称：");
            char oldGraphName[20];
            scanf("%s", oldGraphName);
            printf("\t请输入新图名称：");
            char newGraphName[20];
            scanf("%s", newGraphName);
            if (Graphs.ModifyGraphName(oldGraphName, newGraphName) == OK)
                printf("\t修改成功！\n");
            else
                printf("\t修改失败！\n");
            break;
        case 22:
            printf("\t输出所有图名称\n");
            if (Graphs.PrintGraphName() == OK)
                printf("\t输出成功！\n");
            else
                printf("\t输出失败！\n");
            break;
        case 23:
            std::cout << "\t完整输出当前图" << std::endl;
            G.Traverse();
            break;
        case 0:
            printf("\t退出程序\n");
            break;
        default:
            printf("\t输入错误，请重新输入！\n");
            break;
        }
        printf("\t请按回车键继续...");
        getchar();
        getchar();
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}