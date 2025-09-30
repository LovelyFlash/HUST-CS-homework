#ifndef PRINT_OUT_HPP
#define PRINT_OUT_HPP

#include <stdio.h>
#include <windows.h> // 用于Windows控制台颜色

#define N 9

// 设置控制台颜色函数
void setConsoleColor(int background, int foreground)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, background * 16 + foreground);
}

// 重置控制台颜色到默认
void resetConsoleColor()
{
    setConsoleColor(0, 7); // 黑色背景，白色文字
}

// 判断是否在左上窗口区域 (2-4行2-4列，实际索引1-3)
bool isTopLeftWindow(int i, int j)
{
    return (i >= 1 && i <= 3) && (j >= 1 && j <= 3);
}

// 判断是否在右下窗口区域 (6-8行6-8列，实际索引5-7)
bool isBottomRightWindow(int i, int j)
{
    return (i >= 5 && i <= 7) && (j >= 5 && j <= 7);
}

// 判断是否在撇对角线区域 (右上到左下)
bool isLeftDiagonal(int i, int j)
{
    return (i + j) == (N - 1);
}

// 判断宫格编号 (0-8)
int getBoxNumber(int i, int j)
{
    return (i / 3) * 3 + (j / 3);
}

// 获取单元格的背景颜色
int getCellBackgroundColor(int i, int j)
{
    // 左上窗口区域 - 深蓝色背景
    if (isTopLeftWindow(i, j))
    {
        return 1; // 深蓝色背景
    }
    // 右下窗口区域 - 深绿色背景
    else if (isBottomRightWindow(i, j))
    {
        return 2; // 深绿色背景
    }
    // 撇对角线区域 - 深紫色背景
    else if (isLeftDiagonal(i, j))
    {
        return 5; // 紫色背景
    }
    // 根据宫格编号交替颜色
    else
    {
        int box = getBoxNumber(i, j);
        // 交替使用黄色和青色背景
        return (box % 2 == 0) ? 6 : 3; // 6=黄色, 3=青色
    }
}

// 获取单元格的文字颜色
int getCellForegroundColor(int i, int j, int value)
{
    if (value == 0)
    {
        return 15; // 白色文字（用于空格）
    }
    // 特殊区域的数字使用白色文字确保可读性
    if (isTopLeftWindow(i, j) || isBottomRightWindow(i, j) || isLeftDiagonal(i, j))
    {
        return 15; // 白色文字
    }
    return 0; // 黑色文字（在浅色背景上）
}

// 获取单元格的背景颜色（考虑选中状态）
int getCellBackgroundColorWithSelection(int i, int j, bool isSelected)
{
    if (isSelected)
    {
        return 4; // 红色背景表示选中
    }
    return getCellBackgroundColor(i, j);
}

// 获取单元格的文字颜色（考虑选中状态）
int getCellForegroundColorWithSelection(int i, int j, int value, bool isSelected)
{
    if (isSelected)
    {
        return 15; // 白色文字确保在红色背景上可读
    }
    return getCellForegroundColor(i, j, value);
}

// 打印标准数独
void print_beautiful_sudoku(int board[N][N])
{
    // 打印顶部边框 - 使用正确的Unicode字符
    printf("┌───┬───┬───┬───┬───┬───┬───┬───┬───┐\n");

    for (int i = 0; i < N; ++i)
    {
        printf("│");
        for (int j = 0; j < N; ++j)
        {
            int bgColor = getCellBackgroundColor(i, j);
            int fgColor = getCellForegroundColor(i, j, board[i][j]);

            setConsoleColor(bgColor, fgColor);

            if (board[i][j] == 0)
                printf(" . ");
            else
                printf(" %d ", board[i][j]);

            resetConsoleColor();
            printf("│");
        }
        printf("\n");

        // 打印行分隔符 - 正确处理3x3宫格的分隔
        if (i < N - 1)
        {
            if ((i + 1) % 3 == 0)
            {
                // 粗分隔线（宫格之间）
                printf("├───┼───┼───┼───┼───┼───┼───┼───┼───┤\n");
            }
            else
            {
                // 细分隔线（行之间）
                printf("│───┼───┼───┼───┼───┼───┼───┼───┼───│\n");
            }
        }
    }

    // 打印底部边框
    printf("└───┴───┴───┴───┴───┴───┴───┴───┴───┘\n");

    // 打印图例说明
    printf("\n🎨 颜色区域说明:\n");
    setConsoleColor(1, 15);
    printf("  深蓝色 ");
    resetConsoleColor();
    printf(" - 左上窗口区域 (2-4行2-4列)\n");
    setConsoleColor(2, 15);
    printf("  深绿色 ");
    resetConsoleColor();
    printf(" - 右下窗口区域 (6-8行6-8列)\n");
    setConsoleColor(5, 15);
    printf("  紫色   ");
    resetConsoleColor();
    printf(" - 撇对角线区域\n");
    setConsoleColor(6, 0);
    printf("  黄色   ");
    resetConsoleColor();
    printf(" - 偶数宫格区域\n");
    setConsoleColor(3, 0);
    printf("  青色   ");
    resetConsoleColor();
    printf(" - 奇数宫格区域\n");
}

// 打印带选中状态的数独
void print_beautiful_sudoku_with_selection(int board[N][N], int selected_row, int selected_col)
{
    // 打印顶部边框 - 使用正确的Unicode字符
    printf("┌───┬───┬───┬───┬───┬───┬───┬───┬───┐\n");

    for (int i = 0; i < N; ++i)
    {
        printf("│");
        for (int j = 0; j < N; ++j)
        {
            bool isSelected = (i == selected_row && j == selected_col);
            int bgColor = getCellBackgroundColorWithSelection(i, j, isSelected);
            int fgColor = getCellForegroundColorWithSelection(i, j, board[i][j], isSelected);

            setConsoleColor(bgColor, fgColor);

            if (board[i][j] == 0)
                printf(" . ");
            else
                printf(" %d ", board[i][j]);

            resetConsoleColor();
            printf("│");
        }
        printf("\n");

        // 打印行分隔符 - 正确处理3x3宫格的分隔
        if (i < N - 1)
        {
            if ((i + 1) % 3 == 0)
            {
                // 粗分隔线（宫格之间）
                printf("├───┼───┼───┼───┼───┼───┼───┼───┼───┤\n");
            }
            else
            {
                // 细分隔线（行之间）
                printf("│───┼───┼───┼───┼───┼───┼───┼───┼───│\n");
            }
        }
    }

    // 打印底部边框
    printf("└───┴───┴───┴───┴───┴───┴───┴───┴───┘\n");

    // 打印图例说明
    printf("\n🎨 颜色区域说明:\n");
    setConsoleColor(1, 15);
    printf("  深蓝色 ");
    resetConsoleColor();
    printf(" - 左上窗口区域 (2-4行2-4列)\n");
    setConsoleColor(2, 15);
    printf("  深绿色 ");
    resetConsoleColor();
    printf(" - 右下窗口区域 (6-8行6-8列)\n");
    setConsoleColor(5, 15);
    printf("  紫色   ");
    resetConsoleColor();
    printf(" - 撇对角线区域\n");
    setConsoleColor(6, 0);
    printf("  黄色   ");
    resetConsoleColor();
    printf(" - 偶数宫格区域\n");
    setConsoleColor(3, 0);
    printf("  青色   ");
    resetConsoleColor();
    printf(" - 奇数宫格区域\n");
    setConsoleColor(4, 15);
    printf("  红色   ");
    resetConsoleColor();
    printf(" - 当前选中单元格\n");
}

#endif // PRINT_OUT_HPP
