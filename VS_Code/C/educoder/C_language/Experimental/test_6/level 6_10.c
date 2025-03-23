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

void edit(char *, char *, int len);
int main()
{
    char *arr1 = (char *)malloc(100 * sizeof(char));
    char *arr2 = (char *)malloc(100 * sizeof(char));
    char c;
    int i = 0;
    for(i = 0; (c = getchar()) != '\n'; i++)
    {
        *(arr1+i) = c;
    }
    *(arr1+i) = '\0';
    for(i = 0; (c = getchar()) != EOF; i++)
    {
        *(arr2+i) = c;
    }
    *(arr2+i) = '\0';
    int len = strlen(arr2);
    edit(arr1, arr2, len);
    free(arr1);
    free(arr2);
    return 0;
}

void edit(char *arr1, char *arr2, int len)
{
    int sign = 0;
    for(int k=0, i=0; *(arr1+i+len-1) != '\0'; i++)
    {
        for(k = 0; k <= len; k++)
        {
            if(k!=len && *(arr1+i+k) != *(arr2+k)) break;
            else if(k == len)
            {
                for(int m = i; *(arr1+m)!='\0'; m++)
                *(arr1+m) = *(arr1+m+k);
                sign = 1;
                i--;
            }
        }
    }
    printf("%s\n%d", arr1, sign);
}