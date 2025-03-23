/*
任务描述
实验课本 P107 程序修改替换第（1）题
本关任务：将程序改错(1)中的sum_fac函数修改为一个递归函数，用递归的方式计算s=1!+2!+3!+...+n!

编程要求
在右侧编辑器中编写sum_func函数，必须为递归函数，否则记0分

测试说明
平台会对你编写的代码进行测试：

测试输入：无
预期输出：
k=1 the sum is 1
k=2 the sum is 3
k=3 the sum is 9
...
k=20 the sum is 2561327494111820313

提示：

必须使用递归函数
Sn = Sn-1 + n!
开始你的任务吧，祝你成功！
*/
#include<stdio.h>
unsigned long long sum_fac(int k, int n, unsigned long long s, unsigned long long fac)
{
    fac *= n;
	if(k >= n) return sum_fac(k, n+1, s + fac, fac);
	else return s;
};

int main(void)
{
	int k, n = 1;
    unsigned long long s = 0, fac = 1;
	for(k=1; k<=20; k++)
		printf("k=%d the sum is %llu\n",k,sum_fac(k, n, s, fac));
	return 0;
}