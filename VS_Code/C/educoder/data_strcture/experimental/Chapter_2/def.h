#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#ifndef OVERFLOW
#define OVERFLOW -2
#endif

typedef int status;
typedef int ElemType; // 数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct LNode
{ // 单链表（链式结构）结点的定义
  ElemType data;
  struct LNode *next;
} LNode, *LinkList;

typedef struct
{                    // 线性链表的定义
  LinkList *elem;    // 存储空间基址
  char name[10][40]; // 链表名称
  int length;        // 当前长度
  int listsize;      // 当前分配的存储容量（以sizeof(LNode)为单位）
} List;