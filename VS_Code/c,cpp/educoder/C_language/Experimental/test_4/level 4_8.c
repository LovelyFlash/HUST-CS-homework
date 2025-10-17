/*
任务描述
实验课本 实验4 程序设计第（4）题
本关任务：用带参数的宏计算三角形面积。

相关知识
三角形面积area=(s(s-a)(s-b)(s-c))^0.5,其中s=(a+b+c)/2

编程要求
根据提示，在右侧编辑器定义两个带参数的宏，一个用来求s，另一个用来求area

测试说明
平台会对你编写的代码进行测试：

测试输入：4 5 6
预期输出：9.92

测试输入：5 6 7
预期输出：14.70

提示：

输出保留两位小数
输入的边长满足三角形的边长关系
开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#include <math.h>

#define S(a, b, c) ((a + b + c) / 2.0) // 定义半周长
#define AREA(a, b, c) (sqrt(S(a, b, c) * (S(a, b, c) - a) * (S(a, b, c) - b) * (S(a, b, c) - c))) // 定义面积

int main(void)
{
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a + b > c && a + c > b && b + c > a) { // 检查三角形合法性
        printf("%0.2f\n", AREA(a, b, c));
    } else {
        printf("输入的边长无法构成三角形。\n");
    }
    
    return 0;
}
