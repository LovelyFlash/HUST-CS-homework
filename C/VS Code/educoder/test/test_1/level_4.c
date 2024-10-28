 /*
 任务描述
本关任务：实验教材  1.5 实验一 第4题
找出1000内的所有完数（P36）。

编程要求
认真阅读教材 P37 的实验步骤，学习跟踪进函数、观察变量值等程序调试方法。按步骤调试右侧代码框里程序，找出程序中的错误，使之输出正确结果。

开始你的任务吧，祝你成功！
 */
 #include<stdio.h>
 /*判断x是否是完全数，是则返回1，否则返回0*/
int isPerfect(int a)
{
    int y, s;
    for(s = 0, y = 1; y <= a/2; y++)
    {
        if((a % y) == 0)    s += y;
    }
    if(s == a)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int a;
    for(a=1; a <= 1000; a++)    /*遍历所有数*/
        if(isPerfect(a))
            printf("%d\n", a);
    return 0;
}
