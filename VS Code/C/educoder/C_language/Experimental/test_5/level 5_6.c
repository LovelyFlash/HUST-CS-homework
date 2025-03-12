/*
任务描述
实验指导书 P142 程序设计第（1）题
本关任务：输入一个整数，将它在内存中的二进制表示的每一位转换成对应的数字字符并且存放到一个字符数组中，然后输出该整数的二进制表示（32位有符号整数，输出每4位用空格分隔）。

示例
输入：
1
输出：
0000 0000 0000 0000 0000 0000 0000 0001

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
void trans(int num[], unsigned int a, int i)
{
    if(a/2 != 0) 
    {
        num[i] = a%2;
        trans(num, a/2, i+1);
    }
    else
    {
        if(a == 1) num[i] = 1;
        else num[i] = 0;
        for(int k = 31; k >= 0; k--)
        if(k%4 == 0) printf("%d ", num[k]);
        else printf("%d", num[k]);
    }        
}
    

int main()
{
    int num[32] = {0}, a, i=0;
    scanf("%d", &a);
    unsigned int ua = (unsigned int)a;
    trans(num, ua, i);
    return 0;
}