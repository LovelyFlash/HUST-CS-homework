#include "2-1\stu.h"
#include "2-2\stu.h"
#include "2-3\stu.h"
#include "2-4\stu.h"
#include "2-5\stu.h"
#include "2-6\stu.h"
#include "2-7\stu.h"
#include "2-8\stu.h"
#include "2-9\stu.h"
#include "2-10\stu.h"
#include "2-11\stu.h"
#include "2-12\stu.h"
#include "2-13\stu.h"

status reverseList(LinkList L)
{
    // 反转链表
    if (L == NULL || L->next == NULL)
        return ERROR;
    LinkList prev = NULL, curr = L->next, next = NULL;
    while (curr != NULL)
    {
        next = curr->next; // 保存下一个节点
        curr->next = prev; // 反转当前节点的指针
        prev = curr;       // 移动prev指针
        curr = next;       // 移动curr指针
    }
    L->next = prev; // 更新头结点的指针
    return OK;
}

status RemoveNthFromEnd(LinkList L, int n)
{
    // 删除链表的倒数第n个结点
    if (L == NULL || n <= 0)
        return ERROR;
    int Listlength = ListLength(L);
    if (n > Listlength)
        return ERROR;
    n = Listlength - n + 1;
    ElemType e;
    ListDelete(L, n, e);
    return OK;
}

status sortList(LinkList L)
{
    // 链表排序
    if (L == NULL || L->next == NULL)
        return ERROR;
    LinkList p, q, temp;
    temp = (LinkList)malloc(sizeof(LNode));
    for (p = L->next; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (p->data > q->data)
            {
                temp->data = p->data;
                p->data = q->data;
                q->data = temp->data;
            }
        }
    }
    return OK;
}

status saveListToFile(LinkList L, char *filename)
{
    // 保存链表到文件
    if (L == NULL || filename == NULL)
        return ERROR;
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
        return ERROR;
    LinkList p = L->next;
    while (p != NULL)
    {
        fprintf(fp, "%d ", p->data);
        p = p->next;
    }
    fclose(fp);
    return OK;
}

status LoadListFromFile(LinkList L, char *filename)
{
    // 从文件加载链表
    if (L == NULL || filename == NULL)
        return ERROR;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return ERROR;
    LinkList p = L->next;
    while (p != NULL)
    {
        fscanf(fp, "%d", &p->data);
        p = p->next;
    }
    fclose(fp);
    return OK;
}

status AddList(List &Lists, char *listname)
{
    // 添加链表
    if (Lists.length >= 10)
        return ERROR;
    LinkList L = (LinkList)malloc(sizeof(LinkList));
    L->next = NULL;
    if (L == NULL)
        return ERROR;
    strcpy(Lists.name[Lists.length], listname);
    Lists.length++;
    int elem;
    printf("\t请输入链表的元素（以0结束）：");
    while (1)
    {
        // 尾插法插入元素
        scanf("%d", &elem);
        if (elem == 0)
            break;
        LinkList newNode = (LinkList)malloc(sizeof(LNode));
        if (newNode == NULL)
            return ERROR;
        newNode->data = elem;
        newNode->next = NULL;
        if (L->next == NULL)
        {
            L->next = newNode; // 如果链表为空，则将新节点作为头结点的下一个节点
        }
        else
        {
            LinkList p = L->next;
            while (p->next != NULL)
                p = p->next;   // 找到链表的最后一个节点
            p->next = newNode; // 将新节点插入到链表的末尾
        }
    }
    Lists.elem[Lists.length - 1] = L; // 将新链表的指针存入链表数组
    return OK;
}

status RemoveList(List &Lists, char *listname)
{
    // 删除链表
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.name[i], listname) == 0)
        {
            free(Lists.elem[i]);
            for (int j = i; j < Lists.length - 1; j++)
            {
                Lists.elem[j] = Lists.elem[j + 1];
                strcpy(Lists.name[j], Lists.name[j + 1]);
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}

LocateList(List &Lists, char *listname)
{
    // 定位链表
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.name[i], listname) == 0)
            return i + 1;
    }
    return ERROR;
}
