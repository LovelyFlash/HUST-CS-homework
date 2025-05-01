#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
#include "stu.h"
int main()
{
    int n,i,k;
    ElemType *p;
    scanf("%d%d",&n,&k);
    p=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        p[i]=i+1;
    ShiftRightCircular(p,n,k);
    for(i=0;i<n;i++)
        printf(" %d",p[i]);
    return 1;
}
