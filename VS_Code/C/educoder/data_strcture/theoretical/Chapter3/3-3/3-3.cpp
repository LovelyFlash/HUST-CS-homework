#include "stdio.h"
typedef char ElemType;
#define MAXLENGTH 100
#define N 100
typedef struct TWSTACK {
     ElemType elem[N];
     int top1,top2;
     } TWSTACK;
typedef struct QUEUE {
     ElemType elem[MAXLENGTH];
     int front,length;
     } QUEUE;
#include "../3-1/stu.h"
#include "../3-2/stu.h"
#include "stu.h"


int main()
{
    char str[100];
    scanf("%s",str);
    printf("%s",isPalindrome(str)?"YES":"NO");
    return 0;
}