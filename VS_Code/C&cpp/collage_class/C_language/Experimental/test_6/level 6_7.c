/*
任务描述
实验教材P182 程序设计第（2）题

定义函数RemoveSame(a,n)，去掉有n个元素的有序整数序列a中的重复元素，返回去重后序列的长度。

示例
输入：
5
3 3 3 6 6

输出：注意不需要输出结果长度后的内容
3 6
2

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#define MAX_SIZE 100

void Remove(int num[], int n);

int main()
{
    int n, num[MAX_SIZE];
    scanf("%d", &n);

    if (n > MAX_SIZE) 
    {
        return 1;
    }

    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &num[i]);
    }

    Remove(num, n);
    return 0;
}

void Remove(int num[], int n)
{
    int count[MAX_SIZE] = {0};
    int *p = num;
    int j = 0, result[100];

    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (*(p + i) == *(p + j)) 
            {
                count[j] = 1; 
            }
        }
    }


    for (int i = 0; i < n; i++) 
    {
        if (count[i] != 1) 
        {
            result[j++] = *(p+i);
        }
    }
    for (int i = 0; i < j; i++) 
    {
        printf("%d", result[i]);
        if(i != j-1) printf(" ");
    }
    printf("\n%d", j);
}
