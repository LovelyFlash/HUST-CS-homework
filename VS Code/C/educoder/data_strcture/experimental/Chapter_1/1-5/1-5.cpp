#include "def.h"
#include "stu.h"
int main() {
	SqList L;
	int f,i,j,c=0;
	scanf("%d",&f);
	if (!f) {
		L.elem=NULL;
    	L.length=10;
		j=ListLength(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表求表长");
    }
    else {
    	L.elem=(ElemType *) malloc(sizeof(ElemType));
    	scanf("%d",&i);
     	while (i) {
         ++c;
         scanf("%d",&i);
		}
		L.length=c;
		j=ListLength(L);
		printf("%d", j);
		free(L.elem);
	}
	return 1;
}