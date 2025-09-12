#include "DPLL_envolve.hpp"
#include "sudoku_gen.h"
#include "print_out.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h> // 用于_getch()函数
using namespace std;
using namespace std::filesystem;

// 游戏状态结构体
struct SudokuGame
{
    int puzzle[N][N];       // 原始谜题（0表示空格）
    int solution[N][N];     // 完整解答
    int user_grid[N][N];    // 用户当前填写的网格
    bool fixed_cells[N][N]; // 哪些格子是固定的（不能修改）
    int selected_row;       // 当前选中的行
    int selected_col;       // 当前选中的列
};

// 全局游戏状态
SudokuGame current_game;

// 函数前置声明
void waitForKey();
void clearScreen();
void displayBanner();
int displayMainMenu();
void solve_cnf_batch();
void generate_and_print_sudoku();
void solve_sudoku_file();
void solve_sudoku_SAT();
void play_sudoku_game();
void display_game_interface();
void handle_game_input();
bool is_game_complete();
bool is_game_correct();

void waitForKey()
{
    cout << "\n按回车键继续...";
    cin.ignore();
    cin.get();
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayBanner()
{
    cout << "==============================\n";
    cout << "      SAT/数独工具菜单        \n";
    cout << "        作者：王李超          \n";
    cout << "==============================\n";
}

int displayMainMenu()
{
    cout << "\n请选择功能：\n";
    cout << "1. 批量求解指定路径下所有CNF文件\n";
    cout << "2. 求解并输出填好的数独文件\n";
    cout << "3. 生成数独并输出挖空版\n";
    cout << "4. 直接求解一规约为SAT的数独CNF文件\n";
    cout << "5. 玩数独游戏\n";
    cout << "0. 退出\n";
    cout << "输入选项：";
    int op;
    cin >> op;
    return op;
}

void solve_cnf_batch()
{
    cout << "请输入CNF文件所在目录路径：";
    string path;
    cin >> path;
    string ext = ".cnf";
    for (const auto &entry : recursive_directory_iterator(path))
    {
        if (entry.is_regular_file() && entry.path().extension() == ext)
        {
            string file = entry.path().string();
            cout << file << " -> ";
            bool error = false;
            bool result = false;
            int time;
            CNF cnf;
            try
            {
                cnf.read(file.c_str());
                cnf.solve();
                result = cnf.flag;
                time = cnf.ms;
            }
            catch (const char *e)
            {
                error = true;
                cout << e << endl;
            }
            if (!error)
                cout << time << "ms " << (result ? "SATISFIABLE" : "UNSATISFIABLE") << endl;
        }
    }
}

void generate_and_print_sudoku()
{
    int grid[N][N];
    int puzzle[N][N];
    generate_percent_sudoku(grid);
    printf("生成的百分号数独(完整解)：\n");
    print_beautiful_sudoku(grid);
    puzzle_generate(grid, puzzle);
    printf("生成的百分号数独(挖空版)：\n");
    print_beautiful_sudoku(puzzle);

    // 保存到全局游戏状态
    memcpy(current_game.puzzle, puzzle, sizeof(puzzle));
    memcpy(current_game.solution, grid, sizeof(grid));
    memcpy(current_game.user_grid, puzzle, sizeof(puzzle));

    // 初始化固定单元格标记
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            current_game.fixed_cells[i][j] = (puzzle[i][j] != 0);
        }
    }

    current_game.selected_row = 0;
    current_game.selected_col = 0;

    ofstream fout("sudoku_puzzle.txt");
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            fout << puzzle[i][j] << (j == N - 1 ? '\n' : ' ');
        }
    }
    fout.close();
    printf("挖空版数独已保存为 sudoku_puzzle.txt\n");
}

void solve_sudoku_file()
{
    cout << "请输入待求解数独文件路径：";
    string file;
    cin >> file;
    int puzzle[N][N];
    ifstream fin(file);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            fin >> puzzle[i][j];
    printf("原始数独：\n");
    print_beautiful_sudoku(puzzle);

    // 保存到全局游戏状态
    memcpy(current_game.puzzle, puzzle, sizeof(puzzle));
    memcpy(current_game.user_grid, puzzle, sizeof(puzzle));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            current_game.fixed_cells[i][j] = (puzzle[i][j] != 0);
        }
    }

    const char *base_cnf = "D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\sudoku.cnf";
    const char *out_cnf = "D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\percent_sudoku.cnf";
    generate_sudoku_cnf_with_given(base_cnf, out_cnf, puzzle);
    CNF cnf;
    try
    {
        cnf.read(out_cnf);
        cnf.solve();
        if (cnf.flag)
        {
            printf("求解成功，解如下：\n");
            int solved[N][N] = {0};
            for (int n = 1; n <= 729; ++n)
            {
                if (cnf.value[n])
                {
                    int row = (n - 1) / 81;
                    int col = ((n - 1) % 81) / 9;
                    int val = (n - 1) % 9 + 1;
                    solved[row][col] = val;
                }
            }
            // 保存解答到全局状态
            memcpy(current_game.solution, solved, sizeof(solved));
            print_beautiful_sudoku(solved);
        }
        else
            printf("无解\n");
    }
    catch (const char *e)
    {
        printf("SAT求解失败: %s\n", e);
    }
}

void solve_sudoku_SAT()
{
    cout << "请输入已规约为SAT的数独CNF文件路径：";
    char file[500];
    cin >> file;
    CNF cnf;
    try
    {
        cnf.read(file);
        cnf.solve();
        if (cnf.flag)
        {
            printf("求解成功，解如下：\n");
            int solved[N][N] = {0};
            for (int n = 1; n <= 729; ++n)
            {
                if (cnf.value[n])
                {
                    int row = (n - 1) / 81;
                    int col = ((n - 1) % 81) / 9;
                    int val = (n - 1) % 9 + 1;
                    solved[row][col] = val;
                }
            }
            print_beautiful_sudoku(solved);
        }
        else
        {
            printf("无解\n");
        }
    }
    catch (const char *e)
    {
        printf("SAT求解失败: %s\n", e);
    }
}

// 检查游戏是否完成
bool is_game_complete()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (current_game.user_grid[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

// 检查游戏是否正确完成
bool is_game_correct()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (current_game.user_grid[i][j] != current_game.solution[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

// 显示游戏界面
void display_game_interface()
{
    clearScreen();
    cout << "=========== 数独游戏 ===========\n";
    cout << "方向键: 移动光标  数字1-9: 填入数字\n";
    cout << "空格: 清空单元格  R: 重新开始\n";
    cout << "A: 显示答案      C: 检查答案\n";
    cout << "ESC: 返回主菜单\n";
    cout << "================================\n\n";

    // 打印带选中状态的数独
    for (int i = 0; i < N; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            cout << "│───┼───┼───┼───┼───┼───┼───┼───┼───│\n";
        }
        cout << "│";
        for (int j = 0; j < N; j++)
        {
            // 设置颜色：选中的单元格用不同颜色
            if (i == current_game.selected_row && j == current_game.selected_col)
            {
                cout << "\033[41m"; // 红色背景
            }
            else if (current_game.fixed_cells[i][j])
            {
                cout << "\033[1m"; // 粗体显示固定数字
            }

            if (current_game.user_grid[i][j] == 0)
            {
                cout << " · ";
            }
            else
            {
                cout << " " << current_game.user_grid[i][j] << " ";
            }

            cout << "\033[0m│"; // 重置颜色
        }
        cout << "\n";
    }
    cout << "\n";
}

// 处理游戏输入
void handle_game_input()
{
    int ch = _getch();

    switch (ch)
    {
    case 72: // 上箭头
        if (current_game.selected_row > 0)
            current_game.selected_row--;
        break;
    case 80: // 下箭头
        if (current_game.selected_row < N - 1)
            current_game.selected_row++;
        break;
    case 75: // 左箭头
        if (current_game.selected_col > 0)
            current_game.selected_col--;
        break;
    case 77: // 右箭头
        if (current_game.selected_col < N - 1)
            current_game.selected_col++;
        break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        if (!current_game.fixed_cells[current_game.selected_row][current_game.selected_col])
        {
            current_game.user_grid[current_game.selected_row][current_game.selected_col] = ch - '0';
        }
        break;
    case ' ': // 空格清空
        if (!current_game.fixed_cells[current_game.selected_row][current_game.selected_col])
        {
            current_game.user_grid[current_game.selected_row][current_game.selected_col] = 0;
        }
        break;
    case 'r':
    case 'R': // 重新开始
        memcpy(current_game.user_grid, current_game.puzzle, sizeof(current_game.puzzle));
        break;
    case 'a':
    case 'A': // 显示答案
        memcpy(current_game.user_grid, current_game.solution, sizeof(current_game.solution));
        display_game_interface();
        cout << "已显示完整答案！按任意键继续...";
        _getch();
        break;
    case 'c':
    case 'C': // 检查答案
        if (is_game_complete())
        {
            if (is_game_correct())
            {
                cout << "恭喜！答案完全正确！🎉\n";
            }
            else
            {
                cout << "答案有错误，请继续努力！\n";
            }
        }
        else
        {
            cout << "游戏尚未完成，请继续填写！\n";
        }
        cout << "按任意键继续...";
        _getch();
        break;
    case 27: // ESC键
        return;
    }
}

// 玩数独游戏
void play_sudoku_game()
{
    if (current_game.puzzle[0][0] == 0)
    {
        cout << "请先生成或加载一个数独谜题！\n";
        waitForKey();
        return;
    }

    while (true)
    {
        display_game_interface();
        handle_game_input();

        // 检查游戏是否完成
        if (is_game_complete() && is_game_correct())
        {
            display_game_interface();
            cout << "🎉 恭喜你成功完成了数独！🎉\n";
            cout << "按任意键返回主菜单...";
            _getch();
            break;
        }
    }
}

int main()
{
    system("chcp 65001");
    // 初始化游戏状态
    memset(&current_game, 0, sizeof(current_game));

    while (true)
    {
        clearScreen();
        displayBanner();
        int choice = displayMainMenu();

        switch (choice)
        {
        case 0:
            return 0;
        case 1:
            solve_cnf_batch();
            break;
        case 2:
            solve_sudoku_file();
            break;
        case 3:
            generate_and_print_sudoku();
            break;
        case 4:
            solve_sudoku_SAT();
            break;
        case 5:
            play_sudoku_game();
            break;
        default:
            cout << "无效选项，请重试。\n";
        }

        if (choice != 5)
        { // 游戏界面有自己的等待机制
            waitForKey();
        }
    }
    return 0;
}
