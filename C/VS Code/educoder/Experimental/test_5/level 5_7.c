/*
任务描述
实验指导书 P142 程序设计第（2）题
本关任务：编写一个C程序，要求采用模块化设计思想，将相关功能用函数实现，并提供菜单选项，每次程序运行结束后需通过功能0退出程序。该程序具有以下功能：

退出程序；
输入n个学生的姓名和C语言课程的成绩；
将成绩按从高到低的次序排序，姓名同时进行相应调整（成绩相同的按姓名首字母排序，首字母相同的按第二个字母排序，依次类推）；
输出所有学生的姓名和C语言课程的成绩。
示例
输入1：
依次输入功能编号1，学生数量n，每个学生的姓名和成绩，功能编号3：
1          (功能编号)
3          (学生人数)
xiaoming 90   (学生姓名和成绩)
xiaohong 79
zhangsan 83
3               (功能编号)
0                (功能编号)
输出1：
xiaoming 90
xiaohong 79
zhangsan 83

输入2：
依次输入功能编号1，学生数量n，每个学生的姓名和成绩，功能编号2，功能编号3：
1          (功能编号)
3          (学生人数)
xiaoming 79   (学生姓名和成绩)
xiaohong 79
zhangsan 83
2   (功能编号，成绩相同的按姓名排序)
3   (功能编号) 
0       (功能编号)

输出2：
zhangsan 83
xiaohong 79
xiaoming 79

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#define MAX_LEN 100

void input(int name[MAX_LEN][MAX_LEN], int score[], int n);
void sort(int name[MAX_LEN][MAX_LEN], int score[], int n);
void output(int name[MAX_LEN][MAX_LEN], int score[], int n);

int main()
{
    int func = -1, n, score[MAX_LEN];
    int name[MAX_LEN][MAX_LEN];
    while(func)
    {
        scanf("%d", func);
        switch(func)
        {
            case 1:
            {
                input(name, score, n);
                break;
            }
            case 2:
            {
                sort(name, score, n);
                break;
            }
            case 3:
            {
                output(name, score, n);
                break;
            }
            default:
            {
                return 0;
            }
        }
    }
    return 0;
}

void input(int name[MAX_LEN][MAX_LEN], int score[], int n)
{
    char c;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; (c = getchar()) != ' '; j++)
        {
            name[i][j] = (int)c;
            name[i][j+1] = '\0';
        }
        scanf("%d", score[i]);
    }
}

void sort(int name[MAX_LEN][MAX_LEN], int score[], int n)
{
    
}

void output(int name[MAX_LEN][MAX_LEN], int score[], int n)
{

}