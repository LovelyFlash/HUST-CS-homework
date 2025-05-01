#include "def.h"
#include "stu.h"

int main() {
	LinkList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=ListTraverse(L);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("可能会对不存在的线性表进行遍历操作！");
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
		j=ListTraverse(L);
		if(j==OK && L->next==NULL) printf("空线性表");
	}
	return 1;
}