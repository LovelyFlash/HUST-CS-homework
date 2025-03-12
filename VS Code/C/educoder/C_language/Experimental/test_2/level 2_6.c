#include <stdio.h>
/*
任务描述
本关任务：实验教材P63 程序设计第(6)题
读入无符号长整型数表示的互联网IP地址，对其译码，以常见的点分十进制形式输出。

测试说明
平台会对你编写的代码进行测试：

测试输入：
3232235876
1
^Z
预期输出：
192.168.1.100

提示：

程序应能循环接受输入，直至输入Ctrl+Z。
输入为无符号长整形。
开始你的任务吧，祝你成功！
*/
int main() {
    unsigned long ip;

    // 循环读取输入，直到遇到EOF (Ctrl+Z)
    while (scanf("%lu", &ip) != EOF) {
        // 每个8位段分别提取
        unsigned char octet1 = (ip >> 24) & 0xFF;
        unsigned char octet2 = (ip >> 16) & 0xFF;
        unsigned char octet3 = (ip >> 8) & 0xFF;
        unsigned char octet4 = ip & 0xFF;

        // 输出为点分十进制格式
        printf("%d.%d.%d.%d\n", octet1, octet2, octet3, octet4);
    }

    return 0;
}