#include "def.h"
#include "stu.h"
int main() {
	SqList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		j=GetElem(L,2,e); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表获取元素");
		
	}
	else {
		L.elem=(ElemType *) malloc(sizeof(ElemType)*10);
		L.length=0;
		L.listsize= 100;
		scanf("%d",&i);
		while (i) {
			L.elem[L.length++]=i;
			scanf("%d",&i);
		}
		scanf("%d",&i);
		j=GetElem(L,i,e);
		if(j==OK) printf("OK\n%d",e);
		if(j==ERROR) printf("ERROR");
		free(L.elem);
	}
	return 1;
}