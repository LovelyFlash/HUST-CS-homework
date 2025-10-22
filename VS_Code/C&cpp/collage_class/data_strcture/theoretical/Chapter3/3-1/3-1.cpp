#include <stdio.h>
#include <stdlib.h>
#define N 100
typedef int ElemType;
typedef struct TWSTACK {
     ElemType elem[N];
     int top1,top2;
     } TWSTACK;
#include "stu.h"
int main()
{
int  i,f,e1,e2;
TWSTACK S;
scanf("%d",&f);
switch(f)
{
case 0: inistack(S);
      if (S.top1==0 && S.top2==N-1) printf("OK");
      else printf("初始化失败");
		break;
case 1:	S.top1=rand()%N;
		S.top2=S.top1-1;
      if (push(S,1,10))
      		{  printf("栈1入栈时未判满");break;}
		S.top1=rand()%N;
		S.top2=S.top1-1;
      if (push(S,2,10))
      		{  printf("栈2入栈时未判满");break;}
      S.top1=rand()%N;
		S.top2=S.top1;
      e1=rand();
      if (push(S,1,e1)==0 || S.top1!=S.top2+1|| S.elem[S.top1-1]!=e1)
      		{  printf("栈1入栈时有错");break;}
      S.top1=rand()%N;
		S.top2=S.top1;
      if (push(S,2,e1)==0 || S.top1!=S.top2+1 || S.elem[S.top2+1]!=e1)
      		{  printf("栈2入栈时有错");break;}
      printf("OK");
		break;
case 2: S.top1=0;
      S.top2=N-1;
      if (pop(S,1,e1) || pop(S,2,e1)) 
      	{  printf("出栈时未判空");break;}
      e1=rand();
      push(S,1,e1);
     if (pop(S,1,e2)==0 || e1!=e2) {printf("栈1出栈有错");break;} 
      e1=rand();
      push(S,2,e1);
     if (pop(S,2,e2)==0 || e1!=e2) {printf("栈2出栈有错");break;} 
       printf("OK");
		break;
case 3: i=1;
	   inistack(S);
      scanf("%d",&f);
      while (f)
      {
      	if (f==1) push(S,1,i++);
       else pop(S,1,e1);
	     scanf("%d",&f);
      }
      for(i=0;i<S.top1;i++)
      	printf(" %d",S.elem[i]);
}
return 1;

}