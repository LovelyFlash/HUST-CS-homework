#include "def.h"
#include "stu.h"
int main() {
	LinkList L;
	int i,j;
	scanf("%d",&i);
	if (i==2) { 
		L=(LinkList) malloc(sizeof(LNode));
		L->next=NULL;
		j=ListEmpty(L);
		if (j==OK) printf("TRUE");
		else printf("未正确判空");
		free(L);
    }
	else if(i==1) {
		L=(LinkList) malloc(sizeof(LNode));
		L->next=(LNode*) malloc(sizeof(LNode));
		L->next->next=NULL;
		j=ListEmpty(L);
		if (j==ERROR) printf("FALSE");
		else printf("未正确判空");
		free(L->next);
		free(L);
    }
    else {
    	L=NULL;
		j=ListEmpty(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表判空");
	}
	return 1;
}