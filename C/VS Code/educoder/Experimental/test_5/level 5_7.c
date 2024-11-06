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
#include <string.h>
#define MAX_LEN 100

void input(char name[MAX_LEN][MAX_LEN], int score[], int n);
void sort(char name[MAX_LEN][MAX_LEN], int score[], int n);
void output(char name[MAX_LEN][MAX_LEN], int score[], int n);

int main()
{
    int func = -1, n = 0, score[MAX_LEN] = {0};
    char name[MAX_LEN][MAX_LEN];
    
    while (func)
    {
        scanf("%d", &func);
        if (n == 0) scanf("%d", &n);
        
        switch (func)
        {
            case 1:
                input(name, score, n);
                break;
            case 2:
                sort(name, score, n);
                break;
            case 3:
                output(name, score, n);
                break;
            default:
                return 0;
        }
    }
    
    return 0;
}

void input(char name[MAX_LEN][MAX_LEN], int score[], int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d", name[i], &score[i]);
    }
}

void sort(char name[MAX_LEN][MAX_LEN], int score[], int n)
{
    int temp_score;
    char temp_name[MAX_LEN];
    
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            // 如果分数更高，或者分数相等但名字的字母顺序更靠前，就进行交换
            if (score[j] < score[j + 1] || 
                (score[j] == score[j + 1] && strcmp(name[j], name[j + 1]) > 0))
            {
                // 交换分数
                temp_score = score[j];
                score[j] = score[j + 1];
                score[j + 1] = temp_score;
                
                // 交换名字
                strcpy(temp_name, name[j]);
                strcpy(name[j], name[j + 1]);
                strcpy(name[j + 1], temp_name);
            }
        }
    }
}

void output(char name[MAX_LEN][MAX_LEN], int score[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", name[i], score[i]);
    }
}