/*
任务描述
实验指导书 P142 程序设计第（3）题
本关任务：对第（2）题的程序增加查找功能（功能编号4）：输入一个C语言课程成绩值，用二分查找进行搜索。如果查找到有该成绩，则输出该成绩所有学生的姓名和C语言课程的成绩；否则，输出提示"not found"。

示例
输入：
依次输入功能编号1，学生数量n，每个学生的姓名和成绩，功能编号2，二分查找4，查找的成绩x：
1
3
xiaoming 90
xiaohong 79
zhangsan 83
2
4 90
0
输出：（如果有多个，一行一个学生；如果有相同分数，按照姓名字母排序输出）
xiaoming 90

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#include <string.h>
#define MAX_LEN 100

void input(char name[MAX_LEN][MAX_LEN], int score[], int n);
void sort(char name[MAX_LEN][MAX_LEN], int score[], int n);
void output(char name[MAX_LEN][MAX_LEN], int score[], int n);
void find(char name[MAX_LEN][MAX_LEN], int score[], int n);

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
            case 4:
                find(name, score, n);
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

void find(char name[MAX_LEN][MAX_LEN], int score[], int n)
{
    int target, left = 0, right = n - 1, mid;
    int found = 0;  // 用于标记是否找到目标分数
    scanf("%d", &target);

    while (left <= right)
    {
        mid = (left + right) / 2;
        
        if (target > score[mid])
            right = mid - 1;
        else if (target < score[mid])
            left = mid + 1;
        else
        {
            // 找到一个匹配的分数，向左侧查找最左边的匹配位置
            int start = mid;
            while (start > 0 && score[start - 1] == target)
            {
                start--;
            }

            // 从 start 开始向右打印所有相同分数的学生
            int i = start;
            while (i < n && score[i] == target)
            {
                printf("%s %d\n", name[i], score[i]);
                i++;
            }

            found = 1;
            break;  // 查找完成，退出循环
        }
    }

    // 如果未找到目标分数，输出 "not found"
    if (!found)
        printf("not found\n");
}