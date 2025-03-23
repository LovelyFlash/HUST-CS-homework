/*
任务描述
本关任务：设计一个含有年、月、日的日期结构类型，输入一个日期，计算并输出该日期是该年中的第几天。

测试说明
平台会对你编写的代码进行测试，若是与预期输出相同，则算通关。

年、月、日中间使用空格进行分隔

测试输入：2019 1 1
预期输出：
1

测试输入：2019 3 5
预期输出：
64

测试输入：2019 5 3
预期输出：
123

测试输入：2016 2 29
预期输出：
60

测试输入：2000 2 29
预期输出：
60

测试输入：2100 2 29
预期输出：
不存在这样的日期

测试输入：2019 2 29
预期输出：
不存在这样的日期

开始你的任务吧，祝你成功！
*/
#include <stdio.h>

struct
{
    int year;
    int month;
    int day;
} real_date;

int main()
{
    int date = 0;
    scanf("%d %d %d", &real_date.year, &real_date.month, &real_date.day);
    int day_month[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int flag = (!(real_date.year%4) && (real_date.year%100) || !(real_date.year%400))?1:0;
    if(day_month[real_date.month-1] < real_date.day && real_date.month != 2)
        printf("不存在这样的日期\n");
    else if((day_month[1] + flag) < real_date.day  && real_date.month == 2)
        printf("不存在这样的日期\n");
    else if(real_date.month > 12 || real_date.month < 1)
        printf("不存在这样的日期\n");
    else
    {
        for(int i = 0; i < real_date.month-1; i++)
        {
            date += day_month[i];
        }
        if(real_date.month > 2)
            date += (flag + real_date.day);
        else
            date += real_date.day;
        printf("%d", date);
    }
    return 0;
}