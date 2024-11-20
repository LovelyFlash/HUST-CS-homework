/*
任务描述
实验指导书 P139~140 程序改错与跟踪调试题，请按书中的步骤调试程序，找出函数strncate(t,s)和strdelc(s,c)中的错误并改正。

本任务改用在main函数中输入串a、串b以及待删除字符。

输入输出示例
输入：
Programming
Language
a
输出：
ProgrammingLanguage
ProgrmmingLnguge

开始你的任务吧，祝你成功！
*/

#include <stdio.h>
void strcate(char t[], char s[])
{
    printf("%s%s\n", t, s);
}

void strdelc(char s[], char t[], char c)
{
    int j, k, i;
    for(j = i = 0; s[j] != '\0'; j++)
        if(s[j] != c) s[i++] = s[j];
    for(j = k = 0; t[j] != '\0'; j++)
        if(t[j] != c) t[k++] = t[j];
    s[i] = '\0';
    t[k] = '\0';
}

int main()
{
    char a[80], b[100], c;
    scanf("%s %s %c", b, a, &c);
    strcate(b, a);
    strdelc(b, a, c);
    printf("%s%s\n", b, a);
    return 0;
}