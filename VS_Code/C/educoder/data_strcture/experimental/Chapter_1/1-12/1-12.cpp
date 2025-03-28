#include "def.h"
#include "stu.h"
int main() {
	SqList L;
	int f,i,j;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
		j=ListTraverse(L); 
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表进行遍历操作！");
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
		j=ListTraverse(L);
		if(j==OK && !L.length) printf("空线性表\n");
		free(L.elem);
	}
	return 1;
}