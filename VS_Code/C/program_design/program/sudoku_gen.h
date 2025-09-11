#ifndef SUDOKU_GEN_H
#define SUDOKU_GEN_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 百分号数独生成与SAT规约
// 变量编号: cell(i,j,d) => 1~729, i,j,d∈[1,9]
#define N 9
#define VAR(i, j, d) ((i) * 81 + (j) * 9 + (d) + 1)

// 判断撇对角线（右上到左下）
static inline bool is_left_diag(int i, int j)
{
    return (i + j) == (N - 1);
}
// 判断窗口编号（只对左上和右下3x3区域加约束，0=左上，1=右下，其它返回-1）
static inline int window_id(int i, int j)
{
    if (i >= 1 && i <= 3 && j >= 1 && j <= 3)
        return 0; // 2~4行2~4列
    if (i >= 5 && i <= 7 && j >= 5 && j <= 7)
        return 1; // 6~8行6~8列
    return -1;
}

// 打印数独
void print_sudoku(int grid[N][N])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// 检查当前位置是否合法
static bool is_valid(int grid[N][N], int row, int col, int num)
{
    for (int x = 0; x < N; ++x)
    {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (grid[startRow + i][startCol + j] == num)
                return false;
    // 撇对角线约束
    if (is_left_diag(row, col))
    {
        for (int k = 0; k < N; ++k)
        {
            int x = k, y = N - 1 - k;
            if (is_left_diag(x, y) && grid[x][y] == num)
                return false;
        }
    }
    // 窗口约束
    int win = window_id(row, col);
    if (win != -1)
    {
        for (int i = 1; i <= 3; ++i)
            for (int j = 1; j <= 3; ++j)
                if (win == 0 && grid[i][j] == num)
                    return false;
        for (int i = 5; i <= 7; ++i)
            for (int j = 5; j <= 7; ++j)
                if (win == 1 && grid[i][j] == num)
                    return false;
    }
    return true;
}

// 回溯生成一个合法的百分号数独
static bool fill_grid(int grid[N][N], int pos)
{
    if (pos == N * N)
        return true;
    int row = pos / N, col = pos % N;
    if (grid[row][col] != 0)
        return fill_grid(grid, pos + 1);
    int nums[N];
    for (int i = 0; i < N; ++i)
        nums[i] = i + 1;
    // 洗牌
    for (int i = N - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
    for (int i = 0; i < N; ++i)
    {
        if (is_valid(grid, row, col, nums[i]))
        {
            grid[row][col] = nums[i];
            if (fill_grid(grid, pos + 1))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

// 生成一个完整的百分号数独
void generate_percent_sudoku(int grid[N][N])
{
    memset(grid, 0, sizeof(int) * N * N);
    fill_grid(grid, 0);
}

void puzzle_generate(int grid[N][N], int puzzle[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            puzzle[i][j] = grid[i][j];
    int holes = 40; // 挖40个空
    while (holes > 0)
    {
        int i = rand() % N;
        int j = rand() % N;
        if (puzzle[i][j] != 0)
        {
            puzzle[i][j] = 0;
            --holes;
        }
    }
}
// 规约为SAT（DIMACS CNF格式）
void sudoku_to_SAT(int grid[N][N], FILE *out)
{
    int clause_count = 0;
    // 先写头部占位
    long header_pos = ftell(out);
    fprintf(out, "p cnf 729 0\n");
    // 1. 每格至少一个数
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            for (int d = 0; d < N; ++d)
                fprintf(out, "%d ", VAR(i, j, d));
            fprintf(out, "0\n");
            clause_count++;
        }
    // 2. 每格至多一个数
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int d1 = 0; d1 < N; ++d1)
                for (int d2 = d1 + 1; d2 < N; ++d2)
                {
                    fprintf(out, "-%d -%d 0\n", VAR(i, j, d1), VAR(i, j, d2));
                    clause_count++;
                }
    // 3. 行、列、宫、撇对角线、窗口约束
    for (int d = 0; d < N; ++d)
    {
        // 行
        for (int i = 0; i < N; ++i)
            for (int j1 = 0; j1 < N; ++j1)
                for (int j2 = j1 + 1; j2 < N; ++j2)
                {
                    fprintf(out, "-%d -%d 0\n", VAR(i, j1, d), VAR(i, j2, d));
                    clause_count++;
                }
        // 列
        for (int j = 0; j < N; ++j)
            for (int i1 = 0; i1 < N; ++i1)
                for (int i2 = i1 + 1; i2 < N; ++i2)
                {
                    fprintf(out, "-%d -%d 0\n", VAR(i1, j, d), VAR(i2, j, d));
                    clause_count++;
                }
        // 宫
        for (int bi = 0; bi < 3; ++bi)
            for (int bj = 0; bj < 3; ++bj)
                for (int k1 = 0; k1 < N; ++k1)
                    for (int k2 = k1 + 1; k2 < N; ++k2)
                    {
                        int i1 = bi * 3 + k1 / 3, j1 = bj * 3 + k1 % 3;
                        int i2 = bi * 3 + k2 / 3, j2 = bj * 3 + k2 % 3;
                        fprintf(out, "-%d -%d 0\n", VAR(i1, j1, d), VAR(i2, j2, d));
                        clause_count++;
                    }
        // 撇对角线
        int diag[N], cnt = 0;
        for (int i = 0; i < N; ++i)
        {
            int j = N - 1 - i;
            diag[cnt++] = i;
        }
        for (int k1 = 0; k1 < N; ++k1)
            for (int k2 = k1 + 1; k2 < N; ++k2)
            {
                fprintf(out, "-%d -%d 0\n", VAR(diag[k1], N - 1 - diag[k1], d), VAR(diag[k2], N - 1 - diag[k2], d));
                clause_count++;
            }
        // 窗口
        for (int w = 0; w < 2; ++w)
        {
            int cells[9][2], cnt = 0;
            if (w == 0)
            {
                for (int i = 1; i <= 3; ++i)
                    for (int j = 1; j <= 3; ++j)
                    {
                        cells[cnt][0] = i;
                        cells[cnt][1] = j;
                        cnt++;
                    }
            }
            else
            {
                for (int i = 5; i <= 7; ++i)
                    for (int j = 5; j <= 7; ++j)
                    {
                        cells[cnt][0] = i;
                        cells[cnt][1] = j;
                        cnt++;
                    }
            }
            for (int k1 = 0; k1 < cnt; ++k1)
                for (int k2 = k1 + 1; k2 < cnt; ++k2)
                {
                    fprintf(out, "-%d -%d 0\n", VAR(cells[k1][0], cells[k1][1], d), VAR(cells[k2][0], cells[k2][1], d));
                    clause_count++;
                }
        }
    }
    // 5. 预填数字
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (grid[i][j])
            {
                fprintf(out, "%d 0\n", VAR(i, j, grid[i][j] - 1));
                clause_count++;
            }
    // 回填头部
    long end_pos = ftell(out);
    fseek(out, header_pos, SEEK_SET);
    fprintf(out, "p cnf 729 %d\n", clause_count);
    fseek(out, end_pos, SEEK_SET);
}

// 美观输出数独
void print_beautiful_sudoku(int board[N][N])
{
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < N; ++i)
    {
        printf("| ");
        for (int j = 0; j < N; ++j)
        {
            if (board[i][j] == 0)
                printf(". ");
            else
                printf("%d ", board[i][j]);
            if ((j + 1) % 3 == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
            printf("+-------+-------+-------+\n");
    }
}
#endif // SUDOKU_GEN_H
