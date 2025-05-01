#include "def.h"
#include "ctype.h"
#include "string.h"
#define free free0
#include "stu.h"
#undef free

struct ptr{
    void *pused[100],*pfree[100];
    int len_used,len_free;
    } pm;
void free0(void *p)
{
    pm.pfree[pm.len_free++]=p;
    free(p);
}

int main() {
	LinkList L;
	int f,i,j,e;
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=ListDelete(L,1,e);
		if (j==INFEASIBLE) printf("INFEASIBLE");
    	else printf("不能对不存在的线性表进行删除操作！");
    }
    else {
    	L=(LinkList) malloc(sizeof(LNode));
		L->next=NULL;
		LNode *s,*r=L;
    	scanf("%d",&i);
     	while (i) {
			pm.pused[pm.len_used++]=s=(LNode*) malloc(sizeof(LNode));
			s->data=i;
			r->next=s;
			r=s;
			scanf("%d",&i);
		}
		r->next=NULL;
		scanf("%d",&i);
		j=ListDelete(L,i,e);
		if(j==ERROR) printf("ERROR\n");
		if(j==OK) {
            for(i=0;i<pm.len_used;i++)
                if (pm.pfree[0]==pm.pused[i]) break;
			if (pm.len_free!=1 || i>=pm.len_used)
            {
                printf("未正确释放数据元素空间");
                return 1;
            }
            printf("OK\n%d\n",e);
		}
		for(s=L->next;s;s=s->next)
			printf("%d ",s->data);
	}
	return 1;
}
