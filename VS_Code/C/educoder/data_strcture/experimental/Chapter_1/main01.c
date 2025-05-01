// 数据结构实验一：顺序表演示
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"  // 相关数据类型的定义
#include "func.h" // 相关功能的定义

int main(void)
{
    SqList L;
    LISTS Lists; // 链表头指针
    Lists.elem[0].L = L;
    Lists.length =0;
    strcpy(Lists.elem[0].name, "线性表1"); // 初始化顺序表名称
    L.elem = NULL;
    int op = 1;
    while (op)
    {
        // system("cls"); // 清空面板
        printf("\n\n");
        printf("      顺序表操作菜单 \n");
        printf("===============================================\n");
        printf("  基本操作：\n");
        printf("    1. 初始化顺序表           2. 销毁顺序表\n");
        printf("    3. 清空顺序表             4. 判断顺序表是否为空\n");
        printf("    5. 获取顺序表长度\n");
        printf("-----------------------------------------------\n");
        printf("  元素操作：\n");
        printf("    6. 获取指定位置元素       7. 查找元素位置\n");
        printf("    8. 获取前驱元素           9. 获取后继元素\n");
        printf("   10. 插入元素              11. 删除元素\n");
        printf("-----------------------------------------------\n");
        printf("  遍历操作：\n");
        printf("   12. 遍历顺序表\n");
        printf("-----------------------------------------------\n");
        printf("  附加操作：\n");
        printf("   13. 求最大连续子数组和    14. 求和为 K 的子数组个数\n");
        printf("   15. 顺序表排序            16. 保存线性表到文件\n");
        printf("   17. 从文件加载线性表\n");
        printf("-----------------------------------------------\n");
        printf("  多线性表管理：\n");
        printf("   18. 添加顺序表           19. 删除顺序表\n");
        printf("   20. 定位顺序表           21. 修改顺序表名称\n");
        printf("   22. 输出所有顺序表名称\n");
        printf("    0. 退出程序\n");
        printf("===============================================\n");
        printf("  正在操作的顺序表名称：%s\n", Lists.elem[0].name);
        printf("  请选择你的操作 [0 ~ 22]: ");
        scanf("%d", &op);

        // 输出对应的功能名称
        switch (op)
        {
        case 1:
            printf("\t初始化顺序表\n");
            break;
        case 2:
            printf("\t销毁顺序表\n");
            break;
        case 3:
            printf("\t清空顺序表\n");
            break;
        case 4:
            printf("\t判断顺序表是否为空\n");
            break;
        case 5:
            printf("\t获取顺序表长度\n");
            break;
        case 6:
            printf("\t获取指定位置元素\n");
            break;
        case 7:
            printf("\t查找元素位置\n");
            break;
        case 8:
            printf("\t获取前驱元素\n");
            break;
        case 9:
            printf("\t获取后继元素\n");
            break;
        case 10:
            printf("\t插入元素\n");
            break;
        case 11:
            printf("\t删除元素\n");
            break;
        case 12:
            printf("\t遍历顺序表\n");
            break;
        case 13:
            printf("\t求最大连续子数组和\n");
            break;
        case 14:
            printf("\t求和为 K 的子数组个数\n");
            break;
        case 15:
            printf("\t顺序表排序\n");
            break;
        case 16:
            printf("\t保存线性表到文件\n");
            break;
        case 17:
            printf("\t从文件加载线性表\n");
            break;
        case 18:
            printf("\t添加顺序表\n");
            break;
        case 19:
            printf("\t删除顺序表\n");
            break;
        case 20:
            printf("\t定位顺序表\n");
            break;
        case 21:
            printf("\t修改顺序表名称\n");
            break;
        case 22:
            printf("\t输出所有线性表名称\n");
            break;
        case 0:
            printf("\t退出程序\n");
            break;
        default:
            printf("\t输入错误，请重新输入！\n");
            break;
        }

        switch (op)
        {
        case 1:
            // printf("\n----IntiList功能待实现！\n");
            if (InitList(L) == OK)
                printf("\t线性表创建成功！\n");
            else
                printf("\t线性表创建失败！\n");
            break;
        case 2:
            // printf("\n----DestroyList功能待实现！\n");
            if (DestroyList(L) == OK)
                printf("\t线性表销毁成功！\n");
            else
                printf("\t线性表销毁失败！\n");
            break;
        case 3:
            // printf("\n----ClearList功能待实现！\n");
            if (ClearList(L) == OK)
                printf("\t线性表清空成功！\n");
            else
                printf("\t线性表清空失败！\n");
            break;
        case 4:
            // printf("\n----ListEmpty功能待实现！\n");
            if (ListEmpty(L) == OK)
                printf("\t线性表是空表！\n");
            else
                printf("\t线性表不是空表！\n");
            break;
        case 5:
            // printf("\n----ListLength功能待实现！\n");
            if (ListLength(L) != INFEASIBLE)
                printf("\t线性表的长度为：%d\n", ListLength(L));
            else
                printf("\t线性表的长度获取失败！\n");

            break;
        case 6:
            // printf("\n----GetElem功能待实现！\n");
            printf("\t请输入要获取的元素的序号：");
            int i;
            ElemType e0;
            scanf("%d", &i);
            if (GetElem(L, i, e0) == OK)
                printf("\t线性表的第%d个元素为：%d\n", i, GetElem(L, i, e0));
            else
                printf("\t线性表的第%d个元素获取失败！\n", i);
            break;
        case 7:
            // printf("\n----LocateElem功能待实现！\n");
            printf("\t请输入要查找的元素：");
            int e;
            scanf("%d", &e);
            if (LocateElem(L, e) == OK)
                printf("\t线性表中元素%d的序号为：%d\n", e, LocateElem(L, e));
            else
                printf("\t线性表中元素%d的查找失败！\n", e);
            break;
        case 8:
            // printf("\n----PriorElem功能待实现！\n");
            printf("\t请输入要查找的元素：");
            int e1;
            ElemType pre;
            scanf("%d", &e1);
            if (PriorElem(L, e1, pre) == OK)
                printf("\t线性表中元素%d的前驱元素为：%d\n", e1, pre);
            else
                printf("\t线性表中元素%d的前驱元素查找失败！\n", e1);
            break;
        case 9:
            // printf("\n----NextElem功能待实现！\n");
            printf("\t请输入要查找的元素：");
            int e2;
            ElemType next;
            scanf("%d", &e2);
            if (NextElem(L, e2, next) == OK)
                printf("\t线性表中元素%d的后继元素为：%d\n", e2, next);
            else
                printf("\t线性表中元素%d的后继元素查找失败！\n", e2);
            break;
        case 10:
            // printf("\n----ListInsert功能待实现！\n");
            printf("\t请输入要插入的元素：");
            ElemType e3;
            scanf("%d", &e3);
            printf("\t请输入要插入的位置：");
            int i1;
            scanf("%d", &i1);
            if (ListInsert(L, i1, e3) == OK)
                printf("\t线性表中元素%d插入成功！\n", e3);
            else
                printf("\t线性表中元素%d插入失败！\n", e3);
            break;
        case 11:
            // printf("\n----ListDelete功能待实现！\n");
            ElemType e4;
            printf("\t请输入要删除的位置：");
            int i2;
            scanf("%d", &i2);
            if (ListDelete(L, i2, e4) == OK)
                printf("\t线性表中元素%d删除成功！\n", e4);
            else
                printf("\t线性表中元素%d删除失败！\n", e4);
            break;
        case 12:
            // printf("\n----ListTrabverse功能待实现！\n");
            if (ListTraverse(L) == OK)
                printf("\t线性表遍历成功！\n");
            else
                printf("\t线性表遍历失败！\n");
            break;
        case 13:
            // printf("\n----MaxSubArray功能待实现！\n");
            printf("\t最大连续子数组和为%d\n", MaxSubArray(L));
            break;
        case 14:
            // printf("\n----SubArrayNum功能待实现！\n");
            int k;
            printf("\t请输入要查询的子数组和：");
            scanf("%d", &k);
            int count;
            count = SubArrayNum(L, k);
            if (count)
                printf("\t数组和为k的子数组有%d个\n", count);
            else
                printf("\t没有满足要求的子数组！\n");
            break;
        case 15:
            // printf("\n----sortList功能待实现！\n");
            sortList(L);
            printf("\t顺序表排序完毕！");
            break;
        case 16:
            // printf("\n----saveListToFile功能待实现！\n");
            printf("\t请输入要保存到的文件名称：");
            char filename_w[40];
            scanf("%s", filename_w);
            saveListToFile(L, filename_w);
            break;
        case 17:
            // printf("\n----loadListFromFile功能待实现！\n");
            printf("\t请输入要读取的文件名称：");
            char filename_r[40];
            scanf("%s", filename_r);
            loadListFromFile(L, filename_r);
            break;
        case 18:
            // printf("\n----AddList功能待实现！\n");

            char listname[40];
            AddList(Lists, listname);
            break;
        case 19:
            // printf("\n----RemoveList功能待实现！\n");
            printf("\t请输入要删除的顺序表名称：");
            scanf("%s", listname);
            if (RemoveList(Lists, listname))
                printf("\t线性表成功删除！\n");
            else
                printf("\t未找到该名称的顺序表！\n");
            break;
        case 20:
            // printf("\n----LocateList功能待实现！\n");
            printf("\t请输入要查找的顺序表名称：");
            scanf("%s", listname);
            int num;
            num = LocateList(Lists, listname);
            if (num)
            {
                printf("\t查找到该顺序表为第%d个\n", num);
                L = Lists.elem[num - 1].L;
                printf("\t已将接下来操作的顺序表改为该顺序表！\n");
            }
            else
                printf("\t未找到该名称的顺序表！\n");
            break;
        case 21:
            printf("\t请输入要修改的顺序表名称：");
            scanf("%s", listname);
            num = LocateList(Lists, listname);
            printf("\t请输入你想取的名字：");
            scanf("%s", listname);
            if (strcpy(Lists.elem[num - 1].name, listname))
                printf("\t修改成功！\n");
            else
                printf("\t修改失败！\n");
            break;
        case 22:
            for (int i = 0; i < Lists.length; i++)
                printf("\t%s\n", Lists.elem[i].name);
            break;
        default:
            printf("输入错误，请重新输入！\n");
            break;
        }
        printf("\t请按回车键继续...");
        getchar();
        getchar();
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}