/*
任务描述
实验指导书P183 程序设计第（12）题

本关任务：函数调度。

输入输出示例
输入：
13607122

输出：
task1 is called!
task3 is called!
task6 is called!
task0 is called!
task7 is called!
task1 is called!
task2 is called!
task2 is called!

开始你的任务吧，祝你成功！ 
*/
#include <stdio.h>
#include <string.h>

void scheduler();
void execute(int);
char list[100];

void task0()
{
    printf("task0 is called\n");
}
void task1()
{
    printf("task0 is called\n");
}
void task2()
{
    printf("task2 is called\n");
}
void task3()
{
    printf("task3 is called\n");
}
void task4()
{
    printf("task4 is called\n");
}
void task5()
{
    printf("task5 is called\n");
}
void task6()
{
    printf("task6 is called\n");
}
void task7()
{
    printf("task7 is called\n");
}


void (*p[8])(void) = {task0, task1, task2, task3, task4, task5, task6, task7};

int main() {
    scanf("%s", list);
    scheduler();
    return 0;
}
void scheduler() {
    for (int i = 0; i < strlen(list); i++)
    {
        int n = list[i] - '0';
        execute(n);
        }
}
void execute(int m) {
    p[m]();
}