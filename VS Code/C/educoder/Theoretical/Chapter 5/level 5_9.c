/*
任务描述
输入十个整数，统计其中正数的个数，并计算正数的平均值。要求循环中使用continue语句实现。

相关知识
转移语句，分支结构。

编程要求
根据提示，在右侧Begin-End区域编写一个完整满足任务要求的程序。

测试说明
平台会对你编写的代码进行测试，若是与预期输出相同，则算通关。

测试输入：1 -2 3 -4 5 -6 7 -8 9 -10
预期输出：
numbers=5,average=5.000000

测试输入：10 -20 -30 40 -50 60 70 80 90 -100
预期输出：
numbers=6,average=58.333333

开始你的任务吧，祝你成功！
*/
#include <stdio.h>

int main() {
    /**********  Begin  **********/
    int n = 0;         // 正整数的总和
    int count = 0;     // 正整数的个数
    int a;

    // 读取10个整数
    for (int k = 1; k <= 10; k++) {
        scanf("%d", &a);
        
        if (a > 0) {
            n += a;     // 累加正整数
            count++;    // 计数正整数个数
        }
    }

    // 计算平均值
    if (count > 0) {
        double average = (double)n / count; // 计算平均值
        printf("numbers=%d, average=%.6lf", count, average);
    } else {
        printf("numbers=0, average=0.000000");
    }
    /**********  End  **********/
    
    return 0;
}
