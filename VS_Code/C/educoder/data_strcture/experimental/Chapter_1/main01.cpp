// 数据结构实验一：顺序表演示
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "def.h" // 相关数据类型的定义
#include "func.h" // 相关功能的定义

int main(void) {
    SqList L;
    int op = 1;
    while (op) {
        system("cls");	// 清空面板
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
        switch (op) {
        case 1:
            // printf("\n----IntiList功能待实现！\n");
            if (InitList(L) == OK) printf("线性表创建成功！\n");
            else printf("线性表创建失败！\n");
            getchar();getchar();
            break;
        case 2:
            // printf("\n----DestroyList功能待实现！\n");     
            getchar();getchar();
            break;
        case 3:
            printf("\n----ClearList功能待实现！\n");
            getchar();getchar();
            break;
        case 4:
            printf("\n----ListEmpty功能待实现！\n");
            getchar();getchar();
            break;
        case 5:
            printf("\n----ListLength功能待实现！\n");
            getchar();getchar();
            break;
        case 6:
            printf("\n----GetElem功能待实现！\n");
            getchar();getchar();
            break;
        case 7:
            printf("\n----LocateElem功能待实现！\n");
            getchar();getchar();
            break;
        case 8:
            printf("\n----PriorElem功能待实现！\n");
            getchar();getchar();
            break;
        case 9:
            printf("\n----NextElem功能待实现！\n");
            getchar();getchar();
            break;
        case 10:
            printf("\n----ListInsert功能待实现！\n");
            getchar();getchar();
            break;
        case 11:
            printf("\n----ListDelete功能待实现！\n");
            getchar();getchar();
            break;
        case 12:
            //printf("\n----ListTrabverse功能待实现！\n");     
            if (!ListTraverse(L)) printf("线性表是空表！\n");
            getchar();getchar();
            break;
        case 13:
            printf("\n----ListDelete功能待实现！\n");
            getchar();getchar();
            break;
        case 14:
            printf("\n----ListDelete功能待实现！\n");
            getchar();getchar();
            break;
        case 15:
            printf("\n----ListDelete功能待实现！\n");
            getchar();getchar();
            break;
        case 16:
            printf("\n----ListDelete功能待实现！\n");
            getchar();getchar();
            break;
        case 17:
            printf("\n----ListDelete功能待实现！\n");
            getchar();getchar();
            break;
        case 0:
            break;
        } // end of switch
    } // end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
} // end of main()