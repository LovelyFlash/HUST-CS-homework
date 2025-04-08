#include "def.h"
#include "stu.h"
int main() {
	LinkList L;
	int f,i,j,e,pre;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=PriorElem(L,e,pre);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表求表长");
    }
    else {
    	L=(LinkList) malloc(sizeof(LNode));
		L->next=NULL;
		LNode *s,*r=L;
    	scanf("%d",&i);
     	while (i) {
			s=(LNode*) malloc(sizeof(LNode));
			s->data=i;
			r->next=s;
			r=s;
			scanf("%d",&i);
		}
		r->next=NULL;
		scanf("%d",&e);
		j=PriorElem(L,e,pre);
		if(j==ERROR) printf("ERROR");
		if(j==OK) printf("OK\n%d",pre);
	}
	return 1;
}