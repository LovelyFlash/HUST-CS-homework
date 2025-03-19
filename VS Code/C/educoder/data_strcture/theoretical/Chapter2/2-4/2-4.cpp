#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct node
{
  ElemType data;
  struct node *next;
} NODE, *LinkList;
#include "stu.h"
int main()
{
  LinkList L[3], p;
  ElemType x;
  int i;
  for (i = 0; i < 3; i++)
  {
    L[i] = p = (NODE *)malloc(sizeof(NODE));
    scanf("%d", &x);
    while (x)
    {
      p->next = (NODE *)malloc(sizeof(NODE));
      p = p->next;
      p->data = x;
      scanf("%d", &x);
    }
    p->next = NULL;
  }
  TriLinkList(L[0], L[1], L[2]);
  for (p = L[0]->next; p; p = p->next)
    printf(" %d", p->data);
  return 0;
}
