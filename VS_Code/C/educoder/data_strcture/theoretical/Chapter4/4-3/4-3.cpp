#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct {
	char *ch;
   int length;
} HString;
#include "stu.h"
int main()
{
HString S[3];
char buf[100],i,j;
for(i=0;i<3;i++)
{
	fgets(buf,100,stdin);
	S[i].length=strlen(buf)-1;  //-1是去掉回车符号
	S[i].ch=(char *)malloc(S[i].length);
	for(j=0;j<S[i].length; j++)
		S[i].ch[j]=*(buf+j);
}
Replace(S[0],S[1],S[2]);
printf("S的长度：%d\n",S[0].length);
for(i=0;i<S[0].length;i++)
	putchar(S[0].ch[i]);
return 1;

}