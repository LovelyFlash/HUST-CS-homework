#include "def.h"
#include "stu.h"
#include "string.h"

int main() {
	LinkList L;
	int f,i=0,j,e;
	FILE *fp;
	char FileName[30];
	strcpy(FileName,"src/step13/list.dat");
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=SaveList(L,"src/step13/list.dat");
		if (j==INFEASIBLE) printf("INFEASIBLE\n");
    	else printf("不能对不存在的线性表进行写文件操作！\n");
    	
    	L=(LinkList) malloc(sizeof(LNode));
    	L->next=NULL;
        j=LoadList(L,"");
        if (j==INFEASIBLE) printf("INFEASIBLE\n");
        else printf("不能对已存在的线性表进行写操作！否则会覆盖原数据，造成数据丢失\n");
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
		j=SaveList(L,"src/step13/list.dat");
		if(j==OK) printf("OK\n");
    	while(L)
    	{
        	s = L->next;
            L->data=0;
        	free(L);
        	L = s;
    	}
		j=LoadList(L,"src/step13/list.dat");
		if(j==OK) printf("OK\n");
		for(s=L->next;s;s=s->next)
			printf("%d ",s->data);
	}
	return 1;
}