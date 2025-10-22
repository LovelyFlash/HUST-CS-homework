#include "def.h"
#include "stu.h"
int main() {
	LinkList L;
	int f,i,j;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=ListLength(L);
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
		j=ListLength(L);
		printf("%d", j);
	}
	return 1;
}