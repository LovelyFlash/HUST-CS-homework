/*
任务描述
本关任务：实验教材P63 程序设计第(4)题
 判断输入的字符串是否符合手机号码的格式。

判断条件的优先级规定为：
长度合法>每一位都是数字>第1位合法>第2位合法。

测试说明
平台会对你编写的代码进行测试：

测试输入：
"1304567854"

预期输出：
长度不合法

测试输入：
"10234567543"

预期输出：
第2位不合法

开始你的任务吧，祝你成功！
*/

#include <stdio.h>
#include <string.h>

int main(){
	char num[100];
	scanf("%s", num);
	int a =strlen(num);
	if (a != 11) printf("长度不合法\n");
	else{
		int b = 1, i;
		for(i = 0; i<a; i++)
		{
			if(num[i] < '0' || num[i] > '9') b = 0;
		}
		if(b)
		{
			if (num[0] != '1') printf("第一位不合法\n");
			else if (num[1] != '3' && num[1] != '4' && num[1] != '5' && num[1] != '7' && num[1] != '8') printf("第二位不合法\n");
			else printf("合法的手机号码\n");
		}
		else printf("字符串中存在非数字字符\n");
		
	}
	return 0;
}

