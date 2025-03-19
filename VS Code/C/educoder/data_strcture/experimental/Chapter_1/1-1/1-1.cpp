#include "def.h"
#include "stu.h"
int main()
{
SqList L;
int i,j;
scanf("%d",&i);
if (!i)
	{ 
	L.elem=NULL;
	j=InitList(L);
    if (L.elem==NULL)
    	printf("可能没有正确分配元素空间");
    if (L.length)
    	printf("未正确设置元素个数初始值");
    if (L.listsize!=LIST_INIT_SIZE)
    	printf("未正确设置元素空间容量");
    if (j==OK) {
               printf("OK");
               L.elem[0]=1;
               L.elem[L.listsize-1]=2;
               }
    }
else
     {
     L.elem=(ElemType *) malloc(sizeof(ElemType));
 	 j=InitList(L);
     if (j==INFEASIBLE) printf("INFEASIBLE");
     else printf("可能会对已经存在的线性表初始化");
     free(L.elem);
     }
return 1;
}
