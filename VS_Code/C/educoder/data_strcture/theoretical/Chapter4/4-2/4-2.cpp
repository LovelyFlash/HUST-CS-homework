#include "stdio.h"
#define  MAXSIZE 10000
typedef int ElemType;
typedef struct  {
   int       i,j;//非零元行、列下标
   ElemType    e;
 } Triple;        //三元组定义

typedef struct  {
   Triple  data[MAXSIZE+1];   //三元组从下标1开始存放
   int  mu,nu,tu;         //对于矩阵的行数、列数和非零元素值
 } TSMatrix;              //三元组顺序表的定义
#include "stu.h"
int main()
{
	TSMatrix A[3],B,C;
   int i,j;
   for(i=0;i<2;i++)
   {
   		scanf("%d%d%d",&A[i].mu,&A[i].nu,&A[i].tu);
   		for(j=1;j<=A[i].tu;j++)
   		 	scanf("%d%d%d",&A[i].data[j].i,&A[i].data[j].j,&A[i].data[j].e);
   }
   A[2]=ADD(A[0],A[1]);
   printf("%d %d %d\n",A[2].mu,A[2].nu,A[2].tu);
   for(i=1;i<=A[2].tu;i++)
   		printf("%d %d %d     ",A[2].data[i].i,A[2].data[i].j,A[2].data[i].e);
	return 1;
}