/*
任务描述
本关任务：实验教材P63 程序设计第(3)题
给定n个整数表示一个商店连续n天的销售量，计算出这些天总共有多少个折点。

测试说明
平台会对你编写的代码进行测试：

测试输入：
7
6 3 1 4 5 8 6
预期输出：
2

开始你的任务吧，祝你成功！
*/
#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int num[n];  // declare array after initializing n
    int i, k = 0;

    for(i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
        if(i >= 2)
        {
            if((num[i-1] > num[i]) && (num[i-1] > num[i-2]))
            {
                k++;
            }
            else if((num[i-1] < num[i]) && (num[i-1] < num[i-2]))
            {
                k++;
            }
        }
    }
    printf("%d", k);

    return 0;
}
