/*
任务描述
本关任务：实验教材P63 程序设计第(5)题
取出x从第ｍ位开始向左的ｎ位。

测试说明
平台会对你编写的代码进行测试：

测试输入：
4 2 1
预期输出：(以十六进制输出)
8000

开始你的任务吧，祝你成功！
*/
 #include <stdio.h>

int main()
{
    unsigned short a, m, n;
    scanf("%hx %hu %hu", &a, &m, &n);
    a = (a >> m) << (16-n);
    printf("%hx", a);
    return 0;
}