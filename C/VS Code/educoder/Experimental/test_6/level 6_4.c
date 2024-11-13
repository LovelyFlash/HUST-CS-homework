/*
任务描述
本关任务：实验教材P179 6.3.2节 2.程序完善和修改替换 第（2）题第①问
通过函数指针和菜单选择来调用库函数实现字符串操作：串复制strcpy、串连接strcat或串分解strtok。请完善该程序
( 函数strtok的实现和使用参见理论课教材例8.19)

输入输出示例
输入：
1
the more you learn,
the more you get.
2
the more you learn,
the more you get.
3
www.educoder.net
.
4

输出：
the more you get.
the more you learn,the more you get.
www

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#include <string.h>

int main()
{
    int func = 0;
    char string1[100], string2[100];
    char *result, c;
    char *(*p)(char *, const char *); 
    while (1)
    {
        scanf("%d", &func);
        getchar();
        
        if (func == 4) break;
        fgets(string1, sizeof(string1), stdin);
        string1[strcspn(string1, "\n")] = '\0'; 
        fgets(string2, sizeof(string1), stdin);
        string1[strcspn(string1, "\n")] = '\0'; 
            switch(func)
            {
                case 1:
                    p = strcpy;
                    break;
                case 2:
                    p = strcat;
                        break;
                case 3:
                    p = strtok;
                    break;
            }
        result = p(string1, string2);
        printf("%s", result);
    }
    return 0;
}