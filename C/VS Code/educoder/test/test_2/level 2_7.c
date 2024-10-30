/*
任务描述
本关任务：实验教材P63 程序设计第(8)题
输入一个仅有英文大写字母、逗号、句点和空格符组成的英文句子（字符数不超过80个）和正整数k（1<=k<=26），将其中的大写英文字母替换成字母表中该字母开始的第k个字母，其它字符保持不变.

测试说明
平台会对你编写的代码进行测试：

测试输入：
ON A CLEAR DAY,YOU CAN SEE FOREVER
9
预期输出：
VWI K MTZIL GIG,CWK VIA MMN ZWDMZM

开始你的任务吧，祝你成功！
*/
#include<stdio.h>
void encryption(char REAL[], int n)
{
    for(int i = 0; i<1000 && REAL[i] != '\0'; i++)
    {
        if (REAL[i] != ' ' && REAL[i] >= 'A' && REAL[i] <= 'Z')
        {
            if(REAL[i] + n > 'Z') 
                REAL[i] -= 26-n;
            else 
                REAL[i] += n;
        }
    }
    
    for(int i = 0; (REAL[i]!= '\0')&&(REAL[i+1]!= '\0'); i += 2)
    {
        char temp = REAL[i];
        REAL[i] = REAL[i+1];
        REAL[i+1] = temp;
    }
    printf("%s", REAL);
}

int main(){
    char REAL[1000]={0}, c;
    int n, i = 0;
    while((c = getchar()) != '\n')
    {
        REAL[i++] = c;
    }
    REAL[i] = '\0';
    scanf("%d", &n);
    encryption(REAL, n);
    return 0;
}