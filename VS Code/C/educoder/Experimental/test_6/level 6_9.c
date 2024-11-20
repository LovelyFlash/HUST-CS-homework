/*
任务描述
实验指导书 P182 程序设计第（6）题

本关任务：命令行实现对N个整数排序。

输入输出示例
输入：执行输入的命令，再按照命令输入N个整数。
sort 5 -d      (这是命令行)
4 3 8 5 1      (这是程序执行后输入的5个待排序数据) 

输出：输出排序后的结果。
8 5 4 3 1

注意：要求n个整数的存储无冗余。

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(int *arr, int quant);
void sort_d(int *arr, int quant);

int main(int argc, char **argv)
{
    int quant = atoi(argv[1]);
    int num[quant];
    for(int i = 0; i < quant; i++)
        scanf("%d", &num[i]);
    int *arr = num;
    if (argc > 2) {
        if (strcmp(argv[2], "-d") == 0) 
            sort(arr, quant);
    }
    else
        sort_d(arr, quant);
    for(int i = 0; i < quant; i++)
        printf("%d ", num[i]);
    return 0;
}

void sort(int *arr, int quant)
{
    for(int i = 0; i < quant; i++)
    {
        for(int j = 0; j < quant-i-1; j++)
        {
            if(*(arr+j) < *(arr+j+1))
            {
                int temp = *(arr+j);
                *(arr+j) = *(arr+j+1);
                *(arr+j+1) = temp;
            }
        }
    }
}
void sort_d(int *arr, int quant)
{
    for(int i = 0; i < quant; i++)
    {
        for(int j = 0; j < quant-i-1; j++)
        {
            if(*(arr+j) > *(arr+j+1))
            {
                int temp = *(arr+j);
                *(arr+j) = *(arr+j+1);
                *(arr+j+1) = temp;
            }
        }
    }
}