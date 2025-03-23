/*
任务描述
实验指导书 P143 程序设计第（5）题
本关任务：编写函数strnins(t,s,n),其功能是：将串s插入串t串的第n个字符的后面，编写main函数测试strnins函数的正确性。

示例
输入（依次为t、s、n）：
iyou
love
1
输出：
iloveyou

开始你的任务吧，祝你成功！
*/
#include <stdio.h>

void strnins(char t[], char s[], int n);

int main()
{
    char t[100], s[100];
    int n;
    scanf("%s %s %d", t, s, &n);
    strnins(t, s, n);
    return 0;
}

void strnins(char t[], char s[], int n)
{
    int len_s, len_t;
    for(len_s = n; s[len_s] != '\0'; len_s++);
    for(int i = n, k = 0; i < len_s + n; i++, k++)
    {
        t[i+len_s] = t[i];
        t[i] = s[k];
    }
    printf("%s", t);
}