#include<stdio.h>

/**
  请使用递归定义此函数，将输入的一行字符逆序输出。
  字符的输入和输出用getchar和putchar函数
 **/
void myrever(void)
{
    char c = getchar();
    if (c != '\n') {     // 递归基准条件：遇到换行符结束递归
        myrever();       // 递归调用
        putchar(c);      // 逆序输出字符
    }
}