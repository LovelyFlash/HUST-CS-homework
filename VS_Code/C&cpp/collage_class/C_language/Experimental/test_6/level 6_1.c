/*
任务描述
实验教材P179 6.3.2节 1.程序改错与跟踪调试
请按教材中的线下完成跟踪调试程序，找出错误并改正，然后提交程序进行评测。
在题目所给的源程序中，函数strcopy(t,s)的功能是将字符串s复制给字符串t，并返回串t的首地址。

输入输出示例
输入：
programming
language
输出：
programming
language

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
char *strcopy(char *, const char *);

int main(void)
{
    char s1[100], s2[100], *s3;
    scanf("%99s", s2);
    strcopy(s1, s2);
    printf("%s\n", s1);
    scanf("%99s", s2);
    s3 = strcopy(s1, s2);
    printf("%s\n", s3);
    return 0;
}

char *strcopy(char *t, const char *s)
{
    char *start = t;
    while((*t++ = *s++));
    return start;
}