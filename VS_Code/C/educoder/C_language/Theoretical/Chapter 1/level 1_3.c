/*
任务描述
本关任务：编写一个程序：输入自己名字的汉语拼音，要计算机问候自己。

相关知识
为了完成本关任务，你需要掌握：定义一个字符数组来存储字符串。如下所示：
char name[40];

编程要求
根据提示，在右侧编辑器补充代码。

测试说明
平台会对你编写的代码进行测试：

测试输入：ZhangSan
预期输出：
Hello ZhangSan！

开始你的任务吧，祝你成功！
*/
#include<stdio.h>
int main()
{
    /**********Begin**********/
    char name[40];
    scanf("%s", name);
    printf("Hello %s!", name);
	/**********End**********/
    return 0;
}