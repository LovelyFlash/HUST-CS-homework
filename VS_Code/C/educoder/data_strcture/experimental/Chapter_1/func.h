#include "1-1\stu.h"
#include "1-2\stu.h"
#include "1-3\stu.h"
#include "1-4\stu.h"
#include "1-5\stu.h"
#include "1-6\stu.h"
#include "1-7\stu.h"
#include "1-8\stu.h"
#include "1-9\stu.h"
#include "1-10\stu.h"
#include "1-11\stu.h"
#include "1-12\stu.h"

// 最大连续子数组和
int MaxSubArray(SqList L)
{
    int maxSum = L.elem[0], currentSum = 0;
    for (int i = 0; i < L.length; i++)
    {
        currentSum = (currentSum > 0) ? currentSum + L.elem[i] : L.elem[i];
        if (currentSum > maxSum)
        {
            maxSum = currentSum;
        }
    }
    return maxSum;
}

// 和为 K 的子数组个数
int SubArrayNum(SqList L, int k)
{
    int count = 0, sum = 0;
    for (int i = 0; i < L.length; i++)
    {
        sum = 0;
        for (int j = i; j < L.length; j++)
        {
            sum += L.elem[j];
            if (sum == k)
            {
                count++;
            }
        }
    }
    return count;
}

// 顺序表排序
void sortList(SqList &L)
{
    for (int i = 0; i < L.length - 1; i++)
    {
        for (int j = 0; j < L.length - i - 1; j++)
        {
            if (L.elem[j] > L.elem[j + 1])
            {
                int temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
            }
        }
    }
}

// 保存线性表到文件
void saveListToFile(SqList L, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("\t文件打开失败！\n");
        return;
    }
    fprintf(file, "%d\n", L.length); // 保存线性表长度
    for (int i = 0; i < L.length; i++)
    {
        fprintf(file, "%d ", L.elem[i]); // 保存线性表元素
    }
    fclose(file);
    printf("\t线性表已保存到文件：%s\n", filename);
}

// 从文件加载线性表
void loadListFromFile(SqList &L, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("\t文件打开失败！\n");
        return;
    }
    fscanf(file, "%d", &L.length); // 读取线性表长度
    L.elem = (ElemType *)malloc(L.length * sizeof(ElemType));
    for (int i = 0; i < L.length; i++)
    {
        fscanf(file, "%d", &L.elem[i]); // 读取线性表元素
    }
    fclose(file);
    printf("\t线性表已从文件加载：%s\n", filename);
}

// 多个线性表管理
void manageMultipleLists(LISTS &Lists)
{
    printf("\t当前共有 %d 个线性表：\n", Lists.length);
    for (int i = 0; i < Lists.length; i++)
    {
        printf("\t%d. %s\n", i + 1, Lists.elem[i].name);
    }
}

status AddList(LISTS &Lists, char ListName[])
{
    int n, e;
    printf("\t请输入要添加的顺序表数量：");
    scanf("%d", &n);
    while (n--)
    {
        printf("\t请输入要添加的顺序表名称：");
        scanf("%s", ListName);
        for (int i = 0; i <= Lists.length; i++)
        {
            if (strcmp(Lists.elem[i].name, ListName) == 0)
            {
                printf("\t顺序表名称已存在，请重新输入！\n");
                printf("\t请输入要添加的顺序表名称：");
                scanf("%s", ListName);
                i = 0;
            }
        }
        if (Lists.length >= 10)
        { // 假设 elem 数组的最大容量是 10
            printf("\t顺序表数量已达上限，无法添加更多顺序表！\n");
            return ERROR;
        }
        strcpy(Lists.elem[Lists.length].name, ListName);
        Lists.elem[Lists.length].L.length = 0; // 初始化为空线性表
        Lists.elem[Lists.length].L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
        if (!Lists.elem[Lists.length].L.elem)
        {
            printf("\t内存分配失败！\n");
            return OVERFLOW;
        }
        Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
        Lists.length++;
        printf("\t请输入要添加的顺序表元素（以 0 结束）：");
        scanf("%d", &e);
        while (e)
        {
            if (ListInsert(Lists.elem[Lists.length - 1].L, Lists.elem[Lists.length - 1].L.length + 1, e) != OK)
            {
                printf("\t插入元素失败！\n");
                return ERROR;
            }
            scanf("%d", &e);
        }
        printf("\t插入顺序表成功！\n");
    }
    return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i, j;
    for (i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            // 释放线性表的内存
            free(Lists.elem[i].L.elem);
            // 将后面的元素前移
            for (j = i; j < Lists.length - 1; j++)
            {
                Lists.elem[j] = Lists.elem[j + 1];
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR; // 未找到名称为 ListName 的线性表
    /********** End **********/
}

int LocateList(LISTS Lists, char ListName[])
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            return i + 1; // 返回逻辑序号
        }
    }
    return 0; // 未找到名称为 ListName 的线性表
    /********** End **********/
}