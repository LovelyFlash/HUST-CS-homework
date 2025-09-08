#include "dpll.h"
#include <iostream>
#include <filesystem>
using namespace std;
using namespace std::filesystem;

int main()
{
    system("chcp 65001");

    // // path root(".");//根目录
    // path root("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\true_sample");
    // // path root("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\false_sample");

    // string ext = ".cnf"; // 你要查找的后缀名
    // // 递归遍历所有文件和子文件夹
    // for (const auto &entry : recursive_directory_iterator(root))
    // {
    //     if (entry.is_regular_file() && entry.path().extension() == ext)
    //     {
    //         // path 转 string
    //         string file = entry.path().string();
    //         cout << file << " -> ";
    //         bool error = false;
    //         bool result = false;

    //         try
    //         {
    //             result = DPLL(file.c_str());
    //         }
    //         catch (const char *e)
    //         {
    //             error = true;
    //             cout << e << endl;
    //         }
    //         // cout<<res"ult<<' ';
    //         // if(DEPTH>=10000) cout<<"timeout";
    //         if (!error)
    //             cout << result << endl;
    //     }
    // }

    // cout<<DPLL("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\true_sample\\S\\problem2-50.cnf")<<endl;
    // cout<<DPLL("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\basic_sample\\function_test\\sat-20.cnf")<<endl;
    // cout<<DPLL("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\basic_sample\\function_test\\unsat-5cnf-30.cnf")<<endl;
    // cout<<DPLL("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\basic_sample\\speed_test\\ais10.cnf")<<endl;
    cout<<DPLL("D:\\desktop\\file\\Code\\VS_Code\\C\\program_design\\program\\SAT_test\\basic_sample\\speed_test\\sud00009.cnf")<<endl;

    return 0;
}