#include <bits/stdc++.h>
#include <windows.h>
#include "def.h"  // 相关数据类型的定义
#include "func.h" // 相关功能的定义

int main(void)
{
    SetConsoleOutputCP(65001); // 设置控制台输出编码为UTF-8
    BiTree T;
    List Trees; // 定义一个二叉树数组，最多存储10个二叉树
    Trees.elem = (BiTree *)malloc(sizeof(BiTree));
    Trees.length = 0;                // 初始化二叉树数组长度
    Trees.listsize = LIST_INIT_SIZE; // 初始化二叉树存储空间大小
    strcpy(Trees.name[0], "二叉树1"); // 初始化二叉树名称
    static int num = 0;
    int op = 1;
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
        printf("  正在操作的二叉树名称：%s\n", Trees.name[num - 1]);
        printf("  请选择你的操作 [0 ~ 24]: ");
        scanf("%d", &op);

        // 输出对应的功能名称
        switch (op)
        {
        case 1:
            printf("\t创建二叉树\n");
            
            break;
        case 2:
            printf("\t销毁二叉树\n");
            break;
        case 3:
            printf("\t清空二叉树\n");
            break;
        case 4:
            printf("\t判定空二叉树\n");
            break;
        case 5:
            printf("\t求二叉树深度\n");
            break;
        case 6:
            printf("\t查找结点\n");
            break;
        case 7:
            printf("\t结点赋值\n");
            break;
        case 8:
            printf("\t获得兄弟结点\n");
            break;
        case 9:
            printf("\t插入结点\n");
            break;
        case 10:
            printf("\t删除结点\n");
            break;
        case 11:
            printf("\t前序遍历\n");
            break;
        case 12:
            printf("\t中序遍历\n");
            break;
        case 13:
            printf("\t后序遍历\n");
            break;
        case 14:
            printf("\t按层遍历\n");
            break;
        case 15:
            printf("\t最大路径和\n");
            break;
        case 16:
            printf("\t最近公共祖先\n");
            break;
        case 17:
            printf("\t翻转二叉树\n");
            break;
        case 18:
            printf("\t保存二叉树到文件\n");
            break;
        case 19:
            printf("\t从文件加载二叉树\n");
            break;
        case 20:
            printf("\t添加二叉树\n");
            break;
        case 21:
            printf("\t删除二叉树\n");
            break;
        case 22:
            printf("\t定位二叉树\n");
            break;
        case 23:
            printf("\t修改二叉树名称\n");
            break;
        case 24:
            printf("\t输出所有二叉树名称\n");
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