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
    L.elem = NULL;
    int op = 1;
    while (op)
    {
        system("cls"); // 清空面板
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       9. NextElem\n");
        printf("    	  2. DestroyList    10. ListInsert\n");
        printf("    	  3. ClearList      11. ListDelete \n");
        printf("    	  4. ListEmpty      12. ListTrabverse\n");
        printf("    	  5. ListLength     13. MaxSubArray\n");
        printf("    	  6. GetElem        14. SubArrayNum\n");
        printf("    	  7. LocateElem     15. sortList\n");
        printf("    	  8. PriorElem      16. .。。。\n");
        printf("    	  9. PriorElem      17. .。。。\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作 [0 ~ 16]: ");
        scanf("%d", &op);
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
            if (ListLength(L) == OK)
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
            ElemType next;
            scanf("%d", &e1);
            if (PriorElem(L, e1, next) == OK)
                printf("\t线性表中元素%d的前驱元素为：%d\n", e1, PriorElem(L, e1, next));
            else
                printf("\t线性表中元素%d的前驱元素查找失败！\n", e1);
            break;
        case 9:
            // printf("\n----NextElem功能待实现！\n");
            printf("\t请输入要查找的元素：");
            int e2;
            ElemType pre;
            scanf("%d", &e2);
            if (NextElem(L, e2, pre) == OK)
                printf("\t线性表中元素%d的后继元素为：%d\n", e2, NextElem(L, e2, pre));
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
            
            break;
        case 14:
            printf("\n----ListDelete功能待实现！\n");
            break;
        case 15:
            printf("\n----ListDelete功能待实现！\n");
            break;
        case 16:
            printf("\n----ListDelete功能待实现！\n");
            break;
        case 17:
            printf("\n----ListDelete功能待实现！\n");
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