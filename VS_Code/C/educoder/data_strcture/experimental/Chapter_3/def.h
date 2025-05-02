#include "fun.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;

typedef struct
{
	BiTree *elem; // 存储二叉树的数组
	int length;   // 当前二叉树的数量
} List;