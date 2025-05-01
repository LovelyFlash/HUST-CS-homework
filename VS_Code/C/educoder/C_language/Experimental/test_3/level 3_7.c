/*
任务描述
本关任务：实验课本P85  程序设计第（3）题
输入一直股票连续n天的收盘价格，输出该股票这n天中的最大波动值，波动值是指某天收盘价格与前一天收盘价格只差的绝对值。

编程要求
在右侧编辑器补充代码，使之满足任务描述。

测试说明
平台会对你编写的代码进行测试：

测试输入：
7
24 32 6 9 23 13 15;

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#include <stdlib.h>  // 包含 abs 函数的头文件

int main()
{
    unsigned int i, n, temp = 0;
    scanf("%u", &n);
    unsigned int num[n];  // 定义大小为 n 的数组
    for (i = 0; i < n; i++)
    {
        scanf("%u", &num[i]);  // 输入收盘价格
    }
    
    // 计算相邻两天收盘价格的绝对差值，并找到最大波动值
    for(i = 0; i < n-1; i++)
    {
        unsigned int diff = abs(num[i] - num[i+1]);  // 计算波动的绝对值
        if(diff > temp)  // 找到最大波动值
        {
            temp = diff;
        }
    }
    
    printf("%u", temp);  // 使用 %u 输出 unsigned int 类型
    return 0;
}
