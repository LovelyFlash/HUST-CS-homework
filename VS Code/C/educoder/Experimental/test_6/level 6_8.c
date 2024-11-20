/*
任务描述
实验指导书P182 程序设计第（4）题

输入图像矩阵的行数n和列数m，接下来的n行每行输入m个整数，表示输入的图像，输出原始矩阵逆时针旋转90°后的矩阵。

输入输出示例
输入：
2 3
1 5 3
3 2 4

输出：
3 4
5 2
1 3

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Change(int **arr, int rows, int cols);

int main()
{
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    int **arr = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) 
    {
        arr[i] = (int *)malloc(cols * sizeof(int));
    }
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    Change(arr, rows, cols);
}

void Change(int **arr, int rows, int cols)
{
    /*int **matrix = (int **)malloc(cols * sizeof(int *));
    for (int i = 0; i < cols; i++) 
    {
        matrix[i] = (int *)malloc(rows * sizeof(int));
    }
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            matrix[cols-j-1][i] = arr[i][j]; 
        }
    }*/
    
    for(int i = cols-1; i >=0; i--)
    {
        for(int j = 0; j < rows; j++)
        {
            printf("%d", arr[j][i]);
            if(j != rows-1) printf(" ");
        }
        printf("\n");
    }
}