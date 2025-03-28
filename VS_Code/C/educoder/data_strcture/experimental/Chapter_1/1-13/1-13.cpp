#include "def.h"
#include "string.h"

#include "stu.h"
int main()
{
SqList L;
FILE *fp;
//char FileName[30];
int f,i=0,j,e;
//strcpy(FileName,"src/step13/list.dat");
scanf("%d",&f);
if (!f)
{
    	L.elem=NULL;
   		j=SaveList(L,"src/step13/list.dat");
   		if (j!=INFEASIBLE) printf("不能对不存在的线性表进行写文件操作！");
    	else 
      {
    		 L.elem=(ElemType *) malloc(sizeof(ElemType));
   			 j=LoadList(L,"src/step13/list.dat");
   			 if (j!=INFEASIBLE) printf("不能对已存在的线性表进行读文件操作！");
    	    else printf("INFEASIBLE"); 
    		 free(L.elem);
      }
}
else
     {
        L.elem=(ElemType *) malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L.length=0;
        L.listsize= LIST_INIT_SIZE;
        scanf("%d",&e);
        while (e)
        {
            L.elem[i++]=e;
            scanf("%d",&e);
        }
        L.length=i;
        j=SaveList(L,"src/step13/list.dat");
   		free(L.elem); 
		L.elem=NULL;
        j=LoadList(L,"src/step13/list.dat");
        printf("%d\n",L.length);
        for(i=0;i<L.length;i++) 
            printf("%d ",L.elem[i]);
     }
return 1;
}
