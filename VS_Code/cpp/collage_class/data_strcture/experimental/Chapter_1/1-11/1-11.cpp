#include "def.h"
#include "stu.h"
int main() {
	SqList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		j=ListDelete(L,1,e); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("不能对不存在的线性表进行删除操作！");
	}
	else {
		L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
		L.length=0;
		L.listsize= 10;
		scanf("%d",&i);
		while (i) {
			L.elem[L.length++]=i;
			scanf("%d",&i);
		}
		scanf("%d",&i);
		j=ListDelete(L,i,e);
		if(j==ERROR) printf("ERROR\n");
		if(j==OK) printf("OK\n%d\n",e);
		for(i=0;i<L.length;i++)
        	printf("%d ",L.elem[i]);
		free(L.elem);
	}
	return 1;
}