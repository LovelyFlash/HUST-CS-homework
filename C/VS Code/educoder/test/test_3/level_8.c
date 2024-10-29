/*
任务描述
本关任务：实验课本P85  程序设计第（4）题
将输入的正文复制到输出，复制过程中将每行一个以上的空格字符用一个空格代替。

编程要求
在右侧编辑器补充代码

测试说明
平台会对你编写的代码进行测试：

测试输入：I  love     hust!
预期输出：I love hust!

开始你的任务吧，祝你成功！
*/
#include<stdio.h>

int main()
{
    char word[1000], c;
    int i, ch = 1;
    for(i = 0; (c = getchar()) != EOF; i++)
    {
            word[i] = c;
    }
    for(int j = 0; j < i; j++)
    {
        switch(ch)
        {
            case 1:
            {
                putchar(word[j]);
                if(word[j] == ' ') ch = 0;
                else ch = 1;
                break;
            }
            case 0:
            {
                if(word[j] == ' ') ch = 0;
                else
                {
                    putchar(word[j]);
                    ch = 1;
                }
                break;
            }
        }
    }
    return 0;
}