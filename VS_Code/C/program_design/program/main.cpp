#include "dpll.h"
#include <iostream>
#include <filesystem>
using namespace std;
using namespace std::filesystem;

int main()
{
    system("chcp 65001");
    // path root("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program");
    // string ext = ".cnf"; // 你要查找的后缀名

    // // 递归遍历所有文件和子文件夹
    // for (const auto& entry : recursive_directory_iterator(root)) {
    //     if (entry.is_regular_file() && entry.path().extension() == ext) {
    //         // path 转 string
    //         string file = entry.path().string();
    //         cout << file << endl;
    //     }
    // }

    // cout << DPLL("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\true.cnf");
    cout<<DPLL("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\false_sample\\eu-rand_net60-25-10.shuffled-3000.cnf");
    // cout << DPLL("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\false_sample\\tst_v10_c100.cnf");

    return 0;
}