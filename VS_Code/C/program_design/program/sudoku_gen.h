#ifndef SUDOKU_GEN_H
#define SUDOKU_GEN_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

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

// 改进的唯一解检查函数（更高效）
static int count_solutions(int grid[N][N], int pos, int max_solutions)
{
    if (pos == N * N)
        return 1;

    int row = pos / N, col = pos % N;

    if (grid[row][col] != 0)
        return count_solutions(grid, pos + 1, max_solutions);

    int count = 0;
    for (int num = 1; num <= N; num++)
    {
        if (is_valid(grid, row, col, num))
        {
            grid[row][col] = num;
            count += count_solutions(grid, pos + 1, max_solutions - count);
            grid[row][col] = 0;
            
            if (count >= max_solutions) // 提前终止
                return count;
        }
    }
    return count;
}

// 当前最流行的挖空算法：对称挖空 + 唯一性验证
void puzzle_generate(int grid[N][N], int puzzle[N][N])
{
    // 复制完整数独
    memcpy(puzzle, grid, sizeof(int) * N * N);

    int target_holes = 45; // 目标挖空数（中等难度）
    int current_holes = 0;
    int max_attempts = 200; // 最大尝试次数

    // 创建对称位置对列表
    int symmetric_positions[N * N / 2][2];
    int pair_count = 0;
    
    for (int i = 0; i < N / 2; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int sym_i = N - 1 - i;
            int sym_j = N - 1 - j;
            
            if (i != sym_i || j != sym_j) // 避免中心点重复
            {
                symmetric_positions[pair_count][0] = i * N + j;
                symmetric_positions[pair_count][1] = sym_i * N + sym_j;
                pair_count++;
            }
        }
    }
    
    // 添加中心点（如果需要）
    if (N % 2 == 1)
    {
        symmetric_positions[pair_count][0] = (N/2) * N + (N/2);
        symmetric_positions[pair_count][1] = -1; // 标记为单点
        pair_count++;
    }

    // 打乱对称位置对顺序
    for (int i = pair_count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp0 = symmetric_positions[i][0];
        int temp1 = symmetric_positions[i][1];
        symmetric_positions[i][0] = symmetric_positions[j][0];
        symmetric_positions[i][1] = symmetric_positions[j][1];
        symmetric_positions[j][0] = temp0;
        symmetric_positions[j][1] = temp1;
    }

    // 开始挖空
    for (int attempt = 0; attempt < max_attempts && current_holes < target_holes; attempt++)
    {
        for (int p = 0; p < pair_count && current_holes < target_holes; p++)
        {
            int pos1 = symmetric_positions[p][0];
            int pos2 = symmetric_positions[p][1];
            
            int row1 = pos1 / N, col1 = pos1 % N;
            
            // 如果这个位置已经有数字
            if (puzzle[row1][col1] != 0)
            {
                int original1 = puzzle[row1][col1];
                int original2 = (pos2 != -1) ? puzzle[pos2 / N][pos2 % N] : -1;
                
                // 尝试挖空
                puzzle[row1][col1] = 0;
                if (pos2 != -1)
                    puzzle[pos2 / N][pos2 % N] = 0;
                
                // 检查唯一解
                int temp_grid[N][N];
                memcpy(temp_grid, puzzle, sizeof(int) * N * N);
                
                int solutions = count_solutions(temp_grid, 0, 2); // 最多检查2个解
                
                if (solutions == 1)
                {
                    // 挖空成功
                    current_holes += (pos2 != -1) ? 2 : 1;
                }
                else
                {
                    // 恢复数字
                    puzzle[row1][col1] = original1;
                    if (pos2 != -1)
                        puzzle[pos2 / N][pos2 % N] = original2;
                }
            }
        }
    }

    // 如果挖空数不足，尝试随机挖空单个位置
    if (current_holes < target_holes - 5)
    {
        int positions[N * N];
        for (int i = 0; i < N * N; i++)
            positions[i] = i;
        
        // 打乱顺序
        for (int i = N * N - 1; i > 0; i--)
        {
            int j = rand() % (i + 1);
            int temp = positions[i];
            positions[i] = positions[j];
            positions[j] = temp;
        }
        
        for (int i = 0; i < N * N && current_holes < target_holes; i++)
        {
            int pos = positions[i];
            int row = pos / N, col = pos % N;
            
            if (puzzle[row][col] != 0)
            {
                int original = puzzle[row][col];
                puzzle[row][col] = 0;
                
                int temp_grid[N][N];
                memcpy(temp_grid, puzzle, sizeof(int) * N * N);
                
                int solutions = count_solutions(temp_grid, 0, 2);
                
                if (solutions == 1)
                {
                    current_holes++;
                }
                else
                {
                    puzzle[row][col] = original;
                }
            }
        }
    }
}

// 复制CNF模板文件并在末尾追加预填数字规则
// src_cnf: 固定规则CNF文件路径，dst_cnf: 输出文件路径，grid: 预填数字
void generate_sudoku_cnf_with_given(const char *src_cnf, const char *dst_cnf, int grid[N][N])
{
    // 1. 复制原始CNF文件内容
    FILE *fin = fopen(src_cnf, "r");
    FILE *fout = fopen(dst_cnf, "w");
    if (!fin || !fout)
    {
        if (fin)
            fclose(fin);
        if (fout)
            fclose(fout);
        return;
    }
    char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), fin)) > 0)
    {
        fwrite(buf, 1, n, fout);
    }
    fclose(fin);
    // 2. 追加预填数字规则
    fprintf(fout, "\n");
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (grid[i][j])
                fprintf(fout, "%d 0\n", VAR(i, j, grid[i][j] - 1));
    fclose(fout);
}

// 获取当前挖空数量
int get_hole_count(int puzzle[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (puzzle[i][j] == 0)
                count++;
    return count;
}

#endif // SUDOKU_GEN_H
