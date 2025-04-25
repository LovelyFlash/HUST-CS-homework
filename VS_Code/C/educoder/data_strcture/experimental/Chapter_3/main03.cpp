#include <bits/stdc++.h>
#include <windows.h>
#include "fun.c"
#include "def.h"

using namespace std;

class T
{
private:
    int data;
    int key;

public:
    T(int e)
    {
        data = e;
    }
    int getData()
    {
        return data;
    }
}

template <class T>
class BiTree
{
private:
    T data;
    BiTree<T> *lchild, *rchild;

public:
    BiTree(T e)
    {
        data = e;
        lchild = NULL;
        rchild = NULL;
    }
    
}

int
main()
{
    SetConsoleOutputCP(65001); // 设置控制台输出编码为UTF-8
    static int num = 0;
    int op = 1;
    while (op)
    {
        printf("\n\n");
        printf("      链表操作菜单 \n");
        printf("===============================================\n");
        printf("  基本操作：\n");
        printf("    1. 初始化链表           2. 销毁链表\n");
        printf("    3. 清空链表             4. 判断链表是否为空\n");
        printf("    5. 获取链表长度\n");
        printf("-----------------------------------------------\n");
        printf("  元素操作：\n");
        printf("    6. 获取指定位置元素       7. 查找元素位置\n");
        printf("    8. 获取前驱元素           9. 获取后继元素\n");
        printf("   10. 插入元素              11. 删除元素\n");
        printf("-----------------------------------------------\n");
        printf("  遍历操作：\n");
        printf("   12. 遍历链表\n");
        printf("-----------------------------------------------\n");
        printf("  附加操作：\n");
        printf("   13. 链表翻转             14. 删除链表的倒数第n个结点\n");
        printf("   15. 链表排序             16. 保存链表到文件\n");
        printf("   17. 从文件加载链表\n");
        printf("-----------------------------------------------\n");
        printf("  多链表管理：\n");
        printf("   18. 添加链表           19. 删除链表\n");
        printf("   20. 定位链表           21. 修改链表名称\n");
        printf("   22. 输出所有链表名称\n");
        printf("    0. 退出程序\n");
        printf("===============================================\n");
        printf("  正在操作的链表名称：%s\n", Lists.name[num - 1]);
        printf("  请选择你的操作 [0 ~ 22]: ");
        scanf("%d", &op);

        // 输出对应的功能名称
        switch (op)
        {
        case 1:
            printf("\t初始化链表\n");
            break;
        case 2:
            printf("\t销毁链表\n");
            break;
        case 3:
            printf("\t清空链表\n");
            break;
        case 4:
            printf("\t判断链表是否为空\n");
            break;
        case 5:
            printf("\t获取链表长度\n");
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
            printf("\t遍历链表\n");
            break;
        case 13:
            printf("\t链表翻转\n");
            break;
        case 14:
            printf("\t删除链表的倒数第n个结点\n");
            break;
        case 15:
            printf("\t链表排序\n");
            break;
        case 16:
            printf("\t保存链表到文件\n");
            break;
        case 17:
            printf("\t从文件加载链表\n");
            break;
        case 18:
            printf("\t添加链表\n");
            break;
        case 19:
            printf("\t删除链表\n");
            break;
        case 20:
            printf("\t定位链表\n");
            break;
        case 21:
            printf("\t修改链表名称\n");
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
    }
    return 0;
} // end of main