/*
任务描述
实验指导书P183 程序设计第（8）题

本关任务：删除子串。

输入输出示例
示例1：
输入：先输入字符串str,再输入字符串substr。
hello world!
ll

输出：输出删除子串后的结果字符串以及返回值。
heo world!
1

示例2：
输入：
hello world!
how

输出：
hello world!
0

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void edit(char *, char *);
int main()
{
    char *arr1, *arr2;
    char c = getchar();
    for(int i = 0; c != '\n'; i++)
    {
        *(arr1+i) = c;
    }
    for(int i = 0; c != '\n'; i++)
    {
        *(arr2+i) = c;
    }
    edit(arr1, arr2);
    return 0;
}

void edit(char *arr1, char *arr2)
{
    
}