#include <bits/stdc++.h>
#include <windows.h>
#include "def.h" // 相关数据类型的定义
#include "func.h"

int main()
{
    SetConsoleOutputCP(65001); // 设置控制台输出编码为UTF-8
    BiTree<int, char> T;
    BitreeList<BiTree<int, char>> Trees;
    static int n = 0;
    int op = 1;
    int insertKey, parentKey, oldKey, newKey;
    int isleft;
    char newdata;
    char insertData;
    while (op)
    {
        printf("\n\n");
        printf("      二叉树操作菜单 \n");
        printf("===============================================\n");
        printf("  基本操作：\n");
        printf("    1. 创建二叉树           2. 销毁二叉树\n");
        printf("    3. 清空二叉树           4. 判定空二叉树\n");
        printf("    5. 求二叉树深度\n");
        printf("-----------------------------------------------\n");
        printf("  结点操作：\n");
        printf("    6. 查找结点             7. 结点赋值\n");
        printf("    8. 获得兄弟结点         9. 插入结点\n");
        printf("   10. 删除结点\n");
        printf("-----------------------------------------------\n");
        printf("  遍历操作：\n");
        printf("   11. 前序遍历            12. 中序遍历\n");
        printf("   13. 后序遍历            14. 按层遍历\n");
        printf("-----------------------------------------------\n");
        printf("  附加功能：\n");
        printf("   15. 最大路径和          16. 最近公共祖先\n");
        printf("   17. 翻转二叉树          18. 保存二叉树到文件\n");
        printf("   19. 从文件加载二叉树\n");
        printf("-----------------------------------------------\n");
        printf("  多二叉树管理：\n");
        printf("   20. 添加二叉树          21. 删除二叉树\n");
        printf("   22. 定位二叉树          23. 修改二叉树名称\n");
        printf("   24. 输出所有二叉树名称\n");
        printf("    0. 退出程序\n");
        printf("===============================================\n");
        if (n != 0)
            printf("  正在操作的树为：%s\n", Trees.GetTreename(n - 1));
        printf("  请选择你的操作 [0 ~ 24]: ");
        scanf("%d", &op);

        // 输出对应的功能名称
        switch (op)
        {
        case 1:
            printf("\t创建二叉树\n");
            printf("\t请选择输入的数据排列方式： \n\t1 带空节点的中序遍历\n\t2 前序加中序遍历\n\t3 后序加中序遍历\n\t请输入：");
            int choice;
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                if (T.CreateBiTreeInOrderWithNull() == OK)
                {
                    Trees.AddBiTree(T);
                    n++;
                    printf("\t创建成功！\n");
                }
                else
                    printf("\t创建失败！\n");
                break;
            case 2:
                if (T.CreateBiTreePreOrder_InOrder() == OK)
                {
                    Trees.AddBiTree(T);
                    n++;
                    printf("\t创建成功！\n");
                }
                else
                    printf("\t创建失败！\n");
                break;
            case 3:
                if (T.CreateBiTreePostOrder_InOrder() == OK)
                {
                    Trees.AddBiTree(T);
                    n++;
                    printf("\t创建成功！\n");
                }
                else
                    printf("\t创建失败！\n");
                break;
            default:
                printf("\t输入错误，请重新输入！\n");
                break;
            }
            break;
        case 2:
            printf("\t销毁二叉树\n");
            if (T.DestroyBiTree() == OK)
                printf("\t销毁成功！\n");
            else
                printf("\t销毁失败！\n");
            break;
        case 3:
            printf("\t清空二叉树\n");
            if (T.ClearBiTree() == OK)
                printf("\t清空成功！\n");
            else
                printf("\t清空失败！\n");
            break;
        case 4:
            printf("\t判定空二叉树\n");
            if (T.IsEmpty() == OK)
                printf("\t二叉树为空！\n");
            else
                printf("\t二叉树不为空！\n");
            break;
        case 5:
            printf("\t求二叉树深度\n");
            int depth;
            depth = T.Depth();
            if (depth == 0)
                printf("\t二叉树为空！\n");
            else
                printf("\t二叉树深度为：%d\n", depth);
            break;
        case 6:
            printf("\t查找结点\n");
            printf("\t请输入要查找的结点值：");
            int key;
            scanf("%d", &key);
            BiTree<int, char> *node;
            node = T.FindNode(key);
            if (node != nullptr)
                printf("\t结点值为：%d\n", node->key);
            else
                printf("\t未找到该结点！\n");
            break;
        case 7:
        {
            printf("\t结点赋值\n");
            printf("\t请输入要赋值的结点值：");
            std::cin >> oldKey;
            printf("\t请输入新的结点值：");
            std::cin >> newKey;
            printf("\t请输入新的结点数据：");
            std::cin >> newdata;
            if (T.AssignNode(oldKey, newKey, newdata) == OK)
                printf("\t赋值成功！\n");
            else
                printf("\t赋值失败！\n");
            break;
        }
        case 8:
            printf("\t获得兄弟结点\n");
            printf("\t请输入要查找的结点值：");
            int key1;
            scanf("%d", &key1);
            BiTree<int, char> *brotherNode;
            brotherNode = T.GetSibling(key1);
            if (brotherNode != nullptr)
                printf("\t兄弟结点值为：%d\n", brotherNode->key);
            else
                printf("\t未找到兄弟结点！\n");
            break;
        case 9:
            printf("\t插入结点\n");
            printf("\t请输入要插入的结点值：");
            // scanf("%d", &insertKey);
            std::cin >> insertKey;
            printf("\t请输入要插入的结点数据：");
            // scanf("%c", &insertData);
            std::cin >> insertData;

            printf("\t插入至右侧请输入0，插入至左侧请输入1:");
            std::cin >> isleft;
            if (isleft >= 0)
            {
                printf("\t请输入要插入的父结点值：");
                // scanf("%d", &parentKey);
                std::cin >> parentKey;
                if (T.InsertNode(insertKey, parentKey, insertData, isleft) == OK)
                    printf("\t插入成功！\n");
                else
                    printf("\t插入失败！\n");
            }
            else if (isleft == -1)
            {
                if (T.InsertNodeAsRoot(insertKey, insertData) == OK)
                    printf("\t插入成功！\n");
                else
                    printf("\t插入失败！\n");
            }
            else
            {
                printf("\t输入错误，请重新输入！\n");
            }

            break;
        case 10:
            printf("\t删除结点\n");
            printf("\t请输入要删除的结点值：");
            int deleteKey;
            scanf("%d", &deleteKey);
            if (T.DeleteNode(deleteKey) == OK)
                printf("\t删除成功！\n");
            else
                printf("\t删除失败！\n");
            break;
        case 11:
            printf("\t前序遍历\n");
            if (T.PreOrderPrint() == OK)
                printf("\t遍历成功！\n");
            else
                printf("\t遍历失败！\n");
            break;
        case 12:
            printf("\t中序遍历\n");
            if (T.InOrderPrint() == OK)
                printf("\t遍历成功！\n");
            else
                printf("\t遍历失败！\n");
            break;
        case 13:
            printf("\t后序遍历\n");
            if (T.PostOrderPrint() == OK)
                printf("\t遍历成功！\n");
            else
                printf("\t遍历失败！\n");
            break;
        case 14:
            printf("\t按层遍历\n");
            if (T.LevelOrderPrint() == OK)
                printf("\t遍历成功！\n");
            else
                printf("\t遍历失败！\n");
            break;
        case 15:
            printf("\t最大路径和\n");
            int maxPathSum;
            maxPathSum = T.MaxPathSum();
            if (maxPathSum == 0)
                printf("\t二叉树为空！\n");
            else
                printf("\t最大路径和为：%d\n", maxPathSum);
            break;
        case 16:
            printf("\t最近公共祖先\n");
            printf("\t请输入要查找的两个结点值：");
            int keyA, keyB;
            scanf("%d %d", &keyA, &keyB);
            BiTree<int, char> *lcaNode;
            lcaNode = T.LowestCommonAncestor(keyA, keyB);
            if (lcaNode != nullptr)
                printf("\t最近公共祖先结点值为：%d\n", lcaNode->key);
            else
                printf("\t未找到最近公共祖先！\n");
            break;
        case 17:
            printf("\t翻转二叉树\n");
            if (T.InvertTree() == OK)
                printf("\t翻转成功！\n");
            else
                printf("\t翻转失败！\n");
            break;
        case 18:
            printf("\t保存二叉树到文件\n");
            printf("\t请输入文件名：");
            char filename[100];
            scanf("%s", filename);
            if (T.SaveToFile(filename) == OK)
                printf("\t保存成功！\n");
            else
                printf("\t保存失败！\n");
            break;
        case 19:
            printf("\t从文件加载二叉树\n");
            printf("\t请输入文件名：");
            char loadFilename[100];
            scanf("%s", loadFilename);
            if (T.LoadFromFile(loadFilename) == OK)
                printf("\t加载成功！\n");
            else
                printf("\t加载失败！\n");
            break;
        case 20:
            printf("\t添加二叉树\n");
            if (Trees.AddBiTree(T) == OK)
            {
                n++;
                printf("\t添加成功！\n");
            }
            else
                printf("\t添加失败！\n");
            break;
        case 21:
            printf("\t删除二叉树\n");
            printf("\t请输入要删除的二叉树名称：");
            char deleteTreeName[20];
            scanf("%s", deleteTreeName);
            if (Trees.DeleteBiTree(deleteTreeName) == OK)
                printf("\t删除成功！\n");
            else
                printf("\t删除失败！\n");
            break;
        case 22:
            printf("\t定位二叉树\n");
            printf("\t请输入要定位的二叉树名称：");
            int temp;
            temp = n;
            char locateTreeName[20];
            scanf("%s", locateTreeName);
            n = Trees.SelectBiTree(locateTreeName);
            if (n != -1)
            {
                T = Trees.GetTree(n - 1);
                printf("\t定位成功！\n");
            }
            else
            {
                n = temp;
                printf("\t定位失败！\n");
            }
            break;
        case 23:
            printf("\t修改二叉树名称\n");
            printf("\t请输入要修改的二叉树名称：");
            char oldTreeName[20];
            scanf("%s", oldTreeName);
            printf("\t请输入新的二叉树名称：");
            char newTreeName[20];
            scanf("%s", newTreeName);
            if (Trees.ModifyBiTreeName(oldTreeName, newTreeName) == OK)
                printf("\t修改成功！\n");
            else
                printf("\t修改失败！\n");
            break;
        case 24:
            printf("\t输出所有二叉树名称\n");
            if (Trees.PrintAllBiTreeNames() == OK)
                printf("\t输出成功！\n");
            else
                printf("\t输出失败！\n");
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