/*
任务描述
输出斐波那契数列的前n项，n由终端输入（n>=20），每行输出8个数，每个数显示的宽度为10列。

相关知识
循环控制；
斐波那契数列；

编程要求
根据提示，在右侧Begin-End区域编写一个完整满足任务要求的程序。

测试说明
平台会对你编写的代码进行测试，若是与预期输出相同，则算通关。

测试输入：20
预期输出：



测试输入：32
预期输出：



开始你的任务吧，祝你成功！
*/
/********** Begin **********/
#include <stdio.h>

void fibonacci(int n) {
    long long fib_sequence[1000]; // 用于存储斐波那契数列，数组大小可根据需要调整
    fib_sequence[0] = 1;
    fib_sequence[1] = 1;

    // 生成斐波那契数列
    for (int i = 2; i < n; i++) {
        fib_sequence[i] = fib_sequence[i-1] + fib_sequence[i-2];
    }

    // 每行输出8个数，每个数宽度为10列
    for (int i = 0; i < n; i++) {
        printf("%10lld", fib_sequence[i]); // 每个数宽度为10列
        if ((i + 1) % 8 == 0) {
            printf("\n"); // 输出8个数后换行
        }
    }
    // 如果最后一行不满8个数，手动换行
    if (n % 8 != 0) {
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    if (n >= 20) {
        fibonacci(n);
    } else {
        printf("n值必须大于等于20\n");
    }

    return 0;
}




/**********  End **********/
