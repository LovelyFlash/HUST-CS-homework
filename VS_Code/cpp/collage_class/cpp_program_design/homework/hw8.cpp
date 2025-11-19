#include <bits/stdc++.h>

using namespace std;
class A
{

public:
    A() { cout << "construct A" << endl; }
    ~A() { cout << "deconstruct A" << endl; }
};

void test_deconstruct()

{
    A a;
    throw("exception occur");
    cout << "test end" << endl;
}

int main()

{

    try
    {
        test_deconstruct();
        cout << "try end" << endl;
    }

    catch (const char *p)
    {
        cout << p << endl;
    }
}