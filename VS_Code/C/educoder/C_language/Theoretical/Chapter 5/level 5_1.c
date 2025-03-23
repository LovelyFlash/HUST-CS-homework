/*
任务描述
输入A,B,C三位学生的考试分数，输出分数居中的学生的姓名（用A、B或C表示）以及他的分数。如果出现相同分数的情况，按A、B和C的次序输出前面一个学生的姓名。
####相关知识

为了完成本关任务，你需要掌握：

基本的输入输出格式；
if语句。
编程要求
根据提示，在右侧Begin-End区域编写一个完整满足任务要求的程序。

测试说明
平台会对你编写的代码进行测试，若是与预期输出相同，则算通关。

测试输入：74 91 51
预期输出：A 74

测试输入：80 80 90
预期输出：A 80

测试输入：100 100 100
预期输出：A 100

测试输入：71 81 99
预期输出：B 81

测试输入：51 81 77
预期输出：C 77

开始你的任务吧，祝你成功！
*/
/********** Begin **********/
#include <stdio.h>

int main(){
	int A, B, C;
	scanf("%d %d %d", &A, &B, &C );
	if(A > B)
	{
		if(B > C) printf("B %d", B);
		else if(C > B){
			if(A > C) printf("C %d", C);
			else if(A < C) printf("A %d", A);
			else printf("A %d", A);
		}
		else printf("B %d",B);
	}
	else if(A < B)
	{
		if(B < C) printf("B %d", B);
		else if(C < B){
			if(A > C) printf("A %d", A);
			else if(A < C) printf("C %d", C);
			else printf("A %d", A);
		}
		else printf("B %d", B);
	}
	else if(A == B)
	{
		printf("A %d", A);
	}
	return 0;
}
/**********  End **********/