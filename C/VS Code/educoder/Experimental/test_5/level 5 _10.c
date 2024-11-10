/*
任务描述
实验指导书 P143 程序设计第（6）题
本关任务：消除类游戏是一种益智游戏，其核心规则是将一定的彼此相邻的相同元素配对消除。现给定一个n行m列的棋盘，棋盘中的每一个方格上放着一个棋子，每个棋子都有颜色，编号用1~9表示。当一行或一列上有连续3个或3个以上同色棋子时，这些棋子都被同时消除，对应的方格用0表示，请输出经过消除后的棋盘。例如，给定棋盘为：
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2
消除后为：
4 4 3 0 4
3 0 0 0 0
4 3 4 0 2
4 4 0 0 0

示例
输入（输入的前两个数字为棋盘的行数和列数）：
4 5
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2
输出（同行每个元素之间以空格分隔）：
4 4 3 0 4
3 0 0 0 0
4 3 4 0 2
4 4 0 0 0

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
void check(int board[20][20], int m, int n);

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int chessboard[20][20] = {0};
    check(chessboard, m, n);
    return 0;
}

void check(int board[20][20], int m, int n)
{
    // 输入棋盘数据
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            scanf("%d", &board[i][j]);
    }
    
    int color[20][20] = {0};

    // 行检查：连续三个及以上相同元素时，标记为1
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n - 2; j++)  // 只需要检查到 n-2
        {
            if(board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2])
            {
                color[i][j] = color[i][j+1] = color[i][j+2] = 1;
                int k = j + 3;
                while(k < n && board[i][k] == board[i][j])  // 检查更多的连续元素
                {
                    color[i][k] = 1;
                    k++;
                }
                j = k - 1;  // 跳过已标记的部分，避免重复判断
            }
        }
    }

    // 列检查：连续三个及以上相同元素时，标记为1
    for(int j = 0; j < n; j++)
    {
        for(int i = 0; i < m - 2; i++)  // 只需要检查到 m-2
        {
            if(board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j])
            {
                color[i][j] = color[i+1][j] = color[i+2][j] = 1;
                int k = i + 3;
                while(k < m && board[k][j] == board[i][j])  // 检查更多的连续元素
                {
                    color[k][j] = 1;
                    k++;
                }
                i = k - 1;  // 跳过已标记的部分，避免重复判断
            }
        }
    }

    // 输出结果
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(color[i][j] && j != n-1) 
                printf("0 ");
            else if(color[i][j] && j == n-1)
                printf("0\n");
            else if(color[i][j] == 0 && j != n-1)
                printf("%d ", board[i][j]);
            else
                printf("%d\n", board[i][j]);
        }
    }
}
