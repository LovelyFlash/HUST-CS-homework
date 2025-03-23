/*
任务描述
实验指导书P183 程序设计第（10）题

本关任务：求两个不超过200位的非负整数积。
（本题涉及高精度计算，可参考理论课教材例8.9 和 实验课教材 例6.17）

输入输出示例
示例一
输入：
123
456

输出：
56088

示例二
输入：
666666666666666666666666666666666666666666666666666666666666666666
22222222222222222222222222222222222222222222222222222222222222222

输出：
14814814814814814814814814814814814814814814814814814814814814814651851851851851851851851851851851851851851851851851851851851851852

开始你的任务吧，祝你成功！
*/
#include <stdio.h>
#include <ctype.h>
#define N 200
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

void getBignum(int *, int);
void plusBignum(int *, int *, int *);
void putBignum(int *);

int main()
{
    int x[N+1], y[N+1], z[N+2], len, i;
    getBignum(x, N);
    getBignum(y, N);
    plusBignum(z, x, y);
    putBignum(z);
    putchar('\n');
    return 0;
}

void getBignum(int *x, int lim)
{
    int i, t, c;
    int *p1, *p2;
    for(i = 1; i<lim; i++) *(x+i) = 0;
    for(i = 1; i <= lim && isdigit(c = getchar()); i++)
        *(x+i) = c-'0';
    *x = i-1;
    for(p1 = x+1,p2 = x+i-1; p1<p2; p1++, p2--)
        t = *p1, *p1=*p2, *p2=t;
}

void plusBignum(int *z, int *x, int *y)
{
    int i, j, carry, n;
    for(i = 1; i<=N; i++)   *(z+i) = 0;
    n = max(*x,*y);
    for(carry = 0, i = 1; i <= n; i++)
    {
        for(carry = 0, j = 1; j<=n; j++)
        {
            *(z+j+i) += (*(x+i)) * (*(y+j));
            carry = *(z+j+i)/10;
            *(z+j+i) %= 10;
            *(z+j+i+1) += carry;
        }
    }
    if(carry)
    {
        *(z+i+j) = carry;
        i++;
    }
    *z = i+j-1-1;
}

void putBignum(int *z)
{
    int *p;
    int n = *z;
    for(p = z+n; p>z+1; p--)
    {
        printf("%d", *p);
    }
}