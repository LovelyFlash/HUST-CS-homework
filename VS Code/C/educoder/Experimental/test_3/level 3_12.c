/*
任务描述
本关任务：实验课本P86  程序设计第（12）题
输入正整数x(2≤x≤79)，输出所有形如abcde/fghij=x的表达式，其中a-j由不同的数字0~9组成。

编程要求
在右侧编辑器补充代码，输入x后输出形如abcde/fghij=x的表达式。

测试说明
平台会对你编写的代码进行测试：

测试输入：32；
预期输出：75168/02349=32

测试输入：12；
预期输出：
45792/03816=12
73548/06129=12
89532/07461=12
91584/07632=12

开始你的任务吧，祝你成功！
*/
#include <stdio.h>

// 判断数字 n 是否由 0-9 组成且不重复
int is_unique(int n) {
    int digits[10] = {0};  // 用于记录数字出现的次数
    while (n > 0) {
        int digit = n % 10;
        if (digits[digit] == 1) {  // 如果该数字已出现过
            return 0;
        }
        digits[digit] = 1;
        n /= 10;
    }
    return 1;
}

// 检查两个五位数是否由不同的0-9组成
int is_distinct(int a, int b) {
    int digits[10] = {0};
    
    // 记录 a 的数字
    for (int i = 0; i < 5; i++) {
        digits[a % 10]++;
        a /= 10;
    }
    // 记录 b 的数字，如果有重复返回 0
    for (int i = 0; i < 5; i++) {
        if (digits[b % 10]++ > 0) {
            return 0;
        }
        b /= 10;
    }
    return 1;
}

int main() {
    int x;
    printf("请输入正整数 x（2 ≤ x ≤ 79）：");
    scanf("%d", &x);

    // 枚举所有可能的 abcde 和 fghij
    for (int fghij = 1234; fghij <= 98765 / x; fghij++) {  // 确保 abcde 不超过五位数
        if (is_unique(fghij)) {
            int abcde = fghij * x;
            if (abcde <= 98765 && is_unique(abcde) && is_distinct(abcde, fghij)) {
                printf("%05d/%05d=%d\n", abcde, fghij, x);
            }
        }
    }

    return 0;
}
