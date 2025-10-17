#include "def.h"
#include "stu.h"
int main() {
	SqList L;
	int f,i,j,e,next;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		L.length=3;
		j=NextElem(L,e,next); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表查找后继元素");
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
		scanf("%d",&e);
		j=NextElem(L,e,next);
		if(j==ERROR) printf("ERROR");
		if(j==OK) printf("OK\n%d",next);
		free(L.elem);
	}
	return 1;
}