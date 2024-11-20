#include<stdio.h>
void f0(int b0)
{
    if(b0) printf("the function 0 is called!\n");
}
void f1(int b1)
{
    if(b1) printf("the function 1 is called!\n");
}
void f2(int b2)
{
    if(b2) printf("the function 2 is called!\n");
}
void f3(int b3)
{
    if(b3) printf("the function 3 is called!\n");
}
void f4(int b4)
{
    if(b4) printf("the function 4 is called!\n");
}
void f5(int b5)
{
    if(b5) printf("the function 5 is called!\n");
}
void f6(int b6)
{
    if(b6) printf("the function 6 is called!\n");
}
void f7(int b7)
{
    if(b7) printf("the function 7 is called!\n");
}

int main()
{
    void (*p[8])(int) = {f0, f1, f2, f3, f4, f5, f6, f7};
    int num, b[8];
    scanf("%d", &num);
    for(int i = 0; i < 8; i++)
    {
        b[i] = num%2;
        num /= 2;
        (*p[i])(b[i]);
    }
}