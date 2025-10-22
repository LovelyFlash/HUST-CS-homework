#include "def.h"
#include "stu.h"
void PreOrderTraverse(BiTree T)
{
    if (T)
    {
        printf(" %d,%s",T->data.key,T->data.others);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void InOrderTraverse(BiTree T)
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        printf(" %d,%s",T->data.key,T->data.others);
        InOrderTraverse(T->rchild);
    }
}

int main()
{
TElemType definition[100];
BiTree T;
int ans,i=0;
do {
	scanf("%d%s",&definition[i].key,definition[i].others);
} while (definition[i++].key!=-1);
ans=CreateBiTree(T,definition);
if (ans==OK)
{
    PreOrderTraverse(T);
    printf("\n");
    InOrderTraverse(T);
}
else printf("关键字不唯一");
return 1;
}
