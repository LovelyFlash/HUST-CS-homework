/*
任务描述
本关任务：实验教材P179 6.3.2节 2.程序完善和修改替换 第（1）题
strsort用于对字符串进行升序排序，再主函数中输入N个字符串存入通过malloc动态分配的存储空间，然后调用strsort对这N个串按字典升序排序。

请填写合适代码完善程序

示例
输入：首先输入N，然后输入N个字符。
3
C
Python
Java
输出：
C
Java
Python

开始你的任务吧，祝你成功！
*/
/* 实验6程序完善与修改替换第（1）题源程序：字符串升序排序 */
/* 实验6程序完善与修改替换第（1）题源程序：字符串升序排序 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
/* 对指针数组s指向的size个字符串进行升序排序 */
void strsort(char *s[], int size)
{
    char *temp;
    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (strcmp(s[j], s[j + 1]) > 0)
            {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
}

int main()
{
    int i, n;
    scanf("%d", &n);
    getchar();
    char *s[n], t[50];
    for (i = 0; i < n; i++)
    {
        fgets(t, sizeof(t), stdin);
        t[strcspn(t, "\n")] = '\0';
        s[i] = (char *)malloc(strlen(t) + 1);
        strcpy(s[i], t);
    }
    strsort(s, n);
    for (i = 0; i < n; i++)
        puts(s[i]);
    return 0;
}