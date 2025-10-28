#include <iostream>

using namespace std;

class A
{
private:
int asd=80;
public:
    virtual void f() { cout << "A::f()" << endl; }
    virtual void f(double x) { cout << "A::f(double)" << endl; }
    static void g() { cout << "A::g()" << endl; }
    A() = default;
    virtual ~A() = default;

    friend ostream& operator<<(ostream& out,const A& a){
        out<<a.asd;
        return out;
    }
};

class B : public A
{

public:
    virtual void f() { cout << "B::f()" << endl; }
    virtual void f(double x) { cout << "B::f(double)" << endl; }
    static void g() { cout << "B::g()" << endl; }
    static void g(int) { cout << "B::g(int)" << endl; }
    B() = default;
    virtual ~B() = default;
};

void test1(A &o)
{
    o.f(); // 语句1
    o.f(1.0); // 语句2
    o.g(); // 语句3
    // o.g(1);   //语句4 有错的原因
    ((B &)o).f(); // 语句5
    ((B &)o).g(1); // 语句6
    // ((B)o).g(1);   //语句7 有错的原因
}

void test2(B &o)
{
    o.f(1.0f); // 语句8
    o.f(1.0); // 语句9
    o.g(1); // 语句10
    o.g(); // 语句11
    ((A)o).g(); // 语句12
}

int main()
{
    A a;
    cout<<a;
    B b;
    test1(b);
    test2(b);
}
