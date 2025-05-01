#include "stdio.h"
#include "stdlib.h"

 int suanfa(int a[],int n, int arrsize)
{
/**********begin*********/
  if (n > arrsize) return 0;
  a[0] = 2;
  for (int i = 1; i < n; i++) {
    a[i] = a[i - 1] * (i + 1) * 2;
    if (a[i] > 0x7fffffff || a[i] <= 0) return 0;
  }
  return 1;
/**********end**********/
}

int main()
 {
    int k,*a,arrsize;
    scanf("%d%d",&k,&arrsize);
    a=(int *)malloc(arrsize*sizeof(int));
    if (suanfa(a,k,arrsize))
        for(int i=0;i<k;i++)
            printf(" %d",a[i]);
    else printf("ERROR");
    return 1;
 }
 
