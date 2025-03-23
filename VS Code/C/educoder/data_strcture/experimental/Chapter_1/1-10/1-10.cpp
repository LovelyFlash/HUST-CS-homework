#include "def.h"
#include "stu.h"
int main()
{
SqList L;
int f,i,j,e;
scanf("%d",&f);
if (!f)
	{
	    L.elem=NULL;
        j=ListInsert(L,1,1);
        if (j==INFEASIBLE) printf("INFEASIBLE");
        else printf("不能对不存在的线性表进行插入操作！");
	}

else
     {
     L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
     L.length=0;
     L.listsize= 10;
     scanf("%d",&i);
     while (i)
     {
         L.elem[L.length++]=i;
         scanf("%d",&i);
     }
     scanf("%d%d",&i,&e);
     j=ListInsert(L,i,e);
     printf("%s\n", j==OK? "OK" : j==ERROR? "ERROR" : "OVERFLOW");
     for(i=0;i<L.length;i++)
        printf("%d ",L.elem[i]);
     }
return 1;
}
