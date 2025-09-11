#include "DPLL.hpp"
#include "sudoku_gen.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
using namespace std::filesystem;

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
    // 美观输出完整数独
    print_beautiful_sudoku(grid);
    puzzle_generate(grid, puzzle);
    printf("生成的百分号数独(挖空版)：\n");
    print_beautiful_sudoku(puzzle);
    // 保存挖空版到文件，便于solve_sudoku_file读取
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
    // 规约为SAT并求解
    FILE *fout = fopen("percent_sudoku.cnf", "w");
    if (fout)
    {
        sudoku_to_SAT(puzzle, fout);
        fclose(fout);
        CNF cnf;
        try
        {
            cnf.read("percent_sudoku.cnf");
            cnf.solve();
            if (cnf.flag)
            {
                printf("求解成功，解如下：\n");
                // 解码输出
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
                printf("无解\n");
        }
        catch (const char *e)
        {
            printf("SAT求解失败: %s\n", e);
        }
    }
    else
        printf("无法写入percent_sudoku.cnf\n");
}

void solve_sudoku_SAT()
{
    cout << "请输入已规约为SAT的数独CNF文件路径：";
    string file;
    cin >> file;
    CNF cnf;
    try
    {
        cnf.read(file.c_str());
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
    cout << "0. 退出\n";
    cout << "输入选项：";
    int op;
    cin >> op;
    return op;
}

int main()
{
    system("chcp 65001");
    while (true)
    {
        clearScreen();
        displayBanner();
        int choice = displayMainMenu();
        if (choice == 0)
            break;
        if (choice == 1)
        {
            solve_cnf_batch();
        }
        else if (choice == 2)
        {
            solve_sudoku_file();
        }
        else if (choice == 3)
        {
            generate_and_print_sudoku();
        }
        else if (choice == 4)
        {
            solve_sudoku_SAT();
        }
        else
        {
            cout << "无效选项，请重试。\n";
        }
        waitForKey();
    }
    return 0;
}