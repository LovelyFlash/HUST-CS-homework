/*
任务描述
实验教材P182，程序设计第（1）题
本关任务：编写一个程序，从整形变量的高字节开始，依次取出每字节的高4位和低4位并以十六进制数字字符的形式进行显示，要求通过指针取出每字节。

平台中long为8字节，所以将书中题目的长整形改为整形。

输入输出示例
输入：
123456

输出：十六进制的字母小写输出(2个十六进制数之间空格隔开)
0 0 0 1 e 2 4 0

开始你的任务吧，祝你成功！
*/
#include <stdio.h>

int main()
{
    int num;
    scanf("%d", &num);
    unsigned char *p = (unsigned char*)&num;
    p += sizeof(int) - 1;
    for(int i = 0; i < sizeof(int); i++)
    {
        unsigned char high = (*p >> 4) & 0x0f;
        unsigned char low = *p & 0x0f;
        printf("%x %x ", high, low);
        p--;
    }
}