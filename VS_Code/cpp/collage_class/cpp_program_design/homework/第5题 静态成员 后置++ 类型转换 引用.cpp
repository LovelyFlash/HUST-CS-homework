// 第5题 静态成员 后置++ 类型转换 引用.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

int x = 5, y = x + 30;
struct A
{
    static int x;
    int y;

public:
    operator int() { return x - y; }
    A operator++(int) { return A(x++, y++); }
    A(int x = ::x + 2, int y = ::y + 3)
    {
        A::x = x;
        A::y = y;
        cout << "construct A::x =  " << A::x << " A::y = " << A::y << endl;
    }
    int &h(int &x);
};

int &A::h(int &x)
{
    for (int y = 1; y != 1 || x < 201; x += 11, y++)
        if (x > 200)
        {
            x -= 21;
            y -= 2;
        }
    return x -= 10;
}
int A::x = 23;

void main()
{
    A a(54, 3), b(65), c;
    int i, &z = i, A::*p = &A::y;
    z = b.x;
    cout << "z=b.x ; i= " << i << endl;
    i = a.x;
    cout << "i=a.x ; i= " << i << endl;
    i = c.*p;
    cout << "i=c.*p ; i= " << i << endl;

    cout << "i=a++; begin ...." << endl;
    i = a++;
    cout << " i=a++; over " << endl;
    cout << "i=a++ ; i= " << i << endl;

    i = ::x + c.y;
    cout << "i=::x+c.y ; i= " << i << endl;
    i = a + b;
    cout << "i=a+b ; i= " << i << endl;
    b.h(i) = 7;
    cout << "b.h(i)=7; i= " << i << endl;
}
